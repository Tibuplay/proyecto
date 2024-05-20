#include <iostream>
#include <string>
#include<locale.h> 

using namespace std;

typedef struct {
    string nombre;//nombre el bioma
    string planetas;//hogares donde las especies que no reciben daño
}biome;

typedef struct{
    string nombre;
    int nrg;
    int hp;
    string hogar; //ambiente donde no reciben daño
    char fidelidad; //fidelidad, puede ser h(humano) o a(andromedano)
} especie;

struct nodoalien{
    int  indice;
    especie alien;
    nodoalien *next;
};

typedef struct{
    string nombre; //nombre accesorio
    char tipo; //a(ataque), d(defensa), s(salud) o c(condicion)
    int valor; //cantidad que mueve el accesorio (c es 0)
    string apoyo; //especificar que recupera un "s" o a qué ambiente condiciona un "c"
    int nrgconum; //consumo de energía
    int defensa;//valor inicial no recuperable del escudo
}accesorio;

struct nodoitem{
    int  indice;
    accesorio item;
    nodoitem *next;
};

typedef accesorio mochila[5];

void agregaralien(nodoalien *&listaaliens){
    nodoalien *nuevonodo= new nodoalien();
    nodoalien *aux1=listaaliens;
    nodoalien *aux2=NULL;
    
    cout<<"Ingresa el nombre de la especie: ";
        cin>>nuevonodo->alien.nombre;
        cout<<endl<<"Ingresa cuanta energia tiene la especie: ";
        cin>>nuevonodo->alien.nrg;
        cout<<endl<<"Ingresa cuanta vida tiene la especie: ";
        cin>>nuevonodo->alien.hp;
        cout<<endl<<"Ingresa el planeta hogar de la especie (esto afecta en cuales biomas no pierde vida): ";
        cin>>nuevonodo->alien.hogar;
        cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
        <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
        <<" Su salud es: "<<nuevonodo->alien.hp<<endl
        <<" El planeta de la especie es: "<<nuevonodo->alien.hogar;
        nuevonodo->next=NULL;
        
    if (listaaliens==NULL){
        nuevonodo->indice=1;
        listaaliens=nuevonodo;
        cout<<endl<<"Primer alien de la lista creado";
    }
    else{
        nuevonodo->indice=1;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<endl<<"otro alien de la lista creado";
    }
}

void modificarraza(nodoalien *&listaaliens){
    nodoalien *nuevonodo= new nodoalien();
    nuevonodo = listaaliens;
    bool resp=true;
    char change;
    char estruc;
    while(resp=true){
        cout<<endl<<"Desea hacer cambios a la raza?(S/N)";
        cin>>change;
        if((change == 'S')||(change == 's')){
            cout<<endl<<"Que desea cambiar?"
            <<endl<<"Nombre (N)"<<endl<<"Energia (E)"<<endl<<"Salus (S)"<<endl<<"Planeta (P)"
            <<endl<<"Su eleccion: ";
            cin>>estruc;
            if((estruc == 'N')||(estruc == 'n')){
                cout<<endl<<"Cual es el nuevo nombre de la raza? ";
                cin>>nuevonodo->alien.nombre;
            }
            else if((estruc == 'E')||(estruc == 'e')){
                cout<<endl<<"Cual es la nueva energia de la raza? ";
                cin>>nuevonodo->alien.nrg;
            }
            else if((estruc == 'S')||(estruc == 's')){
                cout<<endl<<"Cual es la nueva salud de la raza? ";
                cin>>nuevonodo->alien.hp;
            }
            else if((estruc == 'P')||(estruc == 'p')){
                cout<<endl<<"Cual es el nuevo planeta de la raza? ";
                cin>>nuevonodo->alien.hogar;
            }
        }else{
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
            <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
            <<" Su salud es: "<<nuevonodo->alien.hp<<endl
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar<<endl;            
            break;
        }
    }
    
}

void eliminarlista(nodoalien *&lista){
    nodoalien *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Elementos borrados";
}


int main(){
    nodoalien *listaaliens=NULL;
    nodoitem *listaitems=NULL;
    bool seleccion=true;
    cout<<"La gran y expansiva galaxia, esta en peligro..."<<endl;
    cout<<"Solo los estudiantes de la academia galactica podran hacer frente ante la amenaza crecientre de la Andromeda..."<<endl;
    cout<<"¿Estas preparado para la lucha soldado?"<<endl;
    
    bool xd=true;
    char x;
    
    while(xd==true){
        cout<<"desea crear una especie?(S/N): "<<endl;
        cin>>x;
    if ((x == 'S')||(x == 's')){
            agregaralien(listaaliens);
            modificarraza(listaaliens);
        }
        else{
            eliminarlista(listaaliens);
            break;
        }
    }
    return 0;
}

