/*
                      __
                     .'  '.
    		 _.-'/  |  \
    ,        _.-"  ,|  /  0 `-.
   |\    .-"       `--""-.__.'=====================-,
   \ '-'`        .___.--._)=========================|
    \            .'      |                          |
     |     /,_.-'        |  CODIFICADO POR:         |
   _/   _.'(             |                          |
   /  ,-'\  \            |          Jairo Medrano   |
   \  \   `-'            |                          |
    `-'                  '--------------------------'
*/


#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;


struct elemento{
	int dato;
	elemento(){ //constructor vacio
		dato = 0;
	};

	elemento( int numero ){ //constructor full
		dato = numero; 
	};
};


class Nodo{
	elemento clave;
	Nodo* izq;
	Nodo* der;
public:
	Nodo() { izq=NULL; der=NULL; };
	void setClave(elemento iClave) { clave = iClave; };
	void setIzq(Nodo* iIzq) { izq = iIzq; };
	void setDer(Nodo* iDer) { der = iDer; };
	elemento Clave() { return clave; };
	int claveDato() { return clave.dato; };
	Nodo* Izq() { return izq; };
	Nodo* Der() { return der; };
};

// Clase Arbol
class Arbol{
	Nodo* raiz;
public:
	Arbol();
	~Arbol();
	Nodo* Raiz() { return raiz; };
	void agregarNodo(elemento clave);
	void inOrden(Nodo* n);
	void preOrden(Nodo* n);
	void preOrdenGrafico(Nodo* n, string espacio);
	Nodo* eliminarNodo(Nodo* n, int hoja);
	void buscarNodo(Nodo* n, int hoja);
	Nodo* pequeno(Nodo* n);
private:
	void agregarNodo(elemento clave, Nodo* hoja);
	void nodoLibre(Nodo* hoja);
};

// Constructor
Arbol::Arbol(){
	raiz = NULL;
}

// Destructor
Arbol::~Arbol(){
	nodoLibre(raiz);
}

//Usando recursion para liberar el nodo y todos sus hijos 
void Arbol::nodoLibre(Nodo* hoja){
	if ( hoja != NULL ){
		nodoLibre(hoja->Izq());
		nodoLibre(hoja->Der());
		delete hoja;
	}
}

// Añadiendo un nodo nuevo, crear la raiz si no existe, si existe raíz reenviar la clave 
// a la funcion agregarNodo para crear el nodo como hijo
void Arbol::agregarNodo(elemento clave) {
	if ( raiz == NULL ){ //Si no existe elementos, se crea la raiz
		cout<<"Nuevo nodo creado: "<<clave.dato<<endl;
		Nodo* n = new Nodo();
		n->setClave(clave);
		raiz = n;
	}else{
		cout<<"Nuevo nodo creado: "<<clave.dato<<endl;
		agregarNodo(clave, raiz);
	}
}

// Agregaegando un nodo, se respeta el orden del arbol enviando los menores a la izquierda y mayores a la derecha.
void Arbol::agregarNodo( elemento clave, Nodo* hoja){
	if ( clave.dato <= hoja->claveDato() ){
		if ( hoja->Izq() != NULL ){
			agregarNodo(clave, hoja->Izq());
		}else{
			Nodo* n = new Nodo();
			n->setClave(clave);
			hoja->setIzq(n);
		}
	}else{
		if ( hoja->Der() != NULL )
			agregarNodo(clave, hoja->Der());
		else 
		{
			Nodo* n = new Nodo();
			n->setClave(clave);
			hoja->setDer(n);
		}
	}
}
void mostrarDatoHijo(Nodo* n, string texto){
	cout<<texto<<" "<<n->claveDato()<<".\n";
}

// Buscar un nodo
void Arbol::buscarNodo(Nodo* n, int hoja){
	if ( n != NULL ){      
		if ( hoja < n->claveDato() ){
			buscarNodo( n->Izq(), hoja);
		}else if ( hoja > n->claveDato() ){
			buscarNodo( n->Der(), hoja);
		}else{
			elemento clave = n->Clave();
			cout<<"\n Nodo encontrado: "<<clave.dato<<".\n";
			if(n->Izq() != NULL){
				mostrarDatoHijo(n->Izq(), " Hijo izquierdo: ");
			}
			if(n->Der() != NULL){
				mostrarDatoHijo(n->Der(), " Hijo derecho: ");
			}
		}  
	}
}

// Eliminar un nodo y redireccionar apuntadores del arbol
Nodo* Arbol::eliminarNodo(Nodo* n, int hoja){
	if ( n == NULL ){ 
		return NULL;
	}
	if ( hoja == n->claveDato() ){
		if ( n->Izq() == NULL && n->Der() == NULL ){
			cout<<"\n nodo "<<n->claveDato()<<" eliminado.\n";
			delete n;
			return NULL;
		}else if ( n->Izq() != NULL && n->Izq() == NULL ){
			Nodo* temp = n->Izq();
			cout<<"\n nodo "<<n->claveDato()<<" eliminado.\n";
			delete n;
			return temp;
		}else if ( n->Izq() == NULL && n->Der() != NULL ){
			Nodo* temp = n->Der();
			cout<<"\n nodo "<<n->claveDato()<<" eliminado.\n";
			delete n;
			return temp;
		}else{
			Nodo* temp = pequeno(n->Der());
			n->Clave() = temp->Clave();
			n->setDer( eliminarNodo( n->Der(), temp->claveDato() ) );
			return n;
		}
	}else if ( hoja < n->claveDato() ){
		n->setIzq( eliminarNodo( n->Izq(), hoja) );
		return n;
	}else if ( hoja > n->claveDato() ){
		n->setDer( eliminarNodo( n->Der(), hoja) );
		return n;
	}
	
	return n;
}

//busca el nodo más pequeño del subarbol enviado
Nodo* Arbol::pequeno(Nodo* n){
	if ( n->Izq() != NULL ){
		pequeno( n->Izq() );
	}else{
		return n;
	}
	return n;
}

//Recorre el arbol en Inorden (subarbol izquierdo, raiz, subarbol derecho) y lo muestra en pantalla.
void Arbol::inOrden(Nodo* n){
	if ( n ) {
		inOrden(n->Izq());
		cout<<"Valor del elemento: "<<n->claveDato()<<" \n";
		inOrden(n->Der());
	}
}

//Recorre el arbol en Preorden (la raíz, subarbol izquierdo, subarbol derecho) y lo muestra en pantalla.
void Arbol::preOrden(Nodo* n){
	if ( n ){
		//Guardando datos en un archivo
		ofstream fichero;
		fichero.open("arbol.txt", ios_base::app);
		if(fichero.fail()){
			cout<<"No se pudo guardar en el fichero\n"; 
		}else{
			fichero<<"clave en nodo: "<<n->claveDato()<<" \r\n";
		}
		fichero.close();
		preOrden(n->Izq());
		preOrden(n->Der());
	}
}

//Recorre el arbol en Preorden (la raíz, subarbol izquierdo, subarbol derecho) y lo muestra en pantalla.
void Arbol::preOrdenGrafico(Nodo* n, string espacio){
	if ( n ){
		cout<<espacio<<n->claveDato()<<endl;
		espacio+="     ";
		preOrdenGrafico(n->Izq(), espacio);
		preOrdenGrafico(n->Der(), espacio);
	}
}

void limpiarTerminal(){
	if (system("cls")){
		system("clear");
	}
}

void pausarPograma(){
	getchar();
	cout<<"\n\n         Presione < ENTER > para continuar... ";
	getchar();
}

int rec[1000006];// representacion de grid de profundidad
void imprimirArbol(Nodo* n, int profundidad){
	int i;
	if(n==NULL)return;
	printf("\t");
	for(int i=0; i<profundidad; i++)
		if(i==profundidad-1)
			printf("%s\u2014\u2014\u2014",rec[profundidad-1]?"\u0371":"\u221F");
		else
			printf("%s   ",rec[i]?"\u23B8":"  ");
		printf("%d\n",n->claveDato());
		rec[profundidad]=1;
		imprimirArbol(n->Izq(),profundidad+1);
		rec[profundidad]=0;
		imprimirArbol(n->Der(),profundidad+1);
}

int main(){
	int opcion = 0;
	int clave = 0;
	elemento nuevoElemento;
	
	Arbol* arbol = new Arbol();
	
	//creando fichero y comenzando programa
	ofstream fichero;
	fichero.open( "arbol.txt" );
	if ( fichero.fail() ){
		cout<<"No se pudo crear el fichero.\n"; 
	}else {
		fichero<<""; 
	}
	fichero.close();
	
	while(opcion != 5){		
		while(opcion < 1 || opcion > 5) { 
			limpiarTerminal();
			cout<<"########################################################\n";
			cout<<"#                 ARBOL BINARIO DE BUSQUEDA            #\n";
			cout<<"########################################################\n";
			cout<<"\n                        BIENVENIDO:                   \n";
			cout<<"          1. Agregar un nuevo nodo\n";
			cout<<"          2. Eliminar un nodo\n";
			cout<<"          3. Buscar un nodo\n";
			cout<<"          4. Imprimir el arbol\n";
			cout<<"          5. Salir\n";
			cout<<"\n\n       Elija una opcion: ";
			cin>>opcion; 
		}
		if(opcion == 1){
			limpiarTerminal();
			cout<<"########################################################\n";
			cout<<"#               INGRESO DE UN NUEVO NODO               #\n";
			cout<<"########################################################\n";
			cout<<"\n\n      Ingrese el valor del nuevo nodo: ";
				
			while( nuevoElemento.dato == 0 ) { cin>>nuevoElemento.dato; }
			cout<<endl;
			arbol->agregarNodo( nuevoElemento );
			pausarPograma();
		}
		
		if(opcion == 2){
			limpiarTerminal();
			cout<<"########################################################\n";
			cout<<"#                ELIMINACION DE UN NODO                #\n";
			cout<<"########################################################\n";
			cout<<"\n\n      Ingrese el valor del nodo a eliminar: ";
			while( clave == 0 ) { cin>>clave; }
			arbol->eliminarNodo( arbol->Raiz(), clave );
			pausarPograma();
		}
		
		if(opcion == 3){
			limpiarTerminal();
			cout<<"########################################################\n";
			cout<<"#                  BUSQUEDA DE UN NODO                 #\n";
			cout<<"########################################################\n";
			cout<<"\n\n      Ingrese el valor del nodo a buscar: ";
			while( clave == 0 ) { cin>>clave; }
			
			arbol->buscarNodo( arbol->Raiz(), clave );
			pausarPograma();
		}
		
		if(opcion == 4){
			limpiarTerminal();
			cout<<"########################################################\n";
			cout<<"#                  IMPRESION DEL ARBOL                 #\n";
			cout<<"########################################################\n\n\n";
			imprimirArbol( arbol->Raiz(), 0);
			//arbol->preOrdenGrafico( arbol->Raiz(), " " );
			cout<<endl;
			pausarPograma();
		}
		
		if(opcion == 5){
			limpiarTerminal();
			cout<<"\n\n\nCerrando el programa y guardando el arbol en arbol.txt......";
			arbol->preOrden( arbol->Raiz() );
			cout<<endl;
			pausarPograma();
		}
		
		if( opcion != 5 ){
			limpiarTerminal();
			opcion = 0; 
		}
		nuevoElemento.dato = 0;
		clave = 0;
	}
	
	delete arbol;
	return 0;
}
