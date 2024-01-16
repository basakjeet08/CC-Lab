#include <stdio.h>

struct Process{
    int burstTime , completionTime , waitingTime , pid , remainingTime , lastRun;
};

const int timeQuantum = 2;

// This function takes the input of all the process
int getProcesses(struct Process process[] , int number){

    int totalTime = 0;
    for(int i = 0 ; i < number ; i++){
        printf("Process %d \n" , i + 1);
        printf("Burst Time : ");
        scanf("%d" , &process[i].burstTime);
        printf("\n\n");

        process[i].pid = i + 1;
        process[i].waitingTime = 0;
        process[i].completionTime = 0;
        process[i].remainingTime = process[i].burstTime;
        process[i].lastRun = 0;
        totalTime += process[i].burstTime;
    }
    return totalTime;
}


// This process runs the process and computes the average Waiting Time
double runProcess(struct Process process[] , int number , int totalTime){
    int currentTime = 0;
    int totalWaitingTime = 0;
    int i = 0;


    while(currentTime < totalTime){
        if(process[i].remainingTime == 0){
            i = (i + 1) % number;
            continue;
        }

        if(process[i].remainingTime < timeQuantum){
            currentTime += process[i].remainingTime;
            process[i].remainingTime = 0;
        }else if(process[i].remainingTime >= timeQuantum){
            currentTime += timeQuantum;
            process[i].remainingTime -= timeQuantum;
            process[i].lastRun = currentTime;
        }

        if(process[i].remainingTime == 0){
            process[i].completionTime = currentTime;
            process[i].waitingTime = currentTime - process[i].burstTime;
            totalWaitingTime += process[i].waitingTime;
        }
        i = (i + 1) % number;
    }

    return (double)totalWaitingTime / number;
}


// This process displays all the process data along with the average waiting Time
void showProcess(struct Process process[] , int number , double avgWaitingTime){
    printf("Process ID \t Burst Time \t Waiting Time \t Completion Time\n");

    for(int i = 0 ; i < number ; i++){
        struct Process curr = process[i];
        printf("%4d \t\t %4d \t\t %4d \t\t %4d \n" ,curr.pid , curr.burstTime , curr.waitingTime , curr.completionTime);
    }

    printf("\n\nAverage Waiting Time : %f" , avgWaitingTime);
}

int main(){
    int number; // Number of Process to be entered

    printf("Enter the Number of Process : ");
    scanf("%d" , &number);

    struct Process process[number]; // Initializing the Processes

    int totalTime = getProcesses(process , number); // Getting the Process input

    // Running the process to get the completion and waiting time. 
    double avgWaitingTime = runProcess(process , number , totalTime);
    
    showProcess(process , number , avgWaitingTime); // Displays all the process data

    return 0;
}