#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to implement Round Robin scheduling
void roundRobin(vector<int>& processes, vector<int>& burst_time, int time_quantum) {
    int n = processes.size();
    vector<int> waiting_time(n, 0), turnaround_time(n, 0);
    queue<int> ready_queue;

    // Enqueue all processes to the ready queue
    for (int i = 0; i < n; i++) {
        ready_queue.push(i);
    }

    int time = 0; // Track the elapsed time

    // Continue until all processes are completed
    while (!ready_queue.empty()) {
        int current_process = ready_queue.front(); // Get the front process
        ready_queue.pop();

        // If the burst time is greater than the time quantum
        if (burst_time[current_process] > time_quantum) {
            time += time_quantum; // Increase the elapsed time
            burst_time[current_process] -= time_quantum; // Decrease the burst time
            ready_queue.push(current_process); // Re-queue the process
        } else {
            // Process completes execution
            time += burst_time[current_process]; // Increase time by remaining burst time
            waiting_time[current_process] = time - (burst_time[current_process] + time_quantum); // Calculate waiting time
            turnaround_time[current_process] = time; // Calculate turnaround time
            burst_time[current_process] = 0; // Set burst time to 0 as the process is complete
        }
    }

    // Display the results
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i] << "\t" << (waiting_time[i] + turnaround_time[i]) << "\t\t"
             << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    // Calculate and display average waiting and turnaround times
    double avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

// Main function
int main() {
    vector<int> processes = {1, 2, 3}; // Process IDs
    vector<int> burst_time = {4, 3, 5}; // Burst time for each process
    int time_quantum = 2; // Define the time quantum

    roundRobin(processes, burst_time, time_quantum);

    return 0;
}
