#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

int n=0, u;

// C program for implementation of RR scheduling



// Function to find the waiting time for all

// processes

void findWaitingTime(int processes[][n], int u, int max, int n, int bt[][n], int wt[][n], int quantum)

{

	// Make a copy of burst times bt[] to store remaining

	// burst times.

	int rem_bt[2][n] , i, j, k, user_no=0, store , p;

	int t = 0; // Current time

	bool done;

	for (i = 0 ; i < n ; i++){

        rem_bt[0][i] = bt[0][i];

		rem_bt[1][i] = bt[1][i];

	}



	// Keep traversing processes in round robin manner

	// until all of them are not done.

	while (1)

	{

		 done = true;

		// Traverse all processes one by one repeatedly



		p=u*max;

		for (j = 0 ; j<p; j++)

		{

			user_no=(user_no+1)%u;

           	 	for(k=0;k<n;k++){

				if(processes[0][k]==user_no){

				        i=processes[1][k];

				        store=processes[1][k];

				   	while(processes[0][k]==user_no&&k<n){

						processes[1][k]=processes[1][k+1];

						k++;

				    	}

                    	processes[1][k-1]=store;



                }



            }



			// If burst time of a process is greater than 0

			// then only need to process further

			if (rem_bt[1][i] > 0)

			{

				done = false; // There is a pending process



				if (rem_bt[1][i] > quantum)

				{

					// Increase the value of t i.e. shows

					// how much time a process has been processed

					t += quantum;



					// Decrease the burst_time of current process

					// by quantum

					rem_bt[1][i] -= quantum;

				}



				// If burst time is smaller than or equal to

				// quantum. Last cycle for this process

				else

				{

					// Increase the value of t i.e. shows

					// how much time a process has been processed

					t = t + rem_bt[1][i];



					// Waiting time is current time minus time

					// used by this process

					wt[0][i]=bt[0][i];

					wt[1][i] = t - bt[1][i];



					// As the process gets fully executed

					// make its remaining burst time = 0

					rem_bt[0][i]=bt[0][i];

					rem_bt[1][i] = 0;

				}

			}

		}



		// If all processes are done

		if (done == true)

		break;

	}

}



// Function to calculate turn around time

void findTurnAroundTime(int processes[][n], int n, int max, int bt[][n], int wt[][n], int tat[][n])

{

	int i;

	// calculating turnaround time by adding

	// bt[i] + wt[i]

	for (i = 0; i < n ; i++)

		tat[1][i] = bt[1][i] + wt[1][i];

}



// Function to calculate average time

void findavgTime(int processes[][n], int u, int max, int n, int  bt[][n], int quantum)

{

	int wt[2][n], tat[2][n], total_wt = 0, total_tat = 0 ,i ;



	// Function to find waiting time of all processes

	findWaitingTime(processes, u, max, n, bt, wt, quantum);



	// Function to find turn around time for all processes

	findTurnAroundTime(processes, n, max, bt, wt, tat);



	// Display processes along with all details

	printf("User \t\tProcesses \t\tBurst time \t\tTurn around time \t\tWaiting time\n");



	// Calculate total waiting time and total turn

	// around time

	for (i=0; i<n; i++)

	{

		total_wt = total_wt + wt[1][i];

		total_tat = total_tat + tat[1][i];

		printf("%d \t\t%d \t\t\t%d \t\t\t%d \t\t\t\t%d\n",bt[0][i],(i+1),bt[1][i],tat[1][i],wt[1][i]);

	}



	printf("Average waiting time = %f",((float)total_wt / (float)n));

	printf("\nAverage turn around time = %f",((float)total_tat / (float)n));

	printf("\nShair given to each User  =  %f percentage\n",(100.00/u));

}



// Driver code

int main()

{

	// process id's

	int i, j, k, quantum , max;

	printf("Enter the no of users\n");

	scanf("%d",&u);

	int user[u];

	for(i=0;i<u;i++){

	printf("Enter the no of processes for user %d: \n",(i+1));

	scanf("%d",&user[i]);

	if(max<user[i])

	max=user[i];

	}

	for(i=0;i<u;i++){

        n+=user[i];

	}

	int processes[2][n], burst_time[2][n];



	// Burst time of all processes



	k=0;

	for(i=0;i<u;i++){

	for(j=0;j<user[i];j++){

	printf("Enter the burst time for user %d for process %d\n",(i+1),(j+1));

	burst_time[0][k]=i;

	scanf("%d",&burst_time[1][k]);

	processes[0][k]=burst_time[0][k];

	processes[1][k]=k;

	k++;

	}

	}



	// Time quantum

	printf("Enter the time quantum for process\n");

	scanf("%d",&quantum);



	findavgTime(processes, u, max, n, burst_time, quantum);



	return 0;

}


