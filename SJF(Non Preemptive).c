#include<stdio.h>
void calculateTimes(int n, int burstTime[], int arrivalTime[], int waitingTime[], int turnaroundTime[], int completionTime[])
{
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
    }
    int complete = 0, time = 0, shortest = -1, minBurst = 9999;
    int check = 0, smallestArrivalTime = arrivalTime[0];

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if (arrivalTime[j] <= time && remainingTime[j] < minBurst && remainingTime[j] > 0)
            {
                minBurst = remainingTime[j];
                shortest = j;
                check = 1;
            }
        }
        if (check == 0)
        {
            time++;
            continue;
        }
        remainingTime[shortest]--;
        minBurst = remainingTime[shortest];
        if (minBurst == 0)
            minBurst = 9999;

        if (remainingTime[shortest] == 0)
        {
            complete++;
            check = 0;
            completionTime[shortest] = time + 1;
            turnaroundTime[shortest] = completionTime[shortest] - arrivalTime[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burstTime[shortest];

            if (waitingTime[shortest] < 0)
                waitingTime[shortest] = 0;
        }
        time++;
    }
}
void calculateAverages(int n, int turnaroundTime[], int waitingTime[])
{
    int totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalTurnaroundTime += turnaroundTime[i];
        totalWaitingTime += waitingTime[i];
    }

    float averageTurnaroundTime = (float)totalTurnaroundTime / n;
    float averageWaitingTime = (float)totalWaitingTime / n;

    printf("\nAverage Turnaround Time: %.2f", averageTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", averageWaitingTime);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n], arrivalTime[n];
    int waitingTime[n], turnaroundTime[n], completionTime[n];

    printf("Enter the burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burstTime[i]);
        printf("Arrival Time: ");
        scanf("%d", &arrivalTime[i]);
    }

    calculateTimes(n, burstTime, arrivalTime, waitingTime, turnaroundTime, completionTime);

    printf("\nProcess\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], arrivalTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    calculateAverages(n, turnaroundTime, waitingTime);

    return 0;
}


