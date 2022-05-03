//
// Created by Noemí on 2/5/2022.
//

#include "Jugador.h"

Jugador::Jugador(int id, string nombre) {

    /*
     * Constructor de la clase Jugador
     *
     * @param id: identificador del jugador
     * @param nombre: nombre del jugador
     */

    this->id = id;
    this->puntaje = 0;
    this->turno = false;
    this->powerUp = 0;
    this->nombre = nombre;
}

int Jugador::getId() {
    /*
     * Retorna el identificador del jugador
     *
     * @return id: identificador del jugador
     */
    return this->id;
}

void Jugador::setId(int id) {
    /*
     * Modifica el identificador del jugador
     *
     * @param id: identificador del jugador
     */
    this->id = id;
}

int Jugador::getPuntaje() {
    /*
     * Retorna el puntaje del jugador
     *
     * @return puntaje: puntaje del jugador
     */
    return this->puntaje;
}

int Jugador::getPowerUp() {
    /*
     * Retorna el powerUp del jugador
     *
     * @return powerUp: powerUp del jugador
     */
    return this->powerUp;
}

void Jugador::setPuntaje(int puntaje) {
    /*
     * Modifica el puntaje del jugador
     *
     * @param puntaje: puntaje del jugador
     */
    this->puntaje += puntaje;
}

void Jugador::setPowerUp(int powerUp) {
    /*
     * Modifica el powerUp del jugador
     *
     * @param powerUp: powerUp del jugador
     */
    this->powerUp = powerUp;
}

void Jugador::setTurno(bool turno) {
    /*
     * Modifica el turno del jugador
     *
     * @param turno: turno del jugador
     */
    this->turno = turno;
}

bool Jugador::getTurno() {
    /*
     * Retorna el turno del jugador
     *
     * @return turno: turno del jugador
     */
    return this->turno;
}



string Jugador::getPS() {
    /*
     * Retorna el nombre del jugador
     *
     * @return nombre: nombre del jugador
     */
    stringstream ss;
    ss << this->puntaje;
    return ss.str();
}

string Jugador::getTS() {

    /*
     * Retorna el turno del jugador
     *
     * @return turno: turno del jugador
     */

    if (this->turno) {
        return "1";
    } else {
        return "0";
    }

}

string Jugador::getPUS() {
    /*
     * Retorna el powerUp del jugador
     *
     * @return powerUp: powerUp del jugador
     */
    stringstream ss;
    ss << this->powerUp;
    return ss.str();
}

string Jugador::getNombre() {
    /*
     * Retorna el nombre del jugador
     *
     * @return nombre: nombre del jugador
     */
    return this->nombre;
}
