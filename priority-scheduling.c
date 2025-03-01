/*priority sheduling algorithms*/

#include<stdio.h>

struct process {
    int WT, AT, BT, TAT, PT;
};

struct process a[10];

int main() {
    int n, temp[10], t, count = 0, short_p, i;
    float total_WT = 0, total_TAT = 0, Avg_WT, Avg_TAT;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Input the arrival time, burst time, and priority for each process\n");

    // Input arrival time, burst time, and priority for each process
    for(i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &a[i].AT);
        printf("Burst Time: ");
        scanf("%d", &a[i].BT);
        printf("Priority: ");
        scanf("%d", &a[i].PT);

        // Store the original burst time for later use
        temp[i] = a[i].BT;
    }

    // Initialize burst time of a process with maximum priority
    a[9].PT = 10000;

    // CPU scheduling algorithm
    for(t = 0; count != n; t++) {
        short_p = 9;

        // Find the process with the highest priority (lowest priority number)
        for(i = 0; i < n; i++) {
            if(a[short_p].PT > a[i].PT && a[i].AT <= t && a[i].BT > 0) {
                short_p = i;
            }
        }

        // Process the selected process
        a[short_p].BT = a[short_p].BT - 1;

        // If a process is completed
        if(a[short_p].BT == 0) {
            // Increment the count as one process is completed
            count++;
            a[short_p].WT = t + 1 - a[short_p].AT - temp[short_p];
            a[short_p].TAT = t + 1 - a[short_p].AT;

            // Calculate the total waiting time and turnaround time
            total_WT = total_WT + a[short_p].WT;
            total_TAT = total_TAT + a[short_p].TAT;
        }
    }

    // Calculate the average waiting time and turnaround time
    Avg_WT = total_WT / n;
    Avg_TAT = total_TAT / n;

    // Output the result
    printf("ID\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, a[i].WT, a[i].TAT);
    }

    printf("Average waiting time: %f\n", Avg_WT);
    printf("Average turnaround time: %f\n", Avg_TAT);

    return 0;
}
