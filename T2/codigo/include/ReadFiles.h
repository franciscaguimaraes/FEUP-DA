//
// Created by franc on 17/05/2022.
//
#ifndef FEUP_DA2_READFILES_H
#define FEUP_DA2_READFILES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
/**
 * This struct stores our input values.
 */
struct Contents {
public:
    int scr, dest, cap, dur;
};

/**
 * tests if file passed
 * @param f_name file name to be found
 * @return boolean if file exists
 */
bool fileExists(const string& f_name);

/**
 * reads from file and stores into contents vector
 * @param file_name file name to be processed
 * @return contents vector with values
 */
vector<Contents> fileReader(const string &file_name);

/**
 * operator << overload for contents, allowing to print a nodes' value
 * @param os ostream to be used for output
 * @param contents values to be outputted
 * @return ostream (altered)
 */
ostream &operator<<(ostream &os, Contents &contents);

/**
 * operator >> overload for contents, allowing extracting contents from istream
 * @param is istream that contains the values to be extracted
 * @param contents contents that will be set
 * @return istream(altered)
 */
istream &operator>>(istream &is, Contents &contents);

#endif //FEUP_DA2_READFILES_H