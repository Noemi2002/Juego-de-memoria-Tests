#include "Archivador.h"

Archivador::Archivador() {
    /*
     * Constructor de la clase Archivador
     */
    LeerJson();
}

void Archivador::GuardarJson(json j, std::string ruta) {

    /*
     * Guarda el json en la ruta especificada
     */

    std::ofstream o(ruta);
    o << std::setw(4) << j << std::endl;

}

void Archivador::GeneradorRutas() {

    /*
     * Genera las rutas de los archivos
     */

    json j;

    j["1"] = "a-post.png";
    j["2"] = "ama.png";
    j["3"] = "amarillo.png";
    j["4"] = "azul.png";
    j["5"] = "ca.png";
    j["6"] = "cafe.png";
    j["7"] = "cafe-claro.png";
    j["8"] = "celeste.png";
    j["9"] = "cels-pas.png";
    j["10"] = "cian.png";
    j["11"] = "cielo.png";
    j["12"] = "gris.png";
    j["13"] = "lila.png";
    j["14"] = "mmm.png";
    j["15"] = "morado.png";
    j["16"] = "morado-oscuro.png";
    j["17"] = "mostaza.png";
    j["18"] = "musgo.png";
    j["19"] = "negro.png";
    j["20"] = "negro-.png";
    j["21"] = "nm.png";
    j["22"] = "orange.png";
    j["23"] = "pastel.png";
    j["24"] = "piel.png";
    j["25"] = "ros.png";
    j["26"] = "rosado-brillante.png";
    j["27"] = "rospiel.png";
    j["28"] = "terracota.png";
    j["29"] = "tur.png";
    j["30"] = "ve.png";
    j["30"] = "ve-fuerte.png";
    j["31"] = "verde-.png";
    j["32"] = "verde-agua.png";
    j["33"] = "vino.png";


    std::string ruta = "../ManejoArchivos/cartas.json";

    GuardarJson(j, ruta);

}



void Archivador::LeerJson() {

    /*
     * Lee el archivo json y lo guarda en una variable de tipo json
     */

    std::ifstream i("../ManejoArchivos/cartas.json");
    i >> j;


}

json Archivador::CargarJson() {

    /*
     * Retorna el json
     */

    LeerJson();

    return j;

}

string Archivador::ObtenerRuta(int id) {

    /*
     * Retorna la ruta de la carta
     */

    for (int i = 0; i < 34; i++) {

        if (to_string(i) == to_string(id)) {

            return j[std::to_string(i)].get<std::string>();

        }

    }

    return "";

}