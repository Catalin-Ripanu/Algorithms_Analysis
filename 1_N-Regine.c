#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 100
int cont = 0;
bool Tabla_buna(char ** tabla_sah, int row, int col, int n) {

  for (int c = 0; c < col; c++) {
    if (tabla_sah[row][c] == 'Q') {
      return false;
    }
  }
  for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--) {
    if (tabla_sah[r][c] == 'Q') {
      return false;
    }
  }

  for (int r = row + 1, c = col - 1; c >= 0 && r < n; r++, c--) {
    if (tabla_sah[r][c] == 'Q') {
      return false;
    }
  }

  return true;
}

void Afisare(char ** tabla_sah, int n, FILE * file_input) {
  int cnt = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (tabla_sah[i][j] == 'Q') {
        cnt++;
        fprintf(file_input, "(%d,%d)", i + 1, j + 1);
        if (cnt < n)
          fprintf(file_input, "\n");
      }
    }
  cont++;
}

void Plasare_regine
  (char ** tabla_sah, int col, int n, FILE * file_input) {

    if (col == n && cont == 0) {
      Afisare
        (tabla_sah, n, file_input);
    } else {

      for (int row = 0; row < n; row++) {

        tabla_sah
          [row][col] = 'Q';

        if (Tabla_buna(tabla_sah, row, col, n) == true) {
          Plasare_regine
            (tabla_sah, col + 1, n, file_input);
        }

        tabla_sah
          [row][col] = '.';
      }
    }
  }

int main() {

  char ** tabla_sah;
  int n;
  int decision;
  char* reader=(char *)malloc(M*sizeof(char));
  FILE * f_in = fopen("sah.in", "r");
  FILE * f_out = fopen("sah.out", "w");
  fgets(reader,M,f_in);
  if(strlen(reader)>1)
    n=10*(reader[0]-'0')+reader[1]-'0';
    else
    n=reader[0]-'0';
  tabla_sah
    = (char ** ) malloc(n * sizeof(char * ));
  for (int i = 0; i < n; i++)
    tabla_sah[i] = (char * ) malloc(n * sizeof(char));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      tabla_sah
        [i][j] = '.';
    }
  Plasare_regine
    (tabla_sah, 0, n, f_out);
  fseek(f_out, 0, SEEK_END);
  decision = ftell(f_out);
  if (decision == 0)
    fprintf(f_out, "Nu exista solutii");
  for (int i = 0; i < n; i++)
    free(tabla_sah[i]);
  free(tabla_sah);
  free(reader);
  fclose(f_in);
  fclose(f_out);
  return 0;
}