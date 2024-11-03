#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure for storing process information
struct Process {
    int id;           // Process ID
    int arrival_time; // Arrival Time of the process
    int burst_time;   // Burst Time of the process
    int remaining_time; // Remaining Time of the process
    int waiting_time; // Waiting Time of the process
    int turnaround_time; // Turnaround Time of the process
};

// Function to implement Preemptive SJF (SRTF) scheduling
void SRTF(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0, time = 0, shortest = -1;
    int min_remaining_time = INT_MAX;

    // Initialize remaining times for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n) {
        // Find process with minimum remaining time at current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++; // If no process is ready, increment time
            continue;
        }

        // Execute the selected process
        processes[shortest].remaining_time--;
        min_remaining_time = processes[shortest].remaining_time;

        // If a process is completed
        if (processes[shortest].remaining_time == 0) {
            completed++;
            min_remaining_time = INT_MAX;
            int completion_time = time + 1;
            processes[shortest].turnaround_time = completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
        }

        time++;
    }

    // Display process details
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (auto& process : processes) {
        cout << "P" << process.id << "\t" << process.arrival_time << "\t\t" 
             << process.burst_time << "\t\t" << process.waiting_time << "\t\t" 
             << process.turnaround_time << endl;
    }

    // Calculate average waiting and turnaround times
    double avg_waiting_time = 0, avg_turnaround_time = 0;
    for (auto& process : processes) {
        avg_waiting_time += process.waiting_time;
        avg_turnaround_time += process.turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

// Main function
int main() {
    vector<Process> processes = {
        {1, 0, 8, 0, 0, 0},  // Process 1 with arrival time 0 and burst time 8
        {2, 1, 4, 0, 0, 0},  // Process 2 with arrival time 1 and burst time 4
        {3, 2, 9, 0, 0, 0},  // Process 3 with arrival time 2 and burst time 9
        {4, 3, 5, 0, 0, 0}   // Process 4 with arrival time 3 and burst time 5
    };

    SRTF(processes);

    return 0;
}
