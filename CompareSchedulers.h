#ifndef COMPARESCHEDULERS_H
#define COMPARESCHEDULERS_H

#include "LinkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * A struct for holding the average wait and turnaround times for the same group
 * of processes if they were scheduled via RR or non-preemptive SJF scheduling.
 */

typedef struct ProcessStats {
	double rrWait;
	double rrTurnaround;
	double sjfWait;
	double sjfTurnaround;
} ProcessStats;

void* runPrompt();

void* runRR();

void* runSJF();

int pullScheduleDataRR(LinkedList* list);

LinkedList* runTimingLoopRR(LinkedList* arriving, int timeQuantum);

void pullScheduleDataSJF(LinkedList* list);

LinkedList* runTimingLoopSJF(LinkedList* jobs);

void calcTimes(LinkedList* finished, double* avgWait, double* avgTurnaround);

void exitProgram();

#endif
