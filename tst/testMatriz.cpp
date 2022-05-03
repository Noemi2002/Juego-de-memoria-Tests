//
// Created by Noemí on 2/5/2022.
//

#include "gtest/gtest.h"
#include "Matrizáginada.h"

TEST(MatrizPaginadaTest, numeros) {
    //arrange
    //act
    //assert
    EXPECT_EQ (MatrizPaginada::GenerarNumero(),  1 || 2);
    //EXPECT_EQ (Formula::bla (10), 20);
    //EXPECT_EQ (Formula::bla (50), 100);
}

TEST(MatrizPaginadaTest, verificarValor) {
    //arrange
    //act
    //assert

    EXPECT_EQ (MatrizPaginada::VerificarMatriz(5),  true);
    EXPECT_EQ (MatrizPaginada::VerificarMatriz(770),  false);
    //EXPECT_EQ (Formula::bla (50), 100);
}


