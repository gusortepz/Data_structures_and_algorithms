//Este programa ordena un arreglo mediante bubblesort y merge sort y haces busquedasa mediante busqueda secuencial
// y busqueda binaria iterativa y recursiva
// Autor: Sebastian Vega Saint Martin
//Matricula: a01637397 



#include <iostream>
#include <vector>
using namespace std;


vector<int> bubbleSort(vector<int> arr,int n){

    //Caso Base
    if(n == 1){
        return arr;
    }

    //Caso general
    for(int i = 0; i < n-1; i++){
        if(arr[i] > arr[i+1]){
            int temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }

    return bubbleSort(arr,n-1);
    
}

//Funcio merge (Para merge sort)
vector<int> merge(vector<int> left, vector<int> right){
    vector<int> sorted;
    int i = 0;
    int j = 0;
    while(i < left.size() && j < right.size()){
        if(left[i] < right[j]){
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
vector<int> mergeSort(vector<int> arr){
    //Caso base
    if(arr.size() == 1){
        return arr;
    }

    //Caso general
    int mid = arr.size()/2;
    vector<int> left;
    vector<int> right;
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

int busqSecuencial(vector<int> arr, int x){
    int n = arr.size();
    for(int i = 0; i < n; i++){
        if(arr[i] == x){
            return i;
        }
    }
    return -1;
}

//Binary search iterativa
int busqBinariaIterativa(vector<int> arr, int x){
    int n = arr.size();
    int low = 0;
    int high = n-1;
    while(low <= high){
        int mid = (low+high)/2;
        if(arr[mid] == x){
            return mid;
        }else if(arr[mid] < x){
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return -1;
}

//Binary search recursiva
int busqBinariaRecursiva(vector<int> arr, int x, int low, int high){

    //Caso base
    if(low > high){
        return -1;
    }

    //Caso general
    int mid = (low+high)/2;
    if(arr[mid] == x){
        return mid;
    }else if(arr[mid] < x){
        return busqBinariaRecursiva(arr,x,mid+1,high);
    }else{
        return busqBinariaRecursiva(arr,x,low,mid-1);
    }
}

int main(){
    
    //Imprimir vector
    vector<int> arr = {8,6,3,4,5,9,1,2};
    int n = arr.size();
    cout << "Vector: "<< endl;
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    
    
    //Imprimir vector Bubble
    vector<int> sortedBubble = bubbleSort(arr,n);
    cout << "Bubble Sort: "<< endl;
    for(int i = 0; i < n; i++){
        cout << sortedBubble[i] << " ";
    }

    //Imprimir vector Merge
    vector<int> sortedMerge = mergeSort(arr);
    cout << endl << "Merge Sort: "<< endl;
    for(int i = 0; i < n; i++){
        cout << sortedMerge[i] << " ";
    }
    cout << endl;

    //Busqueda secuencial
    int x;
    cout << "Busqueda Secuencial" << endl;
    cout << "Ingrese el numero a buscar: ";
    cin >> x;

    int pos = busqSecuencial(sortedMerge,x);
    if(pos == -1){
        cout << "El numero no se encuentra en el vector" << endl;
    }else{
        cout << "El numero se encuentra en la posicion: " << pos << endl;
    }

    //Busqueda binaria iterativa
    cout << "Busqueda Binaria Iterativa" << endl;
    cout << "Ingrese el numero a buscar: ";
    cin >> x;

    pos = busqBinariaIterativa(sortedMerge,x);
    if(pos == -1){
        cout << "El numero no se encuentra en el vector" << endl;
    }else{
        cout << "El numero se encuentra en la posicion: " << pos << endl;
    }

    //Busqueda binaria recursiva
    cout << "Busqueda Binaria Recursiva" << endl;
    cout << "Ingrese el numero a buscar: ";
    cin >> x;
    
    pos = busqBinariaRecursiva(sortedMerge,x,0,n-1);
    if(pos == -1){
        cout << "El numero no se encuentra en el vector" << endl;
    }else{
        cout << "El numero se encuentra en la posicion: " << pos << endl;
    }

    return 0;
}

