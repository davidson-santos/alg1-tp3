// DAVIDSON SANTOS DE OLIVEIRA
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

const long int INF = 2147483647;

struct edge {
    int vertice;
    int weight;

    edge(int v, int w) : vertice(v),
                         weight(w)
                            {}
};

struct graph {
    int n; //quantidade de vertices
    std::vector<std::vector<edge>> adj; //lista de adjecencia

    graph(int numVertices) : n(numVertices),
                            adj(numVertices + 1)
                            {
                            }

    void addEdge(int u, int v, int w){ // adiciona as arestas u -> v
        adj[u].push_back( edge(v, w) );
    }

};


void processaDP(graph &G,int N, long int T, std::vector<std::vector<long int>> &dp){
    dp[1][1] = 0;//caso base

    // para cada k incremental, computo qual o tempo a partir dos vértices computados em k-1 e que seja possível avançar para k
    for(int k=2; k<=N; k++){
        for(int i=1; i<=N; i++){
            for (edge e : G.adj[i]){
                dp[e.vertice][k] = std::min(dp[e.vertice][k], (dp[i][k-1] + e.weight));
            }
        }
    }
};


int main(){
    int N, M;
    long int T;
    int aux1, aux2, aux3;

    // N - num pontos turisticos (vertices)
    // M - numero de vias (arestas)
    // T - tempo até a apresentacao
    std::cin >> N >> M >> T;

    std::vector<std::vector<long int>> dp( 
        N+1, std::vector<long int>(N+1, INF));

    graph G(N);

    for(int i=0; i<M; i++){ // popula lista de adjascencias
        // scanf("%d %d %d", &aux1, &aux2, &aux3);
        std::cin >> aux1 >> aux2 >> aux3;
        G.addEdge(aux1, aux2, aux3);
    }

    // popula a matriz de estados da dp
    processaDP(G, N, T, dp);

    // verifica se foi possível encontrar um k máximo e qual eh ele
    int k = 0;
    for(int i=N; i>0; i--){
        if(dp[N][i] < INF){
            if(dp[N][i]<=T){
                k = i;
                break;
            }
        }
    }
    // caso nenhum k foi possível, retorna -1 e finaliza a execução
    if(k==0){
        printf("-1");
        return 0;
    }

    // impressao da quantidade de pontos possiveis de se visitar
    printf("%d\n", k);

    std::stack<int> backtrack;
    int ultimo = N;
    backtrack.push(ultimo);
    // backtrack do caminho encontrado que visita k pontos
    // armazena em uma stack para naturalmente inverter a ordem
    for(int i = k; i>1; i--){
        int antecessor_valido = -1;

        for(int j=1; j<=N; j++){
            for( edge e : G.adj[j]){
                if(e.vertice == ultimo && (dp[ultimo][i] == dp[j][i - 1] + e.weight)){
                    antecessor_valido = j;
                    break;
                }
            }
            if(antecessor_valido > -1) break;
        }
    
        backtrack.push(antecessor_valido);
        ultimo = antecessor_valido;
    }

    while (!backtrack.empty())
    {
        int aux = backtrack.top();
        backtrack.pop();
        printf("%d ", aux);
    }

    return 0;
};