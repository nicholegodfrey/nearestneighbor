#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>
#include <cfloat> 

using namespace std;

double leave_one_out_cross_validation(vector<vector<double> > data, vector <int> curr_set, int feature) {
   //return val between 0 and 1
    return rand() / (RAND_MAX + 1.0);
    //fix
}
void forwardSelection(vector<vector<double> > data){
    //initialize an empty set
    vector<int> currSet;
    vector<int> bestSet;
    vector<int> tempSet;
    int featureAdd=-1;
    double bestAccuracy=0.0;

    for(int i=1; i< data[0].size();i++) {
        tempSet.push_back(i);
    }
    double accuracy=leave_one_out_cross_validation(data, tempSet,0);
    cout << "Running nearest neighbor with all " << data[0].size()-1 << "features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl;
    cout << endl<<"Beginning search." << endl;
    for(int i=0; i<data[0].size()-1; i++){
        double bestSoFarAccuracy=0.0;
        //cout << "On the " << i+1 << "th level of the search tree" << endl;
        //cout << "Running nearest neighbor with all" << data[0].size()-1 << "features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl;
       
        for(int k=1; k<data[0].size(); k++){
            //skips if feature is already added
            if(find(currSet.begin(), currSet.end(), k) == currSet.end()){
                cout << "Considering adding the " << k << " feature" << endl;
                
                accuracy=leave_one_out_cross_validation(data, currSet,k);
                
                cout << "Using feature(s) {" << k ;
                for(int j=0; j<currSet.size(); j++){
                    if(j!=currSet.size()){
                        cout << ", ";
                    }
                    cout << currSet[j];
                }
                cout << "} accuracy is " << accuracy*100 << "%" << endl;

                if(accuracy>bestSoFarAccuracy){
                    bestSoFarAccuracy=accuracy;
                    featureAdd=k;
                }
            }
        }
        
        
        currSet.push_back(featureAdd);
        if(bestSoFarAccuracy>bestAccuracy){
            bestAccuracy=bestSoFarAccuracy;
            bestSet=currSet;
        }
        else{
            cout << "(Warning: Accuracy has decreased! Continuing search in case of local maxima.)" << endl;
        }

        cout << "Feature set {";
        for(int i=0; i<currSet.size(); i++){
            cout << currSet[i];
            if(i!=currSet.size()-1){
                cout << ", ";
            }
        }
        cout << "} was best, with an accuracy of " << bestSoFarAccuracy*100 << "%" << endl;
    }
    
    cout << "Finished search!! The best feature subset is {";
    for(int i=0; i<bestSet.size(); i++){
        cout << bestSet[i];
        if(i!=bestSet.size()-1){
            cout << ", ";
        }
    }
    cout << "}, which has an accuracy of " << bestAccuracy*100 << "%" << endl;
}
void backwardsElimination(vector<vector<double> > data){
    vector<int> currSet;
    vector<int> bestSet;
    
    double bestAccuracy=0.0;
    //cout << "Running nearest neighbor with all" << data[0].size()-1 << "features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl;
    

    for(int i=1; i< data[0].size();i++) {
        currSet.push_back(i);
    }
    double accuracy=leave_one_out_cross_validation(data, currSet,-1);
    cout << "Running nearest neighbor with all " << data[0].size()-1 << "features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl;
    cout <<endl<< "Beginning search." << endl;

    cout << "Using feature(s) {";
    for(int j=0; j<currSet.size(); j++){
        cout << currSet[j];
        if(j!=currSet.size()-1){
            cout << ", ";
        }
        
    }
    cout << "} accuracy is " << accuracy*100 << "%" << endl;
    vector<int> tempSet;
    for(int i=0; i<data[0].size()-1; i++){
        double bestSoFarAccuracy=0.0;
        int featureRemove=-1;
        //cout << "On the " << i+1 << "th level of the search tree" << endl;
        //cout << "Running nearest neighbor with all" << data[0].size()-1 << "features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl;
       
        for(int k=0; k<currSet.size(); k++){
            tempSet.clear();
            for (int j = 0; j < currSet.size(); j++){
                    if(j!=k){
                        tempSet.push_back(currSet[j]);
                    }
                }  
                if (tempSet.empty()) {
                    continue;
                }
                accuracy=leave_one_out_cross_validation(data, tempSet,k);
                
                cout << "Using feature(s) {" ;
                for(int j=0; j<tempSet.size(); j++){
                    cout << tempSet[j];
                    if(j!=tempSet.size()-1){
                        cout << ", ";
                    }
                    
                }
                cout << "} accuracy is " << accuracy*100 << "%" << endl;

                if(accuracy>bestSoFarAccuracy){
                    bestSoFarAccuracy=accuracy;
                    featureRemove=k;
                }
        }
        
        if(featureRemove==-1){  
            break;
        }
        int featureToRemove = currSet[featureRemove];  
        currSet.erase(remove(currSet.begin(), currSet.end(), featureToRemove), currSet.end());
    if(bestSoFarAccuracy>bestAccuracy){
            bestAccuracy=bestSoFarAccuracy;
            bestSet=currSet;
        }
        else{
            cout << "(Warning: Accuracy has decreased! Continuing search in case of local maxima.)" << endl;
        }

        cout << "Feature set {";
        for(int i=0; i<currSet.size(); i++){
            cout << currSet[i];
            if(i!=currSet.size()-1){
                cout << ", ";
            }
        }
        cout << "} was best, with an accuracy of " << bestSoFarAccuracy*100 << "%" << endl;
    }
    
    cout << "Finished search!! The best feature subset is {";
    for(int i=0; i<bestSet.size(); i++){
        cout << bestSet[i];
        if(i!=bestSet.size()-1){
            cout << ", ";
        }
    }
    cout << "}, which has an accuracy of " << bestAccuracy*100 << "%" << endl;
}       


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
    cout << "Type the number of the algorithm you want to run. \n 1. Forward Selection \n 2. Backward Elimination \n"<<endl;
    int algorithm=0;
    cin >> algorithm;
    cout << "This dataset has " << data[0].size()-1 << " features (not including the class attribute), with " << data.size() << " instances." << endl;
    if(algorithm==1){
        auto start = chrono::high_resolution_clock::now();
        forwardSelection(data);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Time to run: " << elapsed.count() << " seconds" << endl;
    }
    else if(algorithm==2){
        auto start = chrono::high_resolution_clock::now();
        backwardsElimination(data);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Time to run: " << elapsed.count() << " seconds" << endl;
    }
    else{
        cout << "Invalid input." << endl;
    }
    return 0;
}
