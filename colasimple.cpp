#include <stdio.h>

typedef struct TNodoCola {  //Creacion del nodo
  TipoC info;
  struct TNodoCola *sig;
} *pNodoCola;

typedef struct{ // Creación de la estructura Cola pNodoCola primero, ultimo;
  pNodoCola primero, ultimo;
} TCola, *Cola;

void adicCola (Cola col, TipoC elem);
Cola inicCola(void);

Cola inicCola(void) { // Retorna una cola vacía
  Cola col = (Cola) malloc(sizeof(TCola)); //Reserva memoria
  col->primero = col->ultimo = NULL;
  return col;
}

void adicCola(Cola col, TipoC elem) { //Insertar elemento al final
    pNodoCola p = (pNodoCola) malloc(sizeof(TNodoCola));
    p->info = elem;
    p->sig = NULL;
    if (col->primero == NULL)
      col-> primero = col -> ultimo = p;
    else {
      col -> ultimo->sig= p;
      col -> ultimo = p;
    }
}

int main(){

  cout<<"Inserte un valor en la cola";
  cin<<elem;
  (adicCola)
}
