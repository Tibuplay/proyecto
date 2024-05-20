#include <iostream>
#include <string>

using namespace std;

typedef struct {
    string nombre;//nombre el bioma
    string planetas;//hogares donde las especies que no reciben da�o
}biome;

struct nodobioma{
	int indice;
	biome bioma;
	nodobioma *next;
};

typedef struct{
    string nombre;
    int nrg;
    int hp;
    string hogar; //ambiente donde no reciben da�o
    char fidelidad; //fidelidad, puede ser h(humano) o a(andromedano)
} especie;

struct nodoalien{
    int  indice;
    especie alien;
    nodoalien *next;
};

typedef struct{
    string nombre; //nombre accesorio
    int tipo; //1(ataque), 2(defensa), 3(salud) o 4(condicion)
    string valor; //cantidad que mueve el accesorio, da?o que hace, (c es 0)
    string apoyo; //especificar que recupera un "s" o a qu� ambiente condiciona un "c"
    int nrgconum; //consumo de energ�a
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
        nuevonodo->next=NULL;
        
    if (listaaliens==NULL){
        nuevonodo->indice=1;
		listaaliens=nuevonodo;
        cout<<"Primer alien de la lista creado";
    }
    else{
    	nuevonodo->indice=1;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<"Alien agregado como numero: "<<nuevonodo->indice;
    }
}

void agregarbioma(nodobioma *&listabiomas){
	nodobioma *nuevonodo= new nodobioma();
    nodobioma *aux1=listabiomas;
    int numplanetas=0;
    nuevonodo->bioma.planetas=""; string planeta;
    
	cout<<endl<<"Para crear un bioma se necesita asignarle un nombre y luego los planetas que cuenta con ese bioma.";
    cout<<endl<<"Ingresa el nombre del bioma nuevo: ";
    cin>>nuevonodo->bioma.nombre;
    cout<<endl<<"Cuantos planetas contaran con el bioma?: ";
    cin>>numplanetas;
    while (numplanetas>0){
    	cout<<endl<<"Ingrese el nombre de un planeta: ";
    	cin>>planeta;
    	nuevonodo->bioma.planetas=nuevonodo->bioma.planetas+","+planeta;
    	numplanetas--;
    	
	}
        
    if (listabiomas==NULL){
        nuevonodo->indice=1;
		listabiomas=nuevonodo;
        cout<<endl<<"Primer bioma de la lista creado";
    }
    else{
    	nuevonodo->indice=2;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<endl<<"bioma agregado como numero: "<<nuevonodo->indice;
    }
}

void mostrarbiomas(nodobioma *&listabioma){
	nodobioma *aux=listabioma;
	nodobioma *aux2=listabioma;
	cout<<endl<<"Los biomas son: ";
    while(aux2!=NULL){
        aux2=aux->next;
        cout<<aux->indice<<". "<<aux->bioma.nombre<<", con los planetas: "<<aux->bioma.planetas<<endl;
        aux=aux2;
    }
    cout<<endl<<"Listo"<<endl; aux=listabioma;
}

void agregaritem(nodoitem *&listaitems, nodobioma *&listabiomas){
    nodoitem *nuevonodo= new nodoitem();
    nodoitem *aux1=listaitems;
    int apoyo;//apoyo para moverme entre menï¿½s
    
    cout<<endl<<"Ingresa el nombre del item: ";
    cin>>nuevonodo->item.nombre;
    cout<<endl<<"Ingrese un tipo de item:"<<endl<<"1. Ataque"<<endl<<"2. Defensa"<<endl<<"3. Recuperacion"<<endl<<"4. Condicion"<<endl;
    cin>>nuevonodo->item.tipo;
    switch (nuevonodo->item.tipo)
    {
    case 1:
        cout<<endl<<"Ingrese la cantidad de dano que hace: ";
		cin>>nuevonodo->item.valor;
        break;
    
    case 2:
        cout<<endl<<"Ingrese el porcentaje de dano que reduce: ";
		cin>>nuevonodo->item.valor;
		cout<<endl<<"Ingrese el escudo inicial que proporciona (no recuperable)";
		cin>>nuevonodo->item.defensa;
        break;
    
    case 3:
        cout<<endl<<"Su objeto de recuperacion recupera vida o energia?"<<endl;
		cin>>nuevonodo->item.apoyo;
		cout<<endl<<"Indique cuanta "<<nuevonodo->item.apoyo<<" recupera por turno: "<<endl;
		cin>>nuevonodo->item.valor;
		break;

    case 4:
        cout<<"Escriba el nombre de uno de los siguientes biomas al que ayuda a condicionar el onjeto (de escribir uno que no aparezca no tiene efecto el objeto a menos que se cree uno nuevo con ese nombre): ";
        mostrarbiomas(listabiomas);
    	cin>>nuevonodo->item.apoyo;
        break;
    default:
    	break;
    }
	
	cout<<"Ingrese la cantidad de energia que consume por turno: ";
	cin>>nuevonodo->item.nrgconum;
	
    nuevonodo->next=NULL;
        
    if (listaitems==NULL){
        nuevonodo->indice=1;
		listaitems=nuevonodo;
        cout<<"Primer objeto de la lista creado"<<endl;
    }
    else{
    	nuevonodo->indice=1;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<"objeto agregado como numero: "<<nuevonodo->indice<<endl;
    }
}

void mostraralien(nodoalien *&listaaliens){
	nodoalien *aux=listaaliens;
	nodoalien *aux2=listaaliens;
	cout<<endl<<"Los aliens son: ";
    while(listaaliens!=NULL){
        aux2=aux->next;
        cout<<endl<<aux->indice<<"Nombre: "<<aux->alien.nombre
        <<"Energia: "<<aux->alien.nrg<<endl
        <<"Salud: "<<aux->alien.hp<<endl
        <<"Planeta: "<<aux->alien.hogar<<endl;
        aux=aux2;
    }
    cout<<endl<<"Listo"<<endl; aux=listaaliens;;
}


void mostraritem(nodoitem *&listaitems){
	nodoitem *aux=listaitems;
	nodoitem *aux2=listaitems;
	cout<<endl<<"Los items son: ";
    while(aux!=NULL){
        aux2=aux->next;
        cout<<aux->indice<<". "<<aux->item.nombre;
		switch(aux->item.tipo){
			case 1:
				cout<<", de tipo ataque, ";
				cout<<"con un dano de: "<<aux->item.valor<<" y que consume "<<aux->item.nrgconum<<" de energia cada turno";
				break;
			case 2:
				cout<<", de tipo defensa, ";
				cout<<"con una reduccion de dano de: "<<aux->item.valor<<"% y que consume "<<aux->item.nrgconum<<" de energia cada turno";
				cout<<", otorga un escudo inicial de "<<aux->item.defensa;
				break;
			case 3:
				cout<<", de tipo recuperacion, ";
				cout<<"recupera "<<aux->item.valor<<"de "<<aux->item.apoyo<<" cada turno";
				cout<<" consume "<<aux->item.nrgconum<<" de energia cada turno";
				break;
			case 4:
				cout<<", de tipo condicion, ayuda a una especie a un bioma al que no pertenece, ";
				cout<<"ayuda al portador a vivir en el bioma "<<aux->item.apoyo<<" y consume "<<aux->item.nrgconum<<" de energia cada turno";
				break;
			}
		aux=aux2;
    }
    cout<<endl<<"Listo"<<endl; aux=listaitems;
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
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar;            
            break;
        }
    }
    
}

void modificarbioma(nodobioma *&listabiomas){
    nodobioma *nuevonodo= new nodobioma();
    nuevonodo = listabiomas;
    bool resp=true;
    char change;
    char estruc;
    nuevonodo->bioma.planetas=""; string planeta;
    int numplanetas;
    while(resp==true){
        cout<<endl<<"Desea hacer cambios a los biomas?(S/N)";
        cin>>change;
                if((change == 'S')||(change == 's')){
            cout<<endl<<"Que desea cambiar?"
            <<endl<<"Nombre (N)"<<"Planeta(P)"
            <<endl<<"Su eleccion: ";
            cin>>estruc;
            if((estruc == 'N')||(estruc == 'n')){
                cout<<endl<<"Cual es el nuevo nombre de la raza? ";
                cin>>nuevonodo->bioma.nombre;
            }
            if((estruc == 'P')||(estruc == 'p')){
                cout<<endl<<"Cuantos planetas contaran con el bioma?: ";
                cin>>numplanetas;
                while (numplanetas>0){
                	cout<<endl<<"Ingrese el nombre de un planeta: ";
                	cin>>planeta;
                	nuevonodo->bioma.planetas=nuevonodo->bioma.planetas+","+planeta;
                	numplanetas--;
            }
        }else{
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre del bioma es: "<<nuevonodo->bioma.nombre
            <<endl<<"El nombre del planeta: "<<nuevonodo->bioma.planetas; 
            break;
        }
    }
}
}

void modificaritem(nodoitem*&listaitem, nodobioma *&listabiomas){
    nodoitem *nuevonodo= new nodoitem();
    nuevonodo = listaitem;
    bool resp=true;
    char change;
    char estruc;
    while(resp=true){
        cout<<endl<<"Desea cambiar un item? (S/N) ";
        cin >> change;
        if((change == 'S')||(change == 's')){
            cout<<"Ingrese un nuevo nombre del item: ";
            cin>>nuevonodo->item.nombre;
            cout<<endl<<"Ingrese el tipo de item:"<<endl<<"1. Ataque"<<endl<<"2. Defensa"<<endl<<"3. Recuperacion"<<endl<<"4. Condicion"<<endl;
            cin>>nuevonodo->item.tipo;
            switch (nuevonodo->item.tipo)
            {
            case 1:
                cout<<endl<<"Ingrese la cantidad de dano que hace: ";
                cin>>nuevonodo->item.valor;
                break;
            
            case 2:
                cout<<endl<<"Ingrese el porcentaje de dano que reduce: ";
                cin>>nuevonodo->item.valor;
                cout<<endl<<"Ingrese el escudo inicial que proporciona (no recuperable)";
                cin>>nuevonodo->item.defensa;
                break;
            
            case 3:
                cout<<endl<<"Su objeto de recuperacion recupera vida o energia?"<<endl;
                cin>>nuevonodo->item.apoyo;
                cout<<endl<<"Indique cuanta "<<nuevonodo->item.apoyo<<" recupera por turno: "<<endl;
                cin>>nuevonodo->item.valor;
                break;

            case 4:
                cout<<"Escriba el nombre de uno de los siguientes biomas al que ayuda a condicionar el onjeto (de escribir uno que no aparezca no tiene efecto el objeto a menos que se cree uno nuevo con ese nombre): ";
                mostrarbiomas(listabiomas);
                cin>>nuevonodo->item.apoyo;
                break;
            default:
                break;
            }
        }
    }
}

void eliminar1alien(nodoalien*&listaaliens){
	int objetivo;
	cout<<endl<<"Elige un bioma para eliminar. "<<endl;
	mostraralien(listaaliens);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	cin>>objetivo;
    if (listaaliens!=NULL){
		nodoalien *aux_borrar;
		nodoalien *nodoanterior=NULL;
		aux_borrar=listaaliens;
		
		while((aux_borrar!=NULL)&&(aux_borrar->indice!=objetivo)){
			nodoanterior=aux_borrar;
			aux_borrar=aux_borrar->next;
		}
		if(aux_borrar==NULL){
			cout<<endl<<"Elemento no encontrado";
		}
		else if (nodoanterior==NULL){
			listaaliens=listaaliens->next;
			delete aux_borrar;
			nodoalien *aux2=listaaliens;
			while(aux2!=NULL){
        		aux2->indice--;
				aux2=aux2->next;
    			}
		}
		else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
		}
    	}
    else{
    	cout<<endl<<"La lista esta vacia";
	}
    cout<<endl<<"Elemento borrado"<<endl;
	}

void eliminar1bioma(nodobioma *&listabiomas){
	int objetivo;
	cout<<endl<<"Elige un bioma para eliminar. "<<endl;
	mostrarbiomas(listabiomas);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	cin>>objetivo;
    if (listabiomas!=NULL){
		nodobioma *aux_borrar;
		nodobioma *nodoanterior=NULL;
		aux_borrar=listabiomas;
		
		while((aux_borrar!=NULL)&&(aux_borrar->indice!=objetivo)){
			nodoanterior=aux_borrar;
			aux_borrar=aux_borrar->next;
		}
		if(aux_borrar==NULL){
			cout<<endl<<"Elemento no encontrado";
		}
		else if (nodoanterior==NULL){
			listabiomas=listabiomas->next;
			delete aux_borrar;
			nodobioma *aux2=listabiomas;
			while(aux2!=NULL){
        		aux2->indice--;
				aux2=aux2->next;
    			}
		}
		else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
		}
    	}
    else{
    	cout<<endl<<"La lista esta vacia";
	}
    cout<<endl<<"Elemento borrado"<<endl;
	}

void eliminar1item(nodoitem *&listaitems){
	int objetivo;
	cout<<endl<<"Elige un bioma para eliminar. "<<endl;
	mostraritem(listaitems);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	cin>>objetivo;
    if (listaitems!=NULL){
		nodoitem *aux_borrar;
		nodoitem *nodoanterior=NULL;
		aux_borrar=listaitems;
		while((aux_borrar!=NULL)&&(aux_borrar->indice!=objetivo)){
			nodoanterior=aux_borrar;
			aux_borrar=aux_borrar->next;
		}
		if(aux_borrar==NULL){
			cout<<endl<<"Elemento no encontrado";
		}
		else if (nodoanterior==NULL){
			listaitems=listaitems->next;
			delete aux_borrar;
			nodoitem *aux2=listaitems;
			while(aux2!=NULL){
        		aux2->indice--;
				aux2=aux2->next;
    			}
		}
		else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
		}
    	}
    else{
    	cout<<endl<<"La lista esta vacia";
	}
    cout<<endl<<"Elemento borrado"<<endl;
	}

void eliminaraliens(nodoalien *&lista){
    nodoalien *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Elementos borrados";
}

void eliminaritems(nodoitem *&lista){
    nodoitem *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Elementos borrados"<<endl;
}

void eliminarbiomas(nodobioma *&lista){
    nodobioma *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Elementos borrados"<<endl;
}

int main(){
    bool on1, on2;
    on1=true;
    on2=true;
    short int move1, move2;
	nodoalien *listaaliens=NULL;
    nodoitem *listaitems=NULL;
    nodobioma *listabiomas=NULL;

    cout<<"La gran y expansiva galaxia, esta en peligro..."<<endl;
    cout<<"Solo los estudiantes de la academia galactica podran hacer frente ante la amenaza crecientre de la Andromeda..."<<endl;
    cout<<"Estas preparado para la lucha soldado?"<<endl;

    while(on1){
    	
        cout<<"---------------------"<<endl;
        cout<<"Bienvenido al menu"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1. Leer lista de personajes u accesorios"<<endl;
        cout<<"2. Agregar aliens u accesorios a las listas"<<endl;
        cout<<"3. Modificar aliens u accesorios de las listas"<<endl;
        cout<<"4. Eliminar aliens u accesorios de las listas"<<endl;
        cout<<"5. Salir del menu"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"Seleccione la accion a realizar: ";
		cin>>move1; cout<<endl;

        switch (move1)
        {
        case 1:
            while (on2){
            	cout<<"Desea ver:"<<endl<<"1. Lista de aliens."<<endl<<"2. Lista de accesorios."<<endl<<"3. Lista de biomas"<<endl<<"4. Retroceder"<<endl;
                cin>>move2;
            	switch (move2)
                {
                case 1:
                    mostraralien(listaaliens);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    mostraritem(listaitems);
                    cout<<"hecho"<<endl;
                    break;

                case 3:
                    mostrarbiomas(listabiomas);
                    cout<<"hecho"<<endl;
                    break;

                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"Ingrese una opcion valida"<<endl;
                    break;
                }
			}
            break;
        
        case 2:
            while (on2){
            	cout<<"Desea agregar:"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma"<<"4. Retroceder"<<endl;
                cin>>move2;
            	switch (move2)
                {
                case 1:
                    agregaralien(listaaliens);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    agregaritem(listaitems, listabiomas);
                    cout<<"hecho"<<endl;
                    break;

                case 3:
                    agregarbioma(listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"Ingrese una opcion valida"<<endl;
                    break;
                }
			}
            break;

        case 3:
            while (on2){
            	cout<<"Desea modificar:"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma"<<endl<<"4. Retroceder"<<endl;
                cin>>move2;
            	switch (move2)
                {
                case 1:
                    modificarraza(listaaliens);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    modificaritem(listaitems, listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 3:
                    modificarbioma(listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"Ingrese una opcion valida"<<endl;
                    break;
                }
			}
            break;

        case 4:
            while (on2){
            	cout<<"Desea eliminar:"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma."<<endl<<"4. Retroceder"<<endl;
                cin>>move2;
            	switch (move2)
                {
                case 1:
                    eliminar1alien(listaaliens);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    eliminar1item(listaitems);
                    cout<<"hecho"<<endl;
                    break;
                case 3:
                    eliminar1bioma(listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"Ingrese una opcion valida"<<endl;
                    break;
                }
			}
            break;

        case 5:
        	cout<<"Saliendo del menu"<<endl;
        	on1=false;
        	break;
        default:
            cout<<"Error, seleccione una de las opciones propuestas"<<endl;
            break;
        }
        on2=true;//poner el condicional de los switch de vuelta a true
    }
	
    eliminaraliens(listaaliens);
    eliminaritems(listaitems);
	eliminarbiomas(listabiomas);
    return 1;
}
