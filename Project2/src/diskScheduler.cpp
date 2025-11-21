/*
 * CS4310 – Operating Systems
 * Project 2 – Task 2: Disk Scheduling Algorithms
 *
 * Implements and compares:
 *   1. FCFS
 *   2. SSTF
 *   3. SCAN
 *   4. C-SCAN
 *
 * Usage:
 *   g++ task2_diskscheduling.cpp -o diskschedule
 *   ./diskschedule <initial_head> [<previous_head>]
 *
 * If no input.txt is present, 1000 random requests are generated.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const int CYLINDERS = 5000;      // disk size 0-4999
const int REQUEST_COUNT = 1000;  // number of requests

struct Result {
    int totalMovement = 0;
    int directionChanges = 0;
};

// ------------------------------------------------------------
// Utility: load requests from input.txt or generate randomly
// ------------------------------------------------------------
vector<int> loadRequests() {
    vector<int> reqs;
    ifstream in("input.txt");
    int val;
    if (in) {
        while (in >> val) {
            if (val >= 0 && val < CYLINDERS)
                reqs.push_back(val);
        }
        in.close();
        cout << "Loaded " << reqs.size() << " requests from input.txt\n";
    }
    if (reqs.empty()) {
        srand((unsigned)time(nullptr));
        for (int i = 0; i < REQUEST_COUNT; i++)
            reqs.push_back(rand() % CYLINDERS);
        cout << "Generated " << REQUEST_COUNT << " random requests.\n";
    }
    return reqs;
}

// ------------------------------------------------------------
// FCFS – First-Come, First-Served
// ------------------------------------------------------------
Result fcfs(const vector<int>& reqs, int head) {
    Result r;
    int curr = head;
    for (int i : reqs) {
        r.totalMovement += abs(i - curr);
        curr = i;
    }
    return r;
}

// ------------------------------------------------------------
// SSTF – Shortest Seek Time First
// ------------------------------------------------------------
Result sstf(vector<int> reqs, int head) {
    Result r;
    vector<bool> done(reqs.size(), false);
    int curr = head;
    int completed = 0;
    while (completed < (int)reqs.size()) {
        int nearest = -1, minDist = 1e9;
        for (int i = 0; i < (int)reqs.size(); i++) {
            if (!done[i]) {
                int dist = abs(reqs[i] - curr);
                if (dist < minDist) {
                    minDist = dist;
                    nearest = i;
                }
            }
        }
        r.totalMovement += minDist;
        curr = reqs[nearest];
        done[nearest] = true;
        completed++;
    }
    return r;
}

// ------------------------------------------------------------
// SCAN – Elevator Algorithm
// ------------------------------------------------------------
Result scan(vector<int> reqs, int head, int prevHead) {
    Result r;
    sort(reqs.begin(), reqs.end());
    bool movingRight = (head - prevHead) >= 0; // direction

    int idx = lower_bound(reqs.begin(), reqs.end(), head) - reqs.begin();
    int curr = head;

    if (movingRight) {
        // go right to end
        for (int i = idx; i < (int)reqs.size(); i++) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        // reverse direction once
        r.directionChanges++;
        r.totalMovement += abs((CYLINDERS - 1) - curr);
        curr = CYLINDERS - 1;
        for (int i = idx - 1; i >= 0; i--) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
    } else {
        // go left to 0
        for (int i = idx - 1; i >= 0; i--) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        r.directionChanges++;
        r.totalMovement += abs(curr - 0);
        curr = 0;
        for (int i = idx; i < (int)reqs.size(); i++) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
    }
    return r;
}

// ------------------------------------------------------------
// C-SCAN – Circular SCAN
// ------------------------------------------------------------
Result cscan(vector<int> reqs, int head, int prevHead) {
    Result r;
    sort(reqs.begin(), reqs.end());
    bool movingRight = (head - prevHead) >= 0;

    int idx = lower_bound(reqs.begin(), reqs.end(), head) - reqs.begin();
    int curr = head;

    if (movingRight) {
        // go right to end
        for (int i = idx; i < (int)reqs.size(); i++) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        // jump to 0 (no service on jump)
        if (curr != CYLINDERS - 1)
            r.totalMovement += abs((CYLINDERS - 1) - curr);
        r.totalMovement += (CYLINDERS - 1); // jump to start
        curr = 0;
        // continue to the left side
        for (int i = 0; i < idx; i++) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        r.directionChanges = 1;
    } else {
        // go left to 0
        for (int i = idx - 1; i >= 0; i--) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        // jump to end
        if (curr != 0)
            r.totalMovement += curr;
        r.totalMovement += (CYLINDERS - 1);
        curr = CYLINDERS - 1;
        for (int i = reqs.size() - 1; i >= idx; i--) {
            r.totalMovement += abs(reqs[i] - curr);
            curr = reqs[i];
        }
        r.directionChanges = 1;
    }
    return r;
}

// ------------------------------------------------------------
// Main driver
// ------------------------------------------------------------
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./diskschedule <initial_head> [<previous_head>]\n";
        return 1;
    }
    int head = atoi(argv[1]);
    int prev = (argc >= 3) ? atoi(argv[2]) : head - 1;

    vector<int> reqs = loadRequests();

    cout << "\nInitial Head Position: " << head << endl;
    cout << "--------------------------------------------------------\n";
    cout << "Algorithm\tTotal Movement\tDirection Changes\n";
    cout << "--------------------------------------------------------\n";

    Result r1 = fcfs(reqs, head);
    cout << "FCFS\t\t" << r1.totalMovement << "\t\t" << r1.directionChanges << endl;

    Result r2 = sstf(reqs, head);
    cout << "SSTF\t\t" << r2.totalMovement << "\t\t" << r2.directionChanges << endl;

    Result r3 = scan(reqs, head, prev);
    cout << "SCAN\t\t" << r3.totalMovement << "\t\t" << r3.directionChanges << endl;

    Result r4 = cscan(reqs, head, prev);
    cout << "C-SCAN\t\t" << r4.totalMovement << "\t\t" << r4.directionChanges << endl;

    cout << "--------------------------------------------------------\n";
    cout << "Done.\n";
    return 0;
}
