#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int arrivalTime , burstTime , completionTime , waitingTime , pid;
}Process;

// This function takes the input of all the process
void getProcesses(Process process[] , int number){
    for(int i = 0 ; i < number ; i++){
        printf("Process %d \n" , i + 1);
        printf("Arrival Time : ");
        scanf("%d" , &process[i].arrivalTime);
        printf("Burst Time : ");
        scanf("%d" , &process[i].burstTime);
        process[i].pid = i + 1;
        process[i].waitingTime = 0;
        process[i].completionTime = 0;
        printf("\n\n");
    }
}


void minimax(Process process[] , int num){
    int max = -1;
    int maxId = -1;
    
    printf("Min max Scheduling Started !! \n");
    for(int i = 0 ; i < num ; i++){
        max = -1;
        maxId = -1;

        for(int j = 0 ; j < num ; j++)
            if(process[j].burstTime > max){
                max = process[j].burstTime;
                maxId = j;
            }

        printf("Process %d with Burst Time %d is Started \n" , process[maxId].pid , process[maxId].burstTime);
        process[maxId].burstTime = -1;
    }
}


void minmin(Process process[] , int num){
    int min = process[0].burstTime;
    int minId = 0;

    printf("Min Min Scheduling Started !! \n");
    for(int i = 0 ; i < num ; i++){
        min = process[i].burstTime;
        minId = i;

        for(int j = 0 ; j < num ; j++)
            if(process[j].burstTime < min){
                min = process[j].burstTime;
                minId = j;
            }

        printf("Process %d with Burst Time %d is Started \n" , process[minId].pid , process[minId].burstTime);
        process[minId].burstTime = __INT16_MAX__;
    }
}

int main(){
    int number; // Number of Process to be entered

    printf("Enter the Number of Process : ");
    scanf("%d" , &number);

    Process process[number]; // Initializing the Processes

    getProcesses(process , number); // Getting the Process input
    minimax(process , number);
    // minmin(process , number);
    return 0;
}