#include <allegro.h>
#include <iostream>
#include <stdio.h>

using namespace std;


volatile int contador = 0;//Esta variable tiene el objetivo de controlar los fps del juego.

//Esta funcion cumple con aumentar en una unidad la variable contador cada vez que se llame.Cumple la funcion de un temporizador
void mi_temporizador()
{
    contador++;
}END_OF_FUNCTION(inc_speed_counter);

struct Stablero{
    //Coordenada con respecto al eje x de un recuadro de ajedrez
    int Tablero;
    //par o impar
    char cad[2];
    //Apuntador al nodo anterior
    Stablero *anterior;
    //Apuntador al nodo siguiente
    Stablero *siguiente;
};

class Tablero {

    protected:
        //Esta funcion grafica un recuadro bordeado de acuerdo a unas coordenadas
        void GraficarRecuadro(int CoordenadaX=0,int CoordenadaY=0, int LongitudLado=10,int color=10);
        int LadoRecuadro;//Variable que contiene la longitud de uno de los lados de los recuadros de los tableros
        int SaltoLinea;//Esta variable indica el numero de recuadros que deben haber en cada fila de los recuadros
        int XInicial;//Expresa la distancia que existen entre la parte izquierda de la pantalla y la parte izquierda del tablero
        int YInicial;// Expresa la distancia que existe entre la parte superior de la pantalla y la parte superior del tablero

    public:
        //Contructor
        Tablero(int LR,int SL,int XI,int YI){
            LadoRecuadro=LR;
            SaltoLinea=SL;
            XInicial=XI;
            YInicial=YI;
        }

        //Retorna el valor de la variable "LadoRecuadro"
        int getLadoRecuadro(){return LadoRecuadro;}
        //Devuelde el valor de la variable "SaltoLinea"
        int getSaltoLinea(){return SaltoLinea;}
        //Grafica los diderentes tipos de tableros
        virtual void GraficarTablero(){};
        //Destructor
        ~Tablero(){};

};

class TableroAjedrez: public Tablero{
        // Distancia en pixeles entre el tablero de ajedrez y el de jugadas
        int Distancia_Tablas;

        //Coordenadas con respecto al eje X para graficar la tabla de jugadas (de color rojo)
        int x;

        // Aqui se declaran las variables que corresponden a las coordenadas iniciales de la pieza de ajedrez en terminos de pixeles
        float x_inicial,y_inicial;

        struct Stablero *cab, *col;

        //Funcion para insertar nodos
        void insertar(Stablero *p, Stablero *q, int n);

        //Funcion para determianr informacion que debe ir dentro de los apuntadores de los nodos
        void determinar_posicion_lista(int n);

        // La siguiente funcion grafica un conjunto de recuadros de acuerdo a la informacion contenida los nodos del tablero de ajedrez
        void GraficadorCoordenadasPorValor(int NumeroRecuadro, int Color);

    public:
        //Constructor
            //El constructor de la clase derivada debe tener primero los parametros de la clase padre y luego si los de sus atributos
        TableroAjedrez(int LR=100,int SL=8,int XI=0,int YI=0,int DT=200):Tablero(LR,SL,XI,YI),cab(NULL),col(NULL),Distancia_Tablas(DT),
        x(LadoRecuadro*SaltoLinea+Distancia_Tablas+XInicial),x_inicial(LadoRecuadro*4.5),y_inicial(YInicial+LadoRecuadro/2) {InformacionNodosAjedrez();}

        //Asigna valores a  los nodos que contienen la informacion de cada casilla del tablero de ajedrez.
        void InformacionNodosAjedrez();
        //Esta funcion reccorre los nodos para seleccionar aquel que corresponda a la casilla del tablero de ajedrez deseada
        Stablero* Recorrer_Lista(int NumeroCasilla);

        //Grafica el tablero de ajedrez de acuerdo a la informacion contenida en los nodos de la lista encadenada
        void GraficarTablero();
        //Retorna el valor de la variable "x_inicial"
        float getx_inicial(){return x_inicial;}
        //Retorna el valor de la variable "y_inicial"
        float gety_inicial(){return y_inicial;}
        //Realiza un movimiento en el tablero de ajedrez
        int JugarMovimiento(int Movimiento);
        //Retorna el valor contenido en la variable "x"
        int getx(){return x;}
        //Funcion deestructora
        ~TableroAjedrez();


};

class TableroJugadas: public Tablero{

        int NumeroCasillas;
        int Color;
        int y;

    public:
        //Contructor
        TableroJugadas(int LD=50,int SL=16,int XI=1000,int YI=200,int NumCas=63,int Clr=12):Tablero(LD,SL, XI,YI), NumeroCasillas(NumCas),Color(Clr),y(YInicial) {}
        //Grafica la tabla de jugadas (de color rojo)
        void GraficarTablero ();
        void SecuenciaCaracteres(int ValorCaracter,int PosicionCaracter,int Xinicial,int Color1=10);
        int gety(){return y;}
        //Destructor
        ~TableroJugadas(){};
 };

 class Caballo{

     int CasillaActual;
     public:
         //Constructor
         Caballo(int CA=4):CasillaActual(CA){}
         //Arroja el valor de la variable "CasillaActual"
         int getCasillaActual(){return CasillaActual;}
         //Actualiza el valor contenido en la variable "CasillaActual"
         void setCasillaActual(int CA){CasillaActual=CA;}
         //Destructor
         ~Caballo(){};
 };

int main()
{
    // Puntero tipo clase base
    Tablero *PTablero;

    //Se crea el objeto TAjedrez
    TableroAjedrez TAjedrez(100,8,0,0,200);

    //Se crea el objeto TJugadas
    TableroJugadas TJugadas(50,16,TAjedrez.getx(),200,63,12);

    //Se crea el objeto Pieza
    Caballo Pieza(4);


    //Variables correspondientes al tablero de jugadas.*/

    //En este vector se almacena secuencialmente los movimientos que el caballo debe hacer.
    int Vector_Movimiento [63]={3,4,7,5,3,4,7,6,7,8,3,1,7,8,3,5,8,2,4,5,6,
                               4,2,3,2,8,6,1,2,8,6,6,1,6,5,4,5,2,1,3,5,2,
                               1,8,1,6,4,1,7,5,4,3,5,7,6,7,1,3,8,7,1,3,4};

    // XCirculo es la coordenada con respecto al eje x del centro del circulo en el tablero de jugadas
    int Xcirculo=TAjedrez.getx()+TJugadas.getLadoRecuadro()/2;

    // YCirculo es la coordenada con respecto al eje y del centro del circulo del tablero de jugadas
    int Ycirculo=TJugadas.gety()+TJugadas.getLadoRecuadro()/2;

    // RadioCirculo es el radio del circulo que indica la posicion actual del caballo
    int RadioCirculo=TJugadas.getLadoRecuadro()/3;

/*Otras variables*/
   int a;// Esta variable se utiliza para recorrer ciclos for y while.
   int b;// En el proximo ciclo for, esta variable sirve para asignar un valor respectivo al arreglo "Tablero"

//___________________________________________________________________________________________________________________________________


    allegro_init();// Esta funcion instala los componentes fundamentales de la biblioteca Allegro.
    install_keyboard();// Con esta función podremos checar qué teclas están siendo presionadas.

    set_color_depth(32);//
    //Esta funcion sirve para mostrar la interfaz de usuario y asignarle un tamaño.
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1900, 940, 0, 0);


    //Se grafica el tablero de ajedrez
    PTablero=&TAjedrez;
    PTablero->GraficarTablero();

    //Se grafica el tablero de jugadas
    PTablero=&TJugadas;
    PTablero->GraficarTablero();

    //Coloca valores numericos dentro de cada recuadro de la tabla de jugadas
    for(a=0; a<=62; a++){
        TJugadas.SecuenciaCaracteres(*(Vector_Movimiento+a),a,TAjedrez.getx(),10);
    }


    /*El siguiente ciclo while sirve como una restriccion (no deja avanzar al usuario al siguiente codigo hasta
    que presione la tecla "flecha abajo")*/
    while (!*(key+KEY_DOWN))
    {
        rest(1);
    }

    //Evita que la variable contador sera modificada por otros hilos ajenos a este
    LOCK_VARIABLE(contador);
    //Evita que la funcion inc_speed_counter sea utilizada por otros hilos diferentes de este
    LOCK_FUNCTION(mi_temporizador);
    //Esta funcion llama a la funcion inc_speed_counter(), haciendo que se ejecute 2 veces por segundo
    install_int_ex(mi_temporizador, BPS_TO_TIMER(2));

    a=0;

    //Se sombrea la casilla donde se encuentra inicialmente el caballo
    rectfill(screen,TAjedrez.getx_inicial()-TAjedrez.getLadoRecuadro()/2,TAjedrez.gety_inicial()-TAjedrez.getLadoRecuadro()/2,TAjedrez.getx_inicial()+TAjedrez.getLadoRecuadro()/2,TAjedrez.gety_inicial()+TAjedrez.getLadoRecuadro()/2,*(pallete_color+7));
    b=1;



    Stablero *p=NULL;

    while (a!=63)
    {

        //La siguiente condicion sirve para que el codigo dentro se ejecute cada 0,5 segundos
        if(contador > 0){

            //Se devuelve la variable contador al valor 0 para que el condicional se vuelva a ejecutar.
            contador =0;

            p=TAjedrez.Recorrer_Lista(Pieza.getCasillaActual());

            /*Los siguientes condicionales identifican la jugada que se desprende de una casilla cualquiera del tablero de
            ajedrez y relaciona la casilla con el tipo de movimiento (si es par o impar)*/
            if(*(Vector_Movimiento+a)%2==0){
                strcpy(p->cad,"P");
            }

            else{
                strcpy(p->cad,"I");
            }


            //indica que si se dibuja dos veces la misma figura en el mismo lugar esta desaparecera.
            drawing_mode(DRAW_MODE_XOR, NULL, 0, 0);

            //Dibuja un circulo negro en la casilla donde recien el caballo realizo un movimiento (el cual despues sera borrado)
            circlefill(screen, TAjedrez.getx_inicial(), TAjedrez.gety_inicial(), 15, *(pallete_color+7));

            //Indica que toda figura que se realice a partir de ahora sera no transparente
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

            /*Coloca un circulo relleno dentro de los recuadros rojos en sincronia con el
            movimiento del caballo. Sirve para indicar el movimiento que acaba de realizar la pieza de ajedrez*/
            circlefill(screen, Xcirculo, Ycirculo, RadioCirculo,*(pallete_color+1));

            /*Los siguientes condicionales se relacionan con una de las 8 posibles posiciones del caballo
            con el "Vector_Movimiento" para mover el vector del caballo a la posicion correcta*/

            //Indica el numero de la casilla actual despues de haber realizado un movimiento
            Pieza.setCasillaActual(Pieza.getCasillaActual()+TAjedrez.JugarMovimiento(*(Vector_Movimiento+a)));


            //Esta funcion le indica a allegro que se cambia la forma de dibujar y que se va a utilizar el modo transparente
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

            //Este comando establece el grado de transparencia a la hora de pintar
            set_trans_blender(0,0,0, 155);

            //Aumento en LadoRecuadroJugadas unidades las coordenadas del proximo circulo morado con rexpecto al eje x
            Xcirculo=Xcirculo+TJugadas.getLadoRecuadro();

            //Este comando establece el grado de transparencia a la hora de pintar
            set_trans_blender(0,0,0, 250);

            //Coloca "P" o "I" en el tablero de jugadas si el movimiento es par o impar
            textprintf(screen,font,TAjedrez.getx_inicial(),TAjedrez.gety_inicial(),*(pallete_color+10),p->cad);

            drawing_mode(DRAW_MODE_XOR, NULL, 0, 0);

            //Borra el circulo negro que representa la ultima jugada hecho por el caballo en el tablero de ajedrez
            circlefill(screen, TAjedrez.getx_inicial(),TAjedrez.gety_inicial(), 15, *(pallete_color+7));



            /* Este condicional cumple la funcionalidad de un "salto de linea" ya que cuando una
            fila llega a los 16 circulos morados salta a llenar la siguiente fila.*/

             if(b%TJugadas.getSaltoLinea()==0){
                  Xcirculo=TAjedrez.getx()+TJugadas.getLadoRecuadro()/2;
                  Ycirculo=Ycirculo+TJugadas.getLadoRecuadro();
                }

             a++;
             b++;

         }
             rest(1);
    }


/*El siguiente ciclo sirve para que la pantalla quede conjelada despues de haberse realizado la simulacion del
  caballo y se desconjelara unicamente cuando el usuario oprima la "flecha abajo" del teclado*/

 circlefill(screen, TAjedrez.getx_inicial(), TAjedrez.gety_inicial(), 15, *(pallete_color+7));/*Borra el circulo negro que representa la ultima jugada
                                                                         hecho por el caballo en el tablero de ajedrez*/


    while (!*(key+KEY_DOWN))
    {
        rest(1);
    }



    return 0;
}

void TableroAjedrez :: GraficadorCoordenadasPorValor(int NumeroRecuadro, int Color){

 int CoordenadaY=(NumeroRecuadro/SaltoLinea)*LadoRecuadro+YInicial;

 GraficarRecuadro(Recorrer_Lista(NumeroRecuadro)->Tablero,CoordenadaY,LadoRecuadro,Color);
}

void Tablero :: GraficarRecuadro(int CoordenadaX,int CoordenadaY, int LongitudLado,int Color){
    rectfill(screen,CoordenadaX,CoordenadaY,CoordenadaX+LadoRecuadro,CoordenadaY+LadoRecuadro,*(pallete_color+Color));/*Esta funcion sirve para generar varios rectangulos o cuadrados rellenos,
                                                                los cuales representan cada uno un recuadro del tablero de ajedrez */

    rect(screen,CoordenadaX,CoordenadaY,CoordenadaX+LadoRecuadro,CoordenadaY+LadoRecuadro,*(pallete_color+17));/*Esta funcion genera varios rectangulos o cuadrados vacio,
                                                          los cuales sirven para bordear y delimitar un recuadro de ajedrez*/
}

void TableroJugadas :: GraficarTablero(){
 int b=0;
 for (int a=0; a<=NumeroCasillas-1; a++){
 if(b==(SaltoLinea)){
     b=0;
  }
 int CoordenadaX=b*LadoRecuadro+XInicial;
 b++;
 int CoordenadaY=(a/(SaltoLinea))*LadoRecuadro+YInicial;
 GraficarRecuadro(CoordenadaX,CoordenadaY,LadoRecuadro,Color);
 }
}

void TableroJugadas :: SecuenciaCaracteres(int ValorCaracter,int PosicionCaracter,int Xinicial,int Color1){

  int CoordenadaX;
  if(PosicionCaracter<SaltoLinea){
      CoordenadaX=PosicionCaracter*LadoRecuadro+Xinicial;
  }
  else{
    CoordenadaX=((PosicionCaracter/SaltoLinea)*SaltoLinea-PosicionCaracter)*-LadoRecuadro+Xinicial;
  }
 int CoordenadaY=(PosicionCaracter/SaltoLinea)*LadoRecuadro+YInicial;
 textprintf(screen,font,CoordenadaX,CoordenadaY,*(pallete_color+Color1),"%d",ValorCaracter);/*Esta funcion imprime por pantalla los movimientos
                                                                               del caballo en su respectiva asignacion en el "Vector_Movimiento"*/

}


void TableroAjedrez :: determinar_posicion_lista(int n){
    Stablero *p, *q;
    p=NULL;
    q=cab;
    // Con el siguiente while recorremos la lista de principio a fin
    // y al final *p apunta al último nodo de la lista

    /*Este ciclo compara el valor de los nodos con el valor incertado para saber en que posicion se van a colocan*/
    while(q != NULL){
        p=q;
        q=q->siguiente;

    }

    insertar (p,q,n);
}

void TableroAjedrez :: insertar(Stablero *p, Stablero *q, int n){

    Stablero *nuevo;
    nuevo=new Stablero;
    nuevo->Tablero=n;
    nuevo->siguiente=q;

    //Si se entra al siguiete condicional entonces hay uno o más nodos ya insertados
    if(p!= NULL){
        // Al último nodo de la lista se le encadena el nodo nuevo
        p->siguiente=nuevo;
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

struct Stablero *TableroAjedrez :: Recorrer_Lista(int NumeroCasilla){

Stablero *Nodo_Actual;
Nodo_Actual=cab;
int a;

//El siguiente ciclo for recorre la lista hasta encontrar el nodo correspondiente a la casilla requerida.
    for(a=0; a<=NumeroCasilla-1; a++){

        Nodo_Actual=Nodo_Actual->siguiente;

    }

return Nodo_Actual;

}

TableroAjedrez :: ~TableroAjedrez(){

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

void TableroAjedrez:: InformacionNodosAjedrez(){
   int a,b;
   for(a=0; a<=63; a++){
       if(a%SaltoLinea==0){
            b=0;
       }
    determinar_posicion_lista(b*LadoRecuadro+XInicial);
     b++;
   }//Asigna valores a los nodos que representan las casillas del tablero de ajedrez
}

void TableroAjedrez :: GraficarTablero(){
   int a;
    for(a=0;a<=63;a++){

    if((a/8)%2==0){

    if (a%2==0){
    GraficadorCoordenadasPorValor(a,15);
     }
     else{
    GraficadorCoordenadasPorValor(a,6);
     }
        }

        else{

            if (a%2==0){

    GraficadorCoordenadasPorValor(a,6);
      }

     else{
     GraficadorCoordenadasPorValor(a,15);
      }

        }
     }
    }

    int TableroAjedrez :: JugarMovimiento(int Movimiento){

         if(Movimiento==1){

            line(screen,x_inicial,y_inicial,x_inicial+LadoRecuadro,y_inicial-2*LadoRecuadro,*(pallete_color+0));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 1 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
             despues del movimiento  1 como las coordenadas actuales de la pieza de ajedrez*/

            x_inicial=x_inicial + LadoRecuadro;
            y_inicial=y_inicial -2*LadoRecuadro;
            return 1-2*8;
         }

         else if(Movimiento==2){

            line(screen,x_inicial,y_inicial,x_inicial+2*LadoRecuadro,y_inicial-LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 2 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  2 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +2*LadoRecuadro;
            y_inicial=y_inicial -LadoRecuadro;
           return 2-1*8;
        }

         else if(Movimiento==3){
            line(screen,x_inicial,y_inicial,x_inicial +2*LadoRecuadro,y_inicial+LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 3 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
             despues del movimiento  3 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +2*LadoRecuadro;
            y_inicial=y_inicial +LadoRecuadro;
            return 2+1*8;
        }

         else if(Movimiento==4){

            line(screen,x_inicial,y_inicial,x_inicial +LadoRecuadro,y_inicial+2*LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 4 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  4 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial +LadoRecuadro;
            y_inicial=y_inicial +2*LadoRecuadro;
            return 1+2*8;
        }

         else if(Movimiento==5){

            line(screen,x_inicial,y_inicial,x_inicial -LadoRecuadro,y_inicial+2*LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 5 */

            /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  5 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -LadoRecuadro;
            y_inicial=y_inicial +2*LadoRecuadro;
            return -1+2*8;
        }

         else if(Movimiento==6){

            line(screen,x_inicial,y_inicial,x_inicial -2*LadoRecuadro,y_inicial+LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 6 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  6 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -2*LadoRecuadro;
            y_inicial=y_inicial +LadoRecuadro;
            return -2+1*8;
        }

         else if(Movimiento==7){

            line(screen,x_inicial,y_inicial,x_inicial -2*LadoRecuadro,y_inicial-LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 7 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  7 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -2*LadoRecuadro;
            y_inicial=y_inicial -LadoRecuadro;
            return -2-1*8;
        }

          else if(Movimiento==8){

            line(screen,x_inicial,y_inicial,x_inicial -LadoRecuadro,y_inicial-2*LadoRecuadro,*(pallete_color));/* Esta funcion dibuja una linea que va desde
                                                                                            la posicion actual del caballo hasta la casilla
                                                                                            correspondiente al movimiento 8 */

             /* En las siguientes dos reasignaciones de las variables x_inicial y y_inicial se toman las coordenadas del
            despues del movimiento  8 como las coordenadas actuales de la pieza de ajedrez*/
            x_inicial=x_inicial -LadoRecuadro;
            y_inicial=y_inicial -2*LadoRecuadro;
            return -1-2*8;
        }
         rectfill(screen,x_inicial-LadoRecuadro/2,y_inicial-LadoRecuadro/2,x_inicial+LadoRecuadro/2,y_inicial+LadoRecuadro/2,*(pallete_color+7));// Coloca los recuadros de un color gris

      }



END_OF_MAIN()

