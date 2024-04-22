
void makeTree(treeNode* root){
    treeNode* ptr = root;
    while(ptr != NULL){
        cout<< "(<" << ptr.Name << " , " << ptr.Weight << "> , ";
        treeNode* future = ptr -> next;
        if(ptr.isachildof == future.isachildof){
            makeTree(future);
        }
        cout<<")"
        
    }
} //name weight parent children
