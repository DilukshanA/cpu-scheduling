#include <stdio.h>
#include <stdbool.h>

// Structure to hold process details
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time
    bool completed; // Completion status
};

// Function to sort processes by arrival time
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculateTimes(struct Process p[], int n) {
    int currentTime = 0, completedProcesses = 0;
    
    while (completedProcesses < n) {
        int minBurst = __INT_MAX__;
        int index = -1;

        // Find the shortest job that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= currentTime) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    index = i;
                }
            }
        }

        if (index == -1) {
            currentTime++;
        } else {
            p[index].waiting = currentTime - p[index].arrival;
            if (p[index].waiting < 0) p[index].waiting = 0;

            p[index].turnaround = p[index].waiting + p[index].burst;
            currentTime += p[index].burst;
            p[index].completed = true;
            completedProcesses++;
        }
    }
}

// Function to display process details
void displayProcesses(struct Process p[], int n) {
    float total_wait = 0, total_turnaround = 0;

    printf("\nShortest Job First (SJF) Scheduling Algorithm\n");
    printf("---------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
        total_wait += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("---------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter Process ID, Arrival Time, and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].completed = false;
    }

    // Sort by arrival time
    sortByArrival(p, n);

    // Calculate waiting and turnaround times
    calculateTimes(p, n);

    // Display process details
    displayProcesses(p, n);

    return 0;
}
