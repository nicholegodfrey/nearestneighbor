#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>

using namespace std;

int main(){
    cout <<"Welcome to Nichole Godfrey's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";
    string filename="";
    cin >> filename;
    vector<vector<double> > data;
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Cannot open file." << endl;
        return 0;
    }
    string line;
    while (getline(file, line)){
        vector<double> row;
        stringstream ss(line);
        double value;
        while(ss >> value){
            row.push_back(value);
        }
        data.push_back(row);
    }

    file.close();
    cout << "Type the number of the algorithm you want to run. \n 1. Forward Selection \n 2. Backward Elimination \n";
    int algorithm;
    cin >> algorithm;

    
}