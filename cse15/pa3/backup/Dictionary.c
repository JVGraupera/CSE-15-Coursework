//-----------------------------------------------------------------------------
// James Graupera 1686112 11/5
// pa3: Dictionary ADT
// Function: This file implements all the operations of the dictionary ADT
// defined in Dictionary.h, along with some private functions. My Role: I wrote
// it
// ----------------------------------------------------------------------------
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private Types and Functions ------------------------------------------------
// NodeObj
typedef struct NodeObj {
  char *key;
  char *value;
  struct NodeObj *left;
  struct NodeObj *right;
} NodeObj;

// Node
typedef NodeObj *Node;

// newNode()
// Constructor for Node type.
Node newNode(char *k, char *v) {
  Node N = malloc(sizeof(NodeObj));
  N->key = k;
  N->value = v;
  N->right = NULL;
  return (N);
}

// freeNode()
// Destructor for Node type
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}
typedef struct DictionaryObj {
  Node root;
  int numPairs;
} DictionaryObj;

Dictionary newDictionary() {
  Dictionary D = malloc(sizeof(DictionaryObj));
  D->root = NULL;
  D->numPairs = 0;
  return D;
}

void freeDictionary(Dictionary *pD) {
  if (pD != NULL && *pD != NULL) {
    makeEmpty(*pD);
    free(*pD);
    *pD = NULL;
  }
}
// Private helper functions
//-----------------------------------------------------------------------------
int countChars(Dictionary D) {
  int count = 0;
  Node n = D->root;
  while (n != NULL) {
    count += (strlen(n->key) + strlen(n->value) + 2);
    n = n->right;
  }
  return count;
}
Node findKey(Dictionary D, char *k) {
  Node N = D->root;
  Node node = NULL;
  while (N != NULL) {
    if (strcmp(k, N->key) == 0) {
      node = N;
    }
    N = N->right;
  }
  return node;
}

Node find(Dictionary D, int index) {
  Node N = D->root;
  int i;
  for (i = 0; i < index; i++) {
    N = N->right;
  }
  return N;
}
int getIndex(Dictionary D, Node n) {
  Node x = D->root;
  int index = 0;
  while (x != n) {
    index++;
    x = x->right;
  }
  return index;
}
Node getLeft(Dictionary D, Node n) {
  int index = getIndex(D, n);
  if (index == 0) {
    return NULL;
  }
  return find(D, index - 1);
}
void freeAllNodes(Node n) {
  if (n != NULL) {
    freeAllNodes(n->right);
    freeNode(&n);
  }
}
//-----------------------------------------------------------------------------

// Public dictionary operations
//-----------------------------------------------------------------------------
char *lookup(Dictionary D, char *k) {
  char *v = NULL;
  Node n = findKey(D, k);
  if (n != NULL) {
    v = n->value;
  }
  return v;
}

void delete (Dictionary D, char *k) {
  if (D == NULL) {
    fprintf(
        stderr,
        "Dictionary Error: calling delete() on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
  Node n = findKey(D, k);
  if (n == NULL) {
    fprintf(stderr,
            "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
    exit(EXIT_FAILURE);
  }

  Node R = n->right, L = getLeft(D, n);
  if (R == NULL && L != NULL) {
    L->right = NULL;
  } else if (R == NULL && L == NULL) {
    D->root = NULL;
  } else if ((R != NULL) && (L != NULL)) {
    L->right = R;
  } else if (L == NULL && R != NULL) {
    D->root = n->right;
  }
  D->numPairs--;
  freeNode(&n);
}

void makeEmpty(Dictionary D) {
  if (D == NULL) {
    fprintf(
        stderr,
        "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }

  freeAllNodes(D->root);
  D->numPairs = 0;
  D->root = NULL;
}

int size(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr,
            "Dictionary Error: calling size() on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }

  return D->numPairs;
}
void insert(Dictionary D, char *k, char *v) {
  if (D == NULL) {
    fprintf(
        stderr,
        "Dictionary Error: calling insert() on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
  if (lookup(D, k) != NULL) {
    fprintf(stderr, "Dictionary Error: calling insert() with a key that "
                    "already exists in the dictionary\n");
    exit(EXIT_FAILURE);
  }

  Node N = D->root;
  Node B = newNode(k, v);
  if (N == NULL) {
    D->root = B;
  } else {
    while (N->right != NULL) {
      N = N->right;
    }
    N->right = B;
  }
  D->numPairs++;
}

char *DictionaryToString(Dictionary D) {
  char *B;
  int Blen = countChars(D);
  Node N = D->root;
  if (D == NULL) {
    fprintf(stderr, "Dictionary Error: calling DictionaryToString() on NULL "
                    "Dictionary reference\n");
    exit(EXIT_FAILURE);
  }

  B = calloc(Blen + 1, sizeof(char));
  N = D->root;
  while (N != NULL) {
    strcat(B, N->key);
    strcat(B, " ");
    strcat(B, N->value);
    strcat(B, "\n");
    N = N->right;
  }
  //B[Blen] = '\0';
  strcat(B, "\0");
  return B;
}
//-----------------------------------------------------------------------------
