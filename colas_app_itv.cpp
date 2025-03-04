/*

OMAR RODRIGUEZ ALVAREZ
48679912-K
Estructura de datos UMH

*/
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>

using namespace std;

typedef struct vehiculo{
  string matricula; // forma LLDDDDLL
  string marca;
  string modelo;
  int potencia; // [1 a 1000]
  char fecha[15]; // fecha del sistema
  char hora_llegada[15]; // hora del sistema de llegada del vehiculo
  char hora_salida[15]; // hora del sistema de salida del vehiculo
  //bool estado_ITV; //false en manipulacion a mano, aleatorio en simulacion
  struct vehiculo *siguiente;
} *nodovehiculo;

typedef struct cola{
  vehiculo *primero, *ultimo;
} *TipoCola;

TipoCola gasolina, diesel, motos, industrial;

bool inicializarCola();
void muestraCola(TipoCola);
void encolar (struct cola *tipoCola, int valor, string marcacoche, string modelocoche, int potenciacoche, char fechaitv[15], char llegada[15] , char salida[15] );
int menu();
void encolarPorTipo(int tipo, string marca, string modelo, int potencia, char fecha[15], char hora_llegada[15], char hora_salida[15]);
void eliminarPorTipo(int tipo);
void eliminarprimero(struct cola *tipoCola);
bool inicializarCola();
int infocola(struct cola *tipoCola);
void MostrarPorTipo(int tipo);
void infoPorTipo(int tipo);
void formulario(vehiculo nodovehiculo);
bool validamatriculas(string matricula);
char date();
string random();
void encolarsimulacion (struct cola *tipoCola, string matricula);
void simulation(TipoCola control[]);
void muestraColasimulacion(TipoCola cualquiera);
//void datosmanual(vehiculo nodovehiculo);


/*                        Funcion Principal
------------------------------------------------------------------------*/
int main(){
	int tipo;
	int dato;  // numero a encolar
	int op;
    vehiculo nodovehiculo;
      TipoCola control[4];

    if(inicializarCola()){ //INICIALIZAMOS
		Sleep(500);
        do{
	    op = menu();
	    switch(op){
                case 1:
           	       formulario(nodovehiculo);
                   /* cout<<"TIPO DE VEHICULO: [1:GASOLINA 2:DIESEL 3:MOTOS 4:INDUSTRIAL]"<<endl;
           	        cin>>tipo;
                    encolarPorTipo(tipo);*/
                   // datosmanual(nodovehiculo);
                break;

                case 2:
                    cout<<"ELIMINAR VEHICULO TIPO: [1:GASOLINA 2:DIESEL 3:MOTOS 4:INDUSTRIAL]"<<endl;
                    cin>>tipo;
                    eliminarPorTipo(tipo);
                menu();

                // entra en menu->2 eliminar-> eliminarPorTipo->eliminarprimero->****menu****
        		case 3:
                    cout<<"MOSTRAR COLA TIPO: [1:GASOLINA 2:DIESEL 3:MOTOS 4:INDUSTRIAL]"<<endl;
                    cin>>tipo;
                    MostrarPorTipo(tipo);
        		break;

                case 4:
                    cout<<"ELIJA COLA [1:GASOLINA 2:DIESEL 3:MOTOS 4:INDUSTRIAL]"<<endl;
                    cin>>tipo;
                    infoPorTipo(tipo);
        		break;
                
                case 5:
                    simulation(control); //SIMULACION DEL PROGRAMA SOLO CON ENTRADAS
                break;
                
                case 6:
                    cout <<"SALIENDO DEL PROGRAMA..."<<endl;
                    Sleep(1000); //INCORPORAR UN DELETE ALL
                    exit (0);
                break;

                default:
                    cout <<"OPCION NO VALIDA"<<endl;
                break;
                system("pause");
        	     }
                cout<<endl<<endl;
	    }
    while(op!=6);
	} else{
		cout<<"NO INICIALIZADO"<<endl;
	}
    return 0;
}


//_________________________________FUNCIONES__________________________________//


void muestraCola(TipoCola cualquiera){
    /*
    Muestra la cola por pantalla mediante el recorrido de un puntero
    dependiendo de la cola que le pasemos por parametro
    */
	nodovehiculo aux = NULL;
    if(cualquiera->primero != NULL){
		 aux = cualquiera->primero;
		 cout<<"VEHICULOS: "<<endl;
		 while(aux != NULL){
			 cout<< aux->matricula;
			 cout<<", ";
             cout<< aux->marca;
			 if(aux->siguiente != NULL){
                   cout<<", "<<endl;
                    }else {cout<<"."<<endl;}
			 aux = aux->siguiente;
	 } }else{
            cout<<"-- LA COLA ESTA VACIA --"<<endl;
                }
}

void encolar (struct cola *tipoCola, string valor, string marcacoche, string modelocoche, int potenciacoche, char fechaitv[15], char llegada[15] , char salida[15] ){
  nodovehiculo aux = new vehiculo();
  /*
  Funcion para encolar cada dato mediante 
  el puntero en la estructura vehiculo
  */
	if(aux != NULL){
		// crear uno objeto vehiculo con los datos que t eentran
		aux->matricula = valor;
		aux->marca = marcacoche;
		aux->modelo = modelocoche;
		aux->potencia = potenciacoche;
		aux->fecha[15] = fechaitv[15];
		aux->hora_llegada[15] = llegada[15] ;
		aux->hora_salida[15]  = salida[15] ;
        aux->siguiente = NULL;
		// si esta vadio es decir, que el primero es nulo
		if(tipoCola->primero == NULL){
		 tipoCola->primero = aux;   // encola el primero elemento
		 tipoCola->ultimo = tipoCola->primero;// como solo hay uno, el primero es el ultimo tambien
		 cout << "----- INSERTADO COMO PRIMER Y UNICO VEHICULO -----"<<endl;
		}else{
			tipoCola->ultimo->siguiente = aux;
		 	tipoCola->ultimo = aux;
		 	tipoCola->ultimo->siguiente = NULL;
		 	cout << "----- INSERTADO COMO VEHICULO SIGUIENTE -----"<<endl;
			/*
			fila->ultimo->next = aux;
	    fila->ultimo = aux;
	    fila->ultimo->next = NULL;
			*/
		}
	}else{
		cout << "ERROR"<<endl;
	}
}

void eliminarprimero(struct cola *tipoCola){ //Funcion para eliminar el primero
    nodovehiculo aux = new vehiculo();
    if (tipoCola->primero == NULL){
        cout<<"-- LA COLA ESTA VACIA --"<<endl;
        }
    else{
        if(tipoCola->primero->siguiente != NULL){
                 aux=tipoCola->primero;
                 tipoCola->primero = aux->siguiente;
                 delete(aux);
                 cout << "----- PRIMER VEHICULO ELIMINADO -----"<<endl;
            }else{
                delete(tipoCola->primero); 
                tipoCola->primero = tipoCola->ultimo = NULL;
                cout << "----- VEHICULO ELIMINADO -----"<<endl;
                cout << "-- LA COLA ESTA VACIA --"<<endl; //Confirmar que esta vacia
                aux=tipoCola->primero;
                }
    }
}

int menu(){
	int op;
  cout<<"\n\t ITV \n\n";
  cout<<" 1. INTRODUCIR VEHICULO EN COLA                "<<endl;
  cout<<" 2. ELIMINAR VEHICULO DE COLA                  "<<endl;
  cout<<" 3. MOSTRAR COLA DESEADA                       "<<endl;
  cout<<" 4. PRIMER Y ULTIMO COCHE DE COLA              "<<endl;
  cout<<" 5. SIMULACION                                 "<<endl;
  cout<<" 6. SALIR DE ITV                               "<<endl;
  cout<<"\n INGRESE OPCION: ";
    cin>> op;
  return op;
}

void formulario(vehiculo nodovehiculo){ //INTRODUCIR EL VEHICULO
    int tipo;
    string matricula; // forma LLDDDDLL
    string marca;
    string modelo;
    int potencia; // [1 a 1000]
    char fecha [15]; // fecha del sistema
    char hora_llegada [15]; // hora del sistema de llegada del vehiculo
    char hora_salida [15]; // hora del sistema de salida del vehiculo
    bool estado_ITV;

    cout<<"Tipo de vehiculo: [1:GASOLINA 2:DIESEL 3:MOTOS 4:INDUSTRIAL]"<<endl;
    cin>>tipo;
    encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
   //cout<<"Estado de la ITV: ";
   //cin>>estado_ITV; OK ---- KO

}

void encolarPorTipo(int tipo, string marca, string modelo, int potencia, char fecha[15], char hora_llegada[15] , char hora_salida[15] ){
	/*
    Funcion con el menu y los pasos para encolar por cada tipo de vehiculo
    */
    int dato;
	string matricula;
	vehiculo *nodovehiculo;
	int estado;
	char *strFechaHora;
	nodovehiculo = new vehiculo();
    switch(tipo){
		case 1:
		cout<<"COLA GASOLINA"<<endl;
        cout<<"INGRESE MATRICULA (LLNNNNLL): ";
		cin >>matricula;
		estado=validamatriculas(matricula);
        if(estado == true){
            cout<<"La matricula introducida es valida y se ha guardado correctamente"<<endl;
            cout<<"INGRESE POTENCIA (1 a 1000): ";
            cin >> potencia;
            	if (1 < potencia && potencia < 1000){
          			cout<<"INGRESE MARCA: ";
                   	cin >> marca;
          			cout<<"INGRESE MODELO: ";
          			cin >> modelo;
                    date();
                    cout<<"INGRESE HORA SALIDA: ";
                    cin >> hora_salida;
                    encolar(gasolina, matricula, marca, modelo, potencia, fecha, hora_llegada, hora_salida);}
           		else {
                    cout<<"Ingrese una potencia correcta (1 a 1000) "<<endl;
                    encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                                }
               } else {
                cout<<"Ingrese una matricula con el formato correcto "<<endl;
                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                }
            /*cout<<"INGRESE MARCA: ";
			cin >>marca;
			encolar(gasolina, marca);
            cout<<"INGRESE MARCA: ";
			cin>>nodovehiculo->marca;
			*/
		break;
		case 2:
			cout<<"COLA DIESEL"<<endl;
                     cout<<"INGRESE MATRICULA (LLNNNNLL): ";
			cin >>matricula;
			estado=validamatriculas(matricula);
            if(estado == true){
                    cout<<"La matricula introducida es valida y se ha guardado correctamente"<<endl;
                    cout<<"INGRESE POTENCIA (1 a 1000): ";
        			cin >> potencia;
            			if (1 < potencia && potencia < 1000){
                    			cout<<"INGRESE MARCA: ";
                    			cin >> marca;
                    			cout<<"INGRESE MODELO: ";
                    			cin >> modelo;
                                date();
                    			cout<<"INGRESE HORA SALIDA: ";
                    			cin >> hora_salida;
                    			encolar(gasolina, matricula, marca, modelo, potencia, fecha, hora_llegada, hora_salida);}
                    		else {
                                cout<<"Ingrese una potencia correcta (1 a 1000) "<<endl;
                                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                                }
               } else {
                cout<<"Ingrese una matricula con el formato correcto "<<endl;
                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                }	break;
		case 3:
			cout<<"COLA MOTOS"<<endl;
            cout<<"INGRESE MATRICULA (LLNNNNLL): ";
			cin >>matricula;
			estado=validamatriculas(matricula);
            if(estado == true){
                    cout<<"La matricula introducida es valida y se ha guardado correctamente"<<endl;
                    cout<<"INGRESE POTENCIA (1 a 1000): ";
        			cin >> potencia;
            			if (1 < potencia && potencia < 1000){
                    			cout<<"INGRESE MARCA: ";
                    			cin >> marca;
                    			cout<<"INGRESE MODELO: ";
                    			cin >> modelo;
                                date();
                    			cout<<"INGRESE HORA SALIDA: ";
                    			cin >> hora_salida;
                    			encolar(motos, matricula, marca, modelo, potencia, fecha, hora_llegada, hora_salida);}
                    		else {
                                cout<<"Ingrese una potencia correcta (1 a 1000) "<<endl;
                                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                                }
               } else {
                cout<<"Ingrese una matricula con el formato correcto "<<endl;
                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                } 
                break;
		case 4:
			cout<<"COLA INDUSTRIAL"<<endl;
            cout<<"INGRESE MATRICULA (LLNNNNLL): ";
			cin >>matricula;
			estado=validamatriculas(matricula);
            if(estado == true){
                    cout<<"La matricula introducida es valida y se ha guardado correctamente"<<endl;
                    cout<<"INGRESE POTENCIA (1 a 1000): ";
        			cin >> potencia;
            			if (1 < potencia && potencia < 1000){
                    			cout<<"INGRESE MARCA: ";
                    			cin >> marca;
                    			cout<<"INGRESE MODELO: ";
                    			cin >> modelo;
                                date();
                    			cout<<"INGRESE HORA SALIDA:";
                    			cin >> hora_salida;
                    			encolar(industrial, matricula, marca, modelo, potencia, fecha, hora_llegada, hora_salida);}
                    		else {
                                cout<<"Ingrese una potencia correcta (1 a 1000) "<<endl;
                                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                                }
               } else {
                cout<<"Ingrese una matricula con el formato correcto "<<endl;
                encolarPorTipo(tipo, marca, modelo, potencia, fecha, hora_llegada, hora_salida);
                }
		default:
             cout<<"Elige una opcion valida"<<endl;
        break;
	}
}

void eliminarPorTipo(int tipo){ //MENU PARA ELIMINAR POR TIPOS DE VEHICULO
    switch(tipo){
        case 1:
            eliminarprimero(gasolina);
        break;
        case 2:
            eliminarprimero(diesel);
        break;
        case 3:
             eliminarprimero(motos);
        break;
        case 4:
             eliminarprimero(industrial);
        break;
        default:
             cout<<"Elige una opcion valida"<<endl;
        break;
        }
}


void MostrarPorTipo(int tipo) { //MOSTRAR LA COLA POR TIPOS DE VEHICULOS
  switch(tipo){
		case 1:
            cout<<"COLA GASOLINA ";
            muestraCola(gasolina);
		break;
		case 2:
            cout<<"COLA DIESEL ";
            muestraCola(diesel);
		break;
		case 3:
            cout<<"COLA MOTOS ";
            muestraCola(motos);
		break;
		case 4:
            cout<<"COLA INDUSTRIALES ";
            muestraCola(industrial);
        break;
        default:
             cout<<"Elige una opcion valida"<<endl;
        break;
	}
}

int infocola(struct cola *tipoCola){ //INFORMACION DEL PRIMER Y ULTIMO VEHICULO
    if(tipoCola->primero == NULL){
        cout<<"-- COLA VACIA --";
    }else {
        cout<<"PRIMER VEHICULO"<<endl;
        cout<<tipoCola->primero->matricula<<endl;
        cout<<"ULTIMO VEHICULO"<<endl;
        cout<<tipoCola->ultimo->matricula<<endl;
    }
}

void infoPorTipo(int tipo) { //SACAR EL MENU PARA INFORMAR POR CADA TIPO
  switch(tipo){
		case 1:
            cout<<"COLA GASOLINA: "<<endl;
    		infocola(gasolina);
		break;
		case 2:
            cout<<"COLA DIESEL: "<<endl;
            infocola(diesel);
		break;
		case 3:
            cout<<"COLA MOTOS: "<<endl;
    		infocola(motos);
		break;
		case 4:
            cout<<"COLA INDUSTRIAL: "<<endl;
            infocola(industrial);
		break;
		default:
             cout<<"Elige una opcion valida"<<endl;
        break;
	}
}

bool inicializarCola(){ //INICIALIZAMOS LAS COLAS Y ASIGNAMOS MEMORIA
	bool resultado = false;
	gasolina = new cola();// por el sizeof
	diesel = new cola();
	motos = new cola();
	industrial = new cola();

	if(gasolina != NULL && diesel != NULL && motos != NULL && industrial != NULL){
		resultado = true;
		cout << "TODAS LAS COLAS INICILIZADAS CORRECTAMENTE..."<<endl;
	   }
	return resultado;
}


bool validamatriculas(string matricula){ //Funcion que valida la matricula
	string numeros="0123456789";
	string letrasma="ABCDEFGHIJKLMNOPQRUSTVWXYZ";
    //abcdefghijklmnopqrstvwxyz LETRAS MINUSCULAS
	bool valida=true;

	if (matricula.length()==8){ //revisamos que sea si o si de 7 caracteres
		for(int i=0;i<1;i++){ //validamos los dos caracteres
			if(letrasma.find(matricula[i])>letrasma.length())
				valida=false;}
		for(int i=2;i<6;i++){ //validamos los cuatro numeros 
			if (numeros.find(matricula[i])>numeros.length())
								valida=false;}
        for(int i=6;i<7;i++){ //validamos los dos ultimos caracteres
			if (letrasma.find(matricula[i])>letrasma.length())
								valida=false;}
	}else{valida=false;}
    return valida;
}


char date(){
    char fecha;
    time_t tmFechaHora = time(NULL);

    char* strFechaHora = ctime(&tmFechaHora);
     cout << "FECHA Y HORA DE LLEGADA AUTOMATICA: " << strFechaHora;
    return *strFechaHora;
}


void simulation(TipoCola control[]){
      string matricula;
      string matriculas;
      string marca;
      int RandIndex;
      int i = 0, j;
      cout<<"\n\tBIENVENIDO A LA ITV"<<endl<<endl;
      cout<<"Iniciando simulacion..."<<endl;
      cout<<endl;
      
      do{
        cout<<"LLEGADA VEHICULO ";
        
        switch((rand()%4)+1){
          case 1:
            cout<<"GASOLINA: ";
            matricula = random();// Funcion para el numero aleatorio y asignarlo a la matricula
            cout<<matricula<<endl;
            encolarsimulacion(gasolina, matricula); // se encolan los elementos
            muestraColasimulacion(gasolina); // se muestran los elementos
            Sleep(2837);
          break;
          case 2:
            cout<<"DIESEL: ";
            matricula = random();// Funcion para el numero aleatorio
            cout<<matricula<<endl;
            encolarsimulacion(diesel, matricula);
            muestraColasimulacion(diesel);
            Sleep(2837);
          break;
          case 3:
             cout<<"MOTOS: ";
             matricula = random();// Funcion para el numero aleatorio
             cout<<matricula<<endl;
             encolarsimulacion(motos, matricula);
             muestraColasimulacion(motos);
             Sleep(2344);
          break;
          case 4:
                cout<<"INDUSTRIAL:";
                matricula = random();// Funcion para el numero aleatorio
                cout<<matricula<<endl;
                encolarsimulacion(industrial, matricula);
                muestraColasimulacion(industrial);
                Sleep(2324);
          break;
        }
        i++;
      }while(i<10);
}

string random(){ //Funcion para sacar las matriculas de forma aleatoria y sacarlas fuera
    srand (time(NULL)); //initialize the random seed
    string matricula;
    string marca;
    string matriculas[12] = {"EY1234DF", "LP8975HJ", "DW1452NB", "TS6546SD", "PR8934DW", "MD8778HJ", "ZX1485NB", "CV6156XO", "IO1734AA", "VW8975AJ", "RW1982AB", "BV7856SD"};
    //string marcas[16] = {"Renault", "BMW", "Mercedes", "Fiat", "peugeot", "Skoda", "Abarth", "Lexus", "Jaguar", "Seat", "Citroen", "Land Rover"};
    int RandIndex = rand() % 12; //se genera un numero aleatorio para recorrer el vector hasta 16 veces.
    //cout<<matriculas[RandIndex];
    matricula = matriculas[RandIndex];
    //marca = marcas[RandIndex];
    return matricula;
    }

void encolarsimulacion (struct cola *tipoCola, string matricula) {  //Misma funcion encolar pero para la simulacion, sin encolar otros elementos
    nodovehiculo aux = new vehiculo();
	if(aux != NULL){
		// crear uno objeto vehiculo con los datos que t eentran
		aux->matricula = matricula;
        aux->siguiente = NULL;
		// si esta vadio es decir, que el primero es nulo
		if(tipoCola->primero == NULL){
		 tipoCola->primero = aux;   // encola el primero elemento
		 tipoCola->ultimo = tipoCola->primero;// como solo hay uno, el primero es el ultimo tambien
		 cout << "----- INSERTADO COMO PRIMER Y UNICO VEHICULO -----"<<endl;
		}else{
			tipoCola->ultimo->siguiente = aux;
		 	tipoCola->ultimo = aux;
		 	tipoCola->ultimo->siguiente = NULL;
		 	cout << "----- INSERTADO COMO SIGUIENTE -----"<<endl;
			/*
			fila->ultimo->next = aux;
	    fila->ultimo = aux;
	    fila->ultimo->next = NULL;
			*/
		}
	}else{
		cout << "ERROR"<<endl;
	}
}

void muestraColasimulacion(TipoCola cualquiera){ //Funcion que muestra la cola en la simulacion
	nodovehiculo aux = NULL;
    if(cualquiera->primero != NULL){
		 aux = cualquiera->primero;
		 cout<<"VEHICULOS: ";
		 while(aux != NULL){
			 cout<< aux->matricula;
			 if(aux->siguiente != NULL){
                   cout<<", ";
                    }else {cout<<"."<<endl<<endl;}
        aux = aux->siguiente;
	 } }else{cout<<"COLA VACIA"<<endl;}
}

