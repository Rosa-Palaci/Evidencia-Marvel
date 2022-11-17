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
void influencersMarvel(){

}

int main(){
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