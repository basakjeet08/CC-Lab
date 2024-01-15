#include <stdio.h>

struct Process{
    int arrivalTime , burstTime , completionTime , waitingTime , pid;
};


// This function takes the input of all the process
void getProcesses(struct Process process[] , int number){
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

void swapProcess(struct Process process[] , int index1 , int index2){
    struct Process temp = process[index1];
    process[index1] = process[index2];
    process[index2] = temp;
}

// This function schedules / sorts the processes according to the scheduing Algorithm
void sortProcess(struct Process process[] , int number){
    for(int i = 0 ; i < number ; i++){
        int lowest = i;
        for(int j = i + 1 ; j < number ; j++)
            if(process[j].arrivalTime < process[lowest].arrivalTime)
                lowest = j;
        
        swapProcess(process , i , lowest);
    }
}

// This process runs the process and computes the average Waiting Time
double runProcess(struct Process process[] , int number){
    int currentTime = 0;
    int totalWaitingTime = 0;


    for(int i = 0 ; i < number ; i++){
        if(process[i].arrivalTime >= currentTime)
            currentTime = process[i].arrivalTime;
        else{
            int lowest = i;
            int j = i + 1;

            while(process[j].arrivalTime <= currentTime){
                if(process[j].burstTime < process[i].burstTime)
                    lowest = j;
                j++;
            }
            swapProcess(process , lowest , i);
            process[i].waitingTime = currentTime - process[i].arrivalTime;
        }
        
        totalWaitingTime += process[i].waitingTime;
        process[i].completionTime = process[i].burstTime + currentTime;
        currentTime = process[i].completionTime;
    }
    return (double)totalWaitingTime / number;
}


// This process displays all the process data along with the average waiting Time
void showProcess(struct Process process[] , int number , double avgWaitingTime){
    printf("Process ID \t Arrival Time \t Burst Time \t Waiting Time \t Completion Time\n");

    for(int i = 0 ; i < number ; i++){
        struct Process curr = process[i];
        printf("%4d \t\t %4d \t\t %4d \t\t %4d \t\t %4d \n" ,curr.pid , curr.arrivalTime , curr.burstTime , curr.waitingTime , curr.completionTime);
    }

    printf("\n\nAverage Waiting Time : %f" , avgWaitingTime);
}

int main(){
    int number; // Number of Process to be entered

    printf("Enter the Number of Process : ");
    scanf("%d" , &number);

    struct Process process[number]; // Initializing the Processes

    getProcesses(process , number); // Getting the Process input
    sortProcess(process , number); // Sorting the process according to Arrival Time

    // Running the process to get the completion and waiting time. 
    double avgWaitingTime = runProcess(process , number);
    
    showProcess(process , number , avgWaitingTime); // Displays all the process data

    return 0;
}