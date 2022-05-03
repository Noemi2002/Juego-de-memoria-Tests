#include "ComunicacionJuego.h"

ComunicacionJuego::ComunicacionJuego(){

    /*
     * Inicializamos el socket
     */

}

void ComunicacionJuego::EnviarInstrucciones(std::string instrucciones) {

    /*
     * Recibe e interpreta las instrucciones al servidor
     */

    json j = json::parse(instrucciones);
    cout<<j.dump()<<endl;
    string temp;

    if(j["accion"].get<std::string>() == "iniciar"){

        string fila = j["fila"].get<std::string>();
        string columna = j["columna"].get<std::string>();
        string nombre1 = j["nombre1"].get<std::string>();
        string nombre2 = j["nombre2"].get<std::string>();

        temp = InicarJuego(fila, columna, nombre1, nombre2);

    } else if(j["accion"].get<std::string>() == "imagen"){

        string i1 = j["x"].get<std::string>();
        string j1 = j["y"].get<std::string>();

        int i = stoi(i1);
        int j = stoi(j1);

        temp = juego->DevolverRutaImagen(i, j);

    } else if(j["accion"].get<std::string>() == "comprobar"){

        string i1 = j["i1"].get<std::string>();
        string j1 = j["j1"].get<std::string>();
        string i2 = j["i2"].get<std::string>();
        string j2 = j["j2"].get<std::string>();
        string power = j["power"].get<std::string>();

        int fila1 = stoi(i1);
        int columna1 = stoi(j1);
        int fila2 = stoi(i2);
        int columna2 = stoi(j2);
        int powerup = stoi(power);

        this->juego->MainLoop(fila1, columna1, fila2, columna2, powerup);

        temp = juego->DevolverLogica();


    }

    SetMessage(temp);

}

string ComunicacionJuego::InicarJuego(string fila, string columna, string nombre1, string nombre2) {

    /*
     * Inicializa el juego
     */

    int i = stoi(fila);
    int j = stoi(columna);

    this->juego = new Juego(i, j, nombre1, nombre2);

    return this->juego->getPrimerTurno();
}

void ComunicacionJuego::SetMessage(std::string mensaje) {

    /*
     * Setea el mensaje a enviar
     */

    this->mensaje = mensaje;

}

string ComunicacionJuego::GetMessageToSend() {

    /*
     * Devuelve el mensaje a enviar
     */

    return this->mensaje;

}