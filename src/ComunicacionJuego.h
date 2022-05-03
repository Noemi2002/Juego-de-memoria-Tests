#ifndef SERVIDORJUEGOMEMORIA_COMUNICACIONJUEGO_H
#define SERVIDORJUEGOMEMORIA_COMUNICACIONJUEGO_H

#include "json.hpp"
#include "../Juego/Juego.h"

using json = nlohmann::json;
using namespace std;

class ComunicacionJuego {

    private:

        Juego *juego;
        std::string mensaje;

    public:

        ComunicacionJuego();
        void EnviarInstrucciones(std::string instrucciones);
        void SetMessage(std::string mensaje);
        string GetMessageToSend();
        string InicarJuego(string fila, string columna, string nombre1, string nombre2);

};


#endif //SERVIDORJUEGOMEMORIA_COMUNICACIONJUEGO_H
