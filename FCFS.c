#include <stdio.h>

struct table
{
    int PID[10], AT[10], BT[10], CT[10], TAT[10], WT[10], RT[10];
    double avgTAT, avgWT;
} myTable;

struct ganttChart
{
    int PID[10], AT[10], CT[10];
} gantt;

void sortTable(int noOfProcess)
{
    for (int i = 0; i < noOfProcess - 1; i++)
    {
        for (int j = i + 1; j < noOfProcess; j++)
        {
            if (myTable.AT[j] < myTable.AT[i])
            {
                myTable.AT[i] += myTable.AT[j];
                myTable.AT[j] = myTable.AT[i] - myTable.AT[j];
                myTable.AT[i] -= myTable.AT[j];

                myTable.BT[i] += myTable.BT[j];
                myTable.BT[j] = myTable.BT[i] - myTable.BT[j];
                myTable.BT[i] -= myTable.BT[j];

                myTable.PID[i] += myTable.PID[j];
                myTable.PID[j] = myTable.PID[i] - myTable.PID[j];
                myTable.PID[i] -= myTable.PID[j];
            }
        }
    }
}

void insertData(int noOfProcess)
{
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i + 1);
        scanf("%d", &myTable.AT[i]);
        myTable.PID[i] = i + 1;
        printf("Enter Process %d Burst Time: ", i + 1);
        scanf("%d", &myTable.BT[i]);
    }
}

void displayData(int noOfProcess)
{
    printf("\nPID\t| AT\t| BT\t|\n");
    printf("-------------------------\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("P%d\t| %d\t| %d\t|\n", myTable.PID[i], myTable.AT[i], myTable.BT[i]);
    }
    printf("\n\n");
}

void drawGanttChart(int noOfProcess)
{
    int prevCompletionTime = 0;
    for (int i = 0; i < noOfProcess; i++)
    {
        gantt.PID[i] = myTable.PID[i];
        if (myTable.AT[i] <= prevCompletionTime)
        {
            gantt.AT[i] = prevCompletionTime;
        }
        else
        {
            gantt.AT[i] = myTable.AT[i];
        }
        gantt.CT[i] = gantt.AT[i] + myTable.BT[i];
        prevCompletionTime = gantt.CT[i];
    }

    // Calculate CT TAT WT
    myTable.avgTAT = 0;
    myTable.avgWT = 0;
    for (int i = 0; i < noOfProcess; i++)
    {
        myTable.CT[i] = gantt.CT[i];
        myTable.TAT[i] = myTable.CT[i] - myTable.AT[i];
        myTable.WT[i] = myTable.TAT[i] - myTable.BT[i];
        myTable.RT[i] = gantt.AT[i] - myTable.AT[i];
        myTable.avgTAT += myTable.TAT[i];
        myTable.avgWT += myTable.WT[i];
    }
    myTable.avgTAT /= noOfProcess;
    myTable.avgWT /= noOfProcess;
    printf("\nGantt Chart\n");
    for (int i = 0; i < noOfProcess; i++)
        printf("-------------");
    printf("\n");
    prevCompletionTime = 0;
    for (int i = 0; i < noOfProcess; i++)
    {
        if (gantt.AT[i] > prevCompletionTime)
        {
            printf(" //\t| P%d\t|", gantt.PID[i]);
        }
        else
        {
            printf(" P%d\t|", gantt.PID[i]);
        }
        prevCompletionTime = gantt.CT[i];
    }
    printf("\n");
    for (int i = 0; i < noOfProcess; i++)
        printf("-------------");
    printf("\n");
    prevCompletionTime = 0;
    for (int i = 0; i < noOfProcess; i++)
    {
        if (i == 0 && gantt.AT[i] > prevCompletionTime)
        {
            printf("%d\t%d\t%d", prevCompletionTime, gantt.AT[i], gantt.CT[i]);
        }
        else if (gantt.AT[i] > prevCompletionTime)
        {
            printf("\t%d\t%d", gantt.AT[i], gantt.CT[i]);
        }

        else if(gantt.AT[i] == 0){
            printf("%d\t%d", gantt.AT[i], gantt.AT[i] + myTable.BT[i]);
        }
        else
        {
            if (gantt.AT[i] == prevCompletionTime)
            {
                printf("\t%d", gantt.CT[i]);
            }
            else
            {
                printf("\t%d", gantt.CT[i]);
            }
        }
        prevCompletionTime = gantt.CT[i];
    }
    printf("\n");
}

void displayFullData(int noOfProcess)
{
    printf("\nPID\t| AT\t| BT\t| CT\t| TAT\t| WT\t| RT\t|\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t|\n",
               myTable.PID[i], myTable.AT[i], myTable.BT[i], myTable.CT[i], myTable.TAT[i], myTable.WT[i], myTable.RT[i]);
    }
    printf("\nAverage Turn Around Time = %lf\n", myTable.avgTAT);
    printf("Average Waiting Time = %lf\n", myTable.avgWT);
    printf("\n\n\n");
}

int main()
{
    int noOfProcess;
    printf("Enter Number of Process: ");
    scanf("%d", &noOfProcess);
    insertData(noOfProcess);
    sortTable(noOfProcess);
    displayData(noOfProcess);
    drawGanttChart(noOfProcess);
    displayFullData(noOfProcess);
}
