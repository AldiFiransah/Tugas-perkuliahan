#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    string id;
    int numericId;
    int at;
    int bt;
    int st;
    int ct;
    int tat;
    int wt;
};

bool compareFCFS(const Process& p1, const Process& p2) {
    if (p1.at == p2.at) {
        return p1.numericId < p2.numericId;
    }
    return p1.at < p2.at;
}

void printLine() {
    cout << "------------------------------------------------------------------" << endl;
}

int main() {
    string npm = "2517051012";
    int n = npm.length();
    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = "P" + to_string(i + 1);
        processes[i].numericId = i + 1;
        
        processes[i].at = npm[i] - '0';
        
        int bt_val = npm[n - 1 - i] - '0';
        processes[i].bt = (bt_val == 0) ? 10 : bt_val; 
    }

    cout << "==================================================================\n";
    cout << " DATA PROSES AWAL (Berdasarkan NPM: " << npm << ")\n";
    cout << "==================================================================\n";
    cout << "Process ID\tArrival Time (AT)\tBurst Time (BT)\n";
    printLine();
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.at << "\t\t\t" << p.bt << endl;
    }
    cout << endl;

    vector<Process> fcfs_processes = processes;
    
    sort(fcfs_processes.begin(), fcfs_processes.end(), compareFCFS);

    int last_ct = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; ++i) {
        fcfs_processes[i].st = max(fcfs_processes[i].at, last_ct);
        
        fcfs_processes[i].ct = fcfs_processes[i].st + fcfs_processes[i].bt;
        
        fcfs_processes[i].tat = fcfs_processes[i].ct - fcfs_processes[i].at;
        
        fcfs_processes[i].wt = fcfs_processes[i].tat - fcfs_processes[i].bt;

        last_ct = fcfs_processes[i].ct;

        totalTAT += fcfs_processes[i].tat;
        totalWT += fcfs_processes[i].wt;
    }

    cout << "==================================================================\n";
    cout << " URUTAN EKSEKUSI PROSES (FCFS)\n";
    cout << "==================================================================\n";
    for (int i = 0; i < n; ++i) {
        cout << fcfs_processes[i].id;
        if (i != n - 1) cout << " -> ";
    }
    cout << "\n\n";

    cout << "==================================================================\n";
    cout << " HASIL PERHITUNGAN ALGORITMA FCFS\n";
    cout << "==================================================================\n";
    cout << "ID\tAT\tBT\tST\tCT\tTAT\tWT\n";
    printLine();
    
    for (const auto& p : fcfs_processes) {
        cout << p.id << "\t" 
             << p.at << "\t" 
             << p.bt << "\t" 
             << p.st << "\t"
             << p.ct << "\t" 
             << p.tat << "\t" 
             << p.wt << endl;
    }
    printLine();

    cout << fixed << setprecision(2);
    cout << "Rata-rata Turn Around Time (TAT) : " << (totalTAT / n) << " satuan waktu\n";
    cout << "Rata-rata Waiting Time (WT)      : " << (totalWT / n) << " satuan waktu\n";
    cout << "==================================================================\n";

    return 0;
}
