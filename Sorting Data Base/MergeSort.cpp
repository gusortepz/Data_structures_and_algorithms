#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;

vector<vector<string> > crearA(string nombre){//Esta función crea un vector de vectores con los datos proporcionado en el archivo de texto
    ifstream file(nombre);          //Se abre el archivo
    string line;
    vector<vector<string> > base;   //Se crea el vector

    while (getline(file,line)){     
        istringstream iss(line);    //Se guarda el contenido de la linea en la variable "iss" de tipo istringstream

        vector<string> campos;      //Se crea vector auxiliar
        string mes, numes, dia, hora, ip, error;
        iss >> mes >> dia >> hora >> ip >> ws;      //Se asignan los datos a variables auxiliares y se ignora un espacio
        getline(iss, error);                        //El restante de "iss" se asigna a "error"
        if (mes == "Jan"){                          //Se asigna un valor numérico a cada mes para poder comparar después
            numes = "1";
        }else if(mes == "Feb"){
            numes = "2";
        }else if(mes == "Mar"){
            numes = "3";
        }else if(mes == "Apr"){
            numes = "4";
        }else if(mes == "May"){
            numes = "5";
        }else if(mes == "Jun"){
            numes = "6";
        }else if(mes == "Jul"){
            numes = "7";
        }else if(mes == "Aug"){
            numes = "8";
        }else if(mes == "Sep"){
            numes = "9";
        }else if(mes == "Oct"){
            numes = "10";
        }else if(mes == "Nov"){
            numes = "11";
        }else if(mes == "Dec"){
            numes = "12";
        }
        campos.push_back(mes);                      //Se agregan al vector auxiliar los valores de las variables auxiliares
        campos.push_back(numes);
        campos.push_back(dia);
        campos.push_back(hora);
        campos.push_back(ip);
        campos.push_back(error);

        base.push_back(campos);                     //Se agregan los datos del vector auxiliar al vector final
    }
    file.close();                                   //Se cierra el archivo
    return base;
}

vector <vector<string> > merge(vector <vector<string> > left, vector<vector<string> > right){       //Utililzamos merge sort para ordenar el vector y se compara primero por mes y si coincide, por día, y si es el mismo día, por hora
    vector <vector<string> > sorted;
    int i = 0;
    int j = 0;
    int comp, comp2;
    while(i < left.size() && j < right.size()){
        comp = stoi(left[i][1]); comp2 = stoi(right[j][1]);
        if(comp == comp2){
            comp = stoi(left[i][2]);comp2 = stoi(right[j][2]);
            if (comp == comp2){
                if (left[i][3] < right[j][3]){
                    sorted.push_back(left[i]);
                    i++;
                }else{
                    sorted.push_back(right[j]);
                    j++;
                }
                }
                else if (comp < comp2){
                    sorted.push_back(left[i]);
                    i++;
                }else{
                    sorted.push_back(right[j]);
                    j++;
                }
        }else if(comp < comp2){
            sorted.push_back(left[i]);
            i++;
        }else{
            sorted.push_back(right[j]);
            j++;
        }
    }

    while(i < left.size()){
        sorted.push_back(left[i]);
        i++;
    }

    while(j < right.size()){
        sorted.push_back(right[j]);
        j++;
    }

    return sorted;
}


//Merge sort
vector <vector<string> > mergeSort(vector <vector<string> > arr){
    //Caso base
    if(arr.size() == 1){
        return arr;
    }

    //Caso general
    int mid = arr.size()/2;
    vector<vector<string> > left;
    vector<vector<string> > right;
    for(int i = 0; i < mid; i++){
        left.push_back(arr[i]);
    }
    for(int i = mid; i < arr.size(); i++){
        right.push_back(arr[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left,right);
}

int busqSecuencial(vector <vector<string> > arr, int m, int d){                         //Se utiliza una búsqueda secuencial para encontrar el índice del primer valor siempre y cuando sea mayor o igual a la fecha solicitada y recorre el arreglo de izquierda a derecha
    int n = arr.size();
    for(int i = 0; i < n; i++){
        if(stoi(arr[i][1]) >= m){
            if(stoi(arr[i][2]) >= d){
                return i;
            }
        }
    }
    return -1;
}

int busqSecuencial2(vector <vector<string> > arr, int m, int d){                        //Se utiliza una búsqueda secuencial para encontrar el índice superior para encontrar el último índice recorriendo el vector de derecha a izquierda
    int n = arr.size();
    for(int i = n-1; i >= 0; i--){
        if(stoi(arr[i][1]) <= m){
            if(stoi(arr[i][2]) <= d){
                return i;
            }
        }
    }
    return -1;
}

int main(){
    string nombre = "bitacora.txt";
    vector <vector <string> > base = crearA(nombre);
    base = mergeSort(base);
    
    int mes,dia,mes2,dia2,min,max;
    cout << "Bienvenido a el programa de búsqueda de errores por fecha";
    cout << endl << endl;
    int ver = 1;
    int nom = 1;
    while (ver == 1){
        cout << "Ingrese el # de mes de la fecha inicial: ";cin >> mes;
        cout << "Ingrese el dia de la fecha inicial: ";cin >> dia;

        cout << "Ingrese el # de mes de la fecha final: ";cin >> mes2;
        if (mes2 < mes){
            cout << "No puede ser una fecha anterior" << endl;
            return 0;
        }
        cout << "Ingrese el dia de la fecha final: ";cin >> dia2;
        if (dia2 < dia){
            cout << "No puede ser una fecha anterior" << endl;
            return 0;
        }
        string nomb = "archivo" + to_string(dia) + "." + to_string(mes) + "-" + to_string(dia2) + "." + to_string(mes2)+ ".txt";

        min = busqSecuencial(base, mes, dia);
        max = busqSecuencial2(base, mes2, dia2);
        ofstream archivo;
        archivo.open(nomb,fstream::out);

        for (int i = min; i <= max; ++i) {
            cout << base[i][0] << " " << base[i][1] << " " << base[i][2] << " " << base[i][3] << " " << base[i][4] << " " << base[i][5] << endl;
            archivo << base[i][0] << " " << base[i][1] << " " << base[i][2] << " " << base[i][3] << " " << base[i][4] << " " << base[i][5] << endl;
        }

        cout << endl << endl << "Quiere realizar otra búsqueda? \n'1' para si \n'2' para no \nIngrese: ";cin >> ver;
        nom ++;
    }
    
    return 0;
}