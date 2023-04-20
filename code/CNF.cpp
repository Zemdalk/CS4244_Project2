#include "CNF.hpp"
#include <iostream>

using std::ifstream;
using std::ofstream;

CNF CNF::operator+(const CNF obj) {
    CNF res = obj;
    for(auto c : clauses) {
        res.clauses.push_back(c);
    }
    return res;
}

string Literal::to_string() {
    string str = "";
    if(hasNot) str += "!";
    str += name;
    return str;
}

string Clause::to_string() {
    string str = "";
    if (literals.size() == 0) return str;
    str += "(";
    for (int i = 0; i < literals.size(); i++) {
        str += literals[i].to_string();
        if(i != literals.size() - 1){
            str += "|";
        }
    }
    str += ")";
    return str;
}

string CNF::to_string() {
    string str = "";
    for(int i = 0; i < clauses.size(); i++) {
        str += clauses[i].to_string();
        if(i != clauses.size() - 1) {
            str += "&";
        }
    }
    return str;
}

void CNF::showWeightFile(){
    for(Literal l : weightFileLiterals) {
        std::cout << (l.hasNot ? "-" : "") << l.name << "\t" << l.weight << std::endl;
    }
}

void CNF::saveWeightFile(){
    ofstream file(fname + ".weight");
    file << "p ";
    file << weightFileLiterals.size() << std::endl;
    
    for(auto literal : weightFileLiterals) {
        file << "w ";
        file << literal.name << " " << literal.weight << " 0" << std::endl;
        file << "w ";
        file << "-" << literal.name << " 1 0" << std::endl;
    }
    file.close();
}

void CNF::saveCnfFile(){
    ofstream file(fname + ".cnf");
    file << "p cnf ";
    file << weightFileLiterals.size() << " ";
    file << clauses.size() << std::endl;

    for(auto clause : clauses) {
        for(auto literal : clause.literals) {
            if(literal.hasNot) {
                file << "-";
            }
            file << literal.name << " ";
        }
        file << "0" << std::endl;
    }
    file.close();
}