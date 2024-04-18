/**
 * File: tree_node.h
 * 
 * Contains class for a node in a tree
*/

#include <string>
#include <map>
#include <vector>
using namespace std;

class TreeNode {
    public:
        TreeNode(string n, int w, map<string, TreeNode*>& nodeMap){
            name = n;
            weight = w;
            parent = nullptr;
            nodeMap[n] = this;
        }

        TreeNode(string n, int w, string p, map<string, TreeNode*>& nodeMap){
            name = n;
            weight = w;
            if (nodeMap.find(p) != nodeMap.end()){
                parent = nodeMap[p];
                (nodeMap[p] -> children).push_back(this);
            }else {
                parent = nullptr;
            }
            nodeMap[n] = this;
        }

        string name;
        int weight;
        TreeNode* parent;
        vector<TreeNode*> children;

};
