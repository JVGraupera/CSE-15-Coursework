#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"


int main(){
   //int i;
   Dictionary A;
   char* str;
   //char* v;
   //char* k = calloc(100, sizeof(char));
   
   A = newDictionary();
   insert(A, "bb", "bb");
   insert(A, "aa", "aa");
   insert(A, "df", "df");
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   makeEmpty(A);
   insert(A, "1", "A");
   insert(A, "2", "B");
   insert(A, "3", "C");
   printf("lookup(3) = %s\n", lookup(A, "3"));
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   printf("A size = %d\n", size(A));
   delete(A, "1");
   delete(A, "3");
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   insert(A, "download", "shoot out");
   insert(A, "James", "Games");
   insert(A, "games", "james");
   insert(A, "Meme", "me");
   printf("lookup(James) = %s\n", lookup(A, "James"));
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   makeEmpty(A);
   printf("A size = %d\n", size(A));
   freeDictionary(&A);
   return EXIT_SUCCESS;
}
