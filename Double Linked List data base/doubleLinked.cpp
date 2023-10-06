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
    struct node *next;
    struct node *prev;
};

class doubleLinked{
    private:
    node *head;
    node *tail;
    node *temp;

    public:
    doubleLinked();
    void createID(almacen);
    void createP(almacen);
    string del(node*);
    string delID(long int, long int, doubleLinked*);
    string delP(int,int,doubleLinked*);
    string peek();
    bool isEmpty();
    node* readID(long int);
    void impP(int,int);
    void impID(string, string);
    bool crearArchivo(string);
};

doubleLinked::doubleLinked(){
    head = NULL;
    tail = NULL;
}


void doubleLinked::createID(almacen d){
    node* n = new node;
    n -> data = d;
    if (isEmpty() == true){
        tail = n;
        head = n;
        n -> next = NULL;
        n -> prev = NULL;
        return;
    }else{
        temp = head;
        if (n -> data.getID() < temp -> data.getID()){
            while (temp -> next != NULL){
                if (n -> data.getID() < temp -> data.getID()){
                    temp = temp -> next;
                }else{
                    n -> next = temp;
                    n -> prev = temp -> prev;
                    temp -> prev -> next = n;
                    temp -> prev = n;
                    return;
                }
            }n -> prev = tail;
            n -> next = NULL;
            tail -> next = n;
            tail = n;
            return;
        }else{
            n -> prev = NULL;
            n -> next = head;
            head -> prev = n;
            head = n;
            return;
        }
    }
}

void doubleLinked::createP(almacen d){
    node* n = new node;
    n -> data = d;
    if (isEmpty() == true){
        tail = n;
        head = n;
        n -> next = NULL;
        n -> prev = NULL;
        return;
    }else{
        temp = head;
        if (n -> data.getPuerto() < temp -> data.getPuerto()){
            if (temp -> next != NULL){
                while (temp -> next != NULL){
                    if (n -> data.getPuerto() < temp -> data.getPuerto()){
                        temp = temp -> next;
                    }else{
                        n -> next = temp;
                        n -> prev = temp -> prev;
                        temp -> prev -> next = n;
                        temp -> prev = n;
                        return;
                    }
                }n -> prev = temp;
                n -> next = NULL;
                temp -> next = n;
                tail = n;
                return;
            }
        }else{
            n -> prev = NULL;
            n -> next = head;
            head -> prev = n;
            head = n;
            return;
        }
    }
}


string doubleLinked::peek(){
    if (isEmpty() == false){
        return head->data.getComp();
    }
    else{
        return "";
    }
}


node* doubleLinked::readID(long int buscar){
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

void doubleLinked::impID(string inicio, string final){
    long int inID,fiID;
    node *b = new node;
    string nomb = "IP-" + inicio + "-" + final + ".txt";
    if (inicio == final){
        nomb = "IP-" + inicio + ".txt";
    }
    ofstream archivo;
    archivo.open(nomb,fstream::out);
    inID = generarID(inicio);
    fiID = generarID(final);
    if (isEmpty() == false){
        b = tail;
        int i = 0;
        while (inID <= b -> data.getID() && b -> prev != NULL){
            if (fiID >= b -> data.getID()){
                archivo << b -> data.getComp() << endl;
                i++;
                b = b -> prev;
            }else{
                break;
            }
        }if (i > 0){
            cout << "Se encontraron " << i << " IPs en ese rango. El archivo se creo correctamente." << endl;
        }
    }else{
        cout << "No se encontró el puerto deseado" << endl;
    }archivo.close();
}

void doubleLinked::impP(int buscar, int final){
    node *b = new node;
    string nomb = "Puerto_" + to_string(buscar) + "-" + to_string(final) + ".txt";
    if (buscar == final){
        nomb = "Puerto_" + to_string(buscar) + ".txt";
    }
    ofstream archivo;
    archivo.open(nomb,fstream::out);
    if (isEmpty() == false){
        b = tail;
        int i = 0;
        while (final >= b -> data.getPuerto() && b -> prev != NULL){
            if (buscar <= b -> data.getPuerto()){
                archivo << b -> data.getComp() << endl;
                i++;
            }b = b -> prev;
        }if (i > 0){
            cout << "Se encontraron " << i << " IPs en ese rango de puertos. El archivo se creo correctamente." << endl;
            archivo.close();
        }return;
    }
    archivo.close();
    cout << "No se encontró el puerto deseado" << endl;
}

string doubleLinked::delID(long int inicio, long int final, doubleLinked* baseP){
    if (isEmpty() == false){
        node* b = new node;
        b = head;
        int i = 0;
        if(inicio == final){
            baseP -> del(readID(inicio));
            return del(readID(inicio));
        }
        while(b != NULL && b->data.getID() >= inicio){
            if (b->data.getID() <= final){
                node* nextNode = b->next;
                del(b);
                del(baseP -> readID(b->data.getID()));
                i++;
                b = nextNode;
            } else {
                b = b->next;
            }
        }
        if (i > 0){
            string r = "Se eliminaron " + to_string(i) + " ips";
            return r;
        }return "No hubo elementos a eliminar";   
    }return "No se encontró el elemento a eliminar";
}

string doubleLinked::del(node* del){
    if (del != NULL){
        string regresar;
        if (del -> prev == NULL){
            del -> next -> prev = NULL;
            head = del -> next;
        }else if (del -> next == NULL){
            del -> prev -> next = NULL;
            tail = del -> prev;
        }else{
            del -> prev -> next = del -> next;
            del -> next -> prev = del -> prev;
        }
        regresar = "Se ha eliminado: " + del -> data.getComp();
        delete del;
        return regresar;
    }return "";
}

string doubleLinked::delP(int p, int f, doubleLinked* baseID){
    node *b = new node;
    if (isEmpty() == false){
        b = tail;
        int i = 0;
        string regresar;
        while (b -> data.getPuerto() <= f && b -> prev != NULL){
            if (b -> data.getPuerto() >= p){
                node* nextNode = b->prev;  // Guardamos el siguiente nodo antes de eliminar
                baseID->del(baseID->readID(b->data.getID()));
                del(b);
                b = nextNode;  // Movemos a b al siguiente nodo
                i++;
            }else{
                b = b -> prev;
            }
        }if (i > 0){
            regresar =  "Se eliminaron " + to_string(i) + " IPs con éxito del puerto " + to_string(p) + " al puerto " + to_string(f);
            return regresar;
        }
    }b = NULL;
    return "No se encontró el puerto deseado";
}


bool doubleLinked::isEmpty(){
    if (head == NULL && tail == NULL){
        return true;
    }return false;
}

bool doubleLinked::crearArchivo(string nombre){
    if (isEmpty() == false){
        ofstream archivo;
        archivo.open(nombre,fstream::out);
        node* b = new node;
        b = tail;
        while (b != NULL){
            archivo << b -> data.getComp() << to_string(b->data.getID()) << endl;
            b = b -> prev;
        }return true;
    }return false;
}


doubleLinked rellenarID(string nombre){
    ifstream file(nombre);          //Se abre el archivo
    string line;
    doubleLinked baseID;

    while (getline(file,line)){     
        istringstream iss(line);
        almacen o(line);
        baseID.createID(o);
    }
    file.close();                                   //Se cierra el archivo
    return baseID;
}

doubleLinked rellenarPuerto(string nombre){
    ifstream file(nombre);          //Se abre el archivo
    string line;
    doubleLinked basePuerto;

    while (getline(file,line)){
        istringstream iss(line);
        almacen o(line);
        basePuerto.createP(o);
    }
    file.close();                                   //Se cierra el archivo
    return basePuerto;
}

int main(){
    //Main for testing the functions
    string nombre = "bitacora.txt";
    doubleLinked baseID = rellenarID(nombre);
    doubleLinked baseP = rellenarPuerto(nombre);
    if(baseID.crearArchivo("ip_ordenadas.txt") == true && baseP.crearArchivo("puertos_ordenados.txt") == true){
        cout << "Los archivos ordenados se crearon correctamente" << endl;
    }else{
        cout << "No se pudieron crear los archivos correctamente" << endl;
    }
    int i,f;
    long int inicio, final;
    string opcion,in,fi;
    do {
        cout << "----- Menu -----\n";
        cout << "1. Buscar rango de IPs\n";
        cout << "2. Buscar rango de Puertos\n";
        cout << "3. Eliminar una IP\n";
        cout << "4. Eliminar un rango de IPs\n";
        cout << "5. Eliminar todas las IP de un puerto\n";
        cout << "6. Eliminar todas las IP de un rango de puertos\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (opcion == "1") {
            cout << "Buscar rango de IPs\n\n";
            cout << "Ingrese la ip donde empezar a buscar: ";cin >> in;
            cout << "Ingrese la ip donde terminar de buscar: ";cin >> fi;
            baseID.impID(in,fi);
        } else if (opcion == "2") {
            cout << "Buscar rango de Puertos\n\n";
            cout << "Ingrese el puerto donde empezar a buscar: ";cin >> i;
            cout << "Ingrese el puerto donde terminar de buscar: ";cin >> f;
            if (i > f){
                cout << "\nEl inicio es mayor al final" << endl;
            }else{
                baseP.impP(i,f);
            }
        } else if (opcion == "3") {
            cout << "Eliminar una IP\n\n";
            cout << "Ingresa la IP a eliminar: "; cin >> in;
            cout << baseID.delID(generarID(in),generarID(in),&baseP);
        } else if (opcion == "4") {
            cout << "Eliminar un rango de IPs\n\n";
            cout << "Ingrese la ip donde empezar a eliminar: ";cin >> in;
            cout << "Ingrese la ip donde terminar de eliminar: ";cin >> fi;
            cout << baseID.delID(generarID(in),generarID(fi),&baseP) << endl;
        } else if (opcion == "5") {
            cout << "Eliminar todas las IP de un puerto\n\n";
            cout << "Ingrese el puerto a eliminar: ";cin >> i;
            cout << baseP.delP(i,i,&baseID) << endl;
        } else if (opcion == "6") {
            cout << "Eliminar todas las IP de un rango de puertos\n\n";
            cout << "Ingrese el puerto donde empezar a buscar: ";cin >> i;
            cout << "Ingrese el puerto donde terminar de buscar: ";cin >> f;
            if (i > f){
                cout << "\nEl inicio es mayor al final" << endl;
            }else{
                cout << baseP.delP(i,f,&baseID) << endl;
            }
        } else if (opcion == "0") {
            cout << "Saliendo...\n";
        } else {
            cout << "Opcion no valida. Por favor, elija una opcion entre 1 y 6, o 0 para salir.\n";
        }
    } while (opcion != "0");
    return 0;
}