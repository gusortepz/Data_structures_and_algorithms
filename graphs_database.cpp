#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const int miTop = 5;

class Graph{
    private:
        int V; //Número de vertices
        list<int> *adj; //Adj list
        vector<vector <int > > repeticion;
    
    public:
        Graph(int V);
        void addEdge(int v, int w); //Agregar aristas
        void DFS(int S); //Deep First Search
        void BFS(int S); //Breath First Search
        bool isTree(int S);
        void topologicalSort();
        void topologicalSortDFS(int v, bool visit[], stack<int> &stack);
        bool bipartiteGraph();
        void addEdgeIP(string);
        void rellenarIP(string);
        void fanOut();
        void maxFan();
};

Graph::Graph(int V){    //Crear el objeto complejidad O(1)
    this -> V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){  //Agregar aristas complejidad O(1)
    cout << "Paso 3" << endl;
    adj[v].push_back(w);
    cout << "Paso 4 " << adj[v].size()  << endl;
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


//mwtodo que ordena en forma ascendente los datos con el método de DFS o BFS (o ambos)
void Graph::topologicalSort(){
    bool *visit = new bool[V];
    stack<int> stack;

    //Inicializar visitados en false
    for(int i=0;i<V;i++){
        visit[i] = false;
    };

    //Recorrer el grafo
    for(int i=0;i < V; i++){
        if(!visit[i]){
            topologicalSortDFS(i,visit,stack);
        };
    };

    //Imprimir el orden topologico
    while(!stack.empty()){
        cout << stack.top() << " ";
        stack.pop();
    };
};

//Metodo para topologicalSort que recorre el grafo DFS
void Graph::topologicalSortDFS(int v, bool visit[], stack<int> &stack){
    //Marcar el nodo actual como visitado
    visit[v] = true;

    //Recorrer los nodos adyacentes
    for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!visit[*i]){
            topologicalSortDFS(*i,visit,stack);
        };
    };

    //Agregar el nodo actual al stack
    stack.push(v);
};

//Diga si el Grafo Dirigido (DAG) puede ser representado como Grafo bipartita.
bool Graph::bipartiteGraph(){
    bool *visit = new bool[V];
    //Esta variable se utiliza para marcar los nodos con un color y asi poder spararlos en dos grupos
    int *color = new int[V];

    //Inicializar visitados en false y color en -1 (sin color)
    for(int i = 0; i < V; i++){
        visit[i] = false;
        color[i] = -1;
    };

    //Crear cola y agregar la serach key y asignarle un color inicial
    queue<int> q;
    q.push(0);
    color[0] = 1;

    //Recorrer el grafo
    while(!q.empty()){
        int s = q.front(); //La nueva search key es el elemento con mas prioridad
        q.pop();

        //Si no esta visitado, imprimir y marcar como visitado
        if (!visit[s]) {
            visit[s] = true;
            for(list<int>::iterator j = adj[s].begin(); j != adj[s].end(); ++j){
                //Si el nodo adyacente no ha sido visitado, se le asigna un color diferente al de su padre
                if(!visit[*j]){
                    q.push(*j);
                    color[*j] = 1 - color[s];
                }else{
                    if(color[s] == color[*j]){
                        return false;
                        //Si un nodo adyacente ya ha sido visitado, se verifica si su color es diferente
                        //Si es así el grafo no es bipartito
                    };
                };
            };
        };
    };
    return true;
};

void Graph::addEdgeIP(string line){
    string comp = line;
    istringstream iss(line);
    string aux;
    string mes, numes, dia, hora, ipd, error;
    iss >> mes >> dia >> hora >> ipd >> ws;      //Se asignan los datos a variables auxiliares y se ignora un espacio
    getline(iss, error);
    string compIP = ipd;
    int pos;

    pos = compIP.find(":");
    string ip = compIP.substr(0, pos);
    compIP.erase(0, pos + 1);

    int id1, id2, id3, id4;
    id1 = stoi(ip.substr(0, ip.find(".")));
    ip.erase(0, ip.find(".") + 1);

    id2 = stoi(ip.substr(0, ip.find(".")));
    ip.erase(0, ip.find(".") + 1);

    id3 = stoi(ip.substr(0, ip.find(".")));
    ip.erase(0, ip.find(".") + 1);

    id4 = stoi(ip);

    addEdge(id1,id2);
    addEdge(id2,id3);
    addEdge(id3,id4);

    vector <int> r;

    r.push_back(id1);
    r.push_back(id2);
    r.push_back(id3);
    r.push_back(id4);
    repeticion.push_back(r);
}

void Graph::rellenarIP(string nombre){
    ifstream file(nombre);                          //Se abre el archivo
    string line;

    while (getline(file,line)){
        istringstream iss(line);
        addEdgeIP(line);
    }
    file.close();                        //Se cierra el archivo
}

void Graph::fanOut(){
    int t = 0;
    for (int i = 0; i <= 999; i++){
        cout << "Nodo " << i << " repeticiones: " << adj[i].size() << endl;
        if (adj[i].size() > adj[t].size()){
            t = i;
        }
    }
    cout << endl << endl << "TOP: ";
    cout << t << " con " << adj[t].size() << endl;
}

void Graph::maxFan(){
    int top = 0;
    int sum = 0;
    int msum = 0;
    for (int i = 0; i < repeticion.size(); i++){
        sum = adj[repeticion[i][0]].size() + adj[repeticion[i][1]].size() + adj[repeticion[i][2]].size() + adj[repeticion[i][3]].size();
        if (sum > top){
            top = i;
            msum = sum;
        }
    }
    cout << endl << "Max fan out: " << to_string(repeticion[top][0]) << "." << to_string(repeticion[top][1]) << "." << to_string(repeticion[top][2]) << "." << to_string(repeticion[top][3]) << endl;
    cout << endl << to_string(repeticion[top][0]) << " repeticiones: " << adj[repeticion[top][0]].size() << endl;
    cout << to_string(repeticion[top][1]) << " repeticiones: " << adj[repeticion[top][1]].size() << endl;
    cout << to_string(repeticion[top][2]) << " repeticiones: " << adj[repeticion[top][2]].size() << endl;
    cout << to_string(repeticion[top][3]) << " repeticiones: " << adj[repeticion[top][3]].size() << endl;
    cout << "Total: " << msum << endl;
}


int main(){
    string nombre = "bitacora.txt";
    Graph graph(999);
    graph.rellenarIP(nombre);
    graph.fanOut();
    graph.maxFan();

    return 0;
}