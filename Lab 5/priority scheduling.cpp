#include <bits/stdc++.h>

using namespace std;

#define totalprocess 5


struct process
{
int at,bt,pr,pid;
};

process proc[50];


bool comp(process a,process b)
{
if(a.at == b.at)
{
return a.pr<b.pr;
}
else
{
    return a.at<b.at;
}
}


void get_wt_time(int wt[])
{

int service[50];

service[0] = proc[0].at;
wt[0]=0;


for(int i=1;i<totalprocess;i++)
{
service[i]=proc[i-1].bt+service[i-1];

wt[i]=service[i]-proc[i].at;


    if(wt[i]<0)
    {
    wt[i]=0;
    }
}

}

void get_tat_time(int tat[],int wt[])
{


for(int i=0;i<totalprocess;i++)
{
    tat[i]=proc[i].bt+wt[i];
}

}

void findgc()
{

int wt[50],tat[50];

double wavg=0,tavg=0;


get_wt_time(wt);

get_tat_time(tat,wt);

int stime[50],ctime[50];

stime[0] = proc[0].at;
ctime[0] = stime[0]+tat[0];


for(int i=1;i<totalprocess;i++)
    {
        stime[i]=ctime[i-1];
        ctime[i]=stime[i]+tat[i]-wt[i];
    }

cout<<"Process_no\tStart_time\tFinish_time\tResponse_Time\tWaiting_Time"<<endl;



for(int i=0;i<totalprocess;i++)
    {
        wavg += wt[i];
        tavg += tat[i];

        cout<<proc[i].pid<<"\t\t"
            <<stime[i]<<"\t\t"
            <<ctime[i]<<"\t\t"
            <<ctime[i]-proc[i].at<<"\t\t\t"
            <<wt[i]<<endl;
    }


    cout<<"Average waiting time is : ";
    cout<<wavg/(float)totalprocess<<endl;
    cout<<"average response time : ";
    cout<<tavg/(float)totalprocess<<endl;

}

int main()
{
int arrivaltime[] = { 2, 0, 1, 3, 5 };
int bursttime[] = { 13, 1, 2, 16, 7 };
int priority[] = { 3, 1, 3, 4, 2 };
int choice;

cout << "Select a scheduling process.."<< endl;
cin >> choice;

    for(int i=0;i<totalprocess;i++)
    {
    proc[i].at=arrivaltime[i];
    proc[i].bt=bursttime[i];
    proc[i].pr=priority[i];
    proc[i].pid=i+1;
    }

    sort(proc,proc+totalprocess,comp);

    cout<< "Order in which processes gets executed \n";
    for (int  i = 0 ; i <  totalprocess; i++)
    {
        cout << proc[i].pid ;
        if(i < totalprocess-1)
            cout << "->";

    }

        cout << "\n";


    findgc();



    return 0;
}
