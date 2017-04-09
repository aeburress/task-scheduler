/**
 * Author: Alex Burress
 * Subject: OS200
 * SJFScheduler prompts the user for a filename and outputs the average SJF
 * turnaround and wait times. This algorithm is very similar to the SJF algorithm
 * shown in CompareSchedulers.c. Please refer to that file for detailed comments
 * on the algorithm. Note that values output are based on nonpre-emptive SJF
 * scheduling.
 */

#include "LinkedList.h"
#include "SJFScheduler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE !FALSE

int main(void)
{
	char userInput[10];
	LinkedList* jobs;
	LinkedList* finished;
	
	strcpy(userInput, "blank");
	do
	{
		runPrompt(userInput);
			
		if (strcmp(userInput, "quit") != 0 && strcmp(userInput, "QUIT") != 0)
		{
			
			jobs = createList();
			pullScheduleData(userInput, jobs);

			finished = createList();
			runTimingLoop(jobs, finished);

			freeList(jobs);
			freeList(finished);
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

void pullScheduleData(char* filename, LinkedList* list)
{
	FILE *source;
	int timeQuantum;
	int arrivalTime;
	int burstTime;
	Process* newProcess;
	
	source = fopen(filename, "r");
	if (source == NULL)
	{
		printf("Error opening file\n");
	}
	else
	{
		fscanf(source, "%d", &timeQuantum);
		
		while(fscanf(source, "%d %d", &arrivalTime, &burstTime) == 2)
		{
			newProcess = (Process*)malloc(sizeof(Process));
			newProcess->arrivalTime = arrivalTime;
			newProcess->burstTime = burstTime;
			newProcess->waitTime = 0;
			enqueue(list, newProcess);
		}
		
		fclose(source);
	}
}

void runTimingLoop(LinkedList* jobs, LinkedList* finished)
{
	int currentTime;
	int mustWait;
	int searchedAll;
	int foundJob;
	int ii;
	int totalWait;
	int totalTurnaround;
	int countProcesses;
	double avgTurnaround;
	double avgWait;
	Process* candidate;
	Process* shortestJob;
	Process* finishedProcess;
	
	currentTime = 0;
	foundJob = FALSE;
	
	while (jobs->count > 0)
	{
		mustWait = TRUE;
		searchedAll = FALSE;
		/* see if any eligible jobs are in the queue */
		while (mustWait == TRUE && searchedAll == FALSE)
		{
			for (ii = 0; ii < jobs->count; ii++)
			{
				candidate = retrieveElement(jobs, ii);
				if (candidate->arrivalTime <= currentTime)
				{
					shortestJob = candidate;
					mustWait = FALSE;
				}
				if (ii == (jobs->count - 1))
				{
					searchedAll = TRUE;
				}
			}
		}
		
		/* at least 1 eligible job exists */
		if (mustWait == FALSE)
		{
			shortestJob = dequeue(jobs);
			for (ii = 1; ii < jobs->count; ii++)
			{
				candidate = dequeue(jobs);
				if (candidate->arrivalTime <= currentTime && candidate->burstTime < shortestJob->burstTime)
				{
					enqueue(jobs, shortestJob);
					shortestJob = candidate;					
				}
				else
				{
					enqueue(jobs, candidate);
				}
			}
		
			shortestJob->waitTime = currentTime - shortestJob->arrivalTime;
			/* simulating CPU time */
			currentTime += shortestJob->burstTime;
			shortestJob->turnaroundTime = currentTime - shortestJob->arrivalTime;
			enqueue(finished, shortestJob);
		}
		
		/* no eligible job exists, increment time */
		if (searchedAll == FALSE)
		{
			currentTime++;
		}
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
