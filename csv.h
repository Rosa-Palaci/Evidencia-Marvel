#include<iostream>
#include<fstream>
#include<sstream>
#include"grafo.h"

using namespace std;

// Método que obtiene el tamaño total del archivo .csv.
// Toma como parámetro el nombre del csv como string.
// Regresa el tamaño del csv como int.
// Complejidad: O(n)
int csvSize(string documentName){
    int size = 0;
    string line;
    fstream file (documentName, ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            stringstream s(line);
            size++;
        }
        file.close();
    }
    
    // Headers are not considered
    return size - 1;
}

// Método que lee un documento csv y lo transforma a 
// objetos de tipo Persona almacenados en árbol AVL.
// Toma como parámetro de entradael nombre del csv como string.
// Regresa el tamaño del csv como int.
// Complejidad: O(n * m)
GrafoLA<string, Vertex<string> > readCsv(string documentName){
    GrafoLA<string, Vertex<string> > grafoLA;
    
	string line, word;
    fstream file (documentName, ios::in);
    string arr[3];
    int count = 0;
    
    if(file.is_open()){
        // Complexity: O(n)
        getline(file, line);
        while(getline(file, line)){
            
            stringstream s(line);
            // Complexity: O(r)
            while(getline(s, word, ',')){
                arr[count++] = word;
            }
            count = 0;
            stringstream ss;
            int weight = stoi(arr[2]);
            ss << arr[2];
            ss >> weight;
            
            if(grafoLA.relatedNodes(arr[0]) <= -1){
                grafoLA.addVertex(arr[0]);
                grafoLA.addEdge(arr[0], Vertex<string>(arr[1], weight));
            }else{
                grafoLA.addEdge(arr[0], Vertex<string>(arr[1], weight));
            }
        }
    }
    file.close();
    
    return grafoLA;
}