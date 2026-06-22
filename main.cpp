// DAVIDSON SANTOS DE OLIVEIRA
#include <iostream>
#include <vector>

struct edge {
    int vertice;
    int weight;

    edge(int v, int w) : vertice(v),
                         weight(w)
                            {}
};

struct vertice {
    int v;
    int mask;
    int dist;

    vertice(int _v, int _mask, int _dist) : v(_v),
                                            mask(_mask),
                                            dist(_dist)
                                            {} 

    //sobrecarga de operadores para fila de prioridades
    bool operator > (const vertice &v) const{
        return (this->dist > v.dist);
    }

    bool operator < (const vertice &v) const{
        return this->dist < v.dist;
    }

    bool operator >= (const vertice &v) const{
        return this->dist >= v.dist;
    }

    bool operator <= (const vertice &v) const{
        return this->dist <= v.dist;
    }
};

struct graph {
    //inicio sempre v[1] e fim sempre v[N]
    int n; //quantidade de vertices
    std::vector<std::vector<edge>> adj; //lista de adjecencia
    // std::vector<std::vector<int>> distances; // guarda a metrica de distancia dos vertices para o Dijkstra

    graph(int numVertices) : n(numVertices),
                            adj(numVertices + 1)
                            {}

    void addEdge(int u, int v, int w){ // adiciona as arestas u -> v
        adj[u].push_back( edge(v, w) );
    }

};

int main(){
    int N, M, T;
    int aux1, aux2, aux3;
    // N - num pontos turisticos (vertices)
    // M - numero de vias (arestas)
    // T - tempo até a apresentacao

     scanf("%d %d %d", &N, &M, &T);

    graph G(N);

    for(int i=0; i<M; i++){ // popula lista de adjascencias
        scanf("%d %d %d", &aux1, &aux2, &aux3);
        G.addEdge(aux1, aux2, aux3);
    }


    return 0;
}