#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]) {
    auto start_time = chrono::high_resolution_clock::now();
    const char* inputFileName = argv[1];
    ifstream file(inputFileName);
    vector<string> lines;
    string line;
    
    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    int n, m;
    stringstream firstLine(lines[0]);
    firstLine >> n >> m;
    vector<tuple<int, int>> edges;
    // if (m == (n*(n-1))/2){
    //     string x(inputFileName);
    //     x = x.substr(0,x.length()-5);
    //     x+="mapping";
    //     ofstream outputFile1(x);
    //     outputFile1 << "#1" << endl;
    //     for (int i = 0; i < n; i++) {
    //         if (i!=n-1){
    //         outputFile1 << i+1 << " ";
    //         }
    //         else{
    //             outputFile1 << i+1;
    //         }
    //     }
    //     return 0;
    // }
    for (int i = 1; i < lines.size(); i++) {
        int u, v;
        stringstream ss(lines[i]);
        ss >> u >> v;
        edges.push_back(make_tuple(u, v));
    }

    vector<vector<bool>> adj_mat(n + 1, vector<bool>(n + 1, false));
    
    for (auto edge : edges) {
        int u, v;
        tie(u, v) = edge;
        adj_mat[u][v] = true;
        adj_mat[v][u] = true;
    }

    int k;
    int lo = 0;
    int hi = n;
    int maxK = -1;
    vector<int> clique;

    while (lo <= hi) {
        k = (lo + hi) / 2;
        vector<vector<int>> clauses;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == n && j == n) {
                    break;
                }
                if (adj_mat[i][j]) {
                    clauses.push_back({(1 + i - 1) * n + j});
                } else {
                    clauses.push_back({-((1 + i - 1) * n + j)});
                }
                if (i == j) {
                    continue;
                }
                clauses.push_back({-i, -j, (1 + i - 1) * n + j});
            }
        }

        for (int i = 0; i <= n; i++) {
            clauses.push_back({(n+1) * n + i*(k+1)});
        }

        for (int j = 1; j <= k; j++) {
            clauses.push_back({-((n+1) * n + j)});
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                clauses.push_back({-1*((n+1)*n + j + i*(k+1)), (n+1)*n + j + (i-1)*(k+1), i, (-1)*((n+1)*n + j-1 + (i-1)*(k+1))});
                clauses.push_back({-1*((n+1)*n + j + i*(k+1)), (n+1)*n + j + (i-1)*(k+1), (n+1)*n + j-1 + (i-1)*(k+1)});
                clauses.push_back({-1*((n+1)*n + j + (i-1)*(k+1)), (n+1)*n + j + i*(k+1)});
                clauses.push_back({-1*(i), -1*((n+1)*n + j-1 + (i-1)*(k+1)), (n+1)*n + j + i*(k+1), (n+1)*n + j + (i-1)*(k+1)});
            }
        }

        clauses.push_back({(n+1)*n + k + n*(k+1)});

        ofstream cnfFile("sat_input.cnf");
        cnfFile << "p cnf " << (1 + n) * n + k + n*(k+1)<< " " << clauses.size() << endl;

        for (auto clause : clauses) {
            for (int var : clause) {
                cnfFile << var << ' ';
            }
            cnfFile << "0" << endl;
        }
        cnfFile.close();

        int result = system("./minisat sat_input.cnf sat_output.txt > /dev/null 2>&1");

        ifstream satOutput("sat_output.txt");
        string sat_assignment;
        getline(satOutput, sat_assignment);
        if (sat_assignment == "SAT") {
            maxK = k;
            clique.clear();
            string prak;
            getline(satOutput, prak);
            stringstream ss(prak);
            string token;
            vector<string> answer;
            
            while (getline(ss, token, ' ')) {
                answer.push_back(token);
            }
            for (int i = 0; i < n; i++) {
                if (answer[i][0] != '-') {
                    clique.push_back(stoi(answer[i]));
                }
            }
            lo = k + 1;
        } else {
            hi = k - 1;
        }
        satOutput.close();
    }
    const char* filename = "sat_output.txt";
    remove(filename);
    string x(inputFileName);
    x = x.substr(0,x.length()-5);
    x+="mapping";
    ofstream outputFile1(x);
    outputFile1 << "#1" << endl;
    // cout<<maxK<<endl;
    for (int i = 0; i < maxK; i++) {
        if (i!=maxK-1){
        outputFile1 << clique[i] << " ";
        }
        else{
            outputFile1 << clique[i];
        }
    }
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);
    return 0;
}
