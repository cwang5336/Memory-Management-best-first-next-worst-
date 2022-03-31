#include <iostream>
#include <string>
#include <list>
using namespace std;

class Process
{
public:
    int id;
    int size;
    string status = "waiting";
    int particionID;
    int waste = -1;
};

class Particion
{
public:
    int id;
    int size;
    bool partition_status = false;
    int processID;
};

void run()
{
    int num_processes;
    int num_partitions;

    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of partitions: ";
    cin >> num_partitions;

    Process process[num_processes];
    Particion partition[num_partitions];

    cout << endl;

    for (int i = 0; i < num_processes; i++)
    {
        process[i].id = i + 1;
        cout << "Enter the process size: ";
        cin >> process[i].size;
        process[i].status = "waiting";
        process[i].particionID = -1;
        process[i].waste = -1;
    }
    cout << endl;

    for (int i = 0; i < num_partitions; i++)
    {

        partition[i].id = i + 1;
        cout << "Enter the partition size: ";
        cin >> partition[i].size;
        partition[i].partition_status = false;
        partition[i].processID = -1;
    }

    runCases(process, partition, num_processes, num_partitions);
}


void runCases(Process process[], Particion partition[], int num_processes, int num_partitions)
{
    firstFit(process, num_processes, partition, num_partitions);
    nextFit(process, num_processes, partition, num_partitions);
    bestFit(process, num_processes, partition, num_partitions);
    worstFit(process, num_processes, partition, num_partitions);
}

void print(Process process[], int num_processes, string type)
{
    cout << "\n"
         << type << endl;
    cout << "Process ID\tProcess Size\tProcess Status\tPartition ID\tWaste\n";
    int totalWaste = 0;
    for (int i = 0; i < num_processes; i++)
    {
        cout << process[i].id << "\t\t\t" << process[i].size << "\t\t\t\t" << process[i].status << "\t\t\t";
        if (process[i].particionID == -1)
        {
            cout << "N/A\t\t";
        }
        else
        {
            cout << process[i].particionID << "\t\t\t\t";
        }
        if (process[i].waste == -1)
        {
            cout << "\t\tN/A\n";
        }
        else
        {
            cout << process[i].waste << "\n";
            totalWaste += process[i].waste;
        }
    }
    cout << "Total Waste: " << totalWaste << endl;
}

void variableReset(Process process[], int num_processes, Particion partition[], int num_partitions)
{
    for (int i = 0; i < num_processes; i++)
    {
        process[i].status = "waiting";
        process[i].particionID = -1;
        process[i].waste = -1;
    }
    for (int i = 0; i < num_partitions; i++)
    {
        partition[i].partition_status = false;
        partition[i].processID = -1;
    }
}

void firstFit(Process process[], int num_processes, Particion partition[], int num_partitions)
{
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_partitions; j++)
        {
            if (partition[j].partition_status == false && process[i].size <= partition[j].size)
            {
                process[i].particionID = partition[j].id;
                process[i].status = "running";
                partition[j].partition_status = true;
                partition[j].processID = process[i].id;
                process[i].waste = partition[j].size - process[i].size;
                break;
            }
        }
    }
    print(process, num_processes, "First Fit");
    variableReset(process, num_processes, partition, num_partitions);
}

void nextFit(Process process[], int num_processes, Particion partition[], int num_partitions)
{
    int j = 0;
    int partition_index = 0;
    for (int i = 0; i < num_processes; i++)
    {
        while (j < num_partitions)
        {
            if (partition[j].size >= process[i].size && !partition[j].partition_status)
            {
                process[i].particionID = partition[j].id;
                process[i].status = "running";
                process[i].waste = partition[j].size - process[i].size;
                partition[j].partition_status = true;
                partition_index++;
                break;
            }
            if (partition_index > num_partitions)
            {
                break;
            }
            j++;
        }
    }
    print(process, num_processes, "Next Fit");
    variableReset(process, num_processes, partition, num_partitions);
}

void bestFit(Process process[], int num_processes, Particion partition[], int num_partitions)
{
    for (int i = 0; i < num_processes; i++)
    {
        int bestFitIndex = -1;
        for (int j = 0; j < num_partitions; j++)
        {
            if (partition[j].size >= process[i].size && !partition[j].partition_status)
            {
                if (bestFitIndex == -1)
                {
                    bestFitIndex = j;
                }
                else if (partition[j].size < partition[bestFitIndex].size)
                {
                    bestFitIndex = j;
                }
            }
        }
        if (bestFitIndex != -1)
        {
            process[i].particionID = partition[bestFitIndex].id;
            process[i].status = "running";
            process[i].waste = partition[bestFitIndex].size - process[i].size;
            partition[bestFitIndex].partition_status = true;
        }
    }
    print(process, num_processes, "Best Fit");
    variableReset(process, num_processes, partition, num_partitions);
}

void worstFit(Process process[], int num_processes, Particion partition[], int num_partitions)
{
    for (int i = 0; i < num_processes; i++)
    {
        int worstFitIndex = -1;
        for (int j = 0; j < num_partitions; j++)
        {
            if (partition[j].size >= process[i].size && !partition[j].partition_status)
            {
                if (worstFitIndex == -1)
                {
                    worstFitIndex = j;
                }
                else if (partition[j].size > partition[worstFitIndex].size)
                {
                    worstFitIndex = j;
                }
            }
        }
        if (worstFitIndex != -1)
        {
            process[i].particionID = partition[worstFitIndex].id;
            process[i].status = "running";
            process[i].waste = partition[worstFitIndex].size - process[i].size;
            partition[worstFitIndex].partition_status = true;
        }
    }
    print(process, num_processes, "Worst Fit");
    variableReset(process, num_processes, partition, num_partitions);
}