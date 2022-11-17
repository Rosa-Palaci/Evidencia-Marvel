#include <iostream>
using namespace std;

void characterConnections(){

}
void widthAndDepth(){

}
void pruningGrafo(){

}
void friendshipDijsktra(){

}
void influencersMarvels(){

}

void main(){
    int option;
    do{
        cout<<"El universo de Marvel"<<endl;
        cout<<"1. ¿Cuáles son los personajes con menos y más conexiones en el universo Marvel?"<<endl;
        cout<<"2. Implementar los recorridos de anchura y profundidad de un personaje a otro."<<endl;
        cout<<"3. Realizar un “pruning” del grafo, quitando a los personajes qué tengan menos de “n” conexiones que se le pida al usuario."<<endl;
        cout<<"4. Utilizando el valor de friendship debes de realizar el recorrido de Dijsktra para llegar de un personaje a otro."<<endl;
        cout<<"5. Identificar a los personajes qué son influencers en el universo Marvel, una lista de esos influencers ordenada de mayor a menor según su número de relaciones."<<endl;
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