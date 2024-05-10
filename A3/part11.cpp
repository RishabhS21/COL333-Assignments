#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]) {
    // ifstream inputFile("test.graph");
    const char* inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    vector<string> lines;
    string line;
    // cout<<"idhar4"<<endl;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    int n, m, k1, k2;
    istringstream iss(lines[0]);
    iss >> n >> m >> k1 >> k2;

    vector<vector<bool > > adj_mat(n + 1, vector<bool>(n + 1, false));
    vector<vector<int> > clauses;

    for (int i = 1; i < lines.size(); i++) {
        istringstream iss(lines[i]);
        int u, v;
        iss >> u >> v;
        adj_mat[u][v] = true;
        adj_mat[v][u] = true;
    }

    for (int i = 1; i <= n; i++) {
        clauses.push_back({i, n + i, 2 * n + i});
        clauses.push_back({-i, -(n + i)});
        clauses.push_back({-(n + i), -(2 * n + i)});
        clauses.push_back({-(2 * n + i), -i});
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == n && j == n) break;
            if (adj_mat[i][j]) {
                clauses.push_back({(3 + i - 1) * n + j});
            } else {
                clauses.push_back({-((3 + i - 1) * n + j)});
            }
            if (i != j) {
                clauses.push_back({-i, -j, (3 + i - 1) * n + j});
                clauses.push_back({-(n + i), -(n + j), (3 + i - 1) * n + j});
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        clauses.push_back({(3+n)*n + i*(k1+1)});
    }
    for (int j = 1; j <= k1; j++) {
        clauses.push_back({-1*((3+n)*n + j)});
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k1; j++) {
            clauses.push_back({-1*((3+n)*n + j + i*(k1+1)), (3+n)*n + j + (i-1)*(k1+1), i, (-1)*((3+n)*n + j-1 + (i-1)*(k1+1))});
            clauses.push_back({-1*((3+n)*n + j + i*(k1+1)), (3+n)*n + j + (i-1)*(k1+1), (3+n)*n + j-1 + (i-1)*(k1+1)});
            clauses.push_back({-1*((3+n)*n + j+ (i-1)*(k1+1)), (3+n)*n + j + i*(k1+1)});
            clauses.push_back({-1*(i), -1*((3+n)*n + j-1 + (i-1)*(k1+1)), (3+n)*n + j + i*(k1+1), (3+n)*n+j+(i-1)*(k1+1)});
        }
    }

    clauses.push_back({(3+n)*n + k1 + n*(k1+1)});

    for (int i = 0; i <= n; i++) {
        clauses.push_back({(3 + n + n + 1 + 1) * n + i*(k2+1)});
    }
    for (int j = 1; j <= k2; j++) {
        clauses.push_back({-((3 + n + n + 1 + 1) * n + j)});
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k2; j++) {
            clauses.push_back({-((3 + n + n + 1 + 1) * n + j + i*(k2+1)), (3 + n + n + 1 + 1) * n + j + (i-1)*(k2+1), n + i, -((3 + n + n + 1 + 1) * n + j - 1 + (i-1)*(k2+1))});
            clauses.push_back({-((3 + n + n + 1 + 1) * n + j + i*(k2+1)), (3 + n + n + 1 + 1) * n + j + (i-1)*(k2+1), (3 + n + n + 1 + 1) * n + j - 1 + (i-1)*(k2+1)});
            clauses.push_back({-((3 + n + n + 1 + 1) * n + j + (i-1)*(k2+1)), (3 + n + n + 1 + 1) * n + j + i*(k2+1)});
            clauses.push_back({-(n + i), -((3 + n + n + 1 + 1) * n + j - 1 + (i-1)*(k2+1)), (3 + n + n + 1 + 1) * n + j + i*(k2+1), (3 + n + n + 1 + 1) * n + j + (i-1)*(k2+1)});
        }
    }

    clauses.push_back({(3 + n + n + 1 + 1) * n + k2 + n*(k2+1)});
    // cout<<"idhar1"<<endl;
    string x(inputFileName);
    x = x.substr(0,x.length()-5);
    x+="satinput";
    ofstream outputFile(x);
    outputFile << "p cnf " << (3 + n + n + 1 + 1) * n + k2 + n*(k2+1) << " " << clauses.size() << endl;
    for (vector<int>& clause : clauses) {
        for (int lit : clause) {
            outputFile << lit << " ";
        }
        outputFile << "0" << endl;
    }
    // cout<<"idhar2"<<endl;
    ofstream outputFile1("n.txt");
    outputFile1 << n << endl;
    outputFile1 << k1 << endl;
    outputFile1 << k2 << endl;
    // cout<<"idhar3"<<endl;
    // return 0;
}
