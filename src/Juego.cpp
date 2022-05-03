//
// Created by Noemí on 2/5/2022.
//

#include "Juego.h"

Juego::Juego(int filas, int columnas, string nombreJugador1, string nombreJugador2){

    /*
     * Inicializamos el tablero
     *
     * @param filas: numero de filas del tablero
     * @param columnas: numero de columnas del tablero
     * @param nombreJugador1: nombre del jugador 1
     * @param nombreJugador2: nombre del jugador 2
     */

    this->iguales = false;
    this->matriz = new MatrizPaginada(filas, columnas);
    this->jugador1 = new Jugador(1, nombreJugador1);
    this->jugador2 = new Jugador(2, nombreJugador2);

    GeneradorDeTurnos();

}

void Juego::MainLoop(int i1, int j1, int i2, int j2, int powerup) {

    /*
     * Funcion principal del juego
     *
     * @param i1: fila del primer disparo
     * @param j1: columna del primer disparo
     * @param i2: fila del segundo disparo
     * @param j2: columna del segundo disparo
     * @param powerup: numero del powerup
     */

    GenerarPowerUp();

    if(powerup == 1){
        DoblarPuntos();
    } else if(powerup == 2){
        RebajarPuntos();
    }

    if(this->jugador1->getTurno()){

        if(powerup !=3){
            CambiarTurno();
        }

        int temp = this->matriz->ComprobarPareja(i1, j1, i2, j2);

        this->jugador1->setPuntaje(temp);

        if (temp == 0) {
            this->iguales = false;
        } else {
            this->iguales = true;
        }


    }else{

        if(powerup !=3){
            CambiarTurno();
        }

        int temp = this->matriz->ComprobarPareja(i1, j1, i2, j2);

        this->jugador2->setPuntaje(temp);

        if (temp == 0) {
            this->iguales = false;
        } else {
            this->iguales = true;
        }

    }

    if(powerup != 0){
        if(this->jugador1->getTurno()){
            this->jugador1->setPowerUp(0);
        } else{
            this->jugador2->setPowerUp(0);
        }
    }

    this->matriz->MostrarMemoria();

}

void Juego::GeneradorDeTurnos() {

    /*
     * Genera los turnos de los jugadores
     */

    //Genera un numero aleatorio entre 1 y 2
    srand(time(NULL));
    int turno = rand() % 2 + 1;

    if(turno == 1) {
        this->jugador1->setTurno(true);
        this->jugador2->setTurno(false);
    } else {
        this->jugador1->setTurno(false);
        this->jugador2->setTurno(true);
    }

}

void Juego::DoblarPuntos() {

    /*
     * Dobla los puntos del jugador
     */

    if(this->jugador1->getTurno()) {
        this->jugador1->setPuntaje(this->jugador1->getPuntaje());
    } else {
        this->jugador2->setPuntaje(this->jugador2->getPuntaje());
    }

}

void Juego::CambiarTurno() {

    /*
     * Cambia el turno del jugador
     */

    if(this->jugador1->getTurno()) {
        this->jugador1->setTurno(false);
        this->jugador2->setTurno(true);
    } else {
        this->jugador1->setTurno(true);
        this->jugador2->setTurno(false);
    }

}

void Juego::RebajarPuntos() {

    /*
     * Rebaja los puntos del jugador
     */

    if(this->jugador1->getTurno()) {
        this->jugador2->setPuntaje(this->jugador2->getPuntaje() - 2);
    } else {
        this->jugador1->setPuntaje(this->jugador1->getPuntaje() - 2);
    }

}

void Juego::GenerarPowerUp() {

    /*
     * Genera un powerup aleatorio
     */

    //Genera un numero aleatorio entre 1 y 20

    srand(time(NULL));

    int powerUp = rand() % 20 + 1;

    //verifica si el numero aleatorio generado es 1 o 2 o 3

    if(powerUp == 1 || powerUp == 2 || powerUp == 3) {

        if(this->jugador1->getTurno()) {
            this->jugador1->setPowerUp(powerUp);
        } else {
            this->jugador2->setPowerUp(powerUp);
        }

    }

}

string Juego::CargarImagen(int i, int j) {

    /*
     * Carga la imagen del tablero
     *
     * @param i: fila del tablero
     * @param j: columna del tablero
     *
     * @return: la imagen del tablero
     */

    string ruta = matriz->BuscarRuta(i, j);

    return ruta;

}

string Juego::DevolverRutaImagen(int i, int j) {

    /*
     * Devuelve la ruta de la imagen del tablero
     *
     * @param i: fila del tablero
     * @param j: columna del tablero
     *
     * @return: la ruta de la imagen del tablero
     */

    json obj;

    string ruta = CargarImagen(i, j);

    obj["archivo"] = ruta; //Agrega el valor de la ruta a la variable obj str
    obj["x"] = i; //x es la fila str
    obj["y"] = j; //y es la columna str

    return obj.dump();

}

string Juego::DevolverLogica() {

    /*
     * Devuelve la logica del tablero
     *
     * @return: la logica del tablero
     */

    json obj;

    obj["1"]["puntaje"] = this->jugador1->getPS(); //puntaje en string
    obj["1"]["turno"] = this->jugador1->getTS(); //turno en string 0 o 1
    obj["1"]["powerup"] = this->jugador1->getPUS(); //powerup en string 1 o 2 o 3 o 0
    obj["2"]["puntaje"] = this->jugador2->getPS(); //puntaje en string
    obj["2"]["turno"] = this->jugador2->getTS(); //turno en string 0 o 1
    obj["2"]["powerup"] = this->jugador2->getPUS(); //powerup en string 1 o 2 o 3 o 0

    if(this->iguales) {
        obj["iguales"] = "1";
    } else {
        obj["iguales"] = "0";
    }

    bool termino = this->matriz->VerificarSiGano();

    if(termino) {
        obj["termino"] = "1";
    } else {
        obj["termino"] = "0";
    }

    this->iguales = false;

    return obj.dump();


}

string Juego::getPrimerTurno() {

    /*
     * Devuelve el primer turno del juego
     *
     * @return: el primer turno del juego
     */

    json obj;

    string temp;


    bool turno = this->jugador1->getTurno();

    if(turno) {
        temp = "1";
    } else {
        temp = "2";
    }

    obj["jugador"] = temp;

    return obj.dump(); //retorna {jugador: 1} o {jugador: 2}


}
