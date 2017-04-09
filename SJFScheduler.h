#ifndef SJFSCHEDULER_H
#define SJFSCHEDULER_H

#include "LinkedList.h"
#include <stdio.h>

void runPrompt(char* userInput);

void pullScheduleData(char* filename, LinkedList* list);

void runTimingLoop(LinkedList* jobs, LinkedList* finished);

#endif
