#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>

#include "lista.h"
#include "avl.h"

using namespace std;

template <typename T> class Vertex {
	public:
		T dato;
		double cost;
	
		Vertex(T dato, double cost) {
			this->dato = dato;
			this->cost = cost;
		}

        Vertex() {
			this->dato = "";
			this->cost = 0;
		}

        bool operator<(Vertex<T> &p2){
            return cost < p2.cost;
        }

        bool operator>=(Vertex<T> &p2){
            return cost >= p2.cost;
        }

		T getDato(){
			return dato;
		}
};

template <typename T> ostream &operator<<(ostream &, const Vertex<T> &);
template <typename T> ostream &operator<<(ostream &salida, const Vertex<T> &v){
	salida << v.dato << ":" << v.cost;
	return salida;
}

template <typename K, typename T> class GrafoLA {
	private:
		unordered_map<K, vector<T>*>* grafo;
	
	public:
	    // Método constructor del objeto GráfoLA
	    // Complejidad: O(1)
		GrafoLA() {
			grafo = new unordered_map<K, vector<T>*>;
		}

		GrafoLA(unordered_map<K, vector<T>*> *passedMap){
			grafo = passedMap;
		}

		unordered_map<K, vector<T>*>* getGrafo(){
			return grafo;
		}

        void sortGrafo(unordered_map<K, vector<T>*>*& grafo){
            // Defininimos vector de pares
            vector<pair<K, vector<T>*> > A;
            // Copiamos en el vector los pares del unordered map
            for (auto& it : *grafo) {
                A.push_back(it);
            }
            // Sort using comparator function
            sort(A.begin(), A.end());
        }

        // Método que agrega vértices al grafo
        // Como parámetros de entrada requiere una source de tipo K.
        // No posee valores de salida
	    // Complejidad: O(1)
		void addVertex(K source){
			(*grafo)[source] = new vector<T>();
		}
        
        // Método que agrega arcos al grafo.
        // Como parámetros de entrada requiere una soruce de tipo K y un 
        // destiny de tipo T.
        // No posee valores de salida.
	    // Complejidad: O(1)
		void addEdge(K source, T destiny){
			//vector<T>* adyacentes = grafo->get(source);
            (*grafo)[source]->push_back(destiny);
            //sortA(grafo);
        }

        vector<K> keys(){
            vector<K> keysMap;
            for (auto it = grafo->begin(); it != grafo->end(); it++){
                keysMap.push_back(it->first);
            }
            return keysMap;
        }

        int relatedNodes(K key){
			vector<K> vertices = keys();
			auto it = find(vertices.begin(), vertices.end(), key);
			if(it != vertices.end()){
                return (*grafo)[key]->size();
            }else{
                return -1;
            }
		}

	    // Método que imprime los nodos del grafo.
        // Como parámetros de entrada requiere una soruce de tipo K y un 
        // destiny de tipo T.
        // No posee valores de salida.
	    // Complejidad: O(n²)
		void print(){
            vector<K> vertices = keys();
            for(auto it = vertices.begin(); it != vertices.end(); it++){
                K vertex = *it;
                vector<T>* aristas = (*grafo)[vertex];
                cout << vertex << " -> ";
                for(auto iterador = aristas->begin(); iterador != aristas->end(); iterador++){
                	cout << *iterador << " : ";
                }
                cout << endl;
            }
		}
        
        vector<K> maxNodes(){
            vector<K> vertices = keys();
            vector<K> orderedMax;
            int relatedNodesNum, maxNum, index;
            K res;
            do{
                relatedNodesNum = -1;
                maxNum = 0;
                for(auto it = vertices.begin(); it != vertices.end(); it++){
                    relatedNodesNum = relatedNodes(*it);
                    if(relatedNodesNum > maxNum){
                        maxNum = relatedNodesNum;
                        res = *it;
                    }
                }
                orderedMax.push_back(res);
                auto itr = find(vertices.begin(), vertices.end(), res);
                vertices.erase(itr);
            }
            while (vertices.size() != 0);

            return orderedMax;
        }

        vector<K> maxNodesAVL(){
            AVL<Vertex<K> > orderTree;
            Vertex<K> vertexInsert = Vertex<K>("", 0.0);
            for (auto it = grafo->begin(); it != grafo->end(); it++){
                vertexInsert = Vertex<K>(it->first, relatedNodes(it->first));
                orderTree.insert(vertexInsert);
            }

            vector<K> orderedKeys;
			int influencersCount = 0;
            vector<Vertex<K>> orderedVex = orderTree.BST<Vertex<K>>::inOrderSave();
			for(auto it = orderedVex.end() -1; it != orderedVex.begin(); --it){
				if(influencersCount < 10){
					orderedKeys.push_back(it->dato);
					influencersCount++;
				} else {
					return orderedKeys;
				}
			}

            return orderedKeys;
        }

        vector<K> minNodes(){
            vector<K> orderedMin = maxNodes();
            reverse(orderedMin.begin(),orderedMin.end());
            return orderedMin;
        }

        
        // PROBLEMA: Si T es Vertex<string> se tiene que crear un vertex de inicio
        // FALTA DE ABSTRACCIÓN
        // Todo se hizo tomando tipos K para evitar conflictos ?????? Preguntarle al profesor
		vector<K> bfs(K &inicio){
            // Se definen la cola y el vector de visitados
			vector<K> visitados;
            Queue<K> queue;

            // El primer elemento, se declara como descubierto y se mete a la cola
            K descubierto = inicio;
            queue.enqueue(descubierto);

            // Loop que corre hasta que cola este totalmente vacía
            while(!queue.is_empty()){
                // El primero en salir de la cola se declara como descubierto
                descubierto = queue.dequeue();

                // Checamos si el descubierto ya esta en visitados, si está
                // reiniciamos el bucle.
                auto itRepeated = find (visitados.begin(), visitados.end(), descubierto);
                if(itRepeated != visitados.end()){
                    continue;
                }

                // Checamos que descubierto tenga nodos adyacentes, si tiene, obtenemos
                // un vector de estos y uno a uno los metemos a la cola.
                if(relatedNodes(descubierto) >= 1){
                    vector<T>* vecNodosAdyacentes = (*grafo)[descubierto];
                    for(auto it = vecNodosAdyacentes->begin(); it != vecNodosAdyacentes->end(); it++){
                        queue.enqueue(it->dato);
                    }        
                }

                // En el vector visitados, agregamos el nodo descubierto.
                visitados.push_back(descubierto);
            }

			return visitados;
		}
        
        // MISMO PROBLEMA
		vector<K> dfs(K &inicio){
			vector<K> visitados;
            Stack<K> stack;

            // El primer elemento, se declara como descubierto y se mete a la cola
            K descubierto = inicio;
            stack.push(descubierto);

            // Loop que corre hasta que la pila este totalmente vacía
            while(!stack.is_empty()){
                // El primero en salir de la cola se declara como descubierto
                descubierto = stack.pop();

                // Checamos si el descubierto ya esta en visitados, si está
                // reiniciamos el bucle.
                auto itRepeated = find (visitados.begin(), visitados.end(), descubierto);
                if(itRepeated != visitados.end()){
                    continue;
                }
                
                // Checamos que descubierto tenga nodos adyacentes, si tiene, obtenemos
                // un vector de estos y uno a uno los metemos a la cola.
                if(relatedNodes(descubierto) >= 1){
                    vector<T>* vecNodosAdyacentes = (*grafo)[descubierto];
                    for(auto it = vecNodosAdyacentes->begin(); it != vecNodosAdyacentes->end(); it++){
                        stack.push(it->dato);
                    }        
                }

                // En el vector visitados, agregamos el nodo descubierto.
                visitados.push_back(descubierto);
            }
	
			return visitados;
		}

		void testPrint(){
			vector<K> vertices = grafo->keys();
			for(int i = 0; i < vertices.size(); i++){
				cout<<vertices[i]<<endl;
			}
			cout<< endl;
		}

		GrafoLA<K,T>* copyGraph(GrafoLA<K,T>* graphToCopy){
			unordered_map<K, vector<T>*> graphMap = *(graphToCopy->grafo);
			unordered_map<K, vector<T>*> *resultantGraph = new unordered_map<K, vector<T>*>();
			for (auto it = graphMap.begin(); it != graphMap.end(); it++){
				vector<T> *copyVector = new vector<T>(*(it->second));
            	(*resultantGraph)[it->first] = copyVector;
            }
			return new GrafoLA<K, T>(resultantGraph);
		}

		GrafoLA<K,T>* removeCharacters(int nConnections){
			vector<K> remotions;

			// Realizar copia de grafo
			GrafoLA<K,T>* newGraph = copyGraph(this);
			vector<K> vertices = newGraph->keys();
			
			// Encontrar personajes que tienen menos de nConnections
            for (auto it = vertices.begin(); it != vertices.end(); it++){
				if(newGraph->relatedNodes(*it) < nConnections){
					remotions.push_back(*it);
				}
			}
			
			for(int i = 0; i < remotions.size(); i++){
				cout << "Personaje a remover " << i << ": " << remotions[i] << "(" << relatedNodes(remotions[i]) << " conexiones)" << endl;
			}
			
			// Borrar personajes y sus conexiones 
			for(int i = 0; i < remotions.size(); i++){
				newGraph->grafo->erase(remotions[i]);
			}

			// Borrar conexiones a ese personaje
			vertices = newGraph->keys();
			for (auto it = vertices.begin(); it != vertices.end(); it++){
				K vertex = *it;
				vector<Vertex<string>>* vertexVector = new vector<Vertex<string>>();
				for(auto iterador = (*newGraph->getGrafo())[vertex]->begin(); iterador != (*newGraph->getGrafo())[vertex]->end(); iterador++){
					bool shouldRemove = false;
					for(int i = 0; i < remotions.size(); i++){
						if(iterador->getDato() == remotions[i]){
							shouldRemove = true;
						}
					}
					if(!shouldRemove){
						vertexVector->push_back(*iterador);
					}
                }
				(*newGraph->getGrafo())[vertex]->clear();
				(*newGraph->getGrafo())[vertex] = vertexVector;
			}
			return newGraph;
		}
};