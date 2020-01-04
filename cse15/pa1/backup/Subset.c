//---------------------------------------------------
// James Graupera 1686112 10/7/19
// This program prints out every subset of a given
// length(int k) of a set {1,2,3,...n} of a given n.
// My role was to write the entire program.
// Subset.c
// -------------------------------------------------
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
// Returns the in a given bit array
int numOfOnes(int B[], int n) {
  int num = 0;
  for (int i = 0; i <= n; i++) {
    if (B[i] == 1) {
      num += 1;
    }
  }
  return num;
}
// Prints a set based on a given bit array
void printSet(int B[], int n) {
  int count = numOfOnes(B, n);
  printf("{");
  for (int j = 1; j <= n; j++) {
    if (B[j] == 1) {
      printf("%d", j);
      if (count > 1) {
        printf(", ");
        count--;
      }
    }
  }
  printf("}\n");
}
// Recursively finds the subsets
void printSubsets(int B[], int n, int k, int i) {
  if ((k <= (n - i + 1)) && k > 0) {
    B[i] = 1;
    printSubsets(B, n, k - 1, i + 1);
    B[i] = 0;
    printSubsets(B, n, k, i + 1);
  }
  if (k == 0) {
    printSet(B, n);
  }
  if (k > (n - i + 1)) {
    return;
  }
}
// Determines if a given string can be parsed as an int
bool isNumber(char C[]) {
  bool isInt = true;
  for (int j = 0; C[j] != '\0'; j++) {
    if (!isdigit(C[j])) {
      isInt = false;
    }
  }
  return isInt;
}
// Prints why it failed to stdout and exits the program as a failure
int fail() {
  printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");
  return EXIT_FAILURE;
}
int main(int argc, char *argv[]) {
  int n, k;
  int B[MAX_SIZE  + 1];
for (int i = 0; i <= MAX_SIZE + 1; i++) {
          B[i] = 0;
        }
  if (argc == 3) {
    if (isNumber(argv[1]) && isNumber(argv[2])) {
      n = atoi(argv[1]);
      k = atoi(argv[2]);
      if ((k >= 0) && (k <= n) && (n <= 100)) {
        if (k <= 0) {
          printf("{ }\n");
        } else {
          printSubsets(B, n, k, 1);
        }
      } else {
        fail();
      }
    } else {
      fail();
    }
  } else {
    fail();
  }
  return EXIT_SUCCESS;
}
