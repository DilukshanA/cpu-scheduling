#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time
};

// Function to sort processes based on arrival time
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
    int completion_time[n];
    completion_time[0] = p[0].arrival + p[0].burst;
    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;

    for (int i = 1; i < n; i++) {
        if (p[i].arrival > completion_time[i - 1]) {
            completion_time[i] = p[i].arrival + p[i].burst;
        } else {
            completion_time[i] = completion_time[i - 1] + p[i].burst;
        }
        p[i].waiting = completion_time[i] - p[i].arrival - p[i].burst;
        if (p[i].waiting < 0) p[i].waiting = 0;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
}

// Function to display process details
void displayProcesses(struct Process p[], int n) {
    float total_wait = 0, total_turnaround = 0;
    
    printf("\nFCFS Scheduling Algorithm\n");
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
    }

    // Sort by arrival time
    sortByArrival(p, n);

    // Calculate waiting and turnaround times
    calculateTimes(p, n);

    // Display process details
    displayProcesses(p, n);

    return 0;
}
