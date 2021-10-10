/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/* 
 * File:   FuncionesEx01_20202_Preg02.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 10 de octubre de 2021, 12:55 PM
 */

#include "FuncionesEx01_20202_Preg02.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
#include <cstring>  
#define INCREMENTO 5
using namespace std;

void imprimirLinea(ofstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void  leerDatos(char ** &clientes,  int ***&intProductos,char*** &strProductos){
    
    ifstream arch("pedidos.csv", ios::in);
    if(!arch){
        cout<<"No se puede abrir el archivo"<<endl;
        exit(1);
    }
    
    int cap=0,numClientes=0;
    clientes= nullptr; 
    
    int ** aux_productoTienda;
    char** aux_nombreProdTienda;
    char * aux_nombreTienda;
    
    while(1){
        aux_nombreTienda= leerTienda(arch);
        if(aux_nombreTienda== nullptr) break;
        leerProductosTienda(arch, aux_productoTienda, aux_nombreProdTienda);
        
        if(numClientes== cap) 
            incrementarMemoriaTienda_intProductos_StrProductos(clientes,intProductos,strProductos, numClientes,cap);
        clientes[numClientes]= nullptr;  //terminador
        clientes[numClientes -1]= aux_nombreTienda;
        intProductos[numClientes -1] = aux_productoTienda;
        strProductos[numClientes -1]= aux_nombreProdTienda;
        numClientes++;
    }
    mostrarDatos(clientes, intProductos, strProductos);
}

void  mostrarDatos(char **clientes, int***intProductos, char***strProductos){
    
    for(int i=0; clientes[i]!= nullptr; i++){
        cout<<endl<<left<<"Cliente:"<<clientes[i]<<endl;
        if(intProductos[i]!= nullptr){ //si el cliente tiene algun producto
            for(int j=0; intProductos[i][j]!= nullptr; j++){
                mostrarDatosUnProducto(intProductos[i][j], strProductos[i][j]);  
            }
        }
    } 
}

void  mostrarDatosUnProducto( int* intProd, char* strProductos){
 
    cout<<setw(20)<<intProd[0]<<setw(20)<<intProd[1]<<strProductos<<endl; 
}

char* leerTienda(ifstream &arch){
    
    int cod;
    char* ptrNombre, nombre[100];
    
    arch>>cod;
    if(arch.eof()) return nullptr;
    arch.get(); //coma
    arch.getline(nombre, 100, ',');
    ptrNombre= new char[strlen (nombre) +1]; 
    strcpy(ptrNombre, nombre);   
    return ptrNombre;
}

void leerProductosTienda(ifstream &arch, int ** &productoTienda, char **&nombreProdTienda){
    
    int cap=0, numProd=0;
    productoTienda= nullptr;
    
    int dd,mm,aa, rCod, rCant;
    char c, rNombre[50];
       
    while(1){
        arch>>aa>>c>>mm>>c>>dd>>c;
        arch>>rCod;
        arch.get(); //coma
        arch.getline(rNombre, 50, ',');
        arch>>rCant;
        
        if(cap==numProd) incrementarMemoriaProductos(productoTienda, nombreProdTienda, numProd, cap);
        
        int pos=buscarProducto(productoTienda,rCod, numProd);
        if(pos!=-1){ //producto ya exite
            productoTienda[pos][1]+=rCant;
        }
        else{ //producto nuevo
            productoTienda[numProd]= nullptr;
            productoTienda[numProd -1]= guardarCodCantProducto(rCod,rCant);
            nombreProdTienda[numProd -1]= guardarNombreProducto(rNombre);
            numProd++;
        }
         if(arch.get()== '\n') break;
    }
}

void incrementarMemoriaTienda_intProductos_StrProductos(char **&clientes, 
        int ***&intProductos,char ***&strProductos, int &numClientes,int &cap){
    
    cap+= INCREMENTO;
    if(clientes== nullptr){
        clientes= new char*[cap];
        intProductos= new int**[cap];
        strProductos= new char**[cap];
        
        clientes[0]=nullptr; //terminador
        numClientes=1;
    }
    else{
        char**auxCliente=new char*[cap];
        int***auxIntProductos=new int**[cap];
        char***auxStrProductos=new char**[cap];
        
        for(int i=0; i<numClientes; i++){
            auxCliente[i]= clientes[i];
            auxIntProductos[i]= intProductos[i];
            auxStrProductos[i]= strProductos[i];    
        }
        delete clientes;
        delete intProductos;
        delete strProductos;
        clientes=auxCliente;
        intProductos=auxIntProductos;
        strProductos=auxStrProductos;   
    }
}

void  incrementarMemoriaProductos(int ** &productoTienda, char **&nombreProdTienda, int &numProd, int cap){
 
    cap+=INCREMENTO;
    
    if(productoTienda== nullptr){
        productoTienda= new int*[cap];
        nombreProdTienda= new char*[cap];
     
        productoTienda[0]= nullptr;
        numProd=1;
    }
    else{
        int **auxProdTienda= new int*[cap];
        char**auxNombrProduc=new char*[cap];
        for(int i=0; i<numProd; i++){
            auxProdTienda[i]= productoTienda[i];
            auxNombrProduc[i]=nombreProdTienda[i];
        }
        delete productoTienda;
        delete nombreProdTienda;
        productoTienda= auxProdTienda;
        nombreProdTienda= auxNombrProduc;
    }
    
}

int buscarProducto(int **productoTienda,int rCod, int numProd){  //tener en cuenta que ultimo dato(numProd-1) es un nullptro 
    
    for(int i=0; i<numProd-1; i++){ //solo tomo en cuenta hasta antes del dato del terminador
        if(rCod== productoTienda[i][0]){
            return i;
        }
    }
    return -1;
}

int * guardarCodCantProducto(int rCod,int rCant){
    
    int* ptrDatos;
    ptrDatos=new int[2];
    
    ptrDatos[0]= rCod;
    ptrDatos[1]= rCant;
    return ptrDatos;
    
}

char* guardarNombreProducto( char *rNombre){
    
    char*ptrNombre;
    
    ptrNombre= new char[strlen(rNombre) + 1];
    strcpy(ptrNombre, rNombre);
    return ptrNombre;
}

void  imprimirDatos(char **clientes, int ***intProductos, char***strProductos){
    
    ofstream arch("Reporte.txt", ios:: out);
    arch<<setw(50)<<"REPORTE DE ATENCION"<<endl;
    for(int i=0; clientes[i]!= nullptr; i++){
        arch<<left<<"Cliente: "<<clientes[i]<<endl;
        imprimirLinea(arch, '=', 150);
        if(intProductos[i]!= nullptr){ //si tiene productos el cliente
            arch<<right<<setw(20)<<"Cod. Producto"<<left<<setw(10)<<' '<<setw(70)<<"Producto"<<"Cant. Solicitada"<<endl;
            imprimirLinea(arch, '=', 150);
            ordenarProductosPorCantidad(intProductos[i]);
            imprimirProductos(arch, intProductos[i], strProductos[i]);
        } 
        
    }
}

void ordenarProductosPorCantidad(int **intProductos){
    int i;
    for(i=0; intProductos[i]!=nullptr; i++);
    
    quickSortProdCantidad(intProductos,0, i-1);
    
}

void quickSortProdCantidad(int ** intProductos,int ini, int fin){
    
    if(ini>= fin) return;
    
    int pivote= ini;
    for(int i=ini +1; i<=fin; i++){
        if(compararCantidad(intProductos[i], intProductos[ini]) >0 ){  //descendente
            pivote++;
            intercambiar(intProductos, i, pivote);
        }
    }
    
    intercambiar(intProductos, ini, pivote);
    quickSortProdCantidad(intProductos, ini,pivote -1);
    quickSortProdCantidad(intProductos, pivote +1,fin);
    
}

int compararCantidad(int * productoI, int * productoJ){
    
    return productoI[1] - productoJ[1]; //comparando cantidad 
    
}

void intercambiar(int ** intProductos, int i, int j){
    
    int* aux;
    aux= intProductos[i];
    intProductos[i]= intProductos[j];
    intProductos[j]= aux;
    
 }

void imprimirProductos( ofstream &arch, int **intProdClien, char** strProductos){
    for(int i=0 ; intProdClien[i]!= nullptr; i++){
        arch<<right<<setw(20)<<intProdClien[i][0]<<left<<setw(10)<<' '
                              <<setw(70)<<strProductos[i]<<' '<<right<<setw(5)<<intProdClien[i][1]<<endl;
    }
}
