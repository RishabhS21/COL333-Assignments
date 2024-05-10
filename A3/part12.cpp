#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main(int argc,char* argv[]) {
    const char* inputFileName = argv[1];
    ifstream input_n("n.txt");
    string line1;
    getline(input_n,line1);
    int n = stoi(line1);
    getline(input_n,line1);
    int k1 = stoi(line1);
    getline(input_n,line1);
    int k2 = stoi(line1);
    ifstream satOutputFile(argv[1]);

    if (!satOutputFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    string satAssignment;
    
    if (!getline(satOutputFile, satAssignment)) {
        cerr << "Error: Unable to read SAT assignment." << endl;
        return 1;
    }
    string x(inputFileName);
    x = x.substr(0,x.length()-9);
    x+="mapping";
    ofstream outputFile2(x);
    if (satAssignment == "SAT") {
        // cout << "#1" << endl;
        string prak;
        
        if (!getline(satOutputFile, prak)) {
            cerr << "Error: Unable to read SAT assignment details." << endl;
            return 1;
        }
        
        stringstream ss(prak);
        string token;
        vector<string> answer;
        
        while (getline(ss, token, ' ')) {
            answer.push_back(token);
        }
        int temp1 = 0;
        outputFile2 << "#1" << endl;
        for (int i = 0; i < n; i++) {
            if (answer[i][0] != '-') {
                temp1++;
                if (temp1 != k1){
                outputFile2 << i + 1 <<" ";
                }
                else{
                    outputFile2 << i + 1;
                }
            }
        }
        int temp2 = 0;
        outputFile2 << endl << "#2" << endl;
        for (int i = n; i < 2 * n; i++) {
            if (answer[i][0] != '-') {
                temp2++;
                if (temp2!=k2){
                outputFile2 << i - n + 1 << " ";
                }
                else{
                    outputFile2 << i - n + 1;
                }
            }
        }
    } else {
        outputFile2 << 0;
    }
    satOutputFile.close();
    return 0;
}
