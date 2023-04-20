#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "BayesianNetwork.hpp"
#include <fstream>

/* Converter reads from .uai file and converts it to `BayesianNetwork` data structure. */
class Converter {
public:
    string fname;

    Converter(const string fname) : fname(fname) {}
    BayesianNetwork *convert();
    static vector<string> splitString(string str, char delim);
    static string index2assignment(int i, int varnum);
    static int assignment2index(string str);
};

#endif