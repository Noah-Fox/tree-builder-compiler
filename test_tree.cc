/**
 * Test file for using the TreeNode class
*/

#include <iostream>
#include <map>
#include "tree_node.h"

using namespace std;

int main(){
    map<string, TreeNode*> nodeMap;

    TreeNode* root = new TreeNode("root", 1, nodeMap);
    TreeNode* a = new TreeNode("a", 2, "root", nodeMap);
    TreeNode* b = new TreeNode("b", 3, "root", nodeMap);
    TreeNode* c = new TreeNode("c", 4, "a", nodeMap);

    printTree(root);
}
