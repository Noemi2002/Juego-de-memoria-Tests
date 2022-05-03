#include "Tarjetas.h"

Tarjetas::Tarjetas() {
}

int Tarjetas::getId() {
    /*
     * Retorna el id de la tarjeta
     */
    return id;
}

string Tarjetas::getRuta() {
    /*
     * Retorna la ruta de la tarjeta
     */
    return ruta;
}

void Tarjetas::setId(int id) {
    /*
     * Setea el id de la tarjeta
     */
    this->id = id;
}

void Tarjetas::setRuta(string ruta) {
    /*
     * Setea la ruta de la tarjeta
     */
    this->ruta = ruta;
}

int Tarjetas::espacioUsado() {
    /*
     * Retorna el espacio usado de la tarjeta
     */
    return sizeof (id) + sizeof (ruta);

}