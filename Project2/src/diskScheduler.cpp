/*
 * CS4310 – Operating Systems
 * Project 2 – Task 2: Disk Scheduling Algorithms
 *
 * Implements and compares:
 *   1. FCFS
 *   2. SSTF
 *   3. SCAN
 *   4. C-SCAN
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

// Direction Tracker
inline int getDirection(int from, int to) {
    if (to > from) return 1;   // moving right
    if (to < from) return -1;  // moving left
    return 0;                  // no movement
}

// Utility: load requests from input.txt or generate randomly
vector<int> loadRequests() {
    vector<int> reqs;
    int choice;

    cout << "\nChoose request source:\n";
    cout << "1. Load requests from input.txt\n";
    cout << "2. Generate 1000 random requests\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        ifstream in("input.txt");
        int val;

        if (!in) {
            cout << "Error: input.txt not found. Generating random requests instead.\n";
        } else {
            while (in >> val) {
                if (val >= 0 && val < CYLINDERS)
                    reqs.push_back(val);
            }
            in.close();
            cout << "Loaded " << reqs.size() << " requests from input.txt\n";

            if (!reqs.empty())
                return reqs;

            cout << "input.txt was empty or invalid. Generating random requests instead.\n";
        }
    }

    // Option 2 or invalid file → generate 1000 random requests
    srand((unsigned)time(nullptr));
    for (int i = 0; i < REQUEST_COUNT; i++)
        reqs.push_back(rand() % CYLINDERS);

    cout << "Generated " << REQUEST_COUNT << " random requests.\n";
    return reqs;
}

// FCFS 
Result fcfs(const vector<int>& reqs, int head) {
    Result r;
    int curr = head;

    int prevDir = 0;

    for (int next : reqs) {
        int dir = getDirection(curr, next);

        if (prevDir != 0 && dir != 0 && dir != prevDir)
            r.directionChanges++;

        r.totalMovement += abs(next - curr);

        prevDir = dir;
        curr = next;
    }
    return r;
}



// SSTF 
Result sstf(vector<int> reqs, int head) {
    Result r;
    int curr = head;
    int prevDir = 0;

    vector<bool> used(reqs.size(), false);
    int done = 0;

    while (done < reqs.size()) {
        int best = -1, bestDist = 1e9;

        for (int i = 0; i < reqs.size(); i++) {
            if (!used[i]) {
                int dist = abs(reqs[i] - curr);
                if (dist < bestDist) {
                    bestDist = dist;
                    best = i;
                }
            }
        }

        int dir = getDirection(curr, reqs[best]);
        if (prevDir != 0 && dir != 0 && dir != prevDir)
            r.directionChanges++;

        r.totalMovement += bestDist;

        prevDir = dir;
        curr = reqs[best];
        used[best] = true;
        done++;
    }

    return r;
}


// SCAN 
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

// C-SCAN – Circular SCAN
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


// Main allowing command line arguments
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./diskschedule <initial_head> [<previous_head>]\n";
        return 1;
    }
    int head = atoi(argv[1]);
    int prev = (argc >= 3) ? atoi(argv[2]) : head - 1;
    cout << endl;
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


    return 0;
}
