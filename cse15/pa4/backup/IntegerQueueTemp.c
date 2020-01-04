#include<stdlib.h>
#include<stdio.h>
#include"IntegerQueue.h"
#include<string.h>
// Private Types and Functions ------------------------------------------------

// InitialSize
static const int InitialSize = 1;

// IntegerQueueObj
typedef struct IntegerQueueObj{
   int* item;         // array of IntegerQueue items
   int physicalSize;  // current length of underlying array
   int numItems;      // number of items in this IntegerQueue
   int front;         // index of front element
   int back;          // index of back element
   int strLen;
} IntegerQueueObj;

// doubleItemArray
// Doubles the physical size of the underlying array Q->item.
void doubleItemArray(IntegerQueue Q){
   int i, n = Q->numItems, m = Q->physicalSize;
   int* newArray;
   int* oldArray = Q->item;
   newArray = calloc(2*m, sizeof(int));
   for( i=0; i<n; i++){
      newArray[i] = oldArray[((Q->front)+i)%m];
   }
   Q->item = newArray;
   Q->physicalSize = 2*m;
   Q->front = 0;
   Q->back = n-1;
   free(oldArray);
}


// Constructors-Destructors ---------------------------------------------------

// newIntegerQueue()
// Constructor for the IntegerQueue ADT.
IntegerQueue newIntegerQueue(){
   IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
   Q->item = calloc(InitialSize, sizeof(int));
   Q->physicalSize = InitialSize;
   Q->numItems = 0;
   Q->front = 0;
   Q->back = -1;
   Q->strLen = 0;
   return Q;
}

// freeIntegerQueue()
// Destructor for the Queue ADT.
void freeIntegerQueue(IntegerQueue* pQ){
   if( pQ!=NULL && *pQ!=NULL ){
      free((*pQ)->item);
      free(*pQ);
      *pQ = NULL;
   }
}
int NumDigits(int number)
{
    if (number == 0) return 1;
    int n = 0;
    while(number) {
        number /= 10;
        n++;
    }
    return n;
}

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }

   return (Q->numItems == 0);
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: enqueue() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }

   if( (Q->numItems)==(Q->physicalSize) ){
      doubleItemArray(Q);
   }
   Q->strLen += NumDigits(x) + 1;
   Q->back = ((Q->back)+1)%(Q->physicalSize);
   Q->item[Q->back] = x;
   (Q->numItems)++;
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q){
   int x;
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: dequeue() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   if( (Q->numItems)==0 ){
      fprintf(stderr, "IntegerQueue Error: dequeue() called on empty "\
                      "IntegerQueue");
      exit(EXIT_FAILURE);
   }   

   x = Q->item[Q->front];
   Q->strLen -= NumDigits(x) + 1;
   Q->front = ((Q->front)+1)%(Q->physicalSize);
   (Q->numItems)--;
   return x;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: peek() called on NULL "\
                     "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   if( (Q->numItems)==0 ){
      fprintf(stderr, "IntegerQueue Error: peek() called on empty "\
                      "IntegerQueue");
      exit(EXIT_FAILURE);
   }

   return Q->item[Q->front];
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   Q->strLen = 0;
   Q->numItems = 0;
   Q->front = 0;
   Q->back = -1;
}


// Other Operations -----------------------------------------------------------
// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a
// char array, allocated from heap memory, containing the integer sequence
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated
// by a NUL '\n' character. It is the responsibility of the calling function to
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q){
    if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: IntegerQueueToString() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
    }
    int i, n = Q->numItems, m = Q->physicalSize;
    char ch[20];
    char* str = calloc(Q->strLen + 1, sizeof(char));
    //printf("%d\n", Q->strLen);
    for(i = 0; i < n; i++){
         sprintf(ch, "%d", Q->item[((Q->front)+i)%m]);
         strcat(str, ch);
         strcat(str, " ");
    }
    //strcat(str, ch);
    //strcat(str, '\0');
    return str;
}
// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R){
   int i, n, m, eq=0;
   if( Q==NULL || R==NULL ){
      fprintf(stderr, "IntegerQueue Error: equals() called on NULL IntegerQueue "\
                      "reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (Q->numItems)==(R->numItems) );
   for(i=0; eq && i<(Q->numItems); i++){
      n = ((Q->front)+i)%(Q->physicalSize);
      m = ((R->front)+i)%(R->physicalSize);
      eq = ( (Q->item[n])==(R->item[m]) );
   }
   return eq;
}

