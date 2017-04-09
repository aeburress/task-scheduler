#ifndef RRSCHEDULER_H
#define RRSCHEDULER_H

#include "LinkedList.h"
#include <stdio.h>

void runPrompt(char*);

int pullScheduleData(char* filename, LinkedList* list);

void runTimingLoop(LinkedList* arriving, LinkedList* ready, LinkedList* finished, int timeQuantum);

#endif
