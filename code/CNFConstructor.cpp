#include "CNFConstructor.hpp"

/* Read the evidence file and get the assignment to each node. */
void CNFConstructor::evidence2assignment(){
    ifstream file(fname + ".evid");
    string numVarStr;
    file >> numVarStr;
    int numVar = std::stoi(numVarStr);

    // initialize
    for(Node *node : bn.nodes) {
        assignment[node->name] = -1;
    }

    // assign from evidence
    string var;
    string varValueStr;
    int varValue;
    for(int i = 0; i < numVar; i++) {
        file >> var;
        file >> varValueStr;
        varValue = stoi(varValueStr);
        assignment[var] = varValue;
    }
}

/* Construct the CNF formula, which is based on the 
   method professor taught in class. */
CNF CNFConstructor::construct() {
    // 1. Construct the main part of the formula from evidence
    CNF res = CNF(fname);
    int count = 0;
    for(Node *node : bn.nodes) {
        int value = assignment[node->name];
        Clause c = Clause();
        for(auto cptline : node->cpt) {
            count++;
            Literal l = Literal(false, std::to_string(count), count, cptline.second);
            res.weightFileLiterals.push_back(l);

            // Xn = assignment
            if(value == -1 || cptline.first.at(cptline.first.length()-2) == char(value + '0')) {
                c.literals.push_back(l);
            }
        }
        if(c.literals.size() != 0) {
            res.clauses.push_back(c);
        }
    }
    this->cnf = res;
    // 2. Construct the "exactly one" part of the CNF formula.
    constructAllExactlyOne(this->cnf);
    return cnf;
}

void CNFConstructor::exactlyOne(CNF &cnf, vector<Literal> literals){
    if(literals.size() <= 1) return;
    Clause c{};
    c.literals = literals;
    cnf.clauses.push_back(c);

    int varnum = literals.size();
    for(int i = 0; i < varnum; i++){
        Literal l1 = Literal(!literals[i].hasNot, literals[i].name, literals[i].order);
        for(int j = i+1; j < varnum; j++){
            Literal l2 = Literal(!literals[j].hasNot, literals[j].name, literals[j].order);
            Clause c{};
            c.literals.push_back(l1);
            c.literals.push_back(l2);
            cnf.clauses.push_back(c);
        }
    }
}

void CNFConstructor::constructAllExactlyOne(CNF &cnf) {
    int count = 0;
    for(Node *node : bn.nodes){
        vector<Literal> exactlyOneLiterals;
        for(auto cptline : node->cpt){
            count++;
            Literal l = Literal(false, std::to_string(count), count, cptline.second);
            exactlyOneLiterals.push_back(l);
        }
        exactlyOne(cnf, exactlyOneLiterals);
    }
}