#ifndef BAYESIAN_NETWORK_H_
#define BAYESIAN_NETWORK_H_

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;

/* Represent a Node in Bayesian network. */
class Node {
public:
    string name;
    vector<Node*> parents;
    unordered_map<string, double> cpt;

    Node(const string name) : name(name) {}
};

/* The Bayesian network data structure, 
   consisting of multiple nodes. */
class BayesianNetwork {
public:
    vector<Node*> nodes;

    BayesianNetwork(){}
    void addNode(const string name);
    void addEdge(const string parent, const string child);
    void print();

    Node *findNode(const string name);
};

#endif