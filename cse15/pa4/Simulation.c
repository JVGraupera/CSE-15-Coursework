//-----------------------------------------------------------------------------
// Simulation.c
// James Graupera 1686112
// My role: I wrote every method except getJob() it was given in the examples
// Funciton: Simulates a set of jobs preformed by a set of processors
// and prints relevant information to the a report file and a trace to a trace
// file.
//-----------------------------------------------------------------------------
#include "IntegerQueue.h"
#include "Job.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE *in) {
  int a, d;
  fscanf(in, "%d %d\n", &a, &d);
  return newJob(a, d);
}

IntegerQueue findShortest(IntegerQueue *A, int num) {
  IntegerQueue shor = A[1];
  int i;
  for (i = 1; i <= num; i++) {
    if (length(A[i]) < length(shor)) {
      shor = A[i];
    }
  }
  return shor;
}

// printProcessors()
// Prints a job represntation of the proccessors in use
void printProcessors(IntegerQueue *A, Job *jobs, FILE *out, int numProcessors) {
  int c, bLen, k;
  IntegerQueue B;
  for (k = 0; k <= numProcessors; k++) {
    fprintf(out, "%d:", k);
    B = A[k];
    bLen = length(B);
    for (int i = 0; i < bLen; i++) {
      c = dequeue(B);
      enqueue(B, c);
      printJob(out, jobs[c]);
    }
    fprintf(out, "\n");
  }
}

// getNextArrival()
// Gets the time of next arrival
int getNextArrival(IntegerQueue A, Job *jobs) {
  int i;
  if (!isEmpty(A)) {
    i = peek(A);
    if (getFinish(jobs[i]) == UNDEF) {
      return getArrival(jobs[i]);
    }
  }
  return UNDEF;
}

// getNextFinish()
// Gets the time of next finish
int getNextFinish(IntegerQueue *A, Job *jobs, int numProc) {
  int i, next = 0, currentTime;
  Job currentJob;
  IntegerQueue currentQ;
  for (i = 1; i <= numProc; i++) {
    currentQ = A[i];
    if (!isEmpty(currentQ)) {
      currentJob = jobs[peek(currentQ)];
      if (next == 0) {
        next = getFinish(currentJob);
      } else {
        currentTime = getFinish(currentJob);
        if (currentTime < next) {
          next = currentTime;
        }
      }
    }
  }
  return next;
}

// getTotalWait()
// Calculates the total wait time of an array(size m) of finished jobs
int getTotalWait(Job *jobs, int m) {
  int i, wait = 0;
  for (i = 0; i < m; i++) {
    wait += getWaitTime(jobs[i]);
  }
  return wait;
}

// getMaxWait()
// Gets the longest wait from an array(size m) of a finished jobs
int getMaxWait(Job *jobs, int m) {
  int i, maxWait = 0, currentWait = 0;
  for (i = 0; i < m; i++) {
    currentWait = getWaitTime(jobs[i]);
    if (currentWait > maxWait) {
      maxWait = currentWait;
    }
  }
  return maxWait;
}

// Arrive()
// Puts the jobs that are arriving in the proper queue
void Arrive(IntegerQueue *processors, int numProc, Job *backUp, int time) {
  int p, currentQLen, currentJobIdx;
  IntegerQueue currentQ = processors[0];
  Job currentJob;
  currentQLen = length(currentQ);
  for (p = 0; p < currentQLen; p++) {
    if (!isEmpty(currentQ)) {
      currentJobIdx = peek(currentQ);
      currentJob = backUp[currentJobIdx];
      if (getArrival(currentJob) == time) {
        dequeue(currentQ);
        enqueue(findShortest(processors, numProc), currentJobIdx);
      }
    }
  }
}

// setFinishes
// Sets the finish time of the jobs that have finished at the given time
void setFinishes(IntegerQueue *processors, int numProc, Job *backUp, int time) {
  int p;
  Job currentJob;
  IntegerQueue currentQ;
  for (p = 1; p <= numProc; p++) {
    currentQ = processors[p];
    if (!isEmpty(currentQ)) {
      currentJob = backUp[peek(currentQ)];
      if (getFinish(currentJob) == UNDEF) {
        computeFinishTime(currentJob, time);
      }
    }
  }
}

// Finish()
// Moves the finished jobs into the 0th processor
int Finish(IntegerQueue *processors, int numProc, Job *backUp, int time) {
  int p, finishes = 0;
  Job currentJob;
  IntegerQueue currentQ;
  for (p = 1; p <= numProc; p++) {
    currentQ = processors[p];
    if (!isEmpty(currentQ)) {
      currentJob = backUp[peek(currentQ)];
      if (getFinish(currentJob) == time) {
        enqueue(processors[0], peek(currentQ));
        dequeue(currentQ);

        finishes++;
      }
    }
  }
  return finishes;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: file path required\n");
    exit(EXIT_FAILURE);
  }
  char *fileName = argv[1];
  char *reportName = calloc(strlen(fileName) + 5, sizeof(char));
  char *traceName = calloc(strlen(fileName) + 5, sizeof(char));
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    fprintf(stderr, "Usage: unable read file: %s", fileName);
    exit(EXIT_FAILURE);
  }
  FILE *report;
  FILE *trace;
  Job *backUp;
  int m, i, p, j, done = 0, time = 0, nextEvent = 0, nextFinish = 0,
                  nextArrival = 0, totalWait, maxWait;
  double avgWait;
  IntegerQueue *processors;
  IntegerQueue storage = newIntegerQueue();
  strcpy(reportName, fileName);
  strcpy(traceName, fileName);
  strcat(reportName, ".rpt");
  strcat(traceName, ".trc");
  report = fopen(reportName, "w");
  trace = fopen(traceName, "w");
  fscanf(file, "%d", &m);
  backUp = calloc(m, sizeof(Job));
  processors = calloc(m, sizeof(IntegerQueue));
  processors[0] = storage;
  for (i = 0; i < m; i++) {
    backUp[i] = getJob(file);
  }
  for (i = 1; i < m; i++) {
    processors[i] = newIntegerQueue();
  }
  for (j = 0; j < m; j++) {
    enqueue(storage, j);
  }
  fprintf(report, "Report file: %s\n%d Jobs:\n", reportName, m);
  for (j = 0; j < m; j++) {
    printJob(report, backUp[j]);
  }
  fprintf(report, "\n");
  fprintf(trace, "Trace file: %s\n%d Jobs:\n", traceName, m);
  for (j = 0; j < m; j++) {
    printJob(trace, backUp[j]);
  }
  fprintf(report,
          "***********************************************************\n");
  fprintf(trace, "\n");
  for (i = 1; i < m; i++) {
    if (i > 1) {
      fprintf(trace,
              "*****************************\n%d "
              "processors:\n*****************************\n",
              i);
    } else {
      fprintf(trace,
              "*****************************\n%d "
              "processor:\n*****************************\n",
              i);
    }
    while (done < m) {
      if (nextFinish == time) {
        done += Finish(processors, i, backUp, time);
        setFinishes(processors, i, backUp, time);
      }
      if (nextArrival == time) {
        Arrive(processors, i, backUp, time);
        setFinishes(processors, i, backUp, time);
      }
      if (nextEvent == time) {
        fprintf(trace, "time=%d\n", time);
        printProcessors(processors, backUp, trace, i);
        nextEvent = 0;
      }
      // finds next event
      if (nextEvent == 0) {
        nextFinish = getNextFinish(processors, backUp, i);
        nextArrival = getNextArrival(processors[0], backUp);
        if (nextArrival < nextFinish && nextArrival != UNDEF) {
          nextEvent = nextArrival;
        } else if (nextFinish != UNDEF) {
          if (nextFinish != 0) {
            nextEvent = nextFinish;
          } else {
            nextEvent = nextArrival;
          }
        }
      }
      time = nextEvent;
    }
    totalWait = getTotalWait(backUp, m);
    maxWait = getMaxWait(backUp, m);
    avgWait = (double)totalWait / (double)m;
    if (i == 1) {
      fprintf(report,
              "%d processor: totalWait=%d, maxWait=%d, averageWait=%.2f\n", i,
              totalWait, maxWait, avgWait);
    } else {
      fprintf(report,
              "%d processors: totalWait=%d, maxWait=%d, averageWait=%.2f\n", i,
              totalWait, maxWait, avgWait);
    }
    done = 0;
    time = 0;
    nextEvent = 0;
    for (p = 0; p < m; p++) {
      resetFinishTime(backUp[p]);
    }
    dequeueAll(processors[0]);
    for (p = 0; p < m; p++) {
      enqueue(processors[0], p);
    }
  }
  for (i = 0; i < m; i++) {
    freeIntegerQueue(&processors[i]);
    freeJob(&backUp[i]);
  }
  free(backUp);
  free(processors);
  free(reportName);
  free(traceName);
  fclose(report);
  fclose(trace);
  fclose(file);
  return EXIT_SUCCESS;
}
