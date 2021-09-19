#include<iostream>
#include<algorithm>

using namespace std;

int k = 0, f = 0, r = 0;

struct node{
    char pname;
    int burstTime;
    int arrivalTime;
    int restime=0;
    int ctime=0;
    int wtime=-1;
} a[100], b[100], c[100];


bool btimeSort(node a,node b){
    return a.burstTime < b.burstTime;
}

bool atimeSort(node a,node b){
    return a.arrivalTime < b.arrivalTime;
}

void printResults(int rtime, int tArray[5], int nop){
    int i, j;

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout<<"\nRound Robin (quantum = 4) Scheduling:";
    for (i = 0; i < k + 1 && i < 20; i++){
        if(i != k)
            cout << " -> P" << c[i].pname;
    }

    cout << "\n\nGantt Chart:\n\n";

    rtime = 0;
    for (i = 0; i < k + 1 && i < 20; i++){
        if(i != k)
            cout<<"|   "<<'P'<< c[i].pname << "   ";
        rtime += c[i].burstTime;
        for(j = 0; j < 6; j++){
            if(a[j].pname == c[i].pname)
                a[j].ctime = rtime;
        }
    }
    cout<<"\n";

    rtime = 0;
    for (i = 0; i < k+1 && i < 20; i++){
        if (rtime >= 10) {
            cout << rtime << "       ";
        }
        else {
            cout << rtime << "        ";
        }

        tArray[i] = rtime;
        rtime += c[i].burstTime;
    }

    cout<<"\n";
    cout<<"\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tResponse Time\n";

    int startTime;
    for (i = 0; i < 6 && i < nop && a[i].pname != 'i'; i++){
        if(a[i].pname == '\0')
            break;
        if (i == 0) {
            startTime = a[i].arrivalTime;
        }
        else {
            startTime = tArray[i];
        }

        cout << a[i].pname << "\t\t";
        cout << a[i].arrivalTime << "\t\t";
        cout << a[i].burstTime << "\t\t";
        cout << startTime << "\t\t";
        cout << a[i].ctime << "\t\t";
        cout << a[i].wtime + a[i].ctime - rtime << "\t\t";
        cout << a[i].restime - a[i].arrivalTime << "\t\t";
        cout <<"\n";

        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;
        averageResponseTime += a[i].restime - a[i].arrivalTime;
    }

    cout<<"\nAverage Response time: " << (float)averageResponseTime/(float)nop << endl;
    cout<<"Average Waiting time: " << (float)averageWaitingTime/(float)nop << endl;
}

void execute(int nop, int qt){
    int n = nop, q;

    sort(a, a+n, atimeSort);

    int ttime = 0, i;
    int j, tArray[n];
    int alltime = 0;

    bool moveLast = false;

    for(i = 0; i < n; i++){
        alltime += a[i].burstTime;
    }

    alltime += a[0].arrivalTime;

    for(i = 0; ttime <= alltime;){
        j = i;
        while(a[j].arrivalTime <= ttime && j != n){
            b[r] = a[j];
            j++;
            r++;
        }

        if(r == f) {
            c[k].pname = 'i';
            c[k].burstTime = a[j].arrivalTime - ttime;
            c[k].arrivalTime = ttime;
            ttime += c[k].burstTime;
            k++;
            continue;
        }

        i = j;
        if(moveLast == true){
            b[r] = b[f];
            f++;
            r++;
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
                if(b[j].pname != a[q].pname){
                    a[q].wtime += qt;
                }
            }
        }
        else {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].burstTime;
            moveLast = false;
            for(q = 0; q < n; q++){
                if(b[j].pname != a[q].pname){
                    a[q].wtime += b[j].burstTime;
                }
            }
        }
        if(f == r && i >= n)
            break;
    }

    tArray[i] = ttime;
    ttime += a[i].burstTime;

    int rtime = 0;
    for(j = 0; j < n && j < 6; j++){
        rtime = 0;
        for(i = 0; i < k; i++){
            if(c[i].pname == a[j].pname){
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].burstTime;
        }
    }

    printResults(rtime, tArray, nop);
}

int main(){
    a[0].pname = '1';
    a[1].pname = '2';
    a[2].pname = '3';
    a[3].pname = '4';
    a[4].pname = '5';

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

    for(int i = 0; i < 5; i++){
        a[i].wtime =- a[i].arrivalTime;
    }
    int numberOfProcess = 5;
    int quantam = 4;

    execute(numberOfProcess, quantam);

    return 0;
}
