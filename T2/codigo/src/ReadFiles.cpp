//
// Created by franc on 17/05/2022.
//

#include "../include/ReadFiles.h"
#include <iostream>
#include <vector>

bool fileExists(const string& f_name) {
    ifstream f;
    f.open(f_name);

    if(f.is_open()) {
        f.close();
        return true;
    }
    else {
        cout << "File \"" << f_name <<"\" does not exist! Try another one!" << endl;
        return false;
    }
}

ostream &operator<<(ostream &os, const Contents &contents) {
    os << contents.scr << " " << contents.dest << " " << contents.cap << " " << contents.dur;
    return os;
}

istream &operator>>(istream &is, Contents &contents) {
    is >> contents.scr >> contents.dest >> contents.cap >> contents.dur;
    return is;
}

vector<Contents> fileReader(const string &file_name) {

    vector<Contents> result;
    fstream file(file_name, ios::in);

    if(!fileExists(file_name)){
        return {};
    }

    Contents contents{};
    string line;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> contents;
        result.push_back(contents);
    }

    return result;
}

