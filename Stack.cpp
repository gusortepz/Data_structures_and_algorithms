#include <iostream>

using namespace std;

#define SIZE 10

class Stack{
    private:
    int *arr;
    int top;
    int capacity;

    public:
        Stack(int size = SIZE);
        void push(int);
        int pop();
        int peek();
        int size();
        
        bool isEmpty();
        bool isFull();
};


Stack::Stack(int size){
    capacity = -1;
}

void Stack::push(int agregar){
    if(isFull() == false){
        capacity ++;
        arr[capacity] = agregar;
        top = agregar;
    }
}

int Stack::pop(){
    if (isEmpty() == false){
        int key = top;
        arr[capacity] = 0;
        capacity = capacity - 1;
        top = arr[capacity];
        return key;
    }return 0;
}

int Stack::peek(){
    return top;
}

int Stack::size(){
    return capacity + 1;
}

bool Stack::isEmpty(){
    if (capacity == -1){
        return true;
    }return false;
}

bool Stack::isFull(){
    if (capacity+1 >= SIZE){
        return true;
    }return false;
}

int main(){
    Stack st;
    st.push(2);
    st.push(4);
    st.push(5);

    cout << st.isFull() << endl;
    cout << st.isEmpty() << endl;
    

    cout << "El tamaño del arreglo es: " << st.size() << endl;

    int pee = st.peek();
    int top = st.pop();
    cout << "El último número fue: " << pee << endl;
    cout << "Se eliminó el número: " << top << endl;
    cout << "El tamaño del arreglo es: " << st.size() << endl;

    int pee2 = st.peek();
    int top2 = st.pop();

    cout << "El último número fue: " << pee2 << endl;
    cout << "Se eliminó el número: " << top2 << endl;
    cout << "El tamaño del arreglo es: " << st.size() << endl;
    


    return 0;
}