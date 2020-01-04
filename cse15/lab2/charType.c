//---------------------------------
// charType.c
// James Graupera 1686112 10/17/19
// My role: I wrote the whole program
//  Function: Takes an input file and reads it line by line
//  and writes to a given out file about the different char types.
//---------------------------------
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define MAX_SIZE 100
void extract_chars(char *s, char *a, char *d, char *p, char *w);
int main(int argc, char *argv[]) {
  FILE *path;
  FILE *outPath;
  char *inputName;
  char *outputName;
  char *string = calloc(MAX_SIZE + 1, sizeof(char));
  char *alphabetic;
  char *digits;
  char *punctuation;
  char *whitespace;
  int line = 1;
  if (argc != 3) {
    printf("Usage: %s input-file output-file\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    inputName = argv[1];
    outputName = argv[2];
    if ((path = fopen(inputName, "r")) == NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }
    if ((outPath = fopen(outputName, "w")) == NULL) {
      printf("Unable to read from file %s\n", argv[2]);
      exit(EXIT_FAILURE);
    }
    alphabetic = calloc(MAX_SIZE + 1, sizeof(char));
    digits = calloc(MAX_SIZE + 1, sizeof(char));
    punctuation = calloc(MAX_SIZE + 1, sizeof(char));
    whitespace = calloc(MAX_SIZE + 1, sizeof(char));
    assert(alphabetic != NULL && digits != NULL && punctuation != NULL &&
           whitespace != NULL);
    while (fgets(string, MAX_SIZE, path) != NULL) {
      fprintf(outPath, "line %d contains:\n", line);
      extract_chars(string, alphabetic, digits, punctuation, whitespace);
      if ((int)strlen(alphabetic) > 1) {
        fprintf(outPath, "%d alphabetic characters: %s\n",
                (int)strlen(alphabetic), alphabetic);
      } else {
        fprintf(outPath, "%d alphabetic character: %s\n",
                (int)strlen(alphabetic), alphabetic);
      }
      if ((int)strlen(digits) > 1) {
        fprintf(outPath, "%d numeric characters: %s\n", (int)strlen(digits),
                digits);
      } else {
        fprintf(outPath, "%d numeric character: %s\n", (int)strlen(digits),
                digits);
      }
      if ((int)strlen(punctuation) > 1) {
        fprintf(outPath, "%d punctuation characters: %s\n",
                (int)strlen(punctuation), punctuation);
      } else {
        fprintf(outPath, "%d punctuation character: %s\n",
                (int)strlen(punctuation), punctuation);
      }
      if ((int)strlen(whitespace) > 1) {
        fprintf(outPath, "%d whitespace characters: %s\n",
                (int)strlen(whitespace), whitespace);
      } else {
        fprintf(outPath, "%d whitespace character: %s\n",
                (int)strlen(whitespace), whitespace);
      }
      line++;
    }
    free(alphabetic);
    free(digits);
    free(punctuation);
    free(whitespace);
    free(string);
    alphabetic = NULL;
    digits = NULL;
    punctuation = NULL;
    whitespace = NULL;
    string = NULL;
    fclose(path);
    fclose(outPath);
    return EXIT_SUCCESS;
  }
}
void extract_chars(char *s, char *a, char *d, char *p, char *w) {
  int numA = 0;
  int numD = 0;
  int numP = 0;
  int numW = 0;
  int ch = 0;
  for (int j = 0; (s[j] != '\0' && j < MAX_SIZE); j++) {
    ch = (int)s[j];
    if (isalpha(ch)) {
      a[numA] = s[j];
      numA++;
    }
    if (isdigit(ch)) {
      d[numD] = s[j];
      numD++;
    }
    if (ispunct(ch)) {
      p[numP] = s[j];
      numP++;
    }
    if (isspace(ch)) {
      w[numW] = s[j];
      numW++;
    }
  }
  a[numA] = '\0';
  d[numD] = '\0';
  p[numP] = '\0';
  w[numW] = '\0';
}
