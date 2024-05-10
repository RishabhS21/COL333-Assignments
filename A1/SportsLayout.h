#ifndef SPORTSLAYOUT_H
#define	SPORTSLAYOUT_H

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SportsLayout{

    private:
    int z,l;
    int** T;
    int **N;
    float time;
    int *mapping;
    int *min_mapping;

    public:
    SportsLayout(string inputfilename);

    bool check_output_format();

    // void readOutputFile(string output_filename);
    
    long long cost_fn();
    long long cost_fn2();
    void write_to_file(string outputfilename);

    void readInInputFile(string inputfilename);

    int randomInt(int min_val, int max_val);
    vector<int> generate_random();
    int updated_cost1(long long prev_cost, int new_l, int prev_l, int z);
    int updated_cost2(long long prev_cost, int l1, int l2, int z1, int z2);
    void compute_allocation();

};


#endif