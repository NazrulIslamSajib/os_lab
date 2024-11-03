#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure for storing process information
struct Process {
    int id;           // Process ID
    int burst_time;   // Burst Time of the process
    int waiting_time; // Waiting Time of the process
    int turnaround_time; // Turnaround Time of the process
};

// Function to calculate waiting time for all processes
void calculateWaitingTime(vector<Process>& processes) {
    processes[0].waiting_time = 0; // The first process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

// Function to calculate turnaround time for all processes
void calculateTurnaroundTime(vector<Process>& processes) {
    for (int i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

// Function to implement SJF scheduling
void SJF(vector<Process>& processes) {
    // Sort processes based on burst time in ascending order
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burst_time < b.burst_time;
    });

    // Calculate waiting time and turnaround time
    calculateWaitingTime(processes);
    calculateTurnaroundTime(processes);

    // Display process details
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (auto& process : processes) {
        cout << "P" << process.id << "\t" << process.burst_time << "\t\t" 
             << process.waiting_time << "\t\t" << process.turnaround_time << endl;
    }

    // Calculate average waiting and turnaround time
    double avg_waiting_time = 0, avg_turnaround_time = 0;
    for (auto& process : processes) {
        avg_waiting_time += process.waiting_time;
        avg_turnaround_time += process.turnaround_time;
    }
    avg_waiting_time /= processes.size();
    avg_turnaround_time /= processes.size();

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

// Main function
int main() {
    vector<Process> processes = {
        {1, 6, 0, 0},  // Process 1 with burst time 6
        {2, 8, 0, 0},  // Process 2 with burst time 8
        {3, 7, 0, 0},  // Process 3 with burst time 7
        {4, 3, 0, 0}   // Process 4 with burst time 3
    };

    SJF(processes);

    return 0;
}
