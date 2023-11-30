#include <iostream>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Graph{
    private:
        int V; //Número de vertices
        list<int> *adj; //Adj list
    
    public:
        Graph(int V);
        void addEdge(int v, int w); //Agregar aristas
        void DFS(int S); //Deep First Search
        void BFS(int S); //Breath First Search
        bool isTree(int S);
        void topologicalSort();
        bool bipartiteGraph();
};

Graph::Graph(int V){    //Crear el objeto complejidad O(1)
    this -> V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){  //Agregar aristas complejidad O(1)
    adj[v].push_back(w);
}

void Graph::DFS(int s){     //Deep first search complejidad O(V + E)
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++){        //Poner todos los vertices en visited false
        visited[i] = false;
    }

    //Create stack
    stack<int> stack;
    stack.push(s);      //Agregar el nodo inicial de búsqueda

    while (!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s]){       //Se marca como visitado el nodo que estamos visitando
            cout << s << " ";
            visited[s] = true;

            for(list <int>::iterator i = adj[s].begin(); i != adj[s].end(); i++){       //Se agregan todas las conexiones del nodo mientras no esten visitados
                if (!visited[*i]){
                    stack.push(*i);
                }
            }
        }
    }
}

void Graph::BFS(int s){         //Breath First Search complejidad O(V + E)
    queue <int> queue;
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++){        //Poner todos los vertices en visited false
        visited[i] = false;
    }

    queue.push(s);          //Agregar el nodo inicial de búsqueda
    while (!queue.empty()){
        s = queue.front();
        queue.pop();

        if (!visited[s]){           //Se marca como visitado el nodo que estamos visitando
            cout << s << " ";
            visited[s] = true;
            for (list <int>::iterator i = adj[s].begin(); i != adj[s].end(); i++){          //Se agregan todas las conexiones del nodo mientras no esten visitados
                if (!visited[*i]){
                    queue.push(*i);
                }
            }
        }
    }
}



bool Graph::isTree(int s){         //Breath First Search complejidad O(V + E)
    queue <int> queue;
    bool *visited = new bool[V];
    bool *parent = new bool[V];

    for (int i = 0; i < V; i++){        //Poner todos los vertices en visited false
        visited[i] = false;
    }

    queue.push(s);          //Agregar el nodo inicial de búsqueda
    while (!queue.empty()){
        s = queue.front();
        queue.pop();

        if (!visited[s]){           //Se marca como visitado el nodo que estamos visitando
            visited[s] = true;
            for (list <int>::iterator i = adj[s].begin(); i != adj[s].end(); i++){          //Se agregan todas las conexiones del nodo mientras no esten visitados
                if (!visited[*i]){
                    queue.push(*i);
                    parent[*i] = s;
                }else{
                    if (parent[s] != *i){
                        return false;
                    }
                }
            }
        }
    }return true;
}




int main(){
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(3,4);

    g.DFS(0);
    cout << endl;
    g.BFS(0);

    return 0;
}