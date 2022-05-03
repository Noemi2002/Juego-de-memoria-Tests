//
// Created by Noemí on 2/5/2022.
//

#ifndef SERVIDORJUEGOMEMORIA_JUEGO_H
#define SERVIDORJUEGOMEMORIA_JUEGO_H

#include "Jugador.h"
#include "../Matriz/MatrizPaginada.h"
#include "../ManejoArchivos/json.hpp"

using json = nlohmann::json;
using  namespace std;

class Juego {

private:

    Jugador *jugador1;
    Jugador *jugador2;
    MatrizPaginada *matriz;
    bool iguales;

public:

    Juego(int filas, int columnas, string nombreJugador1, string nombreJugador2);
    void MainLoop(int i1, int j1, int i2, int j2, int powerup);
    string CargarImagen(int i, int j);
    void GeneradorDeTurnos();
    void CambiarTurno();
    void DoblarPuntos();
    void RebajarPuntos();
    void GenerarPowerUp();
    string DevolverRutaImagen(int i, int j);
    string DevolverLogica();
    string getPrimerTurno();


};


#endif //SERVIDORJUEGOMEMORIA_JUEGO_H
