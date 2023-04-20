#ifndef ENCODER_H_
#define ENCODER_H_

#include "BayesianNetwork.hpp"
#include "CNF.hpp"

using std::ifstream;

class CNFConstructor {
    BayesianNetwork bn;
    string fname;

public:
    CNF cnf;
    unordered_map<string, int> assignment;

    CNFConstructor(BayesianNetwork bn, string fname) :
        bn(bn),
        fname(fname) {}

    void evidence2assignment();
    CNF construct();
    void exactlyOne(CNF &cnf, vector<Literal> literals);
    void constructAllExactlyOne(CNF &cnf);
};

#endif