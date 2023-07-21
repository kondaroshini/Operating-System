#include <stdio.h>

void findCt(int n, int bt[], int ct[])
{
    ct[0] = bt[0];
    for (int i = 1; i < n; i++) 
    {
        ct[i] = bt[i] + ct[i - 1];
    }
}
void findWt(int n, int bt[], int wt[])
{
    wt[0] = 0; 
    for (int i = 1; i < n; i++) 
    {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}
void findTat(int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++) 
    {
        tat[i] = bt[i] + wt[i];
    }
}
void findAverageTime(int n, int at[], int bt[])
{
    int wt[n], tat[n], ct[n];

    findWt(n, bt, wt);
    findTat(n, bt, wt, tat);
    findCt(n, bt, ct);

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    float total_ct = 0;
    float total_wt = 0;
    float total_tat = 0;

    for (int i = 0; i < n; i++) 
    {
        total_ct += ct[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    float average_ct = total_ct / n;
    float average_wt = total_wt / n;
    float average_tat = total_tat / n;

    printf("\nAverage Completion Time: %.2f", average_ct);
    printf("\nAverage Waiting Time: %.2f", average_wt);
    printf("\nAverage Turnaround Time: %.2f", average_tat);
}
int main()
{
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int at[n],bt[n]; 
    printf("Enter the arrival time for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &at[i]);
    }
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }
    findAverageTime(n, at, bt);
    return 0;
}


