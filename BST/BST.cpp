#include <iostream>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const int miTop = 5;

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
    vector <almacen> repeticion;
    struct node *left;
    struct node *right;
};

class BinaryTrees{
    private:
        node *root;
        vector <node*> top;
    public:
        BinaryTrees();
        void insert(almacen, node*);
        void del(int);
        bool isEmpty();
        node* getRoot();
        void printTop();
};

BinaryTrees::BinaryTrees(){
    root = NULL;
    node *n = new node;
    almacen no("Jun 26 00:00:00 0.0.0.0:0000 Prueba");
    n -> repeticion.push_back(no);
    for (int i = 0; i < miTop; i++){
        top.push_back(n);
    }
}

node* BinaryTrees::getRoot(){
    return root;
}


void BinaryTrees::insert(almacen nuevo, node*root){
    if (root == NULL){
        node *n = new node;
        n -> data = nuevo;
        this -> root = n;
        n -> left = NULL;
        n -> right = NULL;
        return;
    }else{
        if (nuevo.getPuerto() < root -> data.getPuerto()){
            if (root -> left == NULL){
                node *n = new node;
                n -> data = nuevo;
                root -> left = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }
            insert(nuevo, root -> left);
        }else if (nuevo.getPuerto() > root -> data.getPuerto()){
            if (root -> right == NULL){
                node *n = new node;
                n -> data = nuevo;
                root -> right = n;
                n -> left = NULL;
                n -> right = NULL;
                return;
            }
            insert(nuevo, root -> right);
        }else{
            root -> repeticion.push_back(nuevo);
            node *n = new node;
            for (int i = 0; i < miTop; i++){
                if (root -> repeticion.size() > top[i] -> repeticion.size()){
                    n = root;
                    root = top[i];
                    top[i] = n;
                }
            }
            return;
        }
    }
}


void BinaryTrees::del(int del){
}

bool BinaryTrees::isEmpty(){
    if (root == NULL){
        return true;
    }return false;
}

void BinaryTrees::printTop(){
    for (int i = 0; i < miTop; i++){
        cout << "Puerto " << top[i] -> data.getPuerto() << "  Repeticiones " << top[i] -> repeticion.size() + 1 << endl;
        cout << 1 << ": " << top[i] -> data.getComp() << endl;
        for (int j = 0; j < top[i] -> repeticion.size(); j++){
            cout << j + 2 << ": " << top[i] -> repeticion[j].getComp() << endl;
        }
        cout << endl << endl;
    }
}



BinaryTrees rellenarPuerto(string nombre){
    ifstream file(nombre);                          //Se abre el archivo
    string line;
    BinaryTrees basePuerto;

    while (getline(file,line)){
        istringstream iss(line);
        almacen o(line);
        basePuerto.insert(o, basePuerto.getRoot());
    }
    file.close();                        //Se cierra el archivo
    return basePuerto;
}


int main(){
    string nombre = "bitacora.txt";
    BinaryTrees Puerto = rellenarPuerto(nombre);

    string opcion,in,fi,nom;
    int i,f;

    Puerto.printTop();


    return 0;
}