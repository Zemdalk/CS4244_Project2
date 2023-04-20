#include "Converter.hpp"

using std::ifstream;
using std::stoi;

BayesianNetwork *Converter::convert(){
    ifstream file(fname + ".uai");
    string line;
    BayesianNetwork *bn = new BayesianNetwork();

    /* Preamable */
    // Graph Type
    getline(file, line);
    if(line != "BAYES") {
        return NULL;
    }

    // Variables 
    getline(file, line);
    int varnum = stoi(line);
    for(int i = 0; i < varnum; i++){
        // add nodes named "0", "1", ...
        bn->addNode(std::to_string(i));
    }

    // Domains, actually should be all 2's
    getline(file, line);
    vector<string> domainSizeStrs = splitString(line, ' ');
    vector<int> domainSizes;
    for(string domainSizeStr : domainSizeStrs) {
        int size = stoi(domainSizeStr);
        domainSizes.push_back(size);
    }

    // Function Scopes
    // number of functions
    getline(file, line);
    int funcnum = stoi(line);

    for(int i = 0; i < funcnum; i++) {
        getline(file, line);
        vector<string> edges = splitString(line, ' ');
        int nodenum = stoi(edges[0]);
        string child = edges[nodenum];
        for(int j = 1; j < nodenum; j++) {
            bn->addEdge(edges[j], child);
        }
    }

    /* Function Tables */
    for(int i = 0; i < varnum; i++){
        string tableSizeStr;
        file >> tableSizeStr;
        int tableSize = stoi(tableSizeStr);
        // cout << "table size: " << tableSize << endl;
        for(int j = 0; j < tableSize; j++) {
            string probabilityStr;
            file >> probabilityStr;
            double probability = stof(probabilityStr);
            
            Node *node = bn->findNode(std::to_string(i));
            string assignment = index2assignment(j, node->parents.size() + 1);

            node->cpt.emplace(assignment, probability); 
            // cout << "add (" << assignment << ", " << probability << ")" <<endl;
        }
    }

    return bn;
}

/* Split the input string into smaller substrings at the specified delim character,
   and store each of these substrings in a separate string object within the returned vector<string>.*/
vector<string> Converter::splitString(string str, char delim) {
    vector<string> result;
    int last = 0;
    for(int i = 0; i <= str.length(); i++){
        if(str[i] != delim && i != str.length()){
            continue;
        }
        
        string substr = str.substr(last, i-last);
        result.push_back(substr);
        last = i+1;
    }
    return result;
}

/* Convert from the node index to an assignment. This is used in CPT representation.
   For example, if i = 3 and varnum = 4, then string "0 0 1 1" will be returned. */
string Converter::index2assignment(int i, int varnum) {
    string res = "";
    for(int n = 0; n < varnum; n++){
        res = std::to_string(i % 2) + " " + res;
        i = i / 2;
    }
    return res;
}

/* Convert from an assignment to index.*/
int Converter::assignment2index(string str) {
    int index = 0;
    vector<string> assignments = splitString(str, ' ');
    for(int i = 0; i < assignments.size(); i++){
        index = index * 2 + stoi(assignments[i]);
    }
    return index;
}