#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

#include "SportsLayout.h"

using namespace std;

int main(int argc, char** argv )
{
    // auto startTime = chrono::high_resolution_clock::now();

     // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    string outputfilename ( argv[2] );
    
    SportsLayout *s  = new SportsLayout( inputfilename );
    s->compute_allocation();
    s->write_to_file(outputfilename);

    long long cost = s->cost_fn2 ();
    // long long cost2 = s->cost_fn ();
    cout<< "cost:"<<cost<<endl;

    // auto currentTime = chrono::high_resolution_clock::now();
    // double elapsedSeconds = chrono::duration_cast<chrono::duration<double> >(currentTime - startTime).count();
    // cout<<"Total time : "<<elapsedSeconds<<"\n";
    return 0;

}