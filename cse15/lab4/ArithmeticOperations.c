//-----------------------------------------------------------------------------
// James Graupera 1686112
// My role: I wrote the whole program
// ArithmeticOperations.c
//-----------------------------------------------------------------------------

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef int (*fptr_t)(int, int);

int sum(int x, int y) { return x + y; }

int sub(int x, int y) { return x - y; }

int prod(int x, int y) { return x * y; }

int diff(int x, int y) { return x - y; }

int quot(int x, int y) { return x / y; }

int rem(int x, int y) { return x % y; }

int apply(fptr_t fp, int x, int y) { return fp(x, y); }

int compute(fptr_t fcn[5], int *A, int *idx, int n) {
  if (n > 1) {
    return apply(fcn[idx[n - 1]], compute(fcn, A, idx, n - 1), A[n]);
  }
  return apply(fcn[idx[0]], A[0], A[1]);
}

int main(int argc, char *argv[]) {
  FILE *file;
  char *fileName;
  int *A;
  int *idx;
  int n;
  int num;
  if (argc != 2) {
    printf("Usage: %s input-file\n", argv[0]);
    return EXIT_FAILURE;
  }
  fileName = argv[1];
  if ((file = fopen(fileName, "r")) == NULL) {
    printf("Unable to read from file %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%d", &n);
  idx = calloc(n, sizeof(int));
  A = calloc(n + 1, sizeof(int));
  for (int i = 0; i < n; i++) {
    fscanf(file, "%d", &num);
    idx[i] = num;
  }
  for (int i = 0; i <= n; i++) {
    fscanf(file, "%d", &num);
    A[i] = num;
  }
  fptr_t fcn[] = {sum, diff, prod, quot, rem};
  printf("%d\n", compute(fcn, A, idx, n));
  free(idx);
  free(A);
  idx = NULL;
  A = NULL;
  fclose(file);
  return EXIT_SUCCESS;
}
