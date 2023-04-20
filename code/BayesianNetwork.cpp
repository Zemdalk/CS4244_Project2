#include "BayesianNetwork.hpp"

void BayesianNetwork::addNode(const string name) {
    Node *node = new Node(name);
    nodes.push_back(node);
}

void BayesianNetwork::addEdge(const string parent, const string child) {
    Node *parentNode = findNode(parent);
    Node *childNode = findNode(child);
    childNode->parents.push_back(parentNode);
}

/* This function can be used in Main.cpp to visualize the Bayesian network. */
void BayesianNetwork::print(){
    for(Node *node : nodes) {
        cout << "->" << node->name << ":\n";
        for(Node *parent : node->parents) {
            cout << parent->name << " ";
        }
        cout << node->name << " ";
        cout << "probability\n";

        for(auto cptLine : node->cpt) {
            cout << cptLine.first << cptLine.second << endl;
        }
        cout << endl;
    }
}

Node *BayesianNetwork::findNode(const string name) {
    for(Node *node : nodes) {
        if (node->name == name){
            return node;
        }
    }
    // node not found
    Node *node = new Node(name);
    nodes.push_back(node);
    return node;
}