#include <iostream>

using namespace std;


void merge(int arreglo[], int p, int q, int r){
    int nL = q-p+1;
    int nR = r-q;
    int L[nL];
    int R[nR];
    for (int i=0; i <= nL-1; i++){
        L[i] = arreglo[p + i];
    }
    for (int j=0; j <= nR-1; j++){
        R[j] = arreglo[q+j+1];
    }
    int i = 0;
    int j = 0;
    int k = p;

    while (i < nL && j < nR){
        if (L[i] <= R[j]){
            arreglo[k] = L[i];
            i++;
        }else{
            arreglo[k] = R[j];
            j++;
        }k++;
    }
    while (i < nL){
        arreglo[k] = L[i];
        i++;
        k++;
    }while (j < nR){
        arreglo[k] = R[j];
        j++;
        k++;
    }
}

void ordenaMerge(int arreglo[], int p, int r){
    if (p >= r){
        return;
    }
    int q = (p+r)/2;
    cout << "q: " << q << endl;
    ordenaMerge(arreglo, p, q);
    ordenaMerge(arreglo, q+1, r);
    merge(arreglo, p, q, r);
}




int main(){
    int arreglo[] = {22,1,43,6,65,2,564,457,132,547,13,47,658};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);


    int p = 0;
    int r = n-1;

    ordenaMerge(arreglo, p, r);
    for (int i = 0; i < n; i++){
        cout << arreglo[i] << endl;
    }

    return 0;
}