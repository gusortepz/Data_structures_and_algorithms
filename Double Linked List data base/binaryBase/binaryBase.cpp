#include <iostream>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

long int generarID(string ip){
    long int id;
    id = stoi(ip.substr(0, ip.find(".")));
    id = id * 1000000000;
    ip.erase(0, ip.find(".")+1);

    id = id + stoi(ip.substr(0, ip.find("."))) * 1000000;
    ip.erase(0, ip.find(".")+1);

    id = id + stoi(ip.substr(0, ip.find("."))) * 1000;
    ip.erase(0, ip.find(".")+1);

    id = id + stoi(ip);
    return id;
}

class almacen{
    private:
    string comp;
    string ip;
    int puerto;
    long int id;

    public:
    almacen();
    almacen(string);
    long int getID();
    int getPuerto();
    string getIP();
    string getComp();
    void setID(long int);
    void setPuerto(int);
    void setID(string);
};

almacen::almacen(){}

almacen::almacen(string line){
    comp = line;
    istringstream iss(line);
    string aux;
    string mes, numes, dia, hora, ipd, error;
    iss >> mes >> dia >> hora >> ipd >> ws;      //Se asignan los datos a variables auxiliares y se ignora un espacio
    getline(iss, error);
    string compIP = ipd;
    int pos;
    long int id2;

    pos = compIP.find(":");
    ip = compIP.substr(0, pos);
    compIP.erase(0, pos + 1);
    puerto = stoi(compIP);

    id = generarID(ip);
}

long int almacen::getID(){
    return id;
}

int almacen::getPuerto(){
    return puerto;
}

string almacen::getIP(){
    return ip;
}

string almacen::getComp(){
    return comp;
}


struct node{
    almacen data;
    struct node *left;
    struct node *right;
};

class BinaryTrees{
    private:
        node *root;
    public:
        BinaryTrees();
        void insertID(almacen,node*);
        void insertP(almacen,node*);
        void del(int);
        node* search(long int,long int,node*);
        node* searchP(int,node*);
        node* getRoot();
        node* searchL(long int,node*);
        node* searchR(long int,node*);
        bool isEmpty();
        void inOrderID(node*,long int,string);
        void inOrderP(node*, int,string);
        void inOrder(node*,string);
};

BinaryTrees::BinaryTrees(){
    root = NULL;
}

node* BinaryTrees::getRoot(){
    return root;
}

void BinaryTrees::insertID(almacen nuevo, node* temp){
    node *n = new node;
    n -> data = nuevo;
    if (root == NULL){
            root = n;
            n -> left = NULL;
            n -> right = NULL;
            temp = root;
            return;
    }else{
        if(temp -> left == NULL && temp -> right == NULL){
            if (n -> data.getID() < temp -> data.getID()){
                temp -> left = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }else{
                temp -> right = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }
        }else{
            if (n -> data.getID() < temp -> data.getID()){
                if (temp -> left == NULL){
                    temp -> left = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                temp = temp -> left;
                insertID(nuevo,temp);
            }else{
                if (temp -> right == NULL){
                    temp -> right = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                temp = temp -> right;
                insertID(nuevo,temp);
            }
        }
    }
}

void BinaryTrees::insertP(almacen nuevo,node* temp){
    node *n = new node;
    n -> data = nuevo;
    if (root == NULL){
            root = n;
            n -> left = NULL;
            n -> right = NULL;
            return;
    }else{
        if(temp -> left == NULL && temp -> right == NULL){
            if (n -> data.getPuerto() < temp -> data.getPuerto()){
                temp -> left = n;
            }else if (n -> data.getPuerto() > temp -> data.getPuerto()){
                temp -> right = n;
            }else{
                if (n -> data.getID() < temp -> data.getID()){
                    temp -> left = n;
                }else{
                    temp -> right = n;
                }
            }n -> left = NULL;
            n -> right = NULL;
            return;
        }else{
            if (n -> data.getPuerto() < temp -> data.getPuerto()){
                if (temp -> left == NULL){
                    temp -> left = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                temp = temp -> left;
                insertP(nuevo,temp);
            }else if (n -> data.getPuerto() < temp -> data.getPuerto()){
                if (temp -> right == NULL){
                    temp -> right = n;
                    n -> left = NULL;
                    n -> right = NULL;
                    return;
                }
                temp = temp -> right;
                insertP(nuevo,temp);
            }else{
                if (n -> data.getID() < temp -> data.getID()){
                    if (temp -> left == NULL){
                        temp -> left = n;
                        n -> left = NULL;
                        n -> right = NULL;
                        return;
                    }
                    temp = temp -> left;
                    insertP(nuevo,temp);
                }else{
                    if (temp -> right == NULL){
                        temp -> right = n;
                        n -> left = NULL;
                        n -> right = NULL;
                        return;
                    }
                    temp = temp -> right;
                    insertP(nuevo,temp);
                }
            }
        }
    }
}


void BinaryTrees::del(int del){
}

node* BinaryTrees::search(long int i, long int f, node* root){
    if (isEmpty() == false){
        if (root -> data.getID() >= i && root -> data.getID() <= f){
            return root;
        }else{
            if (f < root -> data.getID() && root -> left != NULL){
                return search(i,f,root -> left);
            }else if (i > root -> data.getID() && root -> right != NULL){
                return search(i,f,root -> right);
            }
        }
    }
    return root;
}

node* BinaryTrees::searchP(int s, node* root){
    if (isEmpty() == false){
        if (s < root -> data.getPuerto() && root -> left != NULL){
            return searchP(s,root -> left);
        }else if (s > root -> data.getPuerto() && root -> right != NULL){
            return searchP(s,root -> right);
        }else{
            node* nul = new node;
            if (s == root -> data.getID()){
                *nul = *root;
                return nul;
            }else{
                *nul = *root;
                return nul;
            }
        }
    }
    return root;
}

node* BinaryTrees::searchL(long int s, node* root){
    if (isEmpty() == false){
        if (s > root->data.getID()){
            if (s < root -> data.getPuerto() && root -> left != NULL){
                return searchP(s,root -> left);
            }else if (s > root -> data.getPuerto() && root -> right != NULL){
                return searchP(s,root -> right);
            }else{
                if (s == root -> data.getID()){
                    cout << "FOUND" << endl;
                    return root;
                }else{
                    return root;
                }
            }
        }else{
            return root;
        }
        
    }
    return root;
}

node* BinaryTrees::searchR(long int s, node* root){
    if (isEmpty() == false){
        if (s > root -> right -> data.getID()){
            if (s < root -> data.getPuerto() && root -> left != NULL){
                return searchP(s,root -> left);
            }else if (s > root -> data.getPuerto() && root -> right != NULL){
                return searchP(s,root -> right);
            }else{
                if (s == root -> data.getID()){
                    cout << "FOUND" << endl;
                    return root;
                }else{
                    cout << "FOUNDD2D" << endl;
                    return root;
                }
            }
        }else{
            cout << "ERROR" << endl;
            return root;
        }
        
    }
    cout << "ERROR2" << endl;
    return root;
}

void BinaryTrees::inOrderID(node *r, long int f,string nombre){
    if (r == NULL || r -> data.getID() > f){
        return;
    }
    inOrderID(r->left,f,nombre);

    ofstream archivo;
    archivo.open(nombre,ios::app);
    archivo << r -> data.getComp() << endl;
    archivo.close();
    // cout << r -> data.getComp() << endl;

    inOrderID(r->right,f,nombre);
}

void BinaryTrees::inOrderP(node *r, int f,string nombre){
    if (r == NULL || r -> data.getPuerto() > f){
        return;
    }

    inOrderP(r->left,f,nombre);

    ofstream archivo;
    archivo.open(nombre,ios::app);
    archivo << r -> data.getComp() << endl;
    archivo.close();

    inOrderP(r->right,f,nombre);
}

void BinaryTrees::inOrder(node *r, string nombre){
    if (r == NULL){
        return;
    }

    inOrder(r->left,nombre);

    ofstream archivo;
    archivo.open(nombre,ios::app);
    archivo << r -> data.getComp() << endl;
    archivo.close();
    cout << r -> data.getComp() << endl;

    inOrder(r->right,nombre);
}

bool BinaryTrees::isEmpty(){
    if (root == NULL){
        return true;
    }return false;
}


BinaryTrees rellenarID(string nombre){
    ifstream file(nombre);                          //Se abre el archivo
    string line;
    BinaryTrees baseID;

    while (getline(file,line)){     
        istringstream iss(line);
        almacen o(line);
        baseID.insertID(o,baseID.getRoot());
    }
    file.close();                                   //Se cierra el archivo
    return baseID;
}

BinaryTrees rellenarPuerto(string nombre){
    ifstream file(nombre);                          //Se abre el archivo
    string line;
    BinaryTrees basePuerto;

    while (getline(file,line)){
        istringstream iss(line);
        almacen o(line);
        basePuerto.insertP(o,basePuerto.getRoot());
    }
    file.close();                                   //Se cierra el archivo
    return basePuerto;
}


int main(){
    string nombre = "bitacora.txt";
    BinaryTrees ID = rellenarID(nombre);
    BinaryTrees Puerto = rellenarPuerto(nombre);

    string nombreID = "ip_ordenadas.txt";
    string nombreP = "puertos_ordenados.txt";

    ofstream archivoID;
    archivoID.open(nombreID,fstream::out);
    archivoID.close();
    ID.inOrderID(ID.getRoot(),generarID("999.999.999.999"),nombreID);

    ofstream archivoP;
    archivoP.open(nombreP,fstream::out);
    archivoP.close();
    Puerto.inOrder(Puerto.getRoot(),nombreP);

    string opcion,in,fi,nom;
    int i,f;

    do {
        // system("clear");
        cout << "----- Menu -----\n";
        cout << "1. Buscar rango de IPs\n";
        cout << "2. Buscar rango de Puertos\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (opcion == "1") {
            cout << "Buscar rango de IPs\n\n";
            cout << "Ingrese la ip donde empezar a buscar: ";cin >> in;
            cout << "Ingrese la ip donde terminar de buscar: ";cin >> fi;
            nom = "IP-" + in + "-" + fi + ".txt";
            ofstream archivo;
            archivo.open(nom,fstream::out);
            archivo.close();
            if (generarID(in) > generarID(fi)){
                cout << "\nEl inicio es mayor al final" << endl;
            }else{
                ID.inOrder(ID.search(generarID(in),generarID(fi),ID.getRoot()),nom);
                // ID.inOrderID(ID.search(generarID(fi),ID.getRoot()),generarID(in),nom);
            }
        } else if (opcion == "2") {
            cout << "Buscar rango de Puertos\n\n";
            cout << "Ingrese el puerto donde empezar a buscar: ";cin >> i;
            cout << "Ingrese el puerto donde terminar de buscar: ";cin >> f;
            nom = "Puertos-" + to_string(i) + "-" + to_string(f);
            ofstream archivo;
            archivo.open(nom,fstream::out);
            archivo.close();
            if (i > f){
                cout << "\nEl inicio es mayor al final" << endl;
            }else{
                Puerto.inOrderP(Puerto.searchP(i,Puerto.getRoot()),f,nom);
            }
        } else if (opcion == "0") {
            cout << "Saliendo...\n";
        } else {
            cout << "Opcion no valida. Por favor, elija una opcion entre 1 y 6, o 0 para salir.\n";
        }
    } while (opcion != "0");




    return 0;
}

