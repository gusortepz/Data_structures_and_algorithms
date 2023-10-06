#include <iostream>

using namespace std;

void insertion(int arreglo[], int n){
    int j = 0;
    int key = 0;
    for (int i = 1; i < n; i++){
        key = arreglo[i];
        j = i - 1;
        while (j > -1 && arreglo[j] > key){
            arreglo[j+1] = arreglo [j];
            j = j - 1;
        }
        arreglo[j+1] = key;
    }
}


int main(){
    int arreglo[] = {2,1,7,5,3};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    insertion(arreglo, n);
    for (int i = 0; i < n; i++){
        cout << arreglo[i] << endl;
    }
    return 0;
}