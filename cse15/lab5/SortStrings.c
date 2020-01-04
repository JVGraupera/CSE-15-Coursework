//-----------------------------------------------------------------------------
// James Graupoera 1686112
// lab5
// SortStrings.c
// my role: I wrote the whole thing based off sort.c in examples
//-----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(FILE *out, char **A, int n) {
  int i;
  for (i = 0; i < n; i++) {
    fprintf(out, "%s\n", A[i]);
  }
}

void swap(char **A, int i, int j) {
  char *temp;
  temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int Partition(char **A, int p, int r) {
  int i, j;
  char *x;
  x = A[r];
  i = p - 1;
  for (j = p; j < r; j++) {
    if (strcmp(A[j], x) <= 0) {
      i++;
      swap(A, i, j);
    }
  }
  swap(A, i + 1, r);
  return (i + 1);
}

void QuickSort(char **A, int p, int r) {
  int q;
  if (p < r) {
    q = Partition(A, p, r);
    QuickSort(A, p, q - 1);
    QuickSort(A, q + 1, r);
  }
}

int main(int argc, char **argv) {
  int n, i;
  char **A;
  FILE *in;
  FILE *out;
  if (argc != 3) {
    fprintf(stderr, "Usage: InputFile OutputFile\n");
    exit(EXIT_SUCCESS);
  }
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if (in == NULL) {
    fprintf(stderr, "Usage: file %s could not be read\n", argv[1]);
  }
  fscanf(in, "%d", &n);
  A = calloc(n, sizeof(char *));
  for (i = 0; i < n; i++) {
    A[i] = calloc(200, sizeof(char));
  }
  for (i = 0; i < n; i++) {
    fscanf(in, "%s", A[i]);
  }
  QuickSort(A, 0, n - 1);
  printArray(out, A, n);
  for (i = 0; i < n; i++) {
    free(A[i]);
  }
  free(A);
  fclose(in);
  fclose(out);
  return EXIT_SUCCESS;
}
