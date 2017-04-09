/**
 * Author: Alex Burress
 * Subject: OS200
 * RRScheduler prompts the user for a filename and outputs the average RR
 * turnaround and wait times. This algorithm is very similar to the RR algorithm
 * shown in CompareSchedulers.c. Please refer to that file for detailed comments
 * on the algorithm.
 */

#include "LinkedList.h"
#include "RRScheduler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE !FALSE

int main(void)
{
	char userInput[10];
	LinkedList* arriving;
	LinkedList* ready;
	LinkedList* finished;
	int timeQuantum;
	
	strcpy(userInput, "blank");
	
	do
	{
		runPrompt(userInput);
			
		if (strcmp(userInput, "quit") != 0 && strcmp(userInput, "QUIT") != 0)
		{
			arriving = createList();
			timeQuantum = pullScheduleData(userInput, arriving);
			if (timeQuantum > 0)
			{
				ready = createList();
				finished = createList();
				
				runTimingLoop(arriving, ready, finished, timeQuantum);

				freeList(ready);
				freeList(finished);
			}
			freeList(arriving);
		}
	}
	while (strcmp(userInput, "quit") != 0 && strcmp(userInput, "QUIT") != 0);

	return 0;
}

void runPrompt(char* userInput)
{
	printf("RR simulation: ");
	scanf("%s", userInput);
}

int pullScheduleData(char* filename, LinkedList* list)
{
	FILE* source;
	int timeQuantum;
	int arrivalTime;
	int burstTime;
	Process* newProcess;
	
	source = fopen(filename, "r");
	if (source == NULL)
	{
		printf("Error opening file\n");
		timeQuantum = -1;
	}
	else
	{
		fscanf(source, "%d", &timeQuantum);
		
		while(fscanf(source, "%d %d", &arrivalTime, &burstTime) == 2)
		{
			newProcess = (Process*)malloc(sizeof(Process));
			newProcess->arrivalTime = arrivalTime;
			newProcess->burstTime = burstTime;
			newProcess->remainingBurst = burstTime;
			newProcess->waitTime = 0;
			newProcess->lastAllocated = -1;
			enqueue(list, newProcess);
		}
		
		
		
		fclose(source);
	}
	
	return timeQuantum;
}

void runTimingLoop(LinkedList* arriving, LinkedList* ready, LinkedList* finished, int timeQuantum)
{
	int totalProcesses;
	int currentTime;
	int countProcesses;
	int totalWait;
	int totalTurnaround;
	int processorBusy;
	int partialTimeSlice;
	double avgWait;
	double avgTurnaround;
	Process* peekedProcess;
	Process* readyProcess;
	Process* allocatedProcess;
	Process* finishedProcess;

	currentTime = 0;
	processorBusy = FALSE;
	totalProcesses = arriving->count;
		
	/* while there are processes in the ready queue or arriving queue */
	while(finished->count < totalProcesses)
	{
		/* transfer processes that have arrived to the ready queue */
		while (arriving->count > 0 && currentTime >= retrieveElement(arriving, 0)->arrivalTime)
		{
			peekedProcess = retrieveElement(arriving, 0);
			if (peekedProcess->arrivalTime <= currentTime)
			{
				readyProcess = dequeue(arriving);
				enqueue(ready, readyProcess);
			}
		}
		
		if (processorBusy == TRUE)
		{
			partialTimeSlice++;
			allocatedProcess->remainingBurst--;
			if (allocatedProcess->remainingBurst <= 0)
			{
				allocatedProcess->turnaroundTime = currentTime - allocatedProcess->arrivalTime;
				allocatedProcess->waitTime = currentTime - allocatedProcess->burstTime - allocatedProcess->arrivalTime;
				enqueue(finished,allocatedProcess);
				processorBusy = FALSE;
			}
			else if (partialTimeSlice == timeQuantum)
			{
				enqueue(ready, allocatedProcess);
				processorBusy = FALSE;
			}
		}
		
		if (processorBusy == FALSE && ready->count > 0)
		{
			processorBusy = TRUE;
			allocatedProcess = dequeue(ready);
			partialTimeSlice = 0;
		}
		
		currentTime++;
	}
	
	totalWait = 0;
	totalTurnaround = 0;
	countProcesses = finished->count;
	while (finished->count > 0)
	{
		finishedProcess = dequeue(finished);
		totalWait += finishedProcess->waitTime;
		totalTurnaround += finishedProcess->turnaroundTime;
		
		free(finishedProcess);
	}
	
	avgWait = (double)totalWait/(double)countProcesses;
	avgTurnaround = (double)totalTurnaround/(double)countProcesses;
	
	printf("Average wait:\t\t%f\nAverage turnaround:\t%f\n", avgWait, avgTurnaround);
}
