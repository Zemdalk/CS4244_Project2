#ifndef CNF_H_
#define CNF_H_

#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;

class Literal {
public:
    bool hasNot;
    string name;
    int order;
    double weight;
    int assignment;

    Literal(bool hasNot, string name, int order, double weight) : 
        hasNot(hasNot),
        name(name),
        order(order),
        weight(weight) {
            assignment = -1;
        }
    Literal(bool hasNot, string name, int order) : 
        hasNot(hasNot),
        name(name),
        order(order)
        {
            assignment = -1;
        }
    string to_string();
};

class Clause {
public:
    vector<Literal> literals;

    string to_string();
};

class CNF {
public:
    vector<Clause> clauses;
    vector<Literal> weightFileLiterals;
    string fname;

    CNF(string fname) : fname(fname) {};
    CNF() {};
    CNF(const CNF &other){
        clauses = other.clauses;
        weightFileLiterals = other.weightFileLiterals;
        fname = other.fname;
    }
    string to_string();
    CNF operator+(const CNF obj);
    void showWeightFile();
    void saveCnfFile();
    void saveWeightFile();
};

#endif