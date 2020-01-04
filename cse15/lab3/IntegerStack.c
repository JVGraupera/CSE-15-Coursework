//-----------------------------------------------------------------------------
// James Graupera 1686112 10/29/19
// IntegerStack.c
// My Role: I wrote the whole thing.
// Function: Implements the operations of the IntegerStack ADT
// ----------------------------------------------------------------------------
#include "IntegerStack.h"
#include <stdio.h>
#include <stdlib.h>

static const int InitialSize = 1;
typedef struct IntegerStackObj {
  int *item;        // array of IntegerStack items
  int numItems;     // number of items in this IntegerStack
  int physicalSize; // current length of underlying array
} IntegerStackObj;

void doubleItemArray(IntegerStack S) {
  int i;
  int *newArray;
  int *oldArray = S->item;
  S->physicalSize *= 2;
  newArray = calloc(S->physicalSize, sizeof(int));
  for (i = 0; i < (S->numItems); i++) {
    newArray[i] = oldArray[i];
  }
  S->item = newArray;
  free(oldArray);
}
IntegerStack newIntegerStack() {
  IntegerStack S = malloc(sizeof(IntegerStackObj));
  S->item = calloc(InitialSize, sizeof(int));
  S->numItems = 0;
  S->physicalSize = InitialSize;
  return S;
}
int arrayIndex(int stackIndex) { return stackIndex - 1; }
void freeIntegerStack(IntegerStack *pS) {
  if (pS != NULL && *pS != NULL) {
    free((*pS)->item);
    free(*pS);
    *pS = NULL;
  }
}

int isEmpty(IntegerStack S) {
  if (S == NULL) {
    fprintf(
        stderr,
        "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }

  return (S->numItems == 0);
}

// void push(IntegerStack S, int x) {
// if (S == NULL) {
// fprintf(stderr,
//"IntegerStack Error: push() called on NULL IntegerStack reference");
// exit(EXIT_FAILURE);
//}
// if ((S->numItems) == (S->physicalSize)) {
// doubleItemArray(S);
//}

// S->item[S->numItems] = x;
// S->numItems++;
//}
void push(IntegerStack S, int x) {
  if (S == NULL) {
    fprintf(stderr,
            "IntegerStack Error: push() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }
  if ((S->numItems) == (S->physicalSize)) {
    doubleItemArray(S);
  }

  S->item[S->numItems] = x;
  S->numItems++;
}
int pop(IntegerStack S) {
  if (S == NULL) {
    fprintf(stderr,
            "IntegerStack Error: pop() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(S)) {
    fprintf(stderr,
            "IntegerStack Error: pop() called on an empty IntegerStack");
    exit(EXIT_FAILURE);
  }

  int x = S->item[arrayIndex(S->numItems)];
  S->numItems--;
  return x;
}
int peek(IntegerStack S) {
  if (S == NULL) {
    fprintf(stderr,
            "IntegerStack Error: peek() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(S)) {
    fprintf(stderr,
            "IntegerStack Error: peek() called on an empty IntegerStack");
    exit(EXIT_FAILURE);
  }

  return S->item[arrayIndex(S->numItems)];
}
void popAll(IntegerStack S) {
  if (S == NULL) {
    fprintf(stderr,
            "IntegerStack Error: peek() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }

  S->numItems = 0;
}
void printIntegerStack(FILE *out, IntegerStack S) {
  int i;
  if (S == NULL) {
    fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL "
                    "IntegerStack reference");
    exit(EXIT_FAILURE);
  }

  for (i = arrayIndex(S->numItems); i >= 0; i--) {
    fprintf(out, "%d ", S->item[i]);
  }
  fprintf(out, "\n");
}
int equals(IntegerStack S, IntegerStack T) {
  int i, eq;
  if (S == NULL || T == NULL) {
    fprintf(
        stderr,
        "IntegerStack Error: equals() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
  }

  eq = ((S->numItems) == (T->numItems));
  for (i = 1; eq && i <= (S->numItems); i++) {
    eq = ((S->item[arrayIndex(i)]) == (T->item[arrayIndex(i)]));
  }
  return eq;
}
