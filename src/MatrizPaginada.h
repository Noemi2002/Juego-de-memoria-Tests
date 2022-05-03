
#ifndef SERVIDORJUEGOMEMORIA_MATRIZPAGINADA_H
#define SERVIDORJUEGOMEMORIA_MATRIZPAGINADA_H

#include <iostream>
#include <string>
#include "Tarjetas.h"
#include "Archivador.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class MatrizPaginada {

    private:
        Tarjetas *enMemoria;
        int cantidadMaxima;
        int cantidadActual;
        int memoriaTotal;
        int memoriaOcupada;
        int filas;
        int columnas;
        int **matriz;
        Archivador *archivador;
        int faults;
        int hits;


    public:

        MatrizPaginada(int filas, int columnas);
        void GenerarMatriz();
        void RellenarMatriz();
        bool VerificarMatriz(int num);
        int GenerarNumero();
        void ImprimirMatriz();
        void LlenarMemoria();
        bool VerificarMemoria(int num);
        void ImprimirMemoria();
        int ComprobarPareja(int i1, int j1, int i2, int j2);
        bool ComprobarMemoria(int numero);
        Tarjetas *GetEnMemoria(int numero);
        int GetPosicionMemoria(int numero);
        void CargarEnMemoria(int id, int ocupado);
        int BuscarEspacioEnMemoria(int ocupado);
        string BuscarRuta(int i, int j);
        int GetFaults();
        int GetHits();
        int GetMemoriaOcupada();
        int GetMemoriaTotal();
        bool VerificarSiGano();
        void MostrarMemoria();
        void ResetCantidadActual();

};


#endif //SERVIDORJUEGOMEMORIA_MATRIZPAGINADA_H
