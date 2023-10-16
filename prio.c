#include <stdio.h>

typedef struct
{
	int at;
	int bt;
	int p;
	int ct;
	int rt;
	int wt;
	int tat;
} process;

int main()
{
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	process a[n];

	
	for(int i = 0; i < n; i++){
		printf("Enter the arrival time, burst time and priority of process %d: ",i+1);	
		scanf("%d %d %d", &a[i].at, &a[i].bt, &a[i].p);}
	int completed = 0;
	int twt = 0, ttat = 0, current_time = 0;

	for(int i = 0; i < n; i++)
	{
		a[i].rt = a[i].bt;
		a[i].wt = 0;
	}

	for(int i = 0; i < n - 1; i++)
		for(int j = 0; j < n - i - 1; j++)
			if(a[j].at > a[j + 1].at)
			{
				process temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}

	while(completed < n)
	{
		int top_job = -1;
		int top_priority = 99999;
		for(int i = 0; i < n; i++)
		{
			if(a[i].at <= current_time && a[i].p < top_priority  && a[i].rt > 0)
			{
				top_job = i;
				top_priority = a[i].p;
			}
		}
		if(top_job == -1)
			current_time ++;
		else
		{
			a[top_job].rt--;
			current_time++;
			if(a[top_job].rt == 0)
			{
				completed++;
				a[top_job].tat = current_time - a[top_job].at;
				a[top_job].ct = a[top_job].tat - a[top_job].bt;
			}
		}
	}

	for(int i = 0; i < n; i++)
	{
		a[i].wt = a[i].at + a[i].tat;
		ttat += a[i].tat;
		twt += a[i].ct;
	}

	float avg_tat = (float) ttat / n;
	float avg_wt = (float) twt / n;

        printf("PID\tBurst\tArrival\tPriority\tComple\tWait\tTurn Around\n");
        for(int i = 0; i < n; i ++)
                printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", i+1, a[i].bt, a[i].at, a[i].p, a[i].wt, a[i].ct, a[i].tat);

        printf("\n");
        printf("Total waiting time: %d\n", twt);
        printf("Total turn around time: %d\n", ttat);
        printf("\n");
        printf("Average waiting time: %0.2f\n", avg_wt);
        printf("Average turn around time: %0.2f\n", avg_tat);

       

	return 0;
}
