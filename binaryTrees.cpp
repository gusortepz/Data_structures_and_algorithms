#include <iostream>

using namespace std;

struct node{
    int data;
    struct node *left;
    struct node *right;
};

class BinaryTrees{
    private:
        node *root;
        node *temp;
    public:
        BinaryTrees();
        void insert(int);
        void del(int);
        node* getRoot();
        node* search(int,node*);
        bool isEmpty();
        void preOrder(node*);
        void inOrder(node*);
        void postOrder(node*);
};

BinaryTrees::BinaryTrees(){
    root = NULL;
    temp = root;
}

node* BinaryTrees::getRoot(){
    return root;
}

void BinaryTrees::insert(int nuevo){
    node *n = new node;
        if (root == NULL){
                root = n;
                n -> data = nuevo;
                n -> left = NULL;
                n -> right = NULL;
                temp = root;
                return;
        }else{
            if(temp -> left == NULL && temp -> right == NULL){
                if (nuevo < temp -> data){
                    temp -> left = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    n -> data = nuevo;
                    temp = root;
                    return;
                }else{
                    temp -> right = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    n -> data = nuevo;
                    temp = root;
                    return;
                }
            }else{
                if (nuevo < temp -> data){
                    if (temp -> left == NULL){
                        temp -> left = n;
                        n -> data = nuevo;
                        n -> left = NULL;
                        n -> right = NULL;
                        return;
                    }
                    temp = temp -> left;
                    insert(nuevo);
                }else{
                    if (temp -> right == NULL){
                        temp -> right = n;
                        n -> data = nuevo;
                        n -> left = NULL;
                        n -> right = NULL;
                        return;
                    }
                    temp = temp -> right;
                    insert(nuevo);
                }
            }
        }
    
}

void BinaryTrees::del(int del){
}

node* BinaryTrees::search(int s, node* r){
    if (isEmpty() == false){
        cout << "raiz" << r -> data << endl;
        if (s < r -> data && r -> left != NULL){
            return search(s,r -> left);
        }else if (s > r -> data && r -> right != NULL){
            return search(s,r -> right);
        }else{
            node* nul = new node;
            if (s == r -> data){
                cout << s << " es igual a " << r->data << endl;
                return r;
            }else{
                nul = NULL;
                return nul;
            }
        }
    }
    r = NULL;
    return r;
}

void BinaryTrees::preOrder(node *root){

}

void BinaryTrees::inOrder(node *root){

}

void BinaryTrees::postOrder(node *root){

}



bool BinaryTrees::isEmpty(){
    if (root == NULL){
        return true;
    }return false;
}


int main(){
    BinaryTrees a;
    a.insert(55);
    a.insert(8);
    a.insert(1);
    a.insert(2);
    a.insert(60);
    a.insert(70);
    a.insert(65);
    a.insert(67);

    cout << a.getRoot() -> data << endl;
    cout << a.search(70,a.getRoot()) -> data << endl;
    return 0;
}

