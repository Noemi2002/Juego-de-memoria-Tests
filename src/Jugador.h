//
// Created by Noemí on 2/5/2022.
//



#ifndef SERVIDORJUEGOMEMORIA_JUGADOR_H
#define SERVIDORJUEGOMEMORIA_JUGADOR_H

#include <string>
#include <sstream>

using namespace std;


class Jugador {

private:
    int puntaje;
    int id;
    bool turno;
    int powerUp;
    int movimientos[4] = {0,0,0,0};
    string nombre;

public:

    Jugador(int id, string nombre);
    int getPuntaje();
    void setPuntaje(int puntaje);
    int getId();
    void setId(int id);
    bool getTurno();
    void setTurno(bool turno);
    int getPowerUp();
    void setPowerUp(int powerUp);
    string getPS();
    string getTS();
    string getPUS();
    string getNombre();


};


#endif //SERVIDORJUEGOMEMORIA_JUGADOR_H
