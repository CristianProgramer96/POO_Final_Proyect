#include <allegro.h>
#include <iostream>
#include <stdio.h>

using namespace std;


volatile int contador = 0;//Esta variable tiene el objetivo de controlar los fps del juego.

void mi_temporizador()/*Esta funcion cumple con aumentar en una unidad la variable speed_counter cada vez que se llame.
                          Cumple la funcion de un temporizador*/
{
    contador++;
}END_OF_FUNCTION(inc_speed_counter);

struct Stablero{
    int Tablero;
    char cad[2];
    Stablero *anterior;
    Stablero *siguiente;
   };


class CTablero{
/* Variables correpsondientes al tablero de ajedrez.*/
private:
   struct Stablero *cab, *col;
   int LadoRecuadro;//Variable que contiene la longitud de uno de los lados de los recuadros de ajedrez
   int SaltoLinea;//Esta variable indica el numero de recuadros que deben haber en cada fila del tablero de ajedrez
   int Yinicial;// Expresa la distancia que existe entre la parte superior de la pantalla y la parte superior del tablero de ajedrez
   int Xinicial;//Expresa la distancia que existen entre la parte izquierda de la pantalla y la parte izquierda del tablero de ajedrez.
   int Distanica_Tablas;// Distancia en pixeles entre el tablero de ajedrez y el de jugadas
   int NumeroCasilla;//indica el numero de la casilla en la que se encuentra el caballo

   //Funcion para insertar nodos
   void insertar(Stablero *p, Stablero *q, int n);

public:
   //Constructor
   CTablero(){
   cab=NULL;
   col=NULL;
   LadoRecuadro=100;
   SaltoLinea=8;
   Yinicial=0;
   Xinicial=0;
   Distanica_Tablas=200;
   NumeroCasilla=4;}
    //Funcion para determianr informacion que debe ir dentro de los apuntadores de los nodos
    void posicion_lista(int n);
    //Esta funcion reccorre los nodos para seleccionar aquel que corresponda a la casilla del tablero de ajedrez deseada
    Stablero* Recorrer_Lista(int NumeroCasilla);
    //Retorna el valor del apuntador cab.
    Stablero *getcab();
    //Retorna el valor de la variable "LadoRecuadro".
    int getLadoRecuadro();
    //Retorna el valor de la variable "SaltoLinea".
    int getSaltoLinea();
    //Retorna el valor de la variable "Xinicial".
    int getXinicial();
    //Retorna el valor de la variable "Yinicial".
    int getYinicial();
    // Retorna el valor de la variable "NumeroCasilla".
    int getNumeroCasilla();
    //Retorna el valor de la variable "Distancia_Tablas".
    int getDistancia_Tablas();
    //Modifica el valor de la variable "NumeroCasilla".
    void setNumeroCasilla(int CasillaActual);

//Sirve para eliminar los nodos de la memoria dinamica una vez ejecutado el programa
~CTablero();


} ;

// La siguiente funcion grafica un conjunto de recuadros de acuerdo a la informacion contenida en un arreglo
void GraficadorCoordenadasPorValor(int CoordenadaX,int LadoRecuadro, int SaltoLinea,int NumeroRecuadro, int Yinicial,int Color);
//Esta funcion grafica un recuadro bordeado de acuerdo a unas coordenadas
void GraficarRecuadro(int CoordenadaX,int CoordenadaY, int LadoRecuadro,int Color);
//La siguiente funcion grafica un conjunto de recuadros de acuerdo a especificaciones del usuario
void GraficarMuchosRecuadros(int CantidadRecuadros,int Xinicial,int LadoRecuadro, int SaltoLinea, int Yinicial,int Color);
//Esta funcion muestra un caracter en una posicion determinada de la pantalla
void SecuenciaCaracteres(int ValorCaracter,int PosicionCaracter,int Xinicial,int DistanciaCaracteres, int SaltoLinea,int Yinicial,int Color);


int main()
{
    CTablero Tablero1;//Instancia de la clase CTablero

/* Variables correspondientes al tablero de jugadas.*/

   int Vector_Movimiento [63]={3,4,7,5,3,4,7,6,7,8,3,1,7,8,3,5,8,2,4,5,6,
                               4,2,3,2,8,6,1,2,8,6,6,1,6,5,4,5,2,1,3,5,2,
                               1,8,1,6,4,1,7,5,4,3,5,7,6,7,1,3,8,7,1,3,4};//En este vector se almacena secuencialmente los movimientos que el caballo debe hacer.

   int LadoRecuadroJugadas=50;// Variable que contiene la longitud de uno de los lados de los recuadros del tablero de jugadas
   int x=Tablero1.getLadoRecuadro()*Tablero1.getSaltoLinea()+Tablero1.getDistancia_Tablas()+Tablero1.getXinicial();//Coordenadas con respecto al eje X para graficar la tabla de jugadas (de color rojo)
   int y=200; //Coordenadas con respecto al eje Y para graficar la tabla de jugadas (de color rojo)
   int SaltoRecuadroJugadas=16;//Controla el numero de columnas que tiene el recuadro de jugadas
   int Xcirculo=x+LadoRecuadroJugadas/2,Ycirculo=y+LadoRecuadroJugadas/2;  /*Estas variables contienen coordenadas en pixeles, las cuales ayudan a
                                                                          generar circulos pequeños de color azul dentro de los recuadros rojos que
                                                                          contienen los movimientos que debe hacer el caballo. Estos circulos azules iran apareciendo en los
                                                                          recuadros rojos conforme se haga un movimiento en el tablero de ajedrez (sirven para
                                                                          resaltar la jugada en tiempo real)  */
   int RadioCirculo=LadoRecuadroJugadas/3;//Controla el radio del circulo que va apareciendo en el recuadro de jugadas.

/*Otras variables*/
   int a;// Esta variable se utiliza para recorrer ciclos for y while.
   int b;// En el proximo ciclo for, esta variable sirve para asignar un valor respectivo al arreglo "Tablero"

//___________________________________________________________________________________________________________________________________


   for(a=0; a<=63; a++){
       if(a%Tablero1.getSaltoLinea()==0){
            b=0;
       }
    Tablero1.posicion_lista(b*(Tablero1.getLadoRecuadro())+Tablero1.getXinicial());
     b++;
   }//Asigna valores a  "Tablero_Movimientos[a].Tablero"

   struct Stablero *p=NULL;

    allegro_init();// Esta funcion instala los componentes fundamentales de la biblioteca Allegro.
    install_keyboard();// Con esta función podremos checar qué teclas están siendo presionadas.

    set_color_depth(32);//
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1900, 940, 0, 0);//Esta funcion sirve para mostrar la interfaz de usuario y asignarle un tamaño.


    for(a=0;a<=63;a++){

      p=Tablero1.Recorrer_Lista(a);


    if((a/8)%2==0){

    if (a%2==0){
    GraficadorCoordenadasPorValor(p->Tablero,Tablero1.getLadoRecuadro(),Tablero1.getSaltoLinea(),a,Tablero1.getYinicial(),15);
     }
     else{
    GraficadorCoordenadasPorValor(p->Tablero,Tablero1.getLadoRecuadro(),Tablero1.getSaltoLinea(),a,Tablero1.getYinicial(),6);
     }
        }

        else{

            if (a%2==0){

    GraficadorCoordenadasPorValor(p->Tablero,Tablero1.getLadoRecuadro(),Tablero1.getSaltoLinea(),a,Tablero1.getYinicial(),6);
      }
     else{
     GraficadorCoordenadasPorValor(p->Tablero,Tablero1.getLadoRecuadro(),Tablero1.getSaltoLinea(),a,Tablero1.getYinicial(),15);
      }

        }
    }//Grafica el tablero de ajedrez de acuerdo a la informacion contenida en los nodos de la lista encadenada


   GraficarMuchosRecuadros(63,x,LadoRecuadroJugadas,SaltoRecuadroJugadas,y,12);//Grafica la tabla de jugadas (de color rojo)

   for(a=0; a<=62; a++){
   SecuenciaCaracteres(*(Vector_Movimiento+a),a,x,LadoRecuadroJugadas,SaltoRecuadroJugadas,y,10);
   }//Coloca valores numericos dentro de cada recuadro de la tabla de jugadas (de color rojo)

    float x_inicial=Tablero1.getLadoRecuadro()*4.5,y_inicial=Tablero1.getYinicial()+Tablero1.getLadoRecuadro()/2;/* Aqui se declaran las variables que corresponden a las coordenadas iniciales
                                                                                                    de la pieza de ajedrez en terminos de pixeles*/

    /*El siguiente ciclo while sirve como una restriccion (no deja avanzar al usuario al siguiente codigo hasta
    que presione la tecla "flecha abajo")*/
    while (!*(key+KEY_DOWN))
    {
        rest(1);
    }

    LOCK_VARIABLE(contador);//Evita que la variable speed_counter sera modificada por otros hilos ajenos a este
    LOCK_FUNCTION(mi_temporizador);//Evita que la funcion inc_speed_counter sea utilizada por otros hilos diferentes de este
    install_int_ex(mi_temporizador, BPS_TO_TIMER(2));/*Esta funcion llama a la funcion inc_speed_counter(), haciendo que se ejecute 2 veces
                                                         por segundo*/

  a=0; //Aqui se procede a dejar la variable "a" en 0 porque se va a utilizar como un contador en el siguiente ciclo.


  rectfill(screen,x_inicial-Tablero1.getLadoRecuadro()/2,y_inicial-Tablero1.getLadoRecuadro()/2,x_inicial+Tablero1.getLadoRecuadro()/2,y_inicial+Tablero1.getLadoRecuadro()/2,*(pallete_color+7)); /*Esta funcion se encarga
                                                                                                                                             de sombrear la posicion inicial
                                                                                                                                             del caballo (indicando su posicion inicial)*/



  b=1;/* Esta variable en el proximo ciclo ira aumentando una unidad por cada iteracion. Cuando llegue a un
         multiplo de 16 causara que se ejecute un condicional*/





    while (a!=63)
    {
        /*La siguiente condicion sirve para que el codigo dentro se ejecute cada 0,5 segundos*/


      if(contador > 0){

        contador =0; //Devuelve la variable speed_counter al valor 0 para que el condicional se vuelva a ejecutar.
//______________________________________________________________________________________________________________________
       /*Los siguientes condicionales identifican la jugada que se desprende de una casilla cualquiera del tablero de
       ajedrez y relaciona la casilla con el tipo de movimiento (si es par o impar)*/

      p=Tablero1.Recorrer_Lista(Tablero1.getNumeroCasilla());

        if(*(Vector_Movimiento+a)%2==0){
          strcpy(p->cad,"P");
         }

        else{
         strcpy(p->cad,"I");
         }

//_____________________________________________________________________________________________________________
         drawing_mode(DRAW_MODE_XOR, NULL, 0, 0);//indica que si se dibuja dos veces la misma figura en el mismo lugar esta desaparecera.
         circlefill(screen, x_inicial, y_inicial, 15, *(pallete_color+7));/*Dibuja un circulo negro en la casilla donde recien
                                                                            el caballo realizo un movimiento (el cual despues sera borrado)*/

         drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);//Indica que toda figura que se realice a partir de ahora sera no transparente

         circlefill(screen, Xcirculo, Ycirculo, RadioCirculo,*(pallete_color+1));/*Coloca un circulo relleno dentro de los recuadros rojos
                                                                                  en sincronia con el movimiento del caballo. Sirve para indicar
                                                                                  el movimiento que acaba de realizar la pieza de ajedrez*/


//_____________________________________________________________________________________________________________________________________________________                                                                                                              movimieno es par o impar respectivamente.*/

        /*Los siguientes condicionales se relacionan con una de las 8 posibles posiciones del caballo
         con el "Vector_Movimiento" para mover el vector del caballo a la posicion correcta*/

         if(*(Vector_Movimiento+a)==1){

            line(screen,x_inicial,y_inicial,x_inicial+Tablero1.getLadoRecuadro(),y_inicial-2*Tablero1.getLadoRecuadro(),*(pallete_color+0));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 1 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
             despues del movimiento  1 como las coordenadas actuales de la pieza de ajedrez*/

            x_inicial=x_inicial + Tablero1.getLadoRecuadro();
            y_inicial=y_inicial -2*Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()+1-2*8);
         }

         else if(*(Vector_Movimiento+a)==2){

            line(screen,x_inicial,y_inicial,x_inicial +2*Tablero1.getLadoRecuadro(),y_inicial-Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 2 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  2 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +2*Tablero1.getLadoRecuadro();
            y_inicial=y_inicial -Tablero1.getLadoRecuadro();
           Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()+2-1*8);
        }

         else if(*(Vector_Movimiento+a)==3){
            line(screen,x_inicial,y_inicial,x_inicial +2*Tablero1.getLadoRecuadro(),y_inicial+Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 3 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
             despues del movimiento  3 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +2*Tablero1.getLadoRecuadro();
            y_inicial=y_inicial +Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()+2+1*8);
        }

         else if(*(Vector_Movimiento+a)==4){

            line(screen,x_inicial,y_inicial,x_inicial +Tablero1.getLadoRecuadro(),y_inicial+2*Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 4 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  4 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +Tablero1.getLadoRecuadro();
            y_inicial=y_inicial +2*Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()+1+2*8);
        }

         else if(*(Vector_Movimiento+a)==5){

            line(screen,x_inicial,y_inicial,x_inicial -Tablero1.getLadoRecuadro(),y_inicial+2*Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 5 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  5 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -Tablero1.getLadoRecuadro();
            y_inicial=y_inicial +2*Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()-1+2*8);
        }

         else if(*(Vector_Movimiento+a)==6){

            line(screen,x_inicial,y_inicial,x_inicial -2*Tablero1.getLadoRecuadro(),y_inicial+Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 6 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  6 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -2*Tablero1.getLadoRecuadro();
            y_inicial=y_inicial +Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()-2+1*8);
        }

         else if(*(Vector_Movimiento+a)==7){

            line(screen,x_inicial,y_inicial,x_inicial -2*Tablero1.getLadoRecuadro(),y_inicial-Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 7 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  7 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -2*Tablero1.getLadoRecuadro();
            y_inicial=y_inicial -Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()-2-1*8);
        }

          else if(*(Vector_Movimiento+a)==8){

            line(screen,x_inicial,y_inicial,x_inicial -Tablero1.getLadoRecuadro(),y_inicial-2*Tablero1.getLadoRecuadro(),*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 8 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  8 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -Tablero1.getLadoRecuadro();
            y_inicial=y_inicial -2*Tablero1.getLadoRecuadro();
            Tablero1.setNumeroCasilla(Tablero1.getNumeroCasilla()-1-2*8);
        }
//___________________________________________________________________________________________________________________________________________________________





        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0); /*Esta funcion le indica a allegro que se cambia la forma de dibujar,
                                                    y que se va a utilizar el modo transparente*/

        set_trans_blender(0,0,0, 155);//Este comando establece el grado de transparencia a la hora de pintar

        rectfill(screen,x_inicial-Tablero1.getLadoRecuadro()/2,y_inicial-Tablero1.getLadoRecuadro()/2,x_inicial+Tablero1.getLadoRecuadro()/2,y_inicial+Tablero1.getLadoRecuadro()/2,*(pallete_color+7));/* Coloca los recuadros de un color gris
                                                                                                                                                   transparente cuando el caballo toca
                                                                                                                                                   una casilla del tablero de ajedrez*/


        Xcirculo=Xcirculo+LadoRecuadroJugadas; //Aumento en LadoRecuadroJugadas unidades las coordenadas del proximo circulo morado con rexpecto al eje x

        set_trans_blender(0,0,0, 250);//Este comando establece el grado de transparencia a la hora de pintar

        textprintf(screen,font,x_inicial,y_inicial,*(pallete_color+10),p->cad);//Coloca "P" o "I" en el tablero de jugadas si el


        drawing_mode(DRAW_MODE_XOR, NULL, 0, 0);

        circlefill(screen, x_inicial, y_inicial, 15, *(pallete_color+7));/*Borra el circulo negro que representa la ultima jugada
                                                                         hecho por el caballo en el tablero de ajedrez*/



        /* Este condicional cumple la funcionalidad de un "salto de linea" ya que cuando una
         fila llega a los 16 circulos morados salta a llenar la siguiente fila.*/

             if(b%SaltoRecuadroJugadas==0){
                  Xcirculo=x+LadoRecuadroJugadas/2;
                  Ycirculo=Ycirculo+LadoRecuadroJugadas;
                }

             a++;
             b++;

         }
             rest(1);
    }


/*El siguiente ciclo sirve para que la pantalla quede conjelada despues de haberse realizado la simulacion del
  caballo y se desconjelara unicamente cuando el usuario oprima la "flecha abajo" del teclado*/

 circlefill(screen, x_inicial, y_inicial, 15, *(pallete_color+7));/*Borra el circulo negro que representa la ultima jugada
                                                                         hecho por el caballo en el tablero de ajedrez*/


    while (!*(key+KEY_DOWN))
    {
        rest(1);
    }



    return 0;
}

void GraficadorCoordenadasPorValor(int CoordenadaX,int LadoRecuadro, int SaltoLinea,int NumeroRecuadro, int Yinicial,int Color){
 int CoordenadaY=(NumeroRecuadro/SaltoLinea)*LadoRecuadro+Yinicial;
 GraficarRecuadro(CoordenadaX,CoordenadaY,LadoRecuadro,Color);
}

void GraficarRecuadro(int CoordenadaX,int CoordenadaY, int LadoRecuadro,int Color){
    rectfill(screen,CoordenadaX,CoordenadaY,CoordenadaX+LadoRecuadro,CoordenadaY+LadoRecuadro,*(pallete_color+Color));/*Esta funcion sirve para generar varios rectangulos o cuadrados rellenos,
                                                                los cuales representan cada uno un recuadro del tablero de ajedrez */

    rect(screen,CoordenadaX,CoordenadaY,CoordenadaX+LadoRecuadro,CoordenadaY+LadoRecuadro,*(pallete_color+17));/*Esta funcion genera varios rectangulos o cuadrados vacio,
                                                          los cuales sirven para bordear y delimitar un recuadro de ajedrez*/
}

void GraficarMuchosRecuadros(int CantidadRecuadros,int Xinicial,int LadoRecuadro, int SaltoLinea,int Yinicial,int Color){
 int b=0;
 for (int a=0; a<=CantidadRecuadros-1; a++){
 if(b==(SaltoLinea)){
     b=0;
  }
 int CoordenadaX=b*LadoRecuadro+Xinicial;
 b++;
 int CoordenadaY=(a/(SaltoLinea))*LadoRecuadro+Yinicial;
 GraficarRecuadro(CoordenadaX,CoordenadaY,LadoRecuadro,Color);
 }
}

void SecuenciaCaracteres(int ValorCaracter,int PosicionCaracter,int Xinicial,int DistanciaCaracteres, int SaltoLinea,int Yinicial,int Color){

  int CoordenadaX;
  if(PosicionCaracter<SaltoLinea){
      CoordenadaX=PosicionCaracter*DistanciaCaracteres+Xinicial;
  }
  else{
    CoordenadaX=((PosicionCaracter/SaltoLinea)*SaltoLinea-PosicionCaracter)*-DistanciaCaracteres+Xinicial;
  }
 int CoordenadaY=(PosicionCaracter/SaltoLinea)*DistanciaCaracteres+Yinicial;
 textprintf(screen,font,CoordenadaX,CoordenadaY,*(pallete_color+Color),"%d",ValorCaracter);/*Esta funcion imprime por pantalla los movimientos
                                                                               del caballo en su respectiva asignacion en el "Vector_Movimiento"*/

}


void CTablero :: posicion_lista(int n){
 Stablero *p, *q;
 p=NULL;
 q=cab;
 // Con el siguiente while recorremos la lista de principio a fin
 // y al final *p apunta al último nodo de la lista
 while(q != NULL){/*Este ciclo compara el valor de los nodos con
                                el valor incertado para saber en que posicion
                                se van a colocan*/

   p=q;
   q=q->siguiente;

 }

  insertar (p,q,n);
}

void CTablero :: insertar(Stablero *p, Stablero *q, int n){

 Stablero *nuevo;
 nuevo=new Stablero;
 nuevo->Tablero=n;
 nuevo->siguiente=q;
 if(p!= NULL){ // Quiere decir que hay uno o más nodos ya insertados
  p->siguiente=nuevo; // Al último nodo de la lista se le encadena el nodo nuevo
  nuevo->anterior=p;
  col=nuevo;

 }
/*se determina si solo existe un nodo. Ademas se le asignan los valores de sus respectivos apuntadores
y se modifican las variables cab y col.*/
 else if(q==NULL && p==NULL){
  nuevo->anterior=p;
  nuevo->siguiente=q;
  cab=nuevo;
  col=nuevo;
 }

}

struct Stablero* CTablero :: Recorrer_Lista(int NumeroCasilla){

Stablero *Nodo_Actual;
Nodo_Actual=cab;
int a;

//El siguiente ciclo for recorre la lista hasta encontrar el nodo correspondiente a la casilla requerida.
    for(a=0; a<=NumeroCasilla-1; a++){

        Nodo_Actual=Nodo_Actual->siguiente;

}


return Nodo_Actual;

}

Stablero* CTablero :: getcab(){
return cab;
}
int CTablero :: getLadoRecuadro(){
return LadoRecuadro;
}
int CTablero :: getSaltoLinea(){
return SaltoLinea;
}
int CTablero :: getXinicial(){
return Xinicial;
}
int CTablero :: getYinicial(){
return Yinicial;
}
int CTablero :: getNumeroCasilla(){
return NumeroCasilla;
}
int CTablero :: getDistancia_Tablas(){
return Distanica_Tablas;
}
void CTablero :: setNumeroCasilla(int CasillaActual){
NumeroCasilla=CasillaActual;
}

CTablero :: ~CTablero(){
  Stablero *p, *q;
 p=NULL;
 q=cab;
//El siguiente while recorre toda la lista y va eliminando cada uno de sus nodos
 while (q!=NULL){
   p=q;
   q=q->siguiente;
    delete p;
 }


}



END_OF_MAIN()

