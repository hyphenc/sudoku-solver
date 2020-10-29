#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 9

int matrix[SIZE][SIZE] = {0};

void printhelp(int fatal) {
  printf("sudoku solver\nusage:\n ./solver [file]\n");
  fatal ? exit(1) : exit(0);
}

void pretty_print(int matrix[SIZE][SIZE]) { //ugly but works
  printf("╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n");
  for(int i=0;i<(SIZE-1);i++) {
  printf("║");
    for (int j=0;j<(SIZE-1);j++) {
      if ((j+1)%3 == 0) {
        printf(" %d ║", matrix[i][j]);
      } else {
        printf(" %d │", matrix[i][j]);
      }
    }
    printf(" %d ║\n", matrix[i][SIZE-1]);
    if ((i+1)%3 == 0) {
      printf("╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n");
    } else {
      printf("╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n");
    }
  }
  printf("║");
  for (int i=0;i<(SIZE-1);i++) {
    if ((i+1)%3 == 0) {
      printf(" %d ║", matrix[SIZE-1][i]);
    } else {
      printf(" %d │", matrix[SIZE-1][i]);
    }
  }
  printf(" %d ║\n", matrix[SIZE-1][SIZE-1]);
  printf("╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝\n");
}

int is_possible(int num, int row, int col) {
  for (int i=0;i<SIZE;i++) { //col
    if (matrix[i][col] == num) {
      return 1;
    }
  }
  
  for (int i=0;i<SIZE;i++) { //row
    if (matrix[row][i] == num) {
      return 1;
    }
  }
  // box
  int row_offset = (row/3)*3;
  int col_offset = (col/3)*3;

  for (int i=0;i<(int)sqrt(SIZE);i++) {
    for (int j=0;j<(int)sqrt(SIZE);j++) {
      if (matrix[i+row_offset][j+col_offset] == num) {
        return 1;
      }
    }
  }
  return 0;
}

void solve() {
  for(int i=0;i<SIZE;i++) { //row
    for (int j=0;j<SIZE;j++) { //col
      if (matrix[i][j] == 0) { //free
        for (int n=1;n<=SIZE;n++) { //1-9
          if (is_possible(n, i, j) == 0) {
            matrix[i][j] = n;
            solve();
            matrix[i][j] = 0;
          }
        }
        return;
      }
    }
  }
  printf("\npossible solution:\n");
  pretty_print(matrix);
}

void read_from_file(char *path){
  FILE *fp = fopen(path, "r");

  if (fp == NULL) {
    fprintf(stderr,"error: file is not readable.\n");
    printhelp(1);
  }

  int c, col, row;
  col=row=0;
  while((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      col=0;
      row+=1;
      continue;
    }
    matrix[row][col] = c - '0'; //ascii to num
    col+=1;
  }
  fclose(fp);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printhelp(0);
  }

  read_from_file(argv[1]);
  printf("input:\n");
  pretty_print(matrix);
  printf("\ntrying to solve...\n");

  solve(matrix);

  return 0;
}