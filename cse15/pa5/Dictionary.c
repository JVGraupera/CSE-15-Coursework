//-----------------------------------------------------------------------------
//James Graupera 1686112
//Dictionary.c
//function: Implements the methods prototyped in Dictionary.h based off a hash table
//My Role: I wrote every function except for hash and it's helper functions those were given
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int tableSize = 101; // or some prime other than 101

typedef struct NodeObj {
  char *key;
  char *value;
  struct NodeObj *next;
} NodeObj;

typedef struct NodeObj *Node;

typedef struct DictionaryObj {
  Node *table;
  int numItems;
  int strLen;
} DictionaryObj;

Dictionary newDictionary() {
  Dictionary D = malloc(sizeof(DictionaryObj));
  Node *T = calloc(tableSize, sizeof(Node));
  D->table = T;
  D->strLen = 0;
  D->numItems = 0;
  return D;
}

void freeDictionary(Dictionary *pD) {
  if (pD != NULL && *pD != NULL) {
    makeEmpty(*pD);
    free((*pD)->table);
    free(*pD);
    pD = NULL;
  }
}

void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    pN = NULL;
  }
}

void freeAllNodes(Node N) {
  if (N != NULL) {
    freeAllNodes(N->next);
    freeNode(&N);
  }
}

Node newNode(char *k, char *v) {
  Node N = malloc(sizeof(NodeObj));
  N->value = v;
  N->key = k;
  N->next = NULL;
  return N;
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
  int sizeInBits = 8 * sizeof(unsigned int);
  shift = shift & (sizeInBits - 1);
  if (shift == 0)
    return value;
  return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char *input) {
  unsigned int result = 0xBAE86554;
  while (*input) {
    result ^= *input++;
    result = rotate_left(result, 5);
  }
  return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char *key) { return pre_hash(key) % tableSize; }

int size(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr, "Usage: calling size() on a NULL Dictionary\n");
    exit(EXIT_FAILURE);
  }

  return D->numItems;
}

char *lookup(Dictionary D, char *key) {
  if (D == NULL) {
    fprintf(stderr, "Usage: calling lookup() on a NULL Dictionary\n");
    exit(EXIT_FAILURE);
  }
  Node N = (D->table)[hash(key)];
  while (N != NULL) {
    if (strcmp(key, N->key) == 0) {
      return N->value;
    }
    N = N->next;
  }
  return NULL;
}

void insert(Dictionary D, char *k, char *v) {
  if (lookup(D, k) != NULL) {
    fprintf(stderr, "Usage: calling insert with a key that already exists in "
                    "the dictionary\n");
    exit(EXIT_FAILURE);
  }
  D->strLen += (strlen(k) + strlen(v) + 2);
  Node I = newNode(k, v);
  Node N = (D->table)[hash(k)];
  if (N == NULL) {
    (D->table)[hash(k)] = I;
  } else {
    I->next = N;
  }
  (D->table)[hash(k)] = I;
  D->numItems++;
}

void delete (Dictionary D, char *k) {
  if (lookup(D, k) == NULL) {
    fprintf(stderr, "Usage: calling delete with a key that doesn't exist in "
                    "the dictionary\n");
    exit(EXIT_FAILURE);
  }

  Node N = (D->table)[hash(k)];
  Node left = NULL;
  while (N != NULL && strcmp(k, N->key) != 0) {
    left = N;
    N = N->next;
  }
  Node right = N->next;

  if (left == NULL && right == NULL) {
    (D->table)[hash(k)] = NULL;
  } else if (left == NULL && right != NULL) {
    (D->table)[hash(k)] = right;
  } else if (left != NULL && right == NULL) {
    left->next = NULL;
  } else if (left != NULL && right != NULL) {
    left->next = right;
  }
  D->strLen -= (strlen(k) + strlen(N->value) + 2);
  freeNode(&N);
  D->numItems--;
}

void makeEmpty(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr, "Usage: calling makeEmpty() on a NULL Dictionary\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < tableSize; i++) {
    freeAllNodes((D->table)[i]);
    (D->table)[i] = NULL;
  }
  D->numItems = 0;
  D->strLen = 0;
}
char *DictionaryToString(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr,
            "Usage: calling DictionaryToString() on a NULL Dictionary\n");
    exit(EXIT_FAILURE);
  }

  Node N = NULL;
  char *B = calloc(D->strLen + 1, sizeof(char));
  for (int i = 0; i < tableSize; i++) {
    N = (D->table)[i];
    while (N != NULL) {
      strcat(B, N->key);
      strcat(B, " ");
      strcat(B, N->value);
      strcat(B, "\n");
      N = N->next;
    }
  }
  strcat(B, "\0");
  return B;
}
