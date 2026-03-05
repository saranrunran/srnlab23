#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string &file, vector<string> &name, vector<int> &score, vector<char> &grade){
    ifstream source(file);
    string textline;
    while (getline(source,textline)) {   
        char names[100];
        char format[] = "%[^:]:%d %d %d";
        int s1, s2, s3;
        sscanf(textline.c_str(),format,names,&s1, &s2, &s3);
        
        int total = s1 + s2 + s3;

        name.push_back(names);
        score.push_back(total);
        grade.push_back(score2grade(total));
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    cin >> command;
    command = toUpperStr(command);

    if (command == "EXIT") return;
    if(command != "GRADE" && command != "NAME") return;

    char k[50];
    scanf(" %[^\n]",k);
    key = k;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool isFound = false;
    for (unsigned i = 0; i < names.size(); i++){
        if (toUpperStr(names[i]) == key) {
            printf("%s's score = %d\n",names[i].c_str(),scores[i]);
            printf("%s's grade = %c\n",names[i].c_str(),grades[i]);
            isFound = true;
        }
    }
    if (isFound == false) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool isFound = false;
    for (unsigned i = 0; i < grades.size(); i++){
        if (grades[i] == key[0]) {
            //cout << names[i] << " (" << scores[i] << ")\n";
            printf("%s (%d)\n",names[i].c_str(),scores[i]);
            isFound = true;
        }
    }
    if (isFound == false) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
