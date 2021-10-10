/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 10 de octubre de 2021, 12:12 PM
 * 
 * PUNTEROS MULTIPLES
 */

#include "FuncionesEx01_20202_Preg02.h"

int main(int argc, char** argv) {
    
    char **clientes, ***strProductos;
    int ***intProductos;
    
    leerDatos(clientes, intProductos, strProductos);
    imprimirDatos(clientes, intProductos, strProductos);
    return 0;

}

