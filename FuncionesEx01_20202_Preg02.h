/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesEx01_20202_Preg02.h
 * Author: jhenn
 *
 * Created on 10 de octubre de 2021, 12:55 PM
 */

#ifndef FUNCIONESEX01_20202_PREG02_H
#define FUNCIONESEX01_20202_PREG02_H

#include <iostream>        
#include <fstream>
using namespace std;

void imprimirLinea(ofstream &, char, int);
void leerDatos(char **&clientes, int ***&intProductos, char*** &strProductos);
char* leerTienda(ifstream &arch);
void leerProductosTienda(ifstream &arch, int ** &productoTienda, char **&nombreProdTienda);
void incrementarMemoriaTienda_intProductos_StrProductos(char **&clientes,
        int ***&intProductos, char ***&strProductos, int &numClientes, int &cap);
void incrementarMemoriaProductos(int ** &productoTienda, char **&nombreProdTienda, int &numProd, int cap);
int buscarProducto(int **productoTienda, int rCod, int numProd);
int * guardarCodCantProducto(int rCod, int rCant);
char* guardarNombreProducto(char *rNombre);
void  mostrarDatos(char **clientes, int***intProductos, char***strProductos);
void  mostrarDatosUnProducto( int* intProd, char* strProductos);

void  imprimirDatos(char **clientes, int ***intProductos, char***strProductos);
void ordenarProductosPorCantidad(int **intProductos);
void quickSortProdCantidad(int ** intProductos,int ini, int fin);
int compararCantidad(int * productoI, int * productoJ);
void intercambiar(int ** intProductos, int i, int j);

void imprimirProductos( ofstream &arch, int **intProdClien, char** strProductos);

#endif /* FUNCIONESEX01_20202_PREG02_H */
