#include <iostream>
#include <limits>
using namespace std;


const int INF = numeric_limits<int>::max();
//definiendo el infinito

int min(int a, int b){
    if(a < b) return a;
    return b;
}

// algoritmo de Dijkstra
int** dijkstra(int** graph, int n, int source) {

  // Matriz para almacenar las distancias mínimas
  int** distances = new int*[n + 1];
  for (int i = 0; i < n + 1; i++) {
    distances[i] = new int[n + 1];
  }

  // Inicializar la matriz de distancias a infinito
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      distances[i][j] = INF;
    }
  }

  // Distancia del nodo origen a sí mismo es 0
  distances[source][source] = 0;

  // arreglo para almacenar los nodos visitados
  bool visited[n + 1];
  for (int i = 0; i < n + 1; i++) {
    visited[i] = false;
  }

  // Bucle principal del algoritmo
  for (int i = 0; i < n; i++) {

    // Encontrar el nodo no visitado con la distancia mínima
    int min_distance = INF;
    int min_index = -1;
    for (int j = 0; j < n + 1; j++) {
      if (!visited[j] && distances[source][j] < min_distance) {
        min_distance = distances[source][j];
        min_index = j;
      }
    }

    // Marcar el nodo como visitado
    visited[min_index] = true;

    // Actualizar las distancias de los nodos adyacentes
    for (int j = 0; j < n + 1; j++) {
      if (!visited[j] && graph[min_index][j] != INF) {
        distances[source][j] = min(distances[source][j], distances[source][min_index] + graph[min_index][j]);
      }
    }
  }

  return distances;
}

int main(){

int N, M, P, G;

cin >> N >> M >> P >> G;

 // Crear una matriz dinámica de adyacencia
int** matriz = new int*[N + 1];
  for (int i = 0; i < N + 1; i++) {
    matriz[i] = new int[N + 1];
}

// Inicializamos la matriz en INF
for (int i = 0; i < N + 1; i++) {
  for (int j = 0; j < N + 1; j++) {
    matriz[i][j] = INF;
  }
}

//ciclo para llenar la matriz en los puntos donde el vértice no tiene arista consigo mismo
int i = 1;
while(i <= N){
    int j = 1;
    while(j <= N){
        if(i == j){
            matriz[i][j] = 0;
        }
        j++;
    }
    i++;
}


//tomamos los valores de pesos de la aristas y los ingresamos en la matriz en sus índices correspondientes
i = 1;
while(i <= M){
    int U, V, D;
    cin >> U >> V >> D;
    matriz[U][V] = D;
    matriz[V][U] = D; 
    i++;
}


//copia de matriz dinámica de adyacencia
int** matriz_copy = new int*[N + 1];
  for (int i = 0; i < N + 1; i++) {
    matriz_copy[i] = new int[N + 1];
}

for (int i = 0; i < N + 1; i++) {
  for (int j = 0; j < N + 1; j++) {
    matriz_copy[i][j] = matriz[i][j];
  }
}

//generamos una matriz de distancias mínimas empleando dijkstra
int** distances = dijkstra(matriz, N, P);

cout << endl << endl;

//matriz de distancias simplificada. Nos servirá para encontrar los candidatos
int* simplified_matrix = new int[N+1];

int k = 0;
while(k < N + 1){
    simplified_matrix[k] = distances[P][k];
    k++;
}

//este valor es el que multiplicaremos para hallar los candidatos
int punto_encuentro = simplified_matrix[G];
int counter = 0;
for(int i = 0; i <= N; i++){
    if(simplified_matrix[i] == punto_encuentro * 2){
        counter++;
    }
}

//arreglo de candidatos para escoger el punto falso de encuentro
int candidatos[counter];

i = 0;
while( i < counter){
    int j = 1;
    while(j <= N){
        if(punto_encuentro * 2 == simplified_matrix[j]){
            candidatos[i] = j;
            i++;
        }
        j++;
    }
}


//creamos una matriz de distancias mínimas desde G con la que verificaremos cuáles de los candidatos sí pueden ser los nodos de destino "falsos"
int** distances_from_G = dijkstra(matriz_copy, N, G);


//construimos nuestro arreglo de distancias simplificadas para el punto G
int* simplified_from_G = new int[N+1];

k = 0;
while(k < N + 1){
    simplified_from_G[k] = distances_from_G[G][k];
    k++;
}

int candidates_counter = 0;

//en este ciclos hacemos la impresión de que hallamos los candidatos correctos e imprimimos por pantalla el identificador del nodo
int l = 0;
while(l < counter){
    if(simplified_from_G[candidatos[l]] == punto_encuentro){
        candidates_counter++;
        cout << candidatos[l] << " ";
    }
    l++;
}

//caso de que no exista ningún candidato
if(candidates_counter == 0){
    cout << "*";
}

//finalmente eliminamos las matrices y arreglos después de usarlos
for (int i = 0; i < N + 1; i++) {
  delete[] matriz[i];
}
delete[] matriz;


delete[] simplified_matrix;

for (int i = 0; i < N + 1; i++) {
  delete[] matriz_copy[i];
}
delete[] matriz_copy;

delete[] simplified_from_G;

}