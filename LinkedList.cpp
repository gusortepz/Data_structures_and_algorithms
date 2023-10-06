#include <iostream>


using namespace std;

struct node{
    int data;
    struct node *next;
};

class LinkedList{
    private:
    node *head;
    node *tail;
    node *temp;

    public:
    LinkedList();
    void push(int);
    int pop();
    int peek();
    bool isEmpty();
};

LinkedList::LinkedList(){
    head -> next = NULL;
    tail -> next = NULL;
}

void LinkedList::push(int agregar){
    node* n = new node;
    if (head -> next == NULL && tail -> next == NULL){
        tail -> next = n;
        n -> next = NULL;
    }else{
        n -> next = head -> next;
    }
    n -> data = agregar;
    n -> next = head -> next;
    head -> next = n;
    
}

int LinkedList::pop(){
    int t = head -> next -> data;
    *temp = *head;
    *head = *head -> next;
    delete temp -> next;
    return t;
}

int LinkedList::peek(){
    return head -> next -> data;
}

bool LinkedList::isEmpty(){
    if (head -> next == NULL && tail -> next == NULL){
        return true;
    }return false;
}

int main(){
    LinkedList n;
    cout << n.isEmpty() << endl;
    n.push(1);
    n.push(2);
    n.push(3);
    cout << n.peek() << endl;
    cout << n.pop() << endl;
    cout << n.peek() << endl;
    return 0;
}