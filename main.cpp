#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <limits>
#include <sstream>
#include <fstream>
#include <time.h>
#include <unordered_map>
//Archivos
#include "lista.h"
#include "hero.h"
#include "avl.h"
#include "hashtable.h"
#include "grafo.h"
#include "csv.h"
#include "dijstra.h"
using namespace std;

void characterConnections(){
    string dataBase = "marvel_clean.csv";
    cout << "DATA BASE: " << dataBase << endl;
    GrafoLA<string, Vertex<string> > grafoLA = readCsv(dataBase);
    vector<string> maxMin = grafoLA.maxNodes();
    grafoLA.print();
    vector<string> maxMin = grafoLA.maxNodes();
    vector<string> maxMin = grafoLA.minNodes();
    cout<< ":) Supers con más conexiones: "<< maxMin[0] << endl;
    cout<< ":( Supers con menos conexiones: "<< maxMin[maxMin.size() - 1] << endl;

}
void widthAndDepth(){
    string str = "STEELE SIMON/WOLFGA";
    GrafoLA<string, Vertex<string> > grafoLA;
    vector<string> bfsMarvel = grafoLA.bfs(str);
    for(auto it = bfsMarvel.begin(); it != bfsMarvel.end(); it++){
        cout << *it << endl;
    }
    cout << "Depth First Search: " << endl;
    vector<string> dfsMarvel = grafoLA.dfs(str);
    for(auto it = dfsMarvel.begin(); it != dfsMarvel.end(); it++){
        cout << *it << endl;
    }
    cout << endl;
}
void pruningGrafo(){
	int numConnections;
    GrafoLA<string, Vertex<string> > grafoLA;
	GrafoLA<string, Vertex<string>>* prunnedGraph;
	cout << "Ingresa el número de conexiones para podar a personajes del grafo:" << endl;
	cin >> numConnections;
	prunnedGraph = grafoLA.removeCharacters(numConnections);
	cout << "Grafo:" <<endl;
	prunnedGraph->print();
	cout << endl;
}
void friendshipDijsktra(){

}
void influencersMarvel(){
    int count = 1;
    GrafoLA<string, Vertex<string> > grafoLA;
    vector<string> influencers = grafoLA.maxNodesAVL();
    for(auto it = influencers.begin(); it != influencers.end(); it++){
        cout << "[" << count << "] " << *it <<  ": " << grafoLA.relatedNodes(*it)<< " conexiones" << endl;
        count++;
    }
}

int main(){
    string dataBase = "marvel_clean.csv";
    int option;
    do{
        cout<<"El universo de Marvel"<<endl;
        cout<<"1. Los personajes con menos y más conexiones en el universo Marvel"<<endl;
        cout<<"2. Anchura y profundidad de un personaje a otro"<<endl;
        cout<<"3. Pruning del grafo"<<endl;
        cout<<"4. Recorrido de Dijsktra para llegar de un personaje a otro"<<endl;
        cout<<"5. Influencers en el universo Marvel, de mayor a menor segun su numero de relaciones"<<endl;
        cin>>option;
        switch (option)
        {
        case 1:
            characterConnections();
            break;
        case 2:
            widthAndDepth();
            break;
        case 3:
            pruningGrafo();
            break;
        case 4:
            friendshipDijsktra();
            break;
        case 5:
            influencersMarvel();
            break;
        default:
            cout<<"Opción no válida"<<endl;
            break;
        }
    }while(option <=5 && option>=1);

}