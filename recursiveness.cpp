#include <iostream>

using namespace std;

int sumaIterativa(int n){
    int it = 0;
    for (int i = 1; i <= n; i++){
        it = it + i;
    }
    return it;
}

int sumaRecursiva(int n, int sum){
    if (n < 0){
        return sum;
    }
    sum = sum + n;
    sum = sumaRecursiva(n - 1, sum);
    return sum;
}

int sumaDirecta(int n){
    return (((1+n)*n)/2);
}

int main(){
    int num;
    int sum = 0;
    cout << "Ingrese n: "; cin >> num;
    cout << "Iterativa: " << sumaIterativa(num) << endl;
    cout << "Recursiva: " << sumaRecursiva(num,sum) << endl;
    cout << "Directa: " << sumaDirecta(num) << endl;
    return 0;
}







