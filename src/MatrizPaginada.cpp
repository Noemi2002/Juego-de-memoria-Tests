#include "MatrizPaginada.h"

MatrizPaginada::MatrizPaginada(int filas, int columnas) {

    /*
     * Inicializamos la matriz con el tamaño indicado
     *
     * @param filas: numero de filas de la matriz
     * @param columnas: numero de columnas de la matriz
     */

    this->cantidadMaxima = (32)/3;
    this->cantidadActual = 0;
    this->enMemoria = new Tarjetas[cantidadMaxima];
    this->filas = filas;
    this->columnas = columnas;
    this->archivador = new Archivador();
    this->GenerarMatriz();
    this->RellenarMatriz();
    this->LlenarMemoria();
    this->faults = 0;
    this->hits = 0;
    this->memoriaTotal = 412 * cantidadMaxima;

}

void MatrizPaginada::GenerarMatriz() {

    /*
     * Genera la matriz de la memoria
     */

    matriz = new int*[filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0;
        }
    }

}

void MatrizPaginada::RellenarMatriz() {

    /*
     * Rellena la matriz con los valores de la memoria
     */

    int pares = (filas * columnas) / 2;
    int contador = 0;
    int fila,columna,fila2,columna2;

    srand(time(NULL));

    while (true){

        int numero = GenerarNumero();


        while (true){

            fila = rand() % filas;
            columna = rand() % columnas;
            fila2 = rand() % filas;
            columna2 = rand() % columnas;



            /*
    * Revisa las posiciones generadas estan disponibles para setear la carta
    *
    *
    */


            if (matriz[fila][columna] == 0 && matriz[fila2][columna2] == 0 && fila != fila2 && columna != columna2){
                matriz[fila][columna] = numero;
                matriz[fila2][columna2] = numero;
                contador++;
                break;
            }

            if (contador+1 == pares){

                for (int i = 0; i < filas; i++) {
                    for (int j = 0; j < columnas; j++) {
                        if (matriz[i][j] == 0){
                            matriz[i][j] = numero;
                        }
                    }
                }
                contador++;
                break;
            }

        }

        if (contador == pares){

            break;
        }


    }

}

int MatrizPaginada::GenerarNumero() {

    /*
     * Genera un numero aleatorio entre 1 y 2, para revisar si se repite o no
     *
     * @return: numero aleatorio entre 1 y 2
     */

    int numero;
    srand(time(NULL));

    while (true) {
        numero = rand() % 33 + 1;


        if(VerificarMatriz(numero)){
            break;
        }

    }

    return numero;

}

bool MatrizPaginada::VerificarMatriz(int numero) {

    /*
     * Verifica si el numero ya existe en la matriz
     *
     * @param numero: numero a verificar
     * @return: true si el numero ya existe en la matriz, false si no existe
     */
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == numero) {
                return false;
            }
        }
    }
    return true;

}

void MatrizPaginada::ImprimirMatriz() {

    /*
     * Imprime la matriz
     */

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

}
void MatrizPaginada::LlenarMemoria() {

    /*
     * Llena la memoria con los valores de las tarjetas
     */

    srand(time(NULL));

    while (cantidadMaxima != cantidadActual){
        int numero = rand() % 33 + 1;

        if(VerificarMemoria(numero)){
            string ruta = archivador->ObtenerRuta(numero);
            enMemoria[cantidadActual].setRuta(ruta);
            enMemoria[cantidadActual].setId(numero);
            cantidadActual++;
        }
    }

}

bool MatrizPaginada::VerificarMemoria(int numero) {

    /*
     * Verifica si el numero ya existe en la memoria
     *
     * @param numero: numero a verificar
     * @return: true si el numero ya existe en la memoria, false si no existe
     */

    for (int i = 0; i < cantidadActual; i++) {
        if (enMemoria[i].getId() == numero) {
            return false;
        }
    }
    return true;
}

void MatrizPaginada::ImprimirMemoria() {

    /*
     * Imprime la memoria
     */

    for (int i = 0; i < cantidadActual; i++) {
        cout << i << endl;
        cout << enMemoria[i].getId() << " " << enMemoria[i].getRuta() << endl;
    }
}

int MatrizPaginada::ComprobarPareja(int i1, int j1, int i2, int j2) {

    /*
     * Comprueba si las parejas son iguales
     *
     * @param i1: fila de la primera pareja
     * @param j1: columna de la primera pareja
     * @param i2: fila de la segunda pareja
     * @param j2: columna de la segunda pareja
     * @return: 1 si las parejas son iguales, 0 si no son iguales
     */

    int posicion1 = matriz[i1][j1];
    int posicion2 = matriz[i2][j2];
    bool carta1 = ComprobarMemoria(posicion1);
    bool carta2 = ComprobarMemoria(posicion2);

    int puntaje = 0;

    if (carta1 && carta2){
        Tarjetas *tarjeta1 = GetEnMemoria(posicion1);
        Tarjetas *tarjeta2 = GetEnMemoria(posicion2);

        this->hits += 2;

        if (tarjeta1->getId() == tarjeta2->getId()){

            cantidadActual -= 1;
            cantidadMaxima -= 1;
            puntaje += 2;
        }

    } else if (not carta1 &&  carta2){

        int ocupado = GetPosicionMemoria(posicion2);
        CargarEnMemoria(posicion1, ocupado);
        Tarjetas *tarjeta1 = GetEnMemoria(posicion1);
        Tarjetas *tarjeta2 = GetEnMemoria(posicion2);

        this->faults++;
        this->hits++;

        if (tarjeta1->getId() == tarjeta2->getId()){
            cantidadActual -= 1;
            cantidadMaxima -= 1;
            puntaje += 1;
        }

    } else if (carta1 && not carta2){

        int ocupado = GetPosicionMemoria(posicion1);
        CargarEnMemoria(posicion2, ocupado);
        Tarjetas *tarjeta1 = GetEnMemoria(posicion1);
        Tarjetas *tarjeta2 = GetEnMemoria(posicion2);

        this->faults++;
        this->hits++;

        if (tarjeta1->getId() == tarjeta2->getId()){
            cantidadActual -= 1;
            cantidadMaxima -= 1;
            puntaje += 1;
        }

    } else {

        CargarEnMemoria(posicion1, -1);
        CargarEnMemoria(posicion2, 0);
        Tarjetas *tarjeta1 = GetEnMemoria(posicion1);
        Tarjetas *tarjeta2 = GetEnMemoria(posicion2);

        this->faults += 2;

        if (tarjeta1->getId() == tarjeta2->getId()){
            cantidadActual -= 1;
            cantidadMaxima -= 1;
            puntaje += 1;
        }

    }

    if (puntaje != 0){
        matriz[i1][j1] = -1;
        matriz[i2][j2] = -1;
        ResetCantidadActual();
        LlenarMemoria();
    }

    return puntaje;


}

bool MatrizPaginada::ComprobarMemoria(int numero) {

    /*
     * Comprueba si el numero esta en la memoria
     *
     * @param numero: numero a verificar
     * @return: true si el numero esta en la memoria, false si no esta
     */

    for (int i = 0; i < cantidadActual; i++) {
        if (enMemoria[i].getId() == numero) {
            return true;
        }
    }
    return false;
}

Tarjetas* MatrizPaginada::GetEnMemoria(int numero) {

    /*
     * Obtiene la tarjeta de la memoria
     *
     * @param numero: numero de la tarjeta
     * @return: la tarjeta
     */


    for (int i = 0; i < cantidadActual; i++) {

        if (enMemoria[i].getId() == numero) {
            return &enMemoria[i];
        }
    }
    return nullptr;
}

int MatrizPaginada::GetPosicionMemoria(int numero) {

    /*
     * Obtiene la posicion de la tarjeta en la memoria
     *
     * @param numero: numero de la tarjeta
     * @return: la posicion de la tarjeta en la memoria
     */

    for (int i = 0; i < cantidadActual; i++) {
        if (enMemoria[i].getId() == numero) {
            return i;
        }
    }
    return -1;
}

void MatrizPaginada::CargarEnMemoria(int id, int ocupado) {

    /*
     * Carga una tarjeta en la memoria
     *
     * @param id: numero de la tarjeta
     * @param ocupado: posicion de la tarjeta en la memoria
     */

    int posLibre = BuscarEspacioEnMemoria(ocupado);

    if(posLibre != -1){
        enMemoria[posLibre].setId(id);
        enMemoria[posLibre].setRuta(archivador->ObtenerRuta(id));
    }

}

int MatrizPaginada::BuscarEspacioEnMemoria(int ocupado) {

    /*
     * Busca un espacio en la memoria
     *
     * @param ocupado: posicion de la tarjeta en la memoria
     * @return: la posicion del espacio libre
     */


    for (int i = 0; i < cantidadActual; i++) {
        if (i != ocupado) {
            return i;
        }
    }

    return -1;

}

string MatrizPaginada::BuscarRuta(int i, int j) {

    /*
     * Busca la ruta de la tarjeta
     *
     * @param i: fila de la matriz
     * @param j: columna de la matriz
     * @return: la ruta de la tarjeta
     */

    int posicion = matriz[i][j];
    bool cargada = ComprobarMemoria(posicion);

    if (cargada){
        this->hits++;
        Tarjetas *tarjeta = GetEnMemoria(posicion);
        MostrarMemoria();
        return tarjeta->getRuta();
    } else {
        CargarEnMemoria(posicion, -1);
        this->faults++;
        Tarjetas *tarjeta = GetEnMemoria(posicion);
        MostrarMemoria();
        return tarjeta->getRuta();
    }

}

bool MatrizPaginada::VerificarSiGano() {

    /*
     * Verifica si gano
     *
     * @return: true si gano, false si no
     */

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != -1) {
                return false;
            }
        }
    }

    return true;

}

int MatrizPaginada::GetMemoriaOcupada() {
    return 412 * cantidadActual;
}

int MatrizPaginada::GetMemoriaTotal() {
    return 412 * cantidadMaxima;
}

int MatrizPaginada::GetFaults() {
    return this->faults;
}

int MatrizPaginada::GetHits() {
    return this->hits;
}

void MatrizPaginada::MostrarMemoria() {

    /*
     * Muestra la memoria
     */

    cout << endl;

    cout << "Total de hits: " << this->hits << endl;
    cout << "Total de faults: " << this->faults << endl;

    cout << endl;

    cout << "Cartas Cargadas: " << endl;

    for (int i = 0; i < cantidadActual; i++) {
        cout << "identificador " << enMemoria[i].getId() << endl;
        cout << "ruta " << enMemoria[i].getRuta() << endl;

    }

    cout << endl;

    cout << "Cartas en disco: " << endl;

    json j = archivador->CargarJson();

    for (int i = 1; i < 34; i++) {

        if(!ComprobarMemoria(i)){
            cout << "identificador "<< i << endl;
            cout << "ruta " << j[to_string(i)] << endl;
        }

    }

    int mem = 0;

    for (int i = 0; i < cantidadActual; i++) {
        mem += enMemoria[i].espacioUsado() + 412;
    }

    cout << endl;

    cout << "Espacio de memoria total en bytes: " << GetMemoriaTotal() + 412 << endl;
    cout << "Espacio de memoria ocupado en bytes: " << mem<< endl;


}

void MatrizPaginada::ResetCantidadActual() {

    /*
     * Resetea la cantidad actual de tarjetas
     */

    this->cantidadActual = 0;

}