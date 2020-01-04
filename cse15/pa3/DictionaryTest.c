#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"
#define BREAKER_TEST_RANGE 1000
 int main(){
   Dictionary A, B;
   char* str;
   A = newDictionary();
   B = newDictionary();
   insert(A, "1b","a");
   insert(A, "2b","b");
   insert(A, "3b","c");
   //printf("%s\n", DictionaryToString(A));
   insert(A, "4b","d");
   insert(A, "5b","e");
   insert(A, "6b","f");
   insert(A, "7b","g");
   //delete(A, "8b"); 
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   printf("==========================\n");
   delete(A, "7b");
   printf("delete(A, 7b)\n");
   delete(A, "3b");
   printf("delete(A, 3b)\n");
   delete(A, "5b");
   printf("delete(A, 5b)\n");
   //makeEmpty(A);
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   printf("==========================\n");
   //str = DictionaryToString(A);
   //printf("%s\n", str);
   //free(str);
   //insert(A, "2b", "b");
   insert(B, "1b","a");
   insert(B, "2b","b");
   insert(B, "3b","c");
   insert(B, "4b","d");
   insert(B, "5b","e");
   insert(B, "6b","f");
   insert(B, "7b","g");
   insert(B, "Download", "SHOOT OUT");
   insert(B, "It's a game I made over the summer", "It's on the app store");
   insert(B, "It has 11 reviews", "SHOOOT OUT");
   insert(B, "What should I download?", "SHOOT OUT");
   str = DictionaryToString(B);
   printf("%s\n", str);
   free(str);
   //delete(B, "key that doesn't exist");
   printf("==========================\n");
   printf("lookUp(B, 1b) = %s\n", lookup(B, "1b"));
   printf("lookUp(B, 5b) = %s\n", lookup(B, "5b"));
   printf("lookUp(B, Download) = %s\n", lookup(B, "Download"));
   printf("lookUp(B, What should I downlaod?) = %s\n", lookup(B, "What should I download?"));
   //printf("%s\n", DictionaryToString(A));
   //if (strcmp(DictionaryToString(A),DictionaryToString(B))==0) printf("%s\n%s don't equal\n", DictionaryToString(A), DictionaryToString(B));
   //     	delete(B,"2");
       //	insert(B,"2", "two");
               // printf("%s\n%s", DictionaryToString(A), DictionaryToString(B));
   //if (strcmp(DictionaryToString(A),DictionaryToString(B))!=0) printf("%s\n%s don't equal\n", DictionaryToString(A), DictionaryToString(B));
   printf("==========================\n");
   printf("Size(A) = %d\n", size(A));
   makeEmpty(A);
   printf("Size(A) = %d after MakeEmpty(A)\n", size(A));
   
   
   freeDictionary(&A);
   freeDictionary(&B);
   return EXIT_SUCCESS;
}
