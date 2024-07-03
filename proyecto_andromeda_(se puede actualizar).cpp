#include <iostream> //hecho por Jes�s Acosta
#include <string>//hecho por Leonel Rojas
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;//hecho por Rolando Rodrigo

struct nodobioma{
	int indice;
	string nombre;
	nodobioma *next;
};

typedef struct{
    string nombre;
    int nrg;
    int hp;
    nodobioma *hogar; //ambiente donde no reciben da�o
} especie;

struct nodoalien{
    int  indice;
    especie alien;
    nodoalien *next;
};

typedef struct{
    string nombre; //nombre accesorio
    int tipo; //1(ataque), 2(defensa), 3(salud) o 4(condicion)
    int valor; //cantidad que mueve el accesorio, da?o que hace, (c es 0)
    string apoyo; //especificar que recupera un "s" o a qu� ambiente condiciona un "c"
    int nrgconum; //consumo de energ�a
    int defensa;//valor inicial no recuperable del escudo
}accesorio;

struct nodoitem{
    int  indice;
    accesorio item;
    nodoitem *next;
};

struct soldado{
	especie alien;
	accesorio item1;
	accesorio item2;
	accesorio item3;
};

int input_int(){
	bool x=true;
	string str;
	while(x){
		cout<<"Ingrese un numero entero: ";
		cin>>str;
		for (int i=0; i<str.length(); i++){
			if (!isdigit(str[i])){
				cout<<"Dato invalido, vuelva a intentar"<<endl;
				x=1;
				break;
			}else{
				x=0;
			}
		}}
	int num=atoi(str.c_str());
	return num;
}

string input_str(){
	bool x=true;
	string str;
	while(x){
		getline(cin,str);
		for (int i=0; i<str.length(); i++){
			if (!isascii(str[i])){
				cout<<"Palabra invalida, vuelva a intentar"<<endl;
				x=1;
				break;
			}else{
				x=0;
			}
		}
		}
	return str;
}

void agregarbioma(nodobioma *&listabiomas){
	nodobioma *nuevonodo= new nodobioma();
    nodobioma *aux1=listabiomas;
    cout<<"-----------------------------------------"<<endl;
    cout<<endl<<"Ingresa el nombre del bioma nuevo: ";
    nuevonodo->nombre=input_str();
    cout<<"-----------------------------------------"<<endl;
    if (listabiomas==NULL){
        nuevonodo->indice=1;
		listabiomas=nuevonodo;
        cout<<"----------------------------------------"<<endl;
        cout<<endl<<"Primer bioma de la lista creado."<<endl;
        cout<<"----------------------------------------"<<endl;
    }
    else{
    	nuevonodo->indice=2;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<"----------------------------------------"<<endl;
        cout<<endl<<"bioma agregado como numero: "<<nuevonodo->indice;
        cout<<"----------------------------------------"<<endl;
    }
}

void mostrarbiomas(nodobioma *&listabioma){
	nodobioma *aux=listabioma;
	nodobioma *aux2=listabioma;
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Los biomas son: "<<endl;
    while(aux2!=NULL){
        aux2=aux->next;
        cout<<aux->indice<<". "<<aux->nombre<<endl;
        aux=aux2;
    }
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<"Listo"<<endl; aux=listabioma;
}

void agregaralien(nodoalien *&listaaliens, nodobioma *&listabiomas){
    nodoalien *nuevonodo= new nodoalien();
    nodoalien *aux1=listaaliens;
    nodoalien *aux2=NULL;
    cout<<"---------------------"<<endl;
    cout<<"Ingresa el nombre de la especie: ";
    nuevonodo->alien.nombre=input_str();
    cout<<"---------------------"<<endl;
    cout<<endl<<"Ingresa cuanta energia tiene la especie(Numero entero mayor a 0): ";
    nuevonodo->alien.nrg=input_int();
    cout<<endl<<"Ingresa cuanta vida tiene la especie(Numero entero mayor a 0): ";
    nuevonodo->alien.hp=input_int();
    cout<<endl<<"Ingresa el planeta hogar de la especie (el bioma donde no pierde vida) de la siguiente lista: ";
    nodobioma *bioma=listabiomas;
	mostrarbiomas(listabiomas);
    bool encontrado=false;
    while (encontrado==false){
    	int objetivo=input_int();
        while((bioma!=NULL)&&(bioma->indice!=objetivo)){
            bioma=bioma->next;
				}
        if(bioma==NULL){
    		cout<<endl<<"Objetivo no encontrado, vuelva a intentar: "<<endl;
            bioma=listabiomas;
				}
		else{
           	encontrado=true;
					}
                }
                
        nuevonodo->alien.hogar=bioma;
        nuevonodo->next=NULL;
        
    if (listaaliens==NULL){
        nuevonodo->indice=1;
		listaaliens=nuevonodo;
        cout<<"-----------------------------------"<<endl;
        cout<<"Primer alien de la lista creado."<<endl;
        cout<<"----------------------------------"<<endl;
    }
    else{
        nuevonodo->indice=2;
        while (aux1->next!=NULL){
            aux1=aux1->next;
            nuevonodo->indice+=1;
        }
        aux1->next=nuevonodo;
        cout<<"----------------------------------"<<endl;
        cout<<"Alien agregado como numero: "<<nuevonodo->indice;
        cout<<"----------------------------------"<<endl;
    }
}

void agregaritem(nodoitem *&listaitems, nodobioma *&listabiomas){
    nodoitem *nuevonodo= new nodoitem();
    nodoitem *aux1=listaitems;
    nodobioma *bioma=listabiomas;
    bool encontrado=false;
    int apoyo;//apoyo para moverme entre menï¿½s
    bool x=1;
    int caso3;
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<"Ingresa el nombre del item: ";
    nuevonodo->item.nombre=input_str();
    nuevonodo->item.tipo=0;
            cout<<endl<<"Ingrese el tipo de item:"<<endl<<"1. Ataque"<<endl<<"2. Defensa"<<endl<<"3. Recuperacion"<<endl<<"4. Condicion"<<endl;
            int y=input_int();
			while(y<1 || y>4){
            	cout<<"Opcion invalida, vuelva a intentar: ";
            	y=input_int();
			}
			nuevonodo->item.tipo=y;
            switch (nuevonodo->item.tipo)
            {
            case 1:
                cout<<endl<<"Ingrese la cantidad de dano que hace: ";
                nuevonodo->item.valor=input_int();
                break;
            
            case 2:
                cout<<endl<<"Ingrese el porcentaje de dano que reduce: ";
                nuevonodo->item.valor=input_int();
                cout<<endl<<"Ingrese el escudo inicial que proporciona (no recuperable)";
                nuevonodo->item.defensa=input_int();
                break;
            
            case 3:
                cout<<"----------------------------------------"<<endl;
    	    	while(x){
					cout<<endl<<"Su objeto de recuperacion recupera vida (1) o energia (2)?"<<endl;
					caso3=input_int();
					if (caso3==1){
						nuevonodo->item.apoyo="vida";
						x=false;
					}if (caso3==2){
						nuevonodo->item.apoyo="energia";
						x=false;
					}if(caso3!=1&&caso3!=2){
						cout<<"opcion invalida, intente de nuevo"<<endl;
					}
					}
				cout<<endl<<"Indique cuanta "<<nuevonodo->item.apoyo<<" recupera por turno: "<<endl;
				nuevonodo->item.valor=input_int();
        		cout<<"----------------------------------------"<<endl;
				break;

            case 4:
                cout<<"---------------------------------------------------------------------------------------------"<<endl;
        		cout<<"Ingrese el indice del bioma al que condiciona el objeto: ";
        		mostrarbiomas(listabiomas);
        		while (encontrado==false){
		        	int objetivo=input_int();
        		    while((bioma!=NULL)&&(bioma->indice!=objetivo)){
                		bioma=bioma->next;
					}
            		if(bioma==NULL){
                		cout<<endl<<"Objetivo no encontrado, vuelva a intentar: ";
                		bioma=listabiomas;
					}
					else{
               			encontrado=true;
						}
                }
        		nuevonodo->item.apoyo=bioma->nombre;
        		break;
            }
	
	cout<<"Ingrese la cantidad de energia que consume por turno: ";
	nuevonodo->item.nrgconum=input_int();
    cout<<"----------------------------------------"<<endl;
    
	
    nuevonodo->next=NULL;
        
    if (listaitems==NULL){
        nuevonodo->indice=1;
		listaitems=nuevonodo;
        cout<<"----------------------------------------"<<endl;
        cout<<"Primer objeto de la lista creado."<<endl;
        cout<<"----------------------------------------"<<endl;
    }
    else{
    	nuevonodo->indice=2;
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
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Los aliens son: ";
    while(aux!=NULL){
        aux2=aux->next;
        cout<<endl<<aux->indice<<". Nombre: "<<aux->alien.nombre<<endl
        <<"Energia: "<<aux->alien.nrg<<endl
        <<"Salud: "<<aux->alien.hp<<endl
        <<"Planeta: "<<aux->alien.hogar->nombre<<endl;
        aux=aux2;
    }
    cout<<endl<<"Listo"<<endl; aux=listaaliens;
    cout<<"----------------------------------------"<<endl;
}

void mostraritem(nodoitem *&listaitems){
	nodoitem *aux=listaitems;
	nodoitem *aux2=listaitems;
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Los items son: ";
    while(aux!=NULL){
        aux2=aux->next;
        cout<<aux->indice<<". "<<aux->item.nombre;
		switch(aux->item.tipo){
			case 1:
				cout<<", de tipo ataque, ";
				cout<<"con un dano de: "<<aux->item.valor<<" y que consume "<<aux->item.nrgconum<<" de energia cada turno."<<endl;
				break;
			case 2:
				cout<<", de tipo defensa, ";
				cout<<"con una reduccion de dano de: "<<aux->item.valor<<"% y que consume "<<aux->item.nrgconum<<" de energia cada turno";
				cout<<", otorga un escudo inicial de "<<aux->item.defensa<<endl;
				break;
			case 3:
				cout<<", de tipo recuperacion, ";
				cout<<"recupera "<<aux->item.valor<<" de "<<aux->item.apoyo<<" cada turno";
				cout<<" consume "<<aux->item.nrgconum<<" de energia cada turno."<<endl;
				break;
			case 4:
				cout<<", de tipo condicion, ayuda a una especie a un bioma al que no pertenece, ";
				cout<<"ayuda al portador a vivir en el bioma "<<aux->item.apoyo<<" y consume "<<aux->item.nrgconum<<" de energia cada turno"<<endl;
				break;
			}cout<<endl;
		aux=aux2;
    }
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<"Listo"<<endl; aux=listaitems;
}

void modificarraza(nodoalien *&listaaliens, nodobioma *&listabiomas){
    nodoalien *nuevonodo= new nodoalien();
    nuevonodo = listaaliens;
    int objetivo;
    bool resp=true;
    bool encontrado=true;
    char change;
    char estruc;
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<"Desea hacer cambios a la raza?(S/N)";
    cin>>change;
    if((change == 'S')||(change == 's')){
        cout<<endl<<"A continuacion se mostraran los aliens:"<<endl;
        mostraralien(listaaliens);
        while(resp==true){
            cout<<"Ingrese el indice (numero) del que desea modificar: ";
            objetivo=input_int();
            while((nuevonodo!=NULL)&&(nuevonodo->indice!=objetivo)){
	        	nuevonodo=nuevonodo->next;
                encontrado=false;
                if(nuevonodo->indice==objetivo){
                    encontrado=true;
               }
	        }
        cout<<endl<<"Que desea cambiar?"
        <<endl<<"Nombre (N)"<<endl<<"Energia (E)"<<endl<<"Salus (S)"<<endl<<"Planeta (P)"
        <<endl<<"Su eleccion: ";
        cin>>estruc;
        if((estruc == 'N')||(estruc == 'n')){
            cout<<endl<<"Cual es el nuevo nombre de la raza? ";
            nuevonodo->alien.nombre=input_str();
            cout<<"----------------------------------------"<<endl; 
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
            <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
            <<" Su salud es: "<<nuevonodo->alien.hp<<endl
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar->nombre;    
            cout<<"----------------------------------------"<<endl;    
            break;
        }
        else if((estruc == 'E')||(estruc == 'e')){
            cout<<endl<<"Cual es la nueva energia de la raza? ";
            nuevonodo->alien.nrg=input_int();
            cout<<"----------------------------------------"<<endl; 
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
            <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
            <<" Su salud es: "<<nuevonodo->alien.hp<<endl
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar->nombre;    
            cout<<"----------------------------------------"<<endl;    
            break;
        }
        else if((estruc == 'S')||(estruc == 's')){
            cout<<endl<<"Cual es la nueva salud de la raza? ";
            nuevonodo->alien.hp=input_int();
            cout<<"----------------------------------------"<<endl; 
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
            <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
            <<" Su salud es: "<<nuevonodo->alien.hp<<endl
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar->nombre;    
            cout<<"----------------------------------------"<<endl;    
            break;
        }
        else if((estruc == 'P')||(estruc == 'p')){
            cout<<endl<<"Cual es el nuevo planeta de la raza? ";
            nodobioma *bioma=listabiomas;
		mostrarbiomas(listabiomas);
        bool encontrado=false;
        while (encontrado==false){
        	int objetivo=input_int();
            while((bioma!=NULL)&&(bioma->indice!=objetivo)){
                bioma=bioma->next;
				}
            if(bioma==NULL){
                cout<<endl<<"Objetivo no encontrado, vuelva a intentar: ";
                bioma=listabiomas;
				}
			else{
               	encontrado=true;
					}
                }    
        	nuevonodo->alien.hogar=bioma;
            cout<<"----------------------------------------"<<endl; 
            cout<<"Cambios realizados.";
            cout<<endl<<"El nombre de su raza es: "<<nuevonodo->alien.nombre<<endl
            <<" Su energia es: "<<nuevonodo->alien.nrg<<endl
            <<" Su salud es: "<<nuevonodo->alien.hp<<endl
            <<" El planeta de la especie es: "<<nuevonodo->alien.hogar->nombre;    
            cout<<"----------------------------------------"<<endl;    
            break;
        }
    }    
    if(encontrado==false){
        cout<<endl<<"Objetivo no encontrado"<<endl;
    }
    }
}

void modificarbioma(nodoalien *&listaaliens, nodobioma *&listabiomas){
    nodobioma *nuevonodo= listabiomas;
    nodobioma *bioma = listabiomas;
    int objetivo;
    bool resp=true;
    bool encontrado=true;
    char change;
    char estruc;
    string planeta;
    int numplanetas;
    while(resp==true){
        cout<<"----------------------------------------"<<endl;
        cout<<endl<<"Desea hacer cambios a los biomas? (Estos cambios se veran reflejados en los aliens nativos.) (S/N)";
        cin>>change;
        if((change == 'S')||(change == 's')){
            cout<<endl<<"A continuacion se mostraran los biomas: "<<endl;
            mostrarbiomas(listabiomas);
            while(resp=true){
                cout<<"Ingrese el indice (numero) del bioma cuyo nombre desea modificar: ";
                bool encontrado=false;
        		while (encontrado==false){
        			int objetivo=input_int();
            		while((bioma!=NULL)&&(bioma->indice!=objetivo)){
            		    bioma=bioma->next;
						}
            		if(bioma==NULL){
            		    cout<<endl<<"Objetivo no encontrado, vuelva a intentar: ";
            		    bioma=listabiomas;
						}
					else{
               			encontrado=true;
					}
                }
                	string prev_nombre=bioma->nombre;
                    cout<<endl<<"Cual es el nuevo nombre del bioma? ";
                    bioma->nombre=input_str();
                    cout<<"Cambios realizados.";
                    cout<<endl<<"El nombre del bioma es: "<<bioma->nombre;
                    cout<<endl<<"----------------------------------------"<<endl;
                    nodoalien *aux=listaaliens;
    			while(aux!=NULL){
        			if (aux->alien.hogar->nombre==prev_nombre){
        				aux->alien.hogar->nombre=bioma->nombre;
					}
					aux=aux->next;}
                break;
                
                }
                
                resp=false;
            }
                        
        else{
            break;
        }
    }}


void modificaritem(nodoitem*&listaitem, nodobioma *&listabiomas){
    nodoitem *nuevonodo= new nodoitem();
    nuevonodo = listaitem;
    nodobioma *bioma=listabiomas;
    int objetivo;
    bool resp=true;
    bool encontrado=true;
    char change;
    char estruc;
    bool x=true;
    int caso3;
    while(resp==true){
        cout<<"----------------------------------------"<<endl;
        cout<<endl<<"Desea cambiar un item? (S/N) ";
        cin >> change;
        if((change == 'S')||(change == 's')){
            cout<<endl<<"A continuacion se mostraran los items: "<<endl;
            mostraritem(listaitem);
            while(resp==true){
                cout<<"Ingrese el indice (numero) del que desea modificar: ";
                objetivo=input_int();
                while((nuevonodo!=NULL)&&(nuevonodo->indice!=objetivo)){
                    nuevonodo=nuevonodo->next;
                    encontrado=false;
                    if(nuevonodo->indice==objetivo){
                        encontrado=true;
                }
                }
            cout<<"Ingrese un nuevo nombre del item: ";
            nuevonodo->item.nombre=input_str();
            nuevonodo->item.tipo=0;
            cout<<endl<<"Ingrese el tipo de item:"<<endl<<"1. Ataque"<<endl<<"2. Defensa"<<endl<<"3. Recuperacion"<<endl<<"4. Condicion"<<endl;
            int y=input_int();
			while(y<1 || y>4){
            	cout<<"Opcion invalida, vuelva a intentar: ";
            	y=input_int();
			}
			nuevonodo->item.tipo=y;
            switch (nuevonodo->item.tipo)
            {
            case 1:
                cout<<endl<<"Ingrese la cantidad de dano que hace: ";
                nuevonodo->item.valor=input_int();
                resp = false;
                break;
            
            case 2:
                cout<<endl<<"Ingrese el porcentaje de dano que reduce: ";
                nuevonodo->item.valor=input_int();
                cout<<endl<<"Ingrese el escudo inicial que proporciona (no recuperable)";
                nuevonodo->item.defensa=input_int();
                resp = false;
                break;
            
            case 3:
                cout<<"----------------------------------------"<<endl;
    	    	while(x){
					cout<<endl<<"Su objeto de recuperacion recupera vida (1) o energia (2)?"<<endl;
					caso3=input_int();
					if (caso3==1){
						nuevonodo->item.apoyo="vida";
						x=false;
					}if (caso3==2){
						nuevonodo->item.apoyo="energia";
						x=false;
					}if(caso3!=1&&caso3!=2){
						cout<<"opcion invalida, intente de nuevo"<<endl;
					}
					}
				cout<<endl<<"Indique cuanta "<<nuevonodo->item.apoyo<<" recupera por turno: "<<endl;
				nuevonodo->item.valor=input_int();
        		cout<<"----------------------------------------"<<endl;
       			resp=false;
				break;

            case 4:
                cout<<"---------------------------------------------------------------------------------------------"<<endl;
        		cout<<"Ingrese el indice del bioma al que condiciona el objeto: ";
        		mostrarbiomas(listabiomas);
        		while (encontrado==false){
		        	int objetivo=input_int();
        		    while((bioma!=NULL)&&(bioma->indice!=objetivo)){
                		bioma=bioma->next;
					}
            		if(bioma==NULL){
                		cout<<endl<<"Objetivo no encontrado, vuelva a intentar: ";
                		bioma=listabiomas;
					}
					else{
               			encontrado=true;
						}
                }
        		nuevonodo->item.apoyo=bioma->nombre;
        		resp=false;
        		break;
            }
            cout<<"Ingrese la cantidad de energia que consume por turno: ";
	        nuevonodo->item.nrgconum=input_int();
            cout<<"----------------------------------------"<<endl;
            
        }
        }
        else{
            break;
        }
        
    }
}

void eliminar1alien(nodoalien*&listaaliens){
	int objetivo;
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Elige un alien para eliminar. "<<endl;
	mostraralien(listaaliens);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	objetivo=input_int();
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
			nodoalien *aux2=listaaliens->next;
            listaaliens=listaaliens->next;
			delete aux_borrar;
			while(aux2!=NULL){
                aux2->indice--;
				aux2=aux2->next;
    			}
		}
		else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
			nodoanterior=nodoanterior->next;
            while((nodoanterior!=NULL)){
			    nodoanterior->indice--;
			    nodoanterior=nodoanterior->next;
			    
            }
        
		}
		}
    	
    else{
    	cout<<endl<<"La lista esta vacia";
	}
	if(listaaliens!=NULL){
        	while (listaaliens->indice!=1){
        		if (listaaliens->indice<1){
        			listaaliens->indice++;
				}else if (listaaliens->indice>1){
					listaaliens->indice--;
				}
			}
		}
    cout<<endl<<"Alien borrado"<<endl;
    cout<<"----------------------------------------"<<endl;
}

void eliminar1bioma(nodobioma *&listabiomas){
	int objetivo;
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Elige un bioma para eliminar. "<<endl;
	mostrarbiomas(listabiomas);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	objetivo=input_int();
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
		}else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
			nodoanterior=nodoanterior->next;
            while((nodoanterior!=NULL)){
			    nodoanterior->indice--;
			    nodoanterior=nodoanterior->next;  
            	}
			}
    	}
    else{
    	cout<<endl<<"La lista esta vacia";
	}
	if(listabiomas!=NULL){
        	while (listabiomas->indice!=1){
        		if (listabiomas->indice<1){
        			listabiomas->indice++;
				}else if (listabiomas->indice>1){
					listabiomas->indice--;
				}
			}
		}
    cout<<endl<<"Bioma borrado"<<endl;
    cout<<"----------------------------------------"<<endl;
	}

void eliminar1item(nodoitem *&listaitems){
	int objetivo;
    cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Elige un bioma para eliminar. "<<endl;
	mostraritem(listaitems);
	cout<<endl<<"Escribe el indice (numero) del que quiera eliminar: ";
	objetivo=input_int();
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
			while(nodoanterior!=NULL){
			    nodoanterior->indice--;
			    nodoanterior=nodoanterior->next;  
            }
		}else{
			nodoanterior->next=aux_borrar->next;
			delete aux_borrar;
			nodoanterior=nodoanterior->next;
            while((nodoanterior!=NULL)){
			    nodoanterior->indice--;
			    nodoanterior=nodoanterior->next;  
            	}
			}
    	}
    else{
    	cout<<endl<<"La lista esta vacia";
	}
	if(listaitems!=NULL){
        	while (listaitems->indice!=1){
        		if (listaitems->indice<1){
        			listaitems->indice++;
				}else if (listaitems->indice>1){
					listaitems->indice--;
				}
			}
		}
    cout<<endl<<"Item borrado"<<endl;
    cout<<"----------------------------------------"<<endl;
	}

void eliminaraliens(nodoalien *&lista){
    nodoalien *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Aliens borrados";
}

void eliminaritems(nodoitem *&lista){
    nodoitem *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Items borrados"<<endl;
}

void eliminarbiomas(nodobioma *&lista){
    nodobioma *aux=lista;
    while(lista!=NULL){
        lista=aux->next;
        delete aux;
        aux=lista;
    }
    cout<<endl<<"Biomas borrados"<<endl;
}

void cargarbiomas( nodobioma *&listabiomas){
	ifstream archivo;
	string nombre_archivo;
	string contenido;
	nodobioma *nuevobioma=listabiomas;
	int inicio=0;
	do{
		cout<<"Ingrese el nombre del archivo con los biomas: ";
		getline(cin,nombre_archivo);
		archivo.open(nombre_archivo.c_str(), ios::in);
		if(archivo.fail()){
			cout<<endl<<"archivo no existente, vuelva a intentar"<<endl;
		}
	}while(archivo.fail());
	int salto=0;
	while(!archivo.eof()){
		getline(archivo, contenido);
		if (salto!=0&&contenido!="--"){
			if (listabiomas!=NULL){
				while(nuevobioma->next!=NULL){
					nuevobioma=nuevobioma->next;
				}
				inicio=nuevobioma->indice;
				nuevobioma->next=new nodobioma;
				nuevobioma=nuevobioma->next;
				nuevobioma->indice=inicio+1;
				nuevobioma->nombre=contenido;
				nuevobioma->next=NULL;
				}
			else{
				listabiomas= new nodobioma;
				listabiomas->next=NULL;
				nuevobioma=listabiomas;
				nuevobioma->indice=inicio+1;
				nuevobioma->nombre=contenido;
				nuevobioma->next=NULL;
				}	
			if(contenido!="--"){salto--;}
			}salto++;
		
}
}

void cargaritems( nodoitem *&listaitems){
    ifstream archivo;
	string nombre_archivo;
	string contenido;
	nodoitem *nuevoitem=listaitems;
	int inicio=1;
    do{
		cout<<"Ingrese el nombre del archivo con los accesorios: ";
		getline(cin,nombre_archivo);
		archivo.open(nombre_archivo.c_str(), ios::in);
		if(archivo.fail()){
			cout<<endl<<"archivo no existente, vuelva a intentar"<<endl;
		}
	}while(archivo.fail());
	int salto=0;
	int i=0;
	while(!archivo.eof()){
		getline(archivo, contenido);
		if(listaitems==NULL){
			listaitems= new nodoitem;
			listaitems->next=NULL;
			listaitems->indice=1;
			nuevoitem=listaitems;
		}else{
			while(nuevoitem->next!=NULL){
				nuevoitem=nuevoitem->next;
				inicio=nuevoitem->indice;
				if(nuevoitem->next==NULL){
					nuevoitem->next=new nodoitem;
					nuevoitem=nuevoitem->next;
					nuevoitem->next=NULL;
					inicio++;
				}
			}
		}
		if(contenido=="--"&&salto!=1){
			if(nuevoitem->next==NULL){
				nuevoitem->next=new nodoitem;
			}
			nuevoitem=nuevoitem->next;
			nuevoitem->next=NULL;
			i=0;
		}
		if (salto!=0&&contenido!="--"){
			switch (i){
				case 0:
					nuevoitem->indice=inicio;
					inicio++;
					nuevoitem->item.nombre=contenido;
					break;
				case 1:
					if (strstr(contenido.c_str(), "taqu")){
						nuevoitem->item.tipo=1;
					}
					if (strstr(contenido.c_str(), "efens")){
						nuevoitem->item.tipo=2;
					}
					if (strstr(contenido.c_str(), "viv")){
						nuevoitem->item.tipo=3;
					}
					if (strstr(contenido.c_str(), "ondici")){
						nuevoitem->item.tipo=4;
					}
					break;
				case 2:
					contenido=contenido.substr(6,-1);
					nuevoitem->item.valor=atoi(contenido.c_str());
					break;
				case 3:
					if(nuevoitem->item.tipo==3||nuevoitem->item.tipo==4){
						nuevoitem->item.apoyo=contenido.substr(14,-1);
					}
					break;
				case 4:
					contenido=contenido.substr(8,-1);
					nuevoitem->item.nrgconum=atoi(contenido.c_str());
					break;
				case 5:
					contenido=contenido.substr(11,-1);
					nuevoitem->item.defensa=atoi(contenido.c_str());
					break;
			}
		i++;
		}salto++;
}
}

void cargaraliens( nodoalien *&listaaliens, nodobioma *&listabiomas){
	ifstream archivo;
	string nombre_archivo;
	string contenido;
	nodoalien *nuevoalien=listaaliens;
	nodobioma *biomas=listabiomas;
	int inicio=1;
	int inicio2=1;
	bool encontrado=0;
    do{
		cout<<"Ingrese el nombre del archivo con los aliens: ";
		getline(cin,nombre_archivo);
		archivo.open(nombre_archivo.c_str(), ios::in);
		if(archivo.fail()){
			cout<<endl<<"archivo no existente, vuelva a intentar"<<endl;
		}
	}while(archivo.fail());
	int salto=0;
	int i=0;
	while(!archivo.eof()){
		getline(archivo, contenido);
		if(listaaliens==NULL){
			listaaliens= new nodoalien;
			listaaliens->next=NULL;
			listaaliens->indice=1;
			nuevoalien=listaaliens;
		}else{
			while(nuevoalien->next!=NULL){
				nuevoalien=nuevoalien->next;
				inicio=nuevoalien->indice;
				if(nuevoalien->next==NULL){
					nuevoalien->next=new nodoalien;
					nuevoalien=nuevoalien->next;
					nuevoalien->next=NULL;
					inicio++;
				}
			}
		}
		if(contenido=="--"&&salto!=1){
			if(nuevoalien->next==NULL){
				nuevoalien->next=new nodoalien;
			}
			nuevoalien=nuevoalien->next;
			nuevoalien->next=NULL;
			i=0;
		}
		if (salto!=0&&contenido!="--"){
			switch (i){
				case 0:
					nuevoalien->indice=inicio;
					inicio++;
					nuevoalien->alien.nombre=contenido;
					break;
				case 1:
					contenido=contenido.substr(8,-1);
					nuevoalien->alien.nrg=atoi(contenido.c_str());
					break;
				case 2:
					contenido=contenido.substr(6,-1);
					nuevoalien->alien.hp=atoi(contenido.c_str());
					break;
				case 3:
					biomas=listabiomas;
					if(listabiomas==NULL){
						listabiomas= new nodobioma;
						biomas=listabiomas;
						biomas->nombre=contenido;
						biomas->next=NULL;
						biomas->indice=1;
						nuevoalien->alien.hogar=biomas;
					}else{
						encontrado=0;
						if(biomas->nombre==contenido){
							nuevoalien->alien.hogar=biomas;
						}else{
							while(biomas->next!=NULL&&encontrado==false){
								biomas=biomas->next;
								if(biomas->nombre==contenido){
									nuevoalien->alien.hogar=biomas;
									encontrado=1;
								}
							}
							if(encontrado==false){
								biomas->next=new nodobioma;
								inicio2=biomas->indice;
								biomas=biomas->next;
								biomas->nombre=contenido;
								biomas->next=NULL;
								biomas->indice=inicio2+1;
								nuevoalien->alien.hogar=biomas;
							}
						}
					}
					break;
			}
		i++;
		}salto++;
}
}

void turno_combate(soldado miembros[2], bool item11, bool item12, bool item13, bool item21, bool item22, bool item23){
	int dano=0; int defensa=0; int recibido=0; int escudo=0; int n=0;
	soldado atacante=miembros[0];
	soldado receptor=miembros[1];
	if(item11){
	switch(atacante.item1.tipo){
		case 1:
			cout<<endl<<atacante.alien.nombre<<" ha atacado usando "<<atacante.item1.nombre<<endl;
			cout<<"Ha causado: "<<atacante.item1.valor<<" de dano usando "<<atacante.item1.nombre<<endl;
			if((receptor.item1.tipo==2&&item21)||(receptor.item2.tipo==2&&item22)||(receptor.item3.tipo==2&&item23)){
				if(receptor.item1.tipo==2&&item21){
					defensa+=receptor.item1.valor;
					escudo+=receptor.item1.defensa;
					escudo+=receptor.item1.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item1.nrgconum;
				}
				if(receptor.item2.tipo==2&&item22){
					defensa+=receptor.item2.valor;
					escudo+=receptor.item2.defensa;
					escudo+=receptor.item2.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item2.nrgconum;
					}
				if(receptor.item3.tipo==2&&item23){
					defensa+=receptor.item3.valor;
					escudo+=receptor.item3.defensa;
					escudo+=receptor.item3.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item3.nrgconum;
					}}
				dano=atacante.item1.valor;
				dano=dano-(dano*defensa/100);
				recibido=escudo-dano;
				if(recibido<0){
					cout<<atacante.item1.nombre<< "ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
					cout<<receptor.alien.nombre<<" ha recibido "<<(recibido*(-1))<<" de dano"<<endl;
					cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item1.nrgconum<<" ptos de energia"<<endl;
					atacante.alien.nrg-=atacante.item1.nrgconum;
					receptor.alien.hp+=recibido;
				}else{
					cout<<atacante.item1.nombre<< "ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
					cout<<receptor.alien.nombre<<" no ha recibido dano"<<endl;
					cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item1.nrgconum<<" ptos de energia"<<endl;
					atacante.alien.nrg-=atacante.item1.nrgconum;
				}
				escudo=escudo-dano;
				if(receptor.item1.tipo==2&&item21){
					n++;
				}
				if(receptor.item2.tipo==2&&item22){
					n++;
					}
				if(receptor.item3.tipo==2&&item23){
					n++;
					}
				if(receptor.item1.tipo==2&&item21){
					escudo+=receptor.item1.defensa=escudo/n;
				}
				if(receptor.item2.tipo==2&&item22){
					escudo+=receptor.item2.defensa/n;
					}
				if(receptor.item3.tipo==2&&item23){
					escudo+=receptor.item3.defensa/n;
					}
		break;
		case 3:
			cout<<atacante.alien.nombre<<" ha recuperado "<<atacante.item1.apoyo<<" usando "<<atacante.item1.nombre<<endl;
			cout<<"Ha recuperado: "<<atacante.item1.valor<<" puntos de "<<atacante.item1.apoyo<<endl;
			cout<<atacante.item1.nombre<<" ha perdido "<<atacante.item1.nrgconum<<" ptos de energia"<<endl;
			atacante.alien.nrg-=atacante.item1.nrgconum;
			break;
		
	}
	}
	if(item12){
	switch(atacante.item2.tipo){
		case 1:
			cout<<endl<<atacante.alien.nombre<<" ha atacado usando "<<atacante.item2.nombre<<endl;
			cout<<"Ha causado: "<<atacante.item2.valor<<" de dano usando "<<atacante.item2.nombre<<endl;
			if((receptor.item1.tipo==2&&item21)||(receptor.item2.tipo==2&&item22)||(receptor.item3.tipo==2&&item23)){
				if(receptor.item1.tipo==2&&item21){
					defensa+=receptor.item1.valor;
					escudo+=receptor.item1.defensa;
					escudo+=receptor.item1.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item1.nrgconum;
				}
				if(receptor.item2.tipo==2&&item22){
					defensa+=receptor.item2.valor;
					escudo+=receptor.item2.defensa;
					escudo+=receptor.item2.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item2.nrgconum;
					}
				if(receptor.item3.tipo==2&&item23){
					defensa+=receptor.item3.valor;
					escudo+=receptor.item3.defensa;
					escudo+=receptor.item3.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item3.nrgconum;
					}}
				dano=atacante.item2.valor;
				dano=dano-(dano*defensa/100);
				recibido=escudo-dano;
				if(recibido<0){
					cout<<atacante.item2.nombre<< "ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
					cout<<receptor.alien.nombre<<" ha recibido "<<(recibido*(-1))<<" de dano"<<endl;
					cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item2.nrgconum<<" ptos de energia"<<endl;
					atacante.alien.nrg-=atacante.item2.nrgconum;
					receptor.alien.hp+=recibido;
				}else{
					cout<<atacante.item1.nombre<< "ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
					cout<<receptor.alien.nombre<<" no ha recibido dano"<<endl;
					cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item2.nrgconum<<" ptos de energia"<<endl;
					atacante.alien.nrg-=atacante.item2.nrgconum;
				}
				escudo=escudo-dano;
				if(receptor.item1.tipo==2&&item21){
					n++;
				}
				if(receptor.item2.tipo==2&&item22){
					n++;
					}
				if(receptor.item3.tipo==2&&item23){
					n++;
					}
				if(receptor.item1.tipo==2&&item21){
					receptor.item1.defensa=escudo/n;
				}
				if(receptor.item2.tipo==2&&item22){
					receptor.item2.defensa/n;
					}
				if(receptor.item3.tipo==2&&item23){
					receptor.item3.defensa/n;
					}
		break;
		case 3:
			cout<<atacante.alien.nombre<<" ha recuperado "<<atacante.item2.apoyo<<" usando "<<atacante.item2.nombre<<endl;
			cout<<"Ha recuperado: "<<atacante.item2.valor<<" puntos de "<<atacante.item2.apoyo<<endl;
			cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item2.nrgconum<<" ptos de energia"<<endl;
			atacante.alien.nrg-=atacante.item2.nrgconum;
			break;
		
	}
	}
	if(item13){
	switch(atacante.item3.tipo){
		case 1:
			cout<<endl<<atacante.alien.nombre<<" ha atacado usando "<<atacante.item3.nombre<<endl;
			cout<<"Ha causado: "<<atacante.item3.valor<<" de dano usando "<<atacante.item3.nombre<<endl;
			if((receptor.item1.tipo==2&&item21)||(receptor.item2.tipo==2&&item22)||(receptor.item3.tipo==2&&item23)){
				if(receptor.item1.tipo==2&&item21){
					defensa+=receptor.item1.valor;
					escudo+=receptor.item1.defensa;
					escudo+=receptor.item1.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item1.nrgconum;
				}
				if(receptor.item2.tipo==2&&item22){
					defensa+=receptor.item2.valor;
					escudo+=receptor.item2.defensa;
					escudo+=receptor.item2.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item2.nrgconum;
					}
				if(receptor.item3.tipo==2&&item23){
					defensa+=receptor.item3.valor;
					escudo+=receptor.item3.defensa;
					escudo+=receptor.item3.defensa=0;
					receptor.alien.nrg-=escudo+=receptor.item3.nrgconum;
					}}
			dano=atacante.item3.valor;
			dano=dano-(dano*defensa/100);
			recibido=escudo-dano;
			if(recibido<0){
				cout<<atacante.item3.nombre<<" ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
				cout<<receptor.alien.nombre<<" ha recibido "<<(recibido*(-1))<<" de dano "<<endl;
				cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item3.nrgconum<<" ptos de energia"<<endl;
				atacante.alien.nrg-=atacante.item3.nrgconum;
				receptor.alien.hp+=recibido;
			}else{
				cout<<atacante.item3.nombre<< "ha inflingido "<<dano<<" de dano debido a la proteccion del enemigo, pero "<<receptor.alien.nombre<<" tenia "<<escudo<<" puntos de escudo."<<endl;
				cout<<receptor.alien.nombre<<" no ha recibido dano."<<endl;
				cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item3.nrgconum<<" ptos de energia"<<endl;
				atacante.alien.nrg-=atacante.item3.nrgconum;
			}
			escudo=escudo-dano;
			if(receptor.item1.tipo==2&&item21){
				n++;
			}
			if(receptor.item2.tipo==2&&item22){
			n++;
				}
			if(receptor.item3.tipo==2&&item23){
				n++;
				}
			if(receptor.item1.tipo==2&&item21){
				receptor.item1.defensa=escudo/n;
			}
			if(receptor.item2.tipo==2&&item22){
				receptor.item2.defensa/n;
				}
			if(receptor.item3.tipo==2&&item23){
				receptor.item3.defensa/n;
				}
		break;
		case 3:
			cout<<endl<<atacante.alien.nombre<<" ha recuperado "<<atacante.item3.apoyo<<" usando "<<atacante.item3.nombre<<endl;
			cout<<"Ha recuperado: "<<atacante.item2.valor<<" puntos de "<<atacante.item2.apoyo<<endl;
			cout<<atacante.alien.nombre<<" ha perdido "<<atacante.item3.nrgconum<<" ptos de energia"<<endl;
			atacante.alien.nrg-=atacante.item3.nrgconum;
			break;
		}
		}
		miembros[0]=atacante;
		miembros[1]=receptor;
		}

void combate_maquina(nodoalien *&listaaliens,nodoitem *&listaitems,nodobioma *&listabiomas){
	nodoalien *aliens=listaaliens;//definiciones
	nodoitem *items=listaitems;
	nodobioma *biomas=listabiomas;
	accesorio mochila1[5];
	accesorio mochila2[5];
	string arena;
	soldado soldados1[3];
	soldado soldados2[3];
	int num_aliens;
	int num_items;
	int num_biomas;
	int buscador=0;
	int totalhp1, totalnrg1, totalhp2, totalnrg2;
	while(aliens->next!=NULL){//dandole valor al total de items, aliens y biomas para el random
		aliens=aliens->next;
	}num_aliens=aliens->indice; aliens=listaaliens;
	while(items->next!=NULL){
		items=items->next;
	}num_items=items->indice; items=listaitems;
	while(biomas->next!=NULL){
		biomas=biomas->next;
	}num_biomas=biomas->indice; biomas=listabiomas;
	//preparando para seleccionar un bioma para la arena
	bool encontrado=false;
    while (encontrado==false){
    	buscador=1+rand()%num_biomas;
        while((biomas->next!=NULL)&&(biomas->indice!=buscador)){
            biomas=biomas->next;
				}
        if(biomas==NULL){
            biomas=listabiomas;
				}
		else{
           	encontrado=true;
			}
        }
    arena=biomas->nombre;
    cout<<"El combate se dara en: "<<arena<<endl;
    //maquina selecciona
    for(int p=0; p < 3;p++){
		encontrado = false;
		aliens = listaaliens;
		while(encontrado == false){;
			buscador=1+rand()%(num_aliens+1);
			while((aliens != NULL)&&(aliens->indice!=buscador)){
				aliens=aliens->next;
			}
				if(aliens->indice!=buscador){
					cout<<endl<<"El soldado seleccionado no esta disponible.";
					aliens=listaaliens;
				}
				else{
					encontrado=true;
				}
		}
		soldados2[p].alien=aliens->alien;
	}
	//seleccionar personaje (usuario)
	cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Elige un soldado, combatiente numero 1. "<<endl;
	mostraralien(listaaliens);
	cout<<endl<<"Escribe el indice (numero) de los 3 soldados que quieras seleccionar. ";
	cout<<"----------------------------------------"<<endl;
	for(int p=0; p < 3;p++){
		encontrado = false;
		aliens = listaaliens;
		while(encontrado == false){
			cout<<"----------------------------------------"<<endl;
			cout<<endl<<"Escribe el indice (numero) del soldado "<<p+1<<" que saldra a batallar: ";
			cout<<"----------------------------------------"<<endl;
			buscador=input_int();
			while((aliens->next!= NULL)&&(aliens->indice!=buscador)){
				aliens=aliens->next;
			}
				if(aliens->indice!=buscador){
					cout<<"----------------------------------------"<<endl;
					cout<<endl<<"El soldado seleccionado no esta disponible.";
					cout<<"----------------------------------------"<<endl;
					aliens=listaaliens;
				}
				else{
					encontrado=true;
				}
		}
		soldados1[p].alien= aliens->alien;
	}
    //seleccionar objetos
    encontrado=false;
	cout<<"----------------------------------------"<<endl;
    cout<<"Contamos con los siguientes objetos: "<<endl;
    mostraritem(listaitems);
    cout<<"Seleccione 5 para usar en el combate"<<endl;
	cout<<"----------------------------------------"<<endl;
    for(int i=0; i<5; i++){
    	encontrado=false;
    	items=listaitems;
    	while (encontrado==false){
			cout<<"----------------------------------------"<<endl;
    		cout<<"Ingrese los indices del objeto "<<i+1<<" que vas a llevar: ";
			cout<<"----------------------------------------"<<endl;
    		buscador=input_int();
        	while((items->next!=NULL)&&(items->indice!=buscador)){
        	    items=items->next;
					}
        	if(items->indice!=buscador){
				cout<<"----------------------------------------"<<endl;
        		cout<<endl<<"Objeto no encontrado, vuelva a intentar: "<<endl;
				cout<<"----------------------------------------"<<endl;
        	    items=listaitems;
				}
			else{
           		encontrado=true;
				}
        }mochila1[i]=items->item;
	}
	for(int i=0; i<5; i++){
    	encontrado=false;
    	items=listaitems;
    	while (encontrado==false){
    		buscador=1+rand()%num_items;
        	while((items->next!=NULL)&&(items->indice!=buscador)){
        	    items=items->next;
					}
        	if(items->indice!=buscador){
        	    items=listaitems;
				}
			else{
           		encontrado=true;
				}
        }mochila2[i]=items->item;
	}
	//randomizar aliens
	int aux;
	soldado temp;
	for(int i=0;i<3;i++){
		aux=rand()%4;
		if(aux==0){
			temp=soldados1[i];
			soldados1[i]=soldados2[i];
			soldados2[i]=temp;
		}
	}
	cout<<"----------------------------------------"<<endl;
	cout<<endl<<"Tras la randomizacion de especies, los equipos quedaron: "<<endl;
	for(int i=0;i<3;i++){
		cout<<soldados1[i].alien.nombre<<", ";
	}cout<<"en el equipo del jugador"<<endl;
	
	for(int i=0;i<3;i++){
		cout<<soldados2[i].alien.nombre<<", ";
	}cout<<"en el equipo del enemigo"<<endl;
	cout<<"----------------------------------------"<<endl;
	
	cout<<endl<<"Ahora que hemos seleccionado a los personajes, empecemos el combate"<<endl<<endl;
	bool seleccionado=false;
	int combatiente1;
	int combatiente2;
	int obj;
	int rotar;
	int obj1=-1;
	int obj2=-1;
	int obj3=-1;
	while((soldados1[0].alien.hp>0||soldados1[1].alien.hp>0||soldados1[2].alien.hp>0)&&(soldados2[0].alien.hp>0||soldados2[1].alien.hp>0||soldados2[2].alien.hp>0)){
		seleccionado=false;
		cout<<"De entre sus soldados: "<<endl;
		for(int i=0;i<3;i++){
			cout<<i+1<<". "<<soldados1[i].alien.nombre<<endl;}
		cout<<"Escoja (usando su respectivo numero) al siguiente soldado en pelear: ";
		while(seleccionado==false){
			buscador=input_int();
			if((buscador==1||buscador==2||buscador==3)){
				combatiente1=buscador-1;
				if(soldados1[combatiente1].alien.hp>0){
					cout<<endl<<"Perfecto"<<endl;
					seleccionado=true;	
				}else{
					cout<<endl<<"El soldado seleccionado esta fuera de combate, seleccione otro"<<endl;
				}
			}else{
				cout<<endl<<"Soldado no encontrado, seleccione uno de los 3: "<<endl;
			}
		}//personaje seleccionado, ahora los objetos
		cout<<"De entre sus objetos: "<<endl;
		for(int i=0;i<5;i++){
			cout<<i+1<<". "<<mochila1[i].nombre;
			switch(mochila1[i].tipo){
				case 1:
					cout<<", de tipo ataque, ";
					cout<<"con un dano de: "<<mochila1[i].valor<<" y que consume "<<mochila1[i].nrgconum<<" de energia cada turno."<<endl;
					break;
				case 2:
					cout<<", de tipo defensa, ";
					cout<<"con una reduccion de dano de: "<<mochila1[i].valor<<"% y que consume "<<mochila1[i].nrgconum<<" de energia cada turno";
					cout<<", otorga un escudo inicial de "<<mochila1[i].defensa<<endl;
					break;
				case 3:
					cout<<", de tipo recuperacion, ";
					cout<<"recupera "<<mochila1[i].valor<<" de "<<mochila1[i].apoyo<<" cada turno";
					cout<<" consume "<<mochila1[i].nrgconum<<" de energia cada turno."<<endl;
					break;
				case 4:
					cout<<", de tipo condicion, ";
					cout<<"ayuda al portador a vivir en el bioma "<<mochila1[i].apoyo<<" y consume "<<mochila1[i].nrgconum<<" de energia cada turno"<<endl;
					break;
			}cout<<endl;
			}obj1=-1;
			obj2=-1;
			obj3=-1;
			seleccionado=false;
			for(int i=0;i<3;i++){
			while(seleccionado==false){
				i++;
				cout<<"Escoja el objeto "<<i<<" que cargara el soldado "<<soldados1[combatiente1].alien.nombre<<endl;
				buscador=input_int();
				if(buscador==1||buscador==2||buscador==3||buscador==4||buscador==5){
					obj=buscador-1;
					if(obj!=obj1&&obj!=obj2&&obj!=obj3){
						if(obj1==-1){
							soldados1[combatiente1].item1=mochila1[obj];
							obj1=obj;
						}
						else{
							if(obj2==-1){
							soldados1[combatiente1].item2=mochila1[obj];
							obj2=obj;
						}else{
							soldados1[combatiente1].item3=mochila1[obj];
							obj3=obj;
							cout<<"---------------------"<<endl;
							cout<<"Los 3 objetos que portara el soldado fueron seleccionados."<<endl;
							cout<<"---------------------"<<endl;
							seleccionado=true;
						}
						}
						}else{
							cout<<"---------------------"<<endl;
							cout<<"Objeto seleccionado previamente para este soldado, vuelva a intentar"<<endl;
							cout<<"---------------------"<<endl;
							i--;
						}
				}else{
					cout<<"---------------------"<<endl;
					cout<<endl<<"Objeto no encontrado, seleccione uno de los 5: "<<endl;
					cout<<"---------------------"<<endl;
					i--;
				}
		}seleccionado==false;
		}cout<<endl;
		seleccionado=false;
		while(seleccionado==false){
			buscador=1+rand()%4;
			if((buscador==1||buscador==2||buscador==3)){
				combatiente2=buscador-1;
				if(soldados2[combatiente2].alien.hp>0){
					seleccionado=true;	
				}else{

				}
			}else{
			}
		}//personaje seleccionado, ahora los objetos
		obj1=-1;
		obj2=-1;
		obj3=-1;
		seleccionado=false;
		for(int i=0;i<3;i++){
		while(seleccionado==false){
			i++;
			buscador=1+rand()%6;
			if(buscador==1||buscador==2||buscador==3||buscador==4||buscador==5){
				obj=buscador-1;
				if(obj!=obj1&&obj!=obj2&&obj!=obj3){
					if(obj1==-1){
						soldados2[combatiente2].item1=mochila2[obj];
						obj1=obj;
					}
					else{
						if(obj2==-1){
						soldados2[combatiente2].item2=mochila2[obj];
						obj2=obj;
					}else{
						soldados2[combatiente2].item3=mochila2[obj];
						obj3=obj;
						seleccionado=true;
					}
					}
					}else{
						i--;
					}
				}else{
					i--;
				}
		}seleccionado==false;
		}
		cout<<"El 2do soldado y sus objetos han sido seleccionados. El combate entre los 2 soldados empezara"<<endl;
		//empieza el combate
		cout<<"Hora del combate!!"<<endl;
		cout<<"Cual de los 2 aliens ataca primero se decidira aleatoriamente, suerte!!"<<endl<<endl;
		int moneda=0;
		bool safe1=0; bool safe2= 0;
		bool item11=0;bool item12=0;bool item13=0;
		bool item21=0;bool item22=0;bool item23=0;
		bool turno=1;
		int eleccion;
		int dano=0; int defensa=0; int recibido=0; int escudo=0; int n=0; 
		totalhp1=soldados1[combatiente1].alien.hp; 
		totalnrg1=soldados1[combatiente1].alien.nrg;
		totalhp2=soldados2[combatiente2].alien.hp; 
		totalnrg2=soldados2[combatiente2].alien.nrg;
		soldado miembros[2];
		while(soldados1[combatiente1].alien.hp>0&&soldados2[combatiente2].alien.hp>0){
				cout<<"Tu soldado es: "<<soldados1[combatiente1].alien.nombre<<" con "<<soldados1[combatiente1].alien.hp<<" de vida y "<<soldados1[combatiente1].alien.nrg<<" de energia restantes."<<endl;
				cout<<"Tu enemigo es: "<<soldados2[combatiente2].alien.nombre<<" con "<<soldados2[combatiente2].alien.hp<<" de vida y "<<soldados2[combatiente2].alien.nrg<<" de energia restantes."<<endl;
				cout<<"---------------------"<<endl;
				cout<<"Escoja cuales de los 3 objetos desea usar este turno: "<<endl;
				cout<<"---------------------"<<endl;
				cout<<"1. "<<soldados1[combatiente1].item1.nombre;
				switch(soldados1[combatiente1].item1.tipo){
					case 1:
						cout<<", de tipo ataque, ";
						cout<<"con un dano de: "<<soldados1[combatiente1].item1.valor<<" y que consume "<<soldados1[combatiente1].item1.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 2:
						cout<<", de tipo defensa, ";
						cout<<"con una reduccion de dano de: "<<soldados1[combatiente1].item1.valor<<"% y que consume "<<soldados1[combatiente1].item1.nrgconum<<" de energia cada turno";
						cout<<", otorga un escudo inicial de "<<soldados1[combatiente1].item1.defensa<<endl;
						break;
					case 3:
						cout<<", de tipo recuperacion, ";
						cout<<"recupera "<<soldados1[combatiente1].item1.valor<<" de "<<soldados1[combatiente1].item1.apoyo<<" cada turno";
						cout<<" consume "<<soldados1[combatiente1].item1.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 4:
						cout<<", de tipo condicion, ";
						cout<<"ayuda al portador a vivir en el bioma "<<soldados1[combatiente1].item1.apoyo<<" y consume "<<soldados1[combatiente1].item1.nrgconum<<" de energia cada turno"<<endl;
						break;
				}cout<<endl;
				cout<<"2. "<<soldados1[combatiente1].item2.nombre;
				switch(soldados1[combatiente1].item2.tipo){
					case 1:
						cout<<", de tipo ataque, ";
						cout<<"con un dano de: "<<soldados1[combatiente1].item2.valor<<" y que consume "<<soldados1[combatiente1].item2.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 2:
						cout<<", de tipo defensa, ";
						cout<<"con una reduccion de dano de: "<<soldados1[combatiente1].item2.valor<<"% y que consume "<<soldados1[combatiente1].item2.nrgconum<<" de energia cada turno";
						cout<<", otorga un escudo inicial de "<<soldados1[combatiente1].item2.defensa<<endl;
						break;
					case 3:
						cout<<", de tipo recuperacion, ";
						cout<<"recupera "<<soldados1[combatiente1].item2.valor<<" de "<<soldados1[combatiente1].item2.apoyo<<" cada turno";
						cout<<" consume "<<soldados1[combatiente1].item2.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 4:
						cout<<", de tipo condicion, ";
						cout<<"ayuda al portador a vivir en el bioma "<<soldados1[combatiente1].item2.apoyo<<" y consume "<<soldados1[combatiente1].item2.nrgconum<<" de energia cada turno"<<endl;
						break;
				}cout<<endl;
				cout<<"3. "<<soldados1[combatiente1].item3.nombre;
				switch(soldados1[combatiente1].item3.tipo){
					case 1:
						cout<<", de tipo ataque, ";
						cout<<"con un dano de: "<<soldados1[combatiente1].item3.valor<<" y que consume "<<soldados1[combatiente1].item3.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 2:
						cout<<", de tipo defensa, ";
						cout<<"con una reduccion de dano de: "<<soldados1[combatiente1].item3.valor<<"% y que consume "<<soldados1[combatiente1].item3.nrgconum<<" de energia cada turno";
						cout<<", otorga un escudo inicial de "<<soldados1[combatiente1].item3.defensa<<endl;
						break;
					case 3:
						cout<<", de tipo recuperacion, ";
						cout<<"recupera "<<soldados1[combatiente1].item3.valor<<" de "<<soldados1[combatiente1].item3.apoyo<<" cada turno";
						cout<<" consume "<<soldados1[combatiente1].item3.nrgconum<<" de energia cada turno."<<endl;
						break;
					case 4:
						cout<<", de tipo condicion, ";
						cout<<"ayuda al portador a vivir en el bioma "<<soldados1[combatiente1].item3.apoyo<<" y consume "<<soldados1[combatiente1].item3.nrgconum<<" de energia cada turno"<<endl;
						break;
				}cout<<endl;
				while(turno){
						while (true){
							if(soldados1[combatiente1].item1.nrgconum<=soldados1[combatiente1].alien.nrg){
								cout<<"---------------------"<<endl;
								cout<<"Usar el 1? si(escribir 1) o no (escribir 0): ";
								cout<<"---------------------"<<endl;
								eleccion=input_int();
								if(eleccion==1){
									item11=1;
									break;
								}if(eleccion==0){
									item11=0;
									break;
								}else{
									cout<<"---------------------"<<endl;
									cout<<endl<<"Por favor ingrese 1 o 0"<<endl;
									cout<<"---------------------"<<endl;
								}}else{
									cout<<"---------------------"<<endl;
									cout<<"No tiene energia suficiente para usar el objeto "<<soldados1[combatiente1].item1.nombre<<endl;
									cout<<"---------------------"<<endl;
									item11=0;
									break;
								}
					}
					while (true){
						if(soldados1[combatiente1].item2.nrgconum<=soldados1[combatiente1].alien.nrg){
								cout<<"---------------------"<<endl;
								cout<<"Usar el 2? si(escribir 1) o no (escribir 0): ";
								cout<<"---------------------"<<endl;
								eleccion=input_int();
								if(eleccion==1){
									item12=1;
									break;
								}if(eleccion==0){
									item12=0;
									break;
								}else{
									cout<<"---------------------"<<endl;
									cout<<endl<<"Por favor ingrese 1 o 0"<<endl;
									cout<<"---------------------"<<endl;
								}}else{
									cout<<"---------------------"<<endl;
									cout<<"No tiene energia suficiente para usar el objeto "<<soldados1[combatiente1].item2.nombre<<endl;
									cout<<"---------------------"<<endl;
									item12=0;
									break;
								}
					}
					while (true){
						if(soldados1[combatiente1].item3.nrgconum<=soldados1[combatiente1].alien.nrg){
								cout<<"---------------------"<<endl;
								cout<<"Usar el 3? si(escribir 1) o no (escribir 0): ";
								cout<<"---------------------"<<endl;
								eleccion=input_int();
								if(eleccion==1){
									item13=1;
									break;
								}if(eleccion==0){
									item13=0;
									break;
								}else{
									cout<<"---------------------"<<endl;
									cout<<endl<<"Por favor ingrese 1 o 0"<<endl;
									cout<<"---------------------"<<endl;
								}}else{
									cout<<"---------------------"<<endl;
									cout<<"No tiene energia suficiente para usar el objeto "<<soldados1[combatiente1].item3.nombre<<endl;
									cout<<"---------------------"<<endl;
									item13=0;
									break;
								}
					}turno=0;
				}turno=1;

				if((soldados1[combatiente1].item1.tipo==4&&item11)||(soldados1[combatiente1].item2.tipo==4&&item12)||(soldados1[combatiente1].item3.tipo==4&&item13)){
					if(soldados1[combatiente1].item1.apoyo==arena){
						safe1=true;
					}
					if(soldados1[combatiente1].item2.apoyo==arena){
						safe1=true;
					}
					if(soldados1[combatiente1].item3.apoyo==arena){
						safe1=true;
					}}
				//seleccion de objetos maquina
				while(turno){
					while (true){
						if(soldados2[combatiente2].item1.nrgconum<=soldados2[combatiente2].alien.nrg){
							eleccion=moneda=rand()%2;
							if(eleccion==1){
								item21=1;
								break;
							}if(eleccion==0){
								item21=0;
								break;
							}
						}else{
							item21=0;
							break;
						}
					}
					while (true){
						if(soldados2[combatiente2].item2.nrgconum<=soldados2[combatiente2].alien.nrg){
							eleccion=moneda=rand()%2;
							if(eleccion==1){
								item22=1;
								break;
							}if(eleccion==0){
								item22=0;
								break;
							}
						}else{
							item22=0;
							break;
						}
					}
					while (true){
						if(soldados2[combatiente2].item3.nrgconum<=soldados2[combatiente2].alien.nrg){
							eleccion=moneda=rand()%2;
							if(eleccion==1){
								item23=1;
								break;
							}if(eleccion==0){
								item23=0;
								break;
							}
						}else{
							item23=0;
							break;
						}
					}turno=0;
				}turno=1;
				if((soldados2[combatiente2].item1.tipo==4&&item21)||(soldados2[combatiente2].item2.tipo==4&&item22)||(soldados2[combatiente2].item3.tipo==4&&item23)){
					if(soldados2[combatiente2].item1.apoyo==arena){
						safe2=true;
					}
					if(soldados1[combatiente2].item2.apoyo==arena){
						safe2=true;
					}
					if(soldados2[combatiente2].item3.apoyo==arena){
						safe2=true;
					}}

				if(soldados1[combatiente1].alien.hogar->nombre==arena){
					safe1==true;
				}
				if(soldados2[combatiente2].alien.hogar->nombre==arena){
					safe2==true;
				}

				if(!safe1){
					soldados1[combatiente1].alien.hp-=(soldados1[combatiente1].alien.hp)*1/3;
				}
				if(!safe2){
					soldados2[combatiente2].alien.hp-=(soldados2[combatiente2].alien.hp)*1/3;
				}

				if(safe1==safe2){
					moneda=rand()%2;
					if(moneda==0){
						miembros[0]=soldados1[combatiente1]; miembros[1]=soldados2[combatiente2];
						turno_combate(miembros, item11, item12, item13, item21, item22, item23);
						cout<<endl;
						soldados1[combatiente1]=miembros[0];soldados2[combatiente2]=miembros[1];

						miembros[0]=soldados2[combatiente2]; miembros[1]=soldados1[combatiente1];
						turno_combate(miembros, item21, item22, item23, item11, item12, item13);
						cout<<endl;
						soldados2[combatiente2]=miembros[0];soldados1[combatiente1]=miembros[1];

					}else{
						miembros[0]=soldados2[combatiente2]; miembros[1]=soldados1[combatiente1];
						turno_combate(miembros, item21, item22, item23, item11, item12, item13);
						cout<<endl;
						soldados2[combatiente2]=miembros[0];soldados1[combatiente1]=miembros[1];

						miembros[0]=soldados1[combatiente1]; miembros[1]=soldados2[combatiente2];
						turno_combate(miembros, item11, item12, item13, item21, item22, item23);
						cout<<endl;
						soldados1[combatiente1]=miembros[0];soldados2[combatiente2]=miembros[1];
					}

			}else{//todo de nuevo pero al reves
				if(safe1&&!safe2){
					miembros[0]=soldados2[combatiente2]; miembros[1]=soldados1[combatiente1];
					turno_combate(miembros, item21, item22, item23, item11, item12, item13);
					cout<<endl;
					soldados2[combatiente2]=miembros[0];soldados1[combatiente1]=miembros[1];

					miembros[0]=soldados1[combatiente1]; miembros[1]=soldados2[combatiente2];
					turno_combate(miembros, item11, item12, item13, item21, item22, item23);
					cout<<endl;
					soldados1[combatiente1]=miembros[0];soldados2[combatiente2]=miembros[1];
					}else{
						miembros[0]=soldados1[combatiente1]; miembros[1]=soldados2[combatiente2];
						turno_combate(miembros, item11, item12, item13, item21, item22, item23);
						cout<<endl;
						soldados1[combatiente1]=miembros[0];soldados2[combatiente2]=miembros[1];

						miembros[0]=soldados2[combatiente2]; miembros[1]=soldados1[combatiente1];
						turno_combate(miembros, item21, item22, item23, item11, item12, item13);
						cout<<endl;
						soldados2[combatiente2]=miembros[0];soldados1[combatiente1]=miembros[1];
					}
			}
			if(!safe1){
				soldados1[combatiente1].alien.hp-=totalhp1/3;
				soldados1[combatiente1].alien.nrg-=totalnrg1/3;
				cout<<soldados1[combatiente1].alien.nombre<<" ha perdido "<<totalhp1/3<<" puntos de vida y "<<totalnrg1/3<<" de energia por no estar preparados para el ambiente de la arena."<<endl;
			}
			if(!safe2){
				soldados1[combatiente1].alien.hp-=totalhp2/3;
				soldados1[combatiente1].alien.nrg-=totalnrg2/3;
				cout<<soldados2[combatiente2].alien.nombre<<" ha perdido "<<totalhp2/3<<" puntos de vida y "<<totalnrg2/3<<" de energia por no estar preparados para el ambiente de la arena."<<endl;
			}
		}
	}if((soldados1[0].alien.hp>0||soldados1[1].alien.hp>0||soldados1[2].alien.hp>0)){
	cout<<"Felicidades jugador, usted gano, la galaxia fue salvada!!!"<<endl;
	}else{
		cout<<"---------------------------------------------------------------------------------------"<<endl;
		cout<<"Malas noticias jugador, perdio la batalla, pero no la guerra!!! Mejor suerte la proxima"<<endl;
		cout<<"---------------------------------------------------------------------------------------"<<endl;
	}
}//final del combate



int main(){
    bool on1, on2, on;
    on=true;
    on1=true;
    on2=true;
    short int move, move1, move2;
	nodoalien *listaaliens=NULL;
    nodoitem *listaitems=NULL;
    nodobioma *listabiomas=NULL;
    cout<<"-----------------------------------------"<<endl;
    cout<<"La gran y expansiva galaxia, esta en peligro..."<<endl;
    cout<<"Solo los estudiantes de la academia galactica podran hacer frente ante la amenaza crecientre de la Andromeda..."<<endl;
    cout<<"Estas preparado para la lucha soldado?"<<endl;
    cout<<"-----------------------------------------"<<endl;
    while (on){
		cout<<"---------------------"<<endl;
        cout<<"Bienvenido al menu, por favor seguir las instrucciones de los enunciados para evitar errores."<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1. Modificar listas de personajes, accesorios o biomas."<<endl;
        cout<<"2. Iniciar un combate."<<endl;
        cout<<"3. Salir del juego."<<endl;
        cout<<"---------------------"<<endl;
        cout<<"Seleccione la accion a realizar: ";
		move=input_int(); cout<<endl;
		on2=true;
		switch (move)
		{
		case 1:
		while(on1){
        cout<<"---------------------"<<endl;
        cout<<"Bienvenido al menu, por favor seguir las instrucciones de los enunciados para evitar errores."<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1. Leer lista de personajes, accesorios o biomas."<<endl;
        cout<<"2. Agregar aliens, accesorios o biomas."<<endl;
        cout<<"3. Modificar aliens, accesorios o biomas de las listas."<<endl;
        cout<<"4. Eliminar aliens, accesorios o biomas de las listas."<<endl;
        cout<<"5. Cargar datos de archivos externos"<<endl;
        cout<<"6. Salir del menu."<<endl;
        cout<<"---------------------"<<endl;
        cout<<"Seleccione la accion a realizar: ";
		move1=input_int(); cout<<endl;
		on2=true;
        switch (move1)
        {
        case 1:
            while (on2){
                cout<<"---------------------"<<endl;
            	cout<<"Desea ver(Ingrese uno de los numeros mostrados):"<<endl<<"1. Lista de aliens."<<endl<<"2. Lista de accesorios."<<endl<<"3. Lista de biomas."<<endl<<"4. Retroceder."<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Seleccione la accion a realizar: ";
                move2=input_int();
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
                    cout<<"---------------------"<<endl;
                    cout<<"Ingrese una opcion valida."<<endl;
                    cout<<"---------------------"<<endl;
                    break;
                }
			}
        
        case 2:
            while (on2){
                cout<<"---------------------"<<endl;
            	cout<<"Desea agregar(Ingrese uno de los numeros mostrados):"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma"<<endl<<"4. Retroceder"<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Seleccione la accion a realizar: ";
                move2=input_int();
            	switch (move2)
                {
                case 1:
                	if(listabiomas==NULL){
                		cout<<"Perfecto, pero como no hay ambientes en el archivo para que viva la especie empecemos creando uno"<<endl;
                		agregarbioma(listabiomas);
                	}
					agregaralien(listaaliens,listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    if(listabiomas==NULL){
                		cout<<"Perfecto, pero como no hay ambientes en el archivo en caso de crear un accesorio de aconicionamieno empecemos creando uno"<<endl;
                		agregarbioma(listabiomas);
                	}
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
                    cout<<"---------------------"<<endl;
                    cout<<"Ingrese una opcion valida."<<endl;
                    cout<<"---------------------"<<endl;
                    break;
                }
			}
            break;

        case 3:
            while (on2){
                cout<<"---------------------"<<endl;
            	cout<<"Desea modificar(Ingrese uno de los numeros mostrados):"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma"<<endl<<"4. Retroceder"<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Seleccione la accion a realizar: ";
                move2=input_int();
            	switch (move2)
                {
                case 1:
                    if(listabiomas==NULL){
                		cout<<"Perfecto, pero como no hay ambientes en el archivo para que viva la especie empecemos creando uno"<<endl;
                		agregarbioma(listabiomas);
                	}
					modificarraza(listaaliens,listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    if(listabiomas==NULL){
                		cout<<"Perfecto, pero como no hay ambientes en el archivo en caso de crear un accesorio de aconicionamieno empecemos creando uno"<<endl;
                		agregarbioma(listabiomas);
                	}
					modificaritem(listaitems, listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 3:
                    modificarbioma(listaaliens, listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"---------------------"<<endl;
                    cout<<"Ingrese una opcion valida."<<endl;
                    cout<<"---------------------"<<endl;
                    break;
                }
			}
            break;

        case 4:
            while (on2){
                cout<<"---------------------"<<endl;
            	cout<<"Desea eliminar(Ingrese uno de los numeros mostrados):"<<endl<<"1. Un alien."<<endl<<"2. Un accesorio."<<endl<<"3. Un bioma."<<endl<<"4. Retroceder"<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Seleccione la accion a realizar: ";
                move2=input_int();;
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
                    cout<<"---------------------"<<endl;
                    cout<<"Ingrese una opcion valida."<<endl;
                    cout<<"---------------------"<<endl;
                    break;
                }
			}
            break;
		
		case 5:
			while (on2){
                cout<<"---------------------"<<endl;
            	cout<<"Desea cargar(Ingrese uno de los numeros mostrados):"<<endl<<"1. Aliens."<<endl<<"2. Accesorios."<<endl<<"3. Biomas."<<endl<<"4. Retroceder"<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Seleccione la accion a realizar: ";
                move2=input_int();;
            	switch (move2)
                {
                case 1:
                    cargaraliens(listaaliens, listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 2:
                    cargaritems(listaitems);
                    cout<<"hecho"<<endl;
                    break;
                case 3:
                    cargarbiomas(listabiomas);
                    cout<<"hecho"<<endl;
                    break;
                case 4:
                    on2=false;
                    cout<<"hecho"<<endl;
                    break;
                default:
                    cout<<"---------------------"<<endl;
                    cout<<"Ingrese una opcion valida."<<endl;
                    cout<<"---------------------"<<endl;
                    break;
                }}
			break;
		
        case 6:
            cout<<"---------------------"<<endl;
        	cout<<"Saliendo del menu..."<<endl;
            cout<<"---------------------"<<endl;
            cout<<"La galaxia de Andromeda te esperara, soldado. !Vuelve pronto�"<<endl;
        	on1=false;
        	break;
        default:
        	cout<<"---------------------"<<endl;
            cout<<"Error, seleccione una de las opciones propuestas"<<endl;
            cout<<"---------------------"<<endl;
            break;
        }
		break;
        case 2:
        	if(listaaliens!=NULL&&listaitems!=NULL&&listabiomas!=NULL){
			on2=true;
			while(on2==true){
				cout<<"---------------------"<<endl;
    	    	cout<<"Bienvenido al combate guerrero, por favor seguir las instrucciones de los enunciados para evitar errores."<<endl;
        		cout<<"---------------------"<<endl;
    	    	cout<<"1. Iniciar un combate contra la maquina."<<endl;
        		cout<<"2. Iniciar un combate contra otro jugador."<<endl;
    	    	cout<<"3. Salir del menu."<<endl;
        		cout<<"---------------------"<<endl;
        		cout<<"Seleccione la accion a realizar: ";
				move1=input_int(); cout<<endl;
				switch (move1)
				{
					case 1:
						combate_maquina(listaaliens, listaitems, listabiomas);
						break;
					case 2:
						cout<<"---------------------"<<endl;
						cout<<"Proximamente por un contenido extra de 39.99$"<<endl;
						cout<<"---------------------"<<endl;
						break;
					case 3:
						cout<<"---------------------"<<endl;
						cout<<"Entendido"<<endl;
						cout<<"---------------------"<<endl;
						on2=false;
						break;
					default:
						cout<<"---------------------"<<endl;
            			cout<<"Error, seleccione una de las opciones propuestas"<<endl;
            			cout<<"---------------------"<<endl;
						break;
				}
				}}else{
					cout<<endl<<"Para jugar un combate las 3 listas tienen que tener al menos un elemento, haga que esto e cumpla en las 3 para jugar :)"<<endl;
				}
		break;
		case 3:
			cout<<"Adios, gracias por jugar :)";
			on=0;
		break;
		default:
			cout<<"---------------------"<<endl;
            cout<<"Error, seleccione una de las opciones propuestas"<<endl;
            cout<<"---------------------"<<endl;
            break;
			break;
    }	
	on2=true;//poner el condicional de los switch de vuelta a true
	}}
    eliminaraliens(listaaliens);
    eliminaritems(listaitems);
	eliminarbiomas(listabiomas);
    return 0;}
