//-----------------------------------------------------------------------------
// IntegerQueue.c
// James Graupera
// Function: implements the functions defined in IntegerQueue.h using a linked
// list as the data structure
//-----------------------------------------------------------------------------
#include "IntegerQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Private Types and Functions ------------------------------------------------
typedef struct NodeObj {
  int Item;
  struct NodeObj *left;
  struct NodeObj *right;
} NodeObj;

typedef NodeObj *Node;

Node newNode(int x) {
  Node N = malloc(sizeof(NodeObj));
  N->Item = x;
  N->left = NULL;
  N->right = NULL;
  return (N);
}
// IntegerQueueObj
typedef struct IntegerQueueObj {
  Node head;
  Node tail;
  int numItems; // number of items in this IntegerQueue
  int strLen;
} IntegerQueueObj;

// Constructors-Destructors ---------------------------------------------------

// newIntegerQueue()
// Constructor for the IntegerQueue ADT.
IntegerQueue newIntegerQueue() {
  IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
  Q->head = NULL;
  Q->tail = NULL;
  Q->numItems = 0;
  Q->strLen = 0;
  return Q;
}

// freeIntegerQueue()
// Destructor for the Queue ADT.
void freeIntegerQueue(IntegerQueue *pQ) {
  if (pQ != NULL && *pQ != NULL) {
    dequeueAll(*pQ);
    free(*pQ);
    *pQ = NULL;
  }
}
int NumDigits(int number) {
  if (number == 0)
    return 1;
  int n = 0;
  while (number) {
    number /= 10;
    n++;
  }
  return n;
}
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}
void freeAllNodes(Node n) {
  if (n != NULL) {
    freeAllNodes(n->right);
    freeNode(&n);
  }
}

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }

  return (Q->numItems == 0);
}

int length(IntegerQueue Q) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }

  return Q->numItems;
}
// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: enqueue() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }

  Node n = newNode(x);
  if (Q->head == NULL) {
    Q->head = n;
    Q->tail = n;
  } else {
    (Q->tail)->right = n;
    n->left = Q->tail;
    Q->tail = n;
  }
  Q->strLen += NumDigits(x) + 1;
  (Q->numItems)++;
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q) {
  int x;
  Node temp;
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: dequeue() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }
  if ((Q->numItems) == 0) {
    fprintf(stderr, "IntegerQueue Error: dequeue() called on empty "
                    "IntegerQueue");
    exit(EXIT_FAILURE);
  }
  x = (Q->head)->Item;
  temp = Q->head;
  if (Q->tail == Q->head) {
    Q->head = NULL;
    Q->tail = NULL;
  } else {
    Q->head = temp->right;
    (Q->head)->left = NULL;
  }
  freeNode(&temp);
  (Q->numItems)--;
  return x;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: peek() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }
  if ((Q->numItems) == 0) {
    fprintf(stderr, "IntegerQueue Error: peek() called on empty "
                    "IntegerQueue");
    exit(EXIT_FAILURE);
  }

  return (Q->head)->Item;
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }
  
  freeAllNodes(Q->head);
  Q->tail = NULL;
  Q->head = NULL;
  Q->strLen = 0;
  Q->numItems = 0;
}

// Other Operations -----------------------------------------------------------
// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a
// char array, allocated from heap memory, containing the integer sequence
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated
// by a NUL '\n' character. It is the responsibility of the calling function to
// free this heap memory.
char *IntegerQueueToString(IntegerQueue Q) {
  if (Q == NULL) {
    fprintf(stderr, "IntegerQueue Error: IntegerQueueToString() called on NULL "
                    "IntegerQueue reference");
    exit(EXIT_FAILURE);
  }

  int i, n = Q->numItems;
  char ch[20];
  char *str = calloc(Q->strLen + 1, sizeof(char));
  Node N = Q->head;
  for (i = 0; i < n; i++) {
    sprintf(ch, "%d", N->Item);
    strcat(str, ch);
    strcat(str, " ");
    N = N->right;
  }
  return str;
}
// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0)
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R) {
  int i, eq = 0;
  if (Q == NULL || R == NULL) {
    fprintf(stderr, "IntegerQueue Error: equals() called on NULL IntegerQueue "
                    "reference");
    exit(EXIT_FAILURE);
  }

  Node N = Q->head, V = R->head;
  eq = ((Q->numItems) == (R->numItems));
  for (i = 0; eq && i < (Q->numItems - 1); i++) {
    eq = (((N->right)->Item) == ((V->right)->Item));
    N = N->right;
    V = V->right;
  }
  return eq;
}
