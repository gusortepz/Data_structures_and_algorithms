#include <iostream>
#include <vector>

using namespace std;

struct node{
    int data;
    struct node *left;
    struct node *right;
};

class BinaryTrees{
    private:
        node *root;

    public:
        BinaryTrees();

        //Funcion auxiliar para insertar
        void insert(int);

        //Funcion para insertar los datos
        void insertA(int,node*);

        //Funcion que obtiene la raíz
        node* getRoot();

        //Funcion que regresa el nodo de un valor dado
        node* search(int,node*);

        //Funcion que revisa si el arbol está vació
        bool isEmpty();

        //Funcion visit para elegir como imprimir el arbol
        void visit(int opc);

        //Funcion que imprime en preOrder
        void preOrder(node*);

        //Funcion que imprime en en orden de menor a mayor
        void inOrder(node*);

        //Funcion que imprime post Order
        void postOrder(node*);

        //Funcion auxiliar para imprimir por nivel
        void LevelByLevel();
        //Funcion que imprime por nivel
        void printLevel(node*,int);

        //Funcion que determina la altura de un árbol
        int height(node*);

        //Funcion que imprime los ancestros
        void ancestors(int);

        //Funcion que encuentra los ancestros a un numero dado
        vector<int> ancestorsA(int,node*,vector<int>);

        //Funcion que determina el nivel en el que se encuentra un valor
        int whatLevelAmI(int);
};

BinaryTrees::BinaryTrees(){
    root = NULL;
}

node* BinaryTrees::getRoot(){
    return root;
}

void BinaryTrees::insert(int d){
    insertA(d,root);
}

void BinaryTrees::insertA(int d, node* r){
    node *n = new node;
    n -> data = d;
    if (r == NULL){
            root = n;
            n -> left = NULL;
            n -> right = NULL;
            return;
    }else{
        if(r -> left == NULL && r -> right == NULL){
            if (n -> data < r -> data){
                r -> left = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }else{
                r -> right = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }
        }else{
            if (n -> data < r -> data){
                if (r -> left == NULL){
                    r -> left = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                insertA(d,r -> left);
            }else{
                if (r -> right == NULL){
                    r -> right = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                insertA(d,r -> right);
            }
        }
    }
}


node* BinaryTrees::search(int s, node* r){
    if (isEmpty() == false){
        if (s < r -> data && r -> left != NULL){
            return search(s,r -> left);
        }else if (s > r -> data && r -> right != NULL){
            return search(s,r -> right);
        }else{
            node* nul = new node;
            if (s == r -> data){
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

void BinaryTrees::visit(int opc){
    node* r = getRoot();
    if(opc==1){
        preOrder(r);
    }else if(opc==2){
        inOrder(r);
    }else if(opc==3){
        postOrder(r);
    }else if(opc==4){
        LevelByLevel();
    }else{
        cout << "Opcion no valida" << endl;
    }
}

void BinaryTrees::preOrder(node *r){
    if (r == NULL){
        return;
    }

    cout << r -> data << endl;

    inOrder(r ->left);

    inOrder(r -> right);
}

void BinaryTrees::inOrder(node *r){
    if (r == NULL){
        return;
    }
    inOrder(r ->left);

    cout << r -> data << endl;

    inOrder(r -> right);
}

void BinaryTrees::postOrder(node *r){
    if (r == NULL){
        return;
    }
    inOrder(r ->left);

    inOrder(r -> right);

    cout << r -> data << endl;
}

void BinaryTrees::LevelByLevel(){
    int h = height(root);
    for (int i = 1; i <= h; i++){
        printLevel(root,i);
        cout << endl;
    }
}

void BinaryTrees::printLevel(node *r, int level){
    if (r == NULL){
        return;
    }
    if (level == 1){
        cout << r -> data << " ";
    }else{
        printLevel(r -> left,level-1);
        printLevel(r -> right,level-1);
    }
}

bool BinaryTrees::isEmpty(){
    if (root == NULL){
        return true;
    }return false;
}

int BinaryTrees::height(node* root){
    if (root == NULL){
        return 0;
    }

    int heightL = height(root->left);
    int heightR = height(root->right);

    if (heightL > heightR){
        return heightL + 1;
    }else{
        return heightR + 1;
    }
}

void BinaryTrees::ancestors(int d){
    if (isEmpty() == false){
        vector <int> anc;
        anc = ancestorsA(d,root,anc);
        for (int i = 0; i < anc.size(); i++){
            cout << anc[i] << " ";
        }

    }
}

vector<int> BinaryTrees::ancestorsA(int s, node* root, vector<int> an){
    if (root == NULL){
        return an;
    }
    if (root -> data > s){
        an = ancestorsA(s,root->left,an);
        if (an.size() > 0){
            an.push_back(root -> data);
        }
    }else if (root -> data < s){
        an = ancestorsA(s,root->right,an);
        if (an.size() > 0){
            an.push_back(root -> data);
        }
    }else if (root -> data == s){
        an.push_back(root -> data);
        return an;
    }else{
        return an;
    }
    return an;
}

int BinaryTrees::whatLevelAmI(int s){
    if (isEmpty() == false){
        vector<int> level;
        level = ancestorsA(s,root,level);
        if (level.size() == 0){
            return -1;
        }
        return level.size();
    }return -1;
}

int main(){
    BinaryTrees bst;
    //Añadir Nodos al arbol
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(4);
    bst.insert(6);
    bst.insert(14);
    bst.insert(16);
    bst.insert(3);
    bst.insert(13);
    bst.insert(12);

    //Funcion visit
    cout << "Impresion en preOrder" << endl;
    bst.visit(1); //preOrder
    cout << endl;
    cout << "Impresion en inOrder" << endl;
    bst.visit(2); //inOrder
    cout << endl;
    cout << "Impresion en postOrder" << endl;
    bst.visit(3); //postOrder
    cout << endl;
    cout << "Impresion en LevelByLevel" << endl;
    bst.visit(4); //LevelByLevel
    cout << endl;
    cout << "Ejemplo de Opcion no valida" << endl;
    bst.visit(5); //Opcion Invalida
    cout << endl;

    //Funcion height
    cout << "La altura del arbol es de:" <<endl;
    int altura = bst.height(bst.getRoot());
    cout << altura << endl;
    cout <<endl;

    //Funcion ancestors
    cout << "Los ancestros de 10 son: " <<endl;
    bst.ancestors(10);
    cout <<endl;
    cout << "Los ancestros de 16 son: " <<endl;
    bst.ancestors(16);
    cout <<endl;
    cout << "Los ancestros de 9 son: " <<endl;
    bst.ancestors(9);
    cout <<endl;

    //Funcion whatLevelAmI
    cout << "Nivel de 14: " <<endl;
    int nivel = bst.whatLevelAmI(14);
    cout << nivel <<endl;
    cout << "Nivel de 10:" <<endl;
    nivel = bst.whatLevelAmI(10);
    cout << nivel <<endl;
    cout << "Nivel de 9: " <<endl;
    nivel = bst.whatLevelAmI(9);
    cout << nivel <<endl;

    return 0;
}

