
#ifndef SERVIDORJUEGOMEMORIA_ARCHIVADOR_H
#define SERVIDORJUEGOMEMORIA_ARCHIVADOR_H


#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Archivador {

private:
    json j;

public:

    Archivador();
    void GeneradorRutas();
    void GuardarJson(json j, std::string ruta);
    void LeerJson();
    string ObtenerRuta(int id);
    json CargarJson();


};


#endif //SERVIDORJUEGOMEMORIA_ARCHIVADOR_H
