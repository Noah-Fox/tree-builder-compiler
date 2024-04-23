/**
 * File: tree_node.h
 * 
 * Contains class for a node in a tree
*/

#ifndef TREENODE
#define TREENODE

#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

struct TreeNode {
    TreeNode(){
        name = "";
        weight = -1;
        parent = "";
        children = vector<string>();
    }
    
    TreeNode(string n, int w, map<string, TreeNode>& nodeMap){
        name = n;
        weight = w;
        parent = "";
        children = vector<string>();
        nodeMap[n] = *this;
    }

    TreeNode(string n, int w, string p, map<string, TreeNode>& nodeMap){
        name = n;
        weight = w;
        parent = p;
        nodeMap[n] = *this;
        children = vector<string>();
        nodeMap[p].children.push_back(n);
    }

    string name;
    int weight;
    string parent;
    vector<string> children;
};

void printTree(string rootName, map<string, TreeNode>& nodeMap){
    cout << rootName << " " << nodeMap[rootName].weight << "\n";
    for (size_t i = 0; i < nodeMap[rootName].children.size(); i ++){
        printTree(nodeMap[rootName].children[i], nodeMap);
    }
}


#endif

