#ifndef SERVIDORJUEGOMEMORIA_TARJETAS_H
#define SERVIDORJUEGOMEMORIA_TARJETAS_H

#include <iostream>
#include <string>

using namespace std;

class Tarjetas {

private:
    int id;
    string ruta;

    public:
    Tarjetas();
    int getId();
    string getRuta();
    void setId(int id);
    void setRuta(string ruta);
    int espacioUsado();
};


#endif //SERVIDORJUEGOMEMORIA_TARJETAS_H
