#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define NUM 8
#define NUM1 5
int out[NUM1-1];
int cont=0;
int verif=0;
int iter=0;
int c_K;
int fact(int n)
{
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}
int choose(int n, int r)
{
    return fact(n) / (fact(r) * fact(n - r));
}

void Combinari_aux(int vector[], int n, int r, int index,
                     int data[], int i,int** mat_data)
{
    if (index == r) {
        for (int j = 0; j < r; j++)
           mat_data[cont][j]=data[j];
	     cont++;
        return;
    }
 
    if (i >= n)
        return;

    data[index] = vector[i];
    Combinari_aux(vector, n, r, index + 1, data, i + 1,mat_data);

    Combinari_aux(vector, n, r, index, data, i + 1,mat_data);
}
 
void Combinari(int n, int r,int** mat_data)
{

    int data[r];
    int vector[n];
	for(int i=0;i<n;i++)
	vector[i]=i+1;
    Combinari_aux(vector, n, r, 0, data, 0,mat_data);
}
// Verifica daca cele 2 grafuri sunt izomorfe cu ajutorul matricelor de adiacenta.
void testIsomorphism(int*** Vector,int*** Data,int* Vertex,int* Edges,int K,FILE* file_out,int K2,int z,int y)
{  for(;z<choose(Vertex[iter],K2);z++)
   {   if(verif==1)
      {
	   y=0;
	   verif=0;
	  }
	   printf("%d\n",z);
	for(;y<choose(Vertex[iter+1],K2);y++)
	  {  printf("%d\n",y);
      for(int i=0;i<K2;i++)
	    for(int j=0;j<K2;j++)
	  {
		  
                 if(Vector[iter][Data[iter][z][i]-1][Data[iter][z][j]-1]==0 && 
				               Vector[iter+1][Data[iter+1][y][i]-1][Data[iter+1][y][j]-1]==1)
							{
								//printf("DA");
								verif=1;
                            goto exit;
							}
                 if(Vector[iter][Data[iter][z][i]-1][Data[iter][z][j]-1]==1 && 
				                Vector[iter+1][Data[iter+1][y][i]-1][Data[iter+1][y][j]-1]==0)
								{  //printf("NU");
									verif=1;
								goto exit;
								}

	      }
		  exit:
		  if(verif==0)
		  {
			
			  out[cont]=z;
              cont++;
			  out[cont]=y;
			  cont++;
			  if(iter==K-2)
			  { 
                    int u=0;
				   for(int k=0;k<K;k++)
	              {
	             for(int p=0;p<K2;p++)
	             fprintf(file_out,"%d ",Data[k][out[u]][p]);
	             fprintf(file_out,"\n");
	               u++;
				   
			      }
		      }
			  else
			     {
					 iter++;
					 z=0;
			         testIsomorphism(Vector,Data,Vertex,Edges,K,file_out,K2,z,y);
					 fprintf(file_out,"-1");
				 }
		  }
	  }
   }
}

void sort(int grad_nod[MAX], int *vertex)
{
	int i=0, j, temp=0;
	for(;i<(*vertex);i++)
	{
		j=0;
		for(;j<(*vertex)-i-1;j++)
		{
			if(grad_nod[j]>grad_nod[j+1])
			{
				temp= grad_nod[j];
				grad_nod[j]= grad_nod[j+1];
				grad_nod[j+1]= temp;
			}
		}
	}
	return;
}

int checkdegree(int** A, int *vertex, int* grad_nod)
{
	int i=0, j, degreeA, k=0;	
	for(;i<(*vertex);i++, k++)
	{
		j=0, degreeA=0;
		for(;j<(*vertex);j++)	
		{
			if(A[i][j] == 1)	
				degreeA++;
		}
		grad_nod[k]= degreeA;
	}
	degreeA=0;
	for(k=0;k<(*vertex);k++)
	{
		degreeA= (degreeA + grad_nod[k]); 
	}
	return(degreeA);
}

int isomorphic(int* grad_nod, int* degB, int *vertex)
{
	int decizie=0, i=0, j=0;
	for(;i<(*vertex);i++, j++)
	{
		if(grad_nod[i] != degB[j])
		{
			decizie= 1;
			break;
		}
	}
	return(decizie);
}

int main()
{   
	int*** Vector;
	int*** Data;
	int deg[NUM];
	int dimension;
	int Vertex[NUM1],Edges[NUM1];
    FILE* f=fopen("graf.in","r");
	FILE* f1=fopen("graf.out","w");
	char *reader;
	reader=(char *)malloc(MAX*sizeof(char));
	int K,K2,V,E;
	fgets(reader,MAX,f);
	K=reader[0]-'0';
	c_K=K;
	fgets(reader,MAX,f);
	K2=reader[0]-'0';
	Vector=(int ***)malloc(K*sizeof(int**));
	Data=(int ***)malloc(K*sizeof(int**));
	for(int i=0;i<K;i++)
	{
	  Vector[i]=(int **)malloc(NUM*sizeof(int*));
	  for(int j=0;j<NUM;j++)
      Vector[i][j]=(int *)malloc(NUM*sizeof(int));
	}
	for(int i=0;i<K;i++)
	   for(int j=0;j<NUM;j++)
	     for(int k=0;k<NUM;k++)
		  Vector[i][j][k]=0;
	int cnt=0,cnt1=0;
	int cnt3=0;
    while(fgets(reader,MAX,f)!=NULL)
	{
		if(cnt==Edges[cnt3]+1)
		 {
			cnt1++;
			cnt=0;
		    cnt3++;
		 }
	  if(reader[1]==' ')
	  { 
		  Vertex[cnt3]=reader[0]-'0';
		  Edges[cnt3]=reader[2]-'0';
	  }
	  if(reader[2]==',')
	  {
       Vector[cnt1][reader[1]-1-'0'][reader[3]-1-'0']=1;
	   Vector[cnt1][reader[3]-1-'0'][reader[1]-1-'0']=1;
	  }
	    cnt++;
	}
    for(int i=0;i<K;i++)
	{
	  Data[i]=(int **)malloc(choose(Vertex[i],K2)*sizeof(int*));
	  for(int j=0;j<choose(Vertex[i],K2);j++)
      Data[i][j]=(int *)malloc(K2*sizeof(int));
	}
     for(int j=0;j<K;j++)
	 {
      Combinari(Vertex[j],K2,Data[j]);
	  cont=0;
	 }
	 testIsomorphism(Vector,Data,Vertex,Edges,K,f1,K2,0,0);
	 printf("Combinations\n");
	  for(int k=0;k<K;k++)
	  {
     for(int i=0;i<choose(Vertex[k],K2);i++)
	 {
	   for(int j=0;j<K2;j++)
	   printf("%d ",Data[k][i][j]);
	  printf("\n");
	 }
        printf("Another Matrix\n");
	  }
	 printf("==========\n");
	printf("Vertex from input:\n");
    for(int i=0;i<K;i++)
	printf("%d ",Vertex[i]);
	printf("\n");
	printf("Edges:\n");
	for(int i=0;i<K;i++)
	 printf("%d ",Edges[i]);
	 printf("\n");
	 printf("Adjacency Matrix:\n");
	 for(int i=0;i<K;i++)
	 {
           for(int j=0;j<Vertex[i];j++)
		     {
				 for(int k=0;k<Vertex[i];k++)
				  printf("%d ",Vector[i][j][k]);
				  printf("\n");
			 }
		printf("Another Adjacency Matrix:\n");
	 }

   for(int i=0;i<K;i++)
	{
	  for(int j=0;j<NUM;j++)
      free(Vector[i][j]);
	  free(Vector[i]);
	}
    free(Vector);
	for(int i=0;i<K;i++)
	{
	  for(int j=0;j<choose(Vertex[i],K2);j++)
      free(Data[i][j]);
	  free(Data[i]);
	}
	free(Data);
	free(reader);
	fclose(f);
	fclose(f1);
	 return 0;
}

