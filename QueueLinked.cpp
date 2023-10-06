#include <iostream>


using namespace std;

/**
 * The above code defines a struct type called "node" that contains an integer data member and a
 * pointer to another node.
 * The data property is an integer that stores the value of the node. It can be
 * any integer value.
 * The "next" property is a pointer to the next node in a linked list. It is used to
 * connect nodes together and create a sequence of nodes.
 */
struct node{
    int data;
    struct node *next;
};


/* The LinkedList class represents a linked list data structure and provides methods for creating,
deleting, peeking, checking if it's empty, reading, and updating nodes in the list. */
class LinkedList{
    private:
    node *head;
    node *tail;
    node *temp;

    public:
    LinkedList();
    void create(int);
    int del(int data);
    int peek();
    bool isEmpty();
    node read(int);
    void update(int,int);
};

/**
 * The LinkedList constructor initializes the head and tail pointers to NULL.
 */
LinkedList::LinkedList(){
    head -> next = NULL;
    tail -> next = NULL;
}

/**
 * The create function adds a new node with the given data to a linked list in ascending order.
 * 
 * The parameter "agregar" is an integer value that represents the data to be added to
 * the linked list.
 * 
 * The function does not have a return type specified, so it does not explicitly return
 * anything. However, it does have a return statement within an if condition, which will exit the
 * function and return control to the calling code if the condition is true.
 * 
 * Complexity: O(n) because it has to go through the whole list to find the right place to insert the new node.
 */
void LinkedList::create(int agregar){
    node* n = new node;
    if (isEmpty() == true){
        tail -> next = n;
        head -> next = n;
        n -> next = NULL;
        n -> data = agregar;
        return;
    }else{
        n -> data = agregar;
        if (n->data < head -> next -> data){
            *temp = *head;
            n -> next = temp -> next -> next;
            temp -> next -> next = n;
            while (n -> next != NULL){
                if(n->data < n -> next -> data){
                    temp -> next -> next = n -> next;
                    n -> next = n -> next -> next;
                    temp -> next = temp -> next -> next;
                    temp -> next -> next = n;
                }else{
                    return;
                }
            }tail -> next = n;
            n -> next = NULL;
        }else{
            n -> next = head -> next;
            head -> next = n;
        }
    }
}


/**
 * The function deletes a node with the specified data from a linked list.
 * 
 * The parameter "data" represents the value of the node that needs to be deleted from the
 * linked list.
 * 
 * Returns the value of the data that was deleted from the linked list. If no data is found or if the
 * linked list is empty, it returns -1.
 * 
 * Complexity: O(n) because it has to go through the whole list to find the node to delete.
 */
int LinkedList::del(int data){
    if (isEmpty() == false){
        *temp = *head;
        while (temp -> next -> next != NULL){
            if (temp -> next -> data == data){
                temp -> next = temp -> next -> next;
                return data;
            }temp -> next = temp -> next -> next;
        }
    }return -1;
}

/**
 * The `peek` function returns the data value of the next node in the linked list, or -1 if the list is
 * empty.
 * 
 * Returns the data value of the node that is next to the head node in the linked list. If the linked
 * list is empty, it returns -1.
 * 
 * Complexity: O(1) because it only has to look at the first node.
 */
int LinkedList::peek(){
    if (isEmpty() == false){
        return head->next->data;
    }
    else{
        return -1;
    }
}

/**
 * The function reads through a linked list and returns the node with the specified data value, or a
 * node with data value -1 if the specified value is not found.
 * 
 * The parameter "buscar" is an integer value that represents the data value that we are
 * searching for in the linked list.
 * 
 * The code is returning a node from the linked list that contains the data value equal to the
 * "buscar" parameter. If such a node is found, it is returned. If no node with the specified data
 * value is found, a node with data value -1 is returned.
 * 
 * Complexity: O(n) because it has to go through the whole list to find the node to read.
 */
node LinkedList::read(int buscar){
    if (isEmpty() == false){
        *temp = *head;
        while (temp -> next -> next != NULL){
            if (temp -> next -> data == buscar){
                return *temp;
            }temp -> next = temp -> next -> next;
        }
    }temp -> data = -1;
    return *temp;
}

/**
 * The function updates the data of a node in a linked list with a new value.
 * 
 * The parameter "buscar" is an integer value that represents the data value to be
 * searched for in the linked list.
 * The parameter "reemplazar" is an integer value that will be used to replace the
 * data of a node in the linked list.
 * 
 * Complexity: O(n) because it has to go through the whole list to find the node to update.
 */
void LinkedList::update(int buscar, int reemplazar){
    if (isEmpty() == false){
        read(buscar).next -> data = reemplazar;
    }
}

/**
 * The function checks if a linked list is empty by checking if both the head and tail pointers are
 * NULL.
 * 
 * Returns a boolean value. If the condition `head -> next == NULL && tail -> next == NULL` is true,
 * then the function returns `true`. Otherwise, it returns `false`.
 * 
 * Complexity: O(1) because it only has to look at the first node.
 */
bool LinkedList::isEmpty(){
    if (head -> next == NULL && tail -> next == NULL){
        return true;
    }return false;
}

int main(){
    //Main for testing the functions
    LinkedList n;
    cout << n.isEmpty() << endl;
    n.create(1);
    n.create(9);
    n.create(3);
    n.create(29);
    n.create(220);
    n.create(21);
    cout << n.read(299).next -> data << endl;
    n.update(299,300);
    cout << n.peek() << endl;
    cout << n.del(21) << endl;
    cout << n.peek() << endl;
    cout << n.del(29) << endl;
    cout << n.peek() << endl;
    cout << n.del(220) << endl;
    cout << n.peek() << endl;
    cout << n.del(3) << endl;
    cout << n.peek() << endl;
    cout << n.del(9) << endl;
    cout << n.peek() << endl;
    cout << n.del(1) << endl;
    cout << n.isEmpty() << endl;
    return 0;
}
