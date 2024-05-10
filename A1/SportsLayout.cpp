#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <bits/stdc++.h>

using namespace std;

#include "SportsLayout.h"

SportsLayout::SportsLayout(string inputfilename)
{

    readInInputFile(inputfilename);
    mapping = new int[z+1];
    min_mapping = new int[z+1];
}

bool SportsLayout::check_output_format()
{

    vector<bool> visited(l, false);
    for (int i = 0; i < z; i++)
    {
        if ((min_mapping[i] >= 1 && min_mapping[i] <= l))
        {
            if (!visited[min_mapping[i] - 1])
                visited[min_mapping[i] - 1] = true;
            else
            {
                cout << "Repeated locations, check format\n";
                return false;
            }
        }
        else
        {
            cout << "Invalid location, check format\n";
            return false;
        }
    }

    return true;
}
void SportsLayout::readInInputFile(string inputfilename)
{
    fstream ipfile;
    ipfile.open(inputfilename, ios::in);
    if (!ipfile)
    {
        cout << "No such file\n";
        exit(0);
    }
    else
    {

        ipfile >> time;
        ipfile >> z;
        ipfile >> l;

        if (z > l)
        {
            cout << "Number of zones more than locations, check format of input file\n";
            exit(0);
        }

        int **tempT;
        int **tempN;

        tempT = new int *[l];
        for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];

        tempN = new int *[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for (int i = 0; i < z; i++)
        {
            for (int j = 0; j < z; j++)
                ipfile >> tempN[i][j];
        }

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < l; j++)
                ipfile >> tempT[i][j];
        }

        ipfile.close();

        T = tempT;
        N = tempN;
    }
}

void SportsLayout::write_to_file(string outputfilename)
{

    // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open())
    {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for (int i = 1; i <= z; i++)
        outputFile << min_mapping[i] << " ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;
}

int SportsLayout::randomInt(int min_val, int max_val) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    return dis(gen);
}
vector<int> SportsLayout::generate_random()
{
    vector<int> reverse_map(l+1, -1);
    for(int i=1; i<=z; i++){
        int p = randomInt(1, l);
        while(reverse_map[p]!=-1){
            p = randomInt(1, l);
        }
        reverse_map[p] = i;
        mapping[i] = p;
    }
    return reverse_map;
}
long long SportsLayout::cost_fn()
{

    long long cost = 0;

    for (int i = 1; i <= z; i++)
    {
        for (int j = 1; j <= z; j++)
        {
            cost += (long long)N[i-1][j-1] * (long long)T[mapping[i] - 1][mapping[j] - 1];
        }
    }

    return cost;
}
long long SportsLayout::cost_fn2()
{

    long long cost = 0;

    for (int i = 1; i <= z; i++)
    {
        for (int j = 1; j <= z; j++)
        {
            cost += (long long)N[i-1][j-1] * (long long)T[min_mapping[i] - 1][min_mapping[j] - 1];
        }
    }

    return cost;
}
int SportsLayout::updated_cost1(long long prev_cost, int new_l, int prev_l, int zone){
    long long cost = prev_cost;
    for(int i=1; i<=z; i++){
        if(i != zone){
            cost -= ((long long)(N[i-1][zone-1]+N[zone-1][i-1]) * (long long)T[prev_l-1][mapping[i]-1]);
            cost += ((long long)(N[i-1][zone-1]+N[zone-1][i-1]) * (long long)T[new_l-1][mapping[i]-1]);
        }
    }
    return cost;
}

int SportsLayout::updated_cost2(long long prev_cost, int l1, int l2, int z1, int z2){
    long long cost = prev_cost;
    for(int i=1; i<=z; i++){
        if(i!=z1 && i!=z2){
            cost -= ((long long)(N[i-1][z1-1] + N[z1-1][i-1]) * (long long)T[l1-1][mapping[i]-1] + (long long)(N[i-1][z2-1] + N[z2-1][i-1]) * (long long)T[l2-1][mapping[i]-1]);
            cost += ((long long)(N[i-1][z1-1] + N[z1-1][i-1]) * (long long)T[l2-1][mapping[i]-1] + (long long)(N[i-1][z2-1] + N[z2-1][i-1]) * (long long)T[l1-1][mapping[i]-1]);
        }
    }
    return cost;
}


void SportsLayout::compute_allocation()
{
    auto startTime = chrono::high_resolution_clock::now();
    vector<int> reverse_map(l+1, -1);
    reverse_map = generate_random();
    long long cost = cost_fn();
    long long min_cost = cost;
    for(int i=1; i<=z; i++){
        min_mapping[i] = mapping[i];
    }
    int t=1;
    while (true){
        bool flag = false;
        for (int i = 1; i <= l; i++){
            for (int j = i+1; j <= l; j++){
                long long new_cost1 = 0;
                if (reverse_map[i] == -1 && reverse_map[j] == -1){
                    continue;
                }
                else if(reverse_map[i]==-1){
                    mapping[reverse_map[j]]=i;
                    new_cost1 = updated_cost1(cost, i, j, reverse_map[j]);
                    swap(reverse_map[i], reverse_map[j]);
                }
                else if(reverse_map[j]==-1){
                    mapping[reverse_map[i]]=j;
                    new_cost1 = updated_cost1(cost, j, i, reverse_map[i]);
                    swap(reverse_map[i], reverse_map[j]);
                }
                else{
                    swap(mapping[reverse_map[i]], mapping[reverse_map[j]]);
                    new_cost1 = updated_cost2(cost, i, j, reverse_map[i], reverse_map[j]);
                    swap(reverse_map[i], reverse_map[j]);
                }
                if (new_cost1 < cost){
                    cost = new_cost1;
                    if(cost < min_cost){
                        min_cost = cost;
                        for(int i=1; i<=z; i++){
                            min_mapping[i] = mapping[i];
                        }
                        t++;
                    }
                    flag = true;
                    break;
                }
                if(reverse_map[i]==-1){
                    mapping[reverse_map[j]]=i;
                    swap(reverse_map[i], reverse_map[j]);
                }
                else if(reverse_map[j]==-1){
                    mapping[reverse_map[i]]=j;
                    swap(reverse_map[i], reverse_map[j]);
                }
                else{
                    swap(mapping[reverse_map[i]], mapping[reverse_map[j]]);
                    swap(reverse_map[i], reverse_map[j]);
                }
            }
            if (flag) break;
        }

        if (!flag){
            reverse_map = generate_random();
            cost = cost_fn();
        }
        auto currentTime = chrono::high_resolution_clock::now();
        double elapsedSeconds = chrono::duration_cast<chrono::duration<double> >(currentTime - startTime).count();
        if (elapsedSeconds > time*60) {
            // cout<<"Timeout : "<<elapsedSeconds<<endl;
            break;
        }
    }
}
