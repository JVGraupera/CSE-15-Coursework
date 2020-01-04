//----------------------------------------
// Queens.c
// James Graupera 1686112 10/17/19
// My role: Wrote the whole program
// Function: Finds the solutions to the n-queens problem with a given n
// and if in verbose mode it prints all of them out
//---------------------------------------
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void placeQueen(int **B, int n, int i, int j);
void removeQueen(int **B, int n, int i, int j);
void printBoard(int **B, int n);
int findSolutions(int **B, int n, int i, char *mode);
void createBoard(int **B, int n);
int main(int argc, char *argv[]) {
  int n;
  int **B;
  char *mode;
  char ch;
  if (argc != 2 && argc != 3) {
    printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
    return EXIT_FAILURE;
  }

  if (argc == 3) {
    if (sscanf(argv[2], "%d%c", &n, &ch) == 1) {
      mode = argv[1];
    } else {
      printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
      return EXIT_FAILURE;
    }
  } else {
    if (sscanf(argv[1], "%d%c", &n, &ch) != 1) {
      printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
      return EXIT_FAILURE;
    }
    mode = "";
  }
  if(n > 15 || n < 1){
    printf("Usage: n must be 1 <= n <= 15\n");
    return EXIT_FAILURE;
  }
  B = calloc((n + 1), sizeof(int *));
  createBoard(B, n);
  printf("%d-Queens has %d solutions\n", n, findSolutions(B, n, 1, mode));
  for (int k = 0; k <= n; k++) {
   free(B[k]);
   B[k] = NULL;
  }
  free(B);
  B = NULL;
}
int findSolutions(int **B, int n, int i, char *mode) {
  int sum = 0;
  if (i > n) {
    if (strcmp(mode, "-v") == 0) {
      printBoard(B, n);
    }
    return 1;
  } else {
    for (int j = 1; j <= n; j++) {
      if (B[i][j] == 0) {
        placeQueen(B, n, i, j);
        sum += findSolutions(B, n, i + 1, mode);
        removeQueen(B, n, i, j);
      }
    }
  }
  return sum;
}
void createBoard(int **B, int n) {
  for (int k = 0; k <= n; k++) {
    B[k] = calloc((n + 1), sizeof(int));
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      B[i][j] = 0;
    }
  }
}
void placeQueen(int **B, int n, int i, int j) {
  B[i][j] = 1;
  B[i][0] = j;
  for (int k = 1; (i + k <= n) && (j + k <= n); k++) {
    B[i + k][j + k]--;
  }
  for (int k = 1; (j - k > 0) && (i + k <= n); k++) {
    B[i + k][j - k]--;
  }
  for (int k = 1; i + k <= n; k++) {
    B[i + k][j]--;
  }
}
void removeQueen(int **B, int n, int i, int j) {
  B[i][j] = 0;
  B[i][0] = 0;
  for (int k = 1; (i + k <= n) && (j + k <= n); k++) {
    B[i + k][j + k]++;
  }
  for (int k = 1; (j - k > 0) && (i + k <= n); k++) {
    B[i + k][j - k]++;
  }
  for (int k = 1; i + k <= n; k++) {
    B[i + k][j]++;
  }
}
void printBoard(int **B, int n) {
  printf("(%d", B[1][0]);
  for (int i = 2; i <= n; i++) {
    printf(", %d", B[i][0]);
  }
  printf(")\n");
}
