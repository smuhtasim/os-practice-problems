#include<iostream>
#include<algorithm>
#include <stdlib.h>

using namespace std;

int i, j, ttime = 0, n = 5;
int tArray[5];

struct node{
    int pid;
    int burstTime;
    int arrivalTime;
} a[10];


bool btimeSort(node a,node b){
    return a.burstTime < b.burstTime;
}

bool atimeSort(node a,node b){
    return a.arrivalTime < b.arrivalTime;
}

void execute(int n) {
    sort(a, a+n, btimeSort);
    sort(a, a+n, atimeSort);

    for(i = 0; i < n; i++){
        j = i;

        while(a[j].arrivalTime <= ttime && j != n){
            j++;
        }

        sort(a+i, a+j, btimeSort);

        tArray[i] = ttime;
        ttime += a[i].burstTime;
    }

    tArray[i] = ttime;
}

void output(int n) {
    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout<<"\nNon-preemptive SJF Scheduling:";
    for (i = 0; i < n; i++){
        cout << " --> P" << a[i].pid;
    }

    cout << "\n\nGantt Chart:\n\n";
    for (i = 0; i < n; i++){
        cout <<"|   "<< "P" << a[i].pid << "   ";
    }
    cout<<"\n";

    for (i = 0; i < n+1; i++){
        cout << tArray[i] << "        ";
    }
    cout<<"\n";

    cout<<"\nProcess ID\tArrival Time\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tResponse Time\n";

    int startTime;
    for (i = 0; i < n; i++){
        if (i == 0) {
            startTime = a[i].arrivalTime;
        }
        else {
            startTime = tArray[i];
        }

        cout << a[i].pid << "\t\t";
        cout << a[i].arrivalTime << "\t\t";
        cout << a[i].burstTime << "\t\t";
        cout << startTime << "\t\t";
        cout << tArray[i+1] << "\t\t";
        cout << tArray[i] - a[i].arrivalTime << "\t\t";
        cout << tArray[i] - a[i].arrivalTime << "\t\t";
        cout <<"\n";

        averageWaitingTime += tArray[i] - a[i].arrivalTime;
        averageResponseTime += tArray[i] - a[i].arrivalTime;
    }

    cout<<"\nAverage Response time: " << (float)averageResponseTime/(float)n << endl;
    cout<<"Average Waiting time: " << (float)averageWaitingTime/(float)n << endl;
}

int main() {

    a[0].pid = 1;
    a[1].pid = 2;
    a[2].pid = 3;
    a[3].pid = 4;
    a[4].pid = 5;

    a[0].arrivalTime = 2;
    a[1].arrivalTime = 0;
    a[2].arrivalTime = 1;
    a[3].arrivalTime = 3;
    a[4].arrivalTime = 5;

    a[0].burstTime = 13;
    a[1].burstTime = 1;
    a[2].burstTime = 2;
    a[3].burstTime = 16;
    a[4].burstTime = 7;
    execute(n);
    output(n);

    return 0;
}

