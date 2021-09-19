#include <bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include <stdlib.h>

using namespace std;

int n = 5, k = 0, f = 0, r = 0;

struct node{
    int pid;
    int burstTime;
    int arrivalTime;
    int restime = 0;
    int ctime = 0;
    int wtime = 0;
} a[1000], b[1000], c[1000];



bool btimeSort(node a, node b){
    return a.burstTime < b.burstTime;
}

bool btimeOppSort(node a,node b){
    if(a.burstTime!=b.burstTime)
        return a.burstTime > b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

bool arrivalTimeSort(node a, node b){
    return a.arrivalTime < b.arrivalTime;
}

void output(int rtime, int tArray[5]) {
    float averageWaitingTime = 0;
    float averageResponseTime = 0;

    int i, j;

    cout<<"\nPreemptive SJF Scheduling:";
    for (i = 0; i < k; i++){
        if(i != k) {
            cout << " --> P" << c[i].pid;
        }
    }

    cout << "\n\nGantt Chart:\n\n";

    rtime = 0;
    for (i = 0; i < k; i++){
        if(i != k) {
            if (c[i].pid == 'i') {
                cout<<"| "<<"Free"<< "  ";
            }
            else {
                cout<<"|  "<<'P'<< c[i].pid << "   ";
            }
        }
        rtime += c[i].burstTime;

        for(j = 0; j < n; j++){
            if(a[j].pid == c[i].pid)
                a[j].ctime = rtime;
        }
    }
    cout<<"\n";

    rtime = 0;
    int z = 0, stime[100];
    vector<char> p;

    for (i = 0; i < k+1; i++){
        if (find(p.begin(), p.end(), c[i].pid) == p.end()) {
            p.push_back(c[i].pid);
            stime[z] = rtime;
            z++;
        }

        cout << rtime << "\t";
        tArray[i] = rtime;
        rtime += c[i].burstTime;
    }
    cout<<"\n\n";


    int startTime;
    cout<<"Process  Arrival Time\t  Burst Time\tStart Time    End Time\t Waiting Time\tResponse Time\n";
    for (i = 0; i < n && a[i].pid != 'i'; i++){
        if(a[i].pid == '\0')
            break;

        for (int z = 0; z < n; z++) {
            if ( p[z] == a[i].pid )
                startTime = stime[z];
        }

        cout << 'P' << a[i].pid << "\t\t";
        cout << a[i].arrivalTime << "\t\t";
        cout << a[i].burstTime << "\t  ";
        cout << startTime << "\t\t";
        cout << a[i].ctime << "\t\t";
        cout << a[i].wtime + a[i].ctime - rtime << "\t\t";
        cout << a[i].restime - a[i].arrivalTime << "\t\t";
        cout << "\n";

        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;
        averageResponseTime += a[i].restime - a[i].arrivalTime;
    }

    cout<<"\nAverage Response time: "<<(float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
}

void execute(int qt){
    int q;

    sort(a, a+n, arrivalTimeSort);



    int ttime = 0, i;
    int alltime = 0;
    int j, tArray[n];

    bool moveLast = false;

    for(i = 0; i < n; i++){
        alltime += a[i].burstTime;

    }

    alltime += a[0].arrivalTime;

    for(i = 0; ttime <= alltime;){
        j = i;
        while(a[j].arrivalTime <= ttime && j != n){

            b[r]=a[j];
            j++;
            r++;
        }

        if(r == f) {
            c[k].pid = 'i';
            c[k].burstTime = a[j].arrivalTime - ttime;
            c[k].arrivalTime = ttime;
            ttime += c[k].burstTime;
            k++;
            continue;
        }

        i = j;
        if(moveLast == true) {

            sort(b+f, b+r, btimeSort);

        }

        j = f;
        if(b[j].burstTime > qt){
            c[k] = b[j];
            c[k].burstTime = qt;
            k++;
            b[j].burstTime = b[j].burstTime - qt;
            ttime += qt;

            moveLast = true;

            for(q = 0; q < n; q++){
                if(b[j].pid != a[q].pid){
                    a[q].wtime += qt;
                }
            }
        }
        else{
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].burstTime;
            moveLast = false;
            for(q = 0; q < n; q++){
                if(b[j].pid != a[q].pid){
                    a[q].wtime += b[j].burstTime;
                }
            }
        }

        if(f == r && i >= n)
            break;
    }


    tArray[i] = ttime;
    ttime += a[i].burstTime;

    for(i = 0; i < k-1; i++){
        if(c[i].pid == c[i+1].pid){
            c[i].burstTime += c[i+1].burstTime;

            for(j = i+1; j<k-1; j++)
                c[j] = c[j+1];

            k--;
            i--;
        }
    }

    int rtime = 0;

    for(j = 0; j < n; j++){
        rtime = 0;
        for(i = 0; i < k; i++){
            if(c[i].pid == a[j].pid){
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].burstTime;
        }
    }

    output(rtime, tArray);
}

int main(){

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

    for(int i = 0; i < n; i++) {
        a[i].wtime = -a[i].arrivalTime + 1;
    }
    execute(1);

    return 0;
}
