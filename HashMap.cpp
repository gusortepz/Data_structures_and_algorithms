#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

//Generamos un ID único en base a su IP para facilitar el ordenamiento
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
    struct node *next;
};

class linkedList{
    private:
    node *head;
    node *tail;
    node *temp;

    public:
    linkedList();
    void create(almacen);
    bool isEmpty();
    node* read(long int);
    void impP(int,int);
    void impID(string, string);
    bool crearArchivo(string);
};

linkedList::linkedList(){
    head = NULL;
    tail = NULL;
}


void linkedList::create(almacen d){
    node* n = new node;
    if (isEmpty() == true){
        tail = n;
        head = n;
        n -> next = NULL;
        n -> data = d;
        return;
    }else{
        n -> data = d;
        tail -> next = n;
        tail = n;
        n -> next = NULL;
    }
}

node* linkedList::read(long int buscar){
    node *b = new node;
    if (isEmpty() == false){
        b = head;
        while (b != NULL){
            if (b -> data.getID() == buscar){
                return b;
            }b = b -> next;
        }
    }
    b = NULL;
    return b;
}

bool linkedList::isEmpty(){
    if (head == NULL && tail == NULL){
        return true;
    }return false;
}

int hashC(long int id){
    long int sum = 0;
    string str = to_string(id);
    for (char digit : str) {
        if (isdigit(digit)) {  // Asegurarse de que el carácter es un dígito
            sum += static_cast<int>(digit);  // Convertir el dígito a su valor ASCII y sumarlo
        }
    }
    return sum / 100000000000;
}

unordered_map<int, linkedList> rellenarID(string nombre){
    unordered_map<int, linkedList> Hash;
    ifstream file(nombre);          //Se abre el archivo
    string line;
    linkedList l1;
    linkedList l2;
    linkedList l3;
    linkedList l4;
    linkedList l5;
    linkedList l6;
    linkedList l7;
    linkedList l8;
    linkedList l9;
    linkedList l10;

    Hash[1] = l1;
    Hash[2] = l2;
    Hash[3] = l3;
    Hash[4] = l4;
    Hash[5] = l5;
    Hash[6] = l6;
    Hash[7] = l7;
    Hash[8] = l8;
    Hash[9] = l9;
    Hash[10] = l10;

    while (getline(file,line)){     
        istringstream iss(line);
        almacen o(line);
        Hash[hashC(o.getID())].create(o);
    }
    file.close();                                   //Se cierra el archivo
    return Hash;
}


int main(){
    string nombre = "bitacora.txt";
    unordered_map<int, linkedList> Hash = rellenarID(nombre);


    return 0;
}