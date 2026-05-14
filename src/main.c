// Trabajo tralaleritos Enrique, German,Ena, Nando. -__-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polinomio.h"


void ejecutarPrueba(const char* nombrePrueba, Polinomio* p, const char* resultadoEsperado) {
    char* resultadoActual = polinomioToString(p);
    printf("=== %s ===\n", nombrePrueba);
    printf("Obtenido : %s\n", resultadoActual);
    printf("Esperado : %s\n", resultadoEsperado);
    
    if (strcmp(resultadoActual, resultadoEsperado) == 0) {
        printf("ESTADO   : [EXITO]\n\n");
    } else {
        printf("ESTADO   : [FALLO]\n\n");
    }
    
    free(resultadoActual); 
}

int main() {
    printf("***************************************************\n");
    printf("*  Probador de Polinomios  *\n");
    printf("***************************************************\n\n");

// Para crear un poolinomio vacio
    Polinomio* p_vacio = crearPolinomio();
    ejecutarPrueba("CASO 1: Crear un polinomio vacio", p_vacio, "0");
    destruirPolinomio(p_vacio);

  // Inserccion y ordenar ow.
    Polinomio* p_orden = crearPolinomio();
    insertarTermino(p_orden, 1, 0);
    insertarTermino(p_orden, 3, 2);
    insertarTermino(p_orden, 2, 1); 
    ejecutarPrueba("CASO 2: Insercion en orden descendente", p_orden, "3x^2+2x+1");
    destruirPolinomio(p_orden);

    //Simplificar y  hacer una eliminacion automatica
    Polinomio* p_simp = crearPolinomio();
    insertarTermino(p_simp, 3, 2);  
    insertarTermino(p_simp, -3, 2); 
    insertarTermino(p_simp, 5, 3);  
    ejecutarPrueba("CASO 3: Simplificacion y eliminacion de coeficientes cero", p_simp, "5x^3");
    destruirPolinomio(p_simp);

    //Sumar los polinomios ahi.
    Polinomio* p1_suma = crearPolinomio();
    Polinomio* p2_suma = crearPolinomio();
    insertarTermino(p1_suma, 3, 2);
    insertarTermino(p1_suma, 2, 1);
    insertarTermino(p1_suma, 1, 0);
    
    insertarTermino(p2_suma, 1, 2);
    insertarTermino(p2_suma, 4, 0);
    
    Polinomio* res_suma = sumarPolinomios(p1_suma, p2_suma);
    ejecutarPrueba("CASO 4: Suma de polinomios (3x^2+2x+1) + (x^2+4)", res_suma, "4x^2+2x+5");
    
    destruirPolinomio(p1_suma);
    destruirPolinomio(p2_suma);
    destruirPolinomio(res_suma);

    //Multiplicar los polinomios
    Polinomio* p1_mult = crearPolinomio();
    Polinomio* p2_mult = crearPolinomio();
    insertarTermino(p1_mult, 1, 1);
    insertarTermino(p1_mult, 1, 0); 
    
    insertarTermino(p2_mult, 1, 1); 
    insertarTermino(p2_mult, -1, 0);
    
    Polinomio* res_mult = multiplicarPolinomios(p1_mult, p2_mult);
    ejecutarPrueba("CASO 5: Multiplicacion de binomios conjugados (x+1)*(x-1)", res_mult, "1x^2-1");
    
    destruirPolinomio(p1_mult);
    destruirPolinomio(p2_mult);
    destruirPolinomio(res_mult);

    //Evaluacion Numerica de los polinomios kar
    Polinomio* p_eval = crearPolinomio();
    insertarTermino(p_eval, 3, 2); 
    insertarTermino(p_eval, 2, 1); 
    insertarTermino(p_eval, 1, 0); 
    
    float x = 2.0;
    float res_eval = evaluarPolinomio(p_eval, x); 
    
    printf("=== CASO 6: Evaluacion Numerica ===\n");
    printf("Polinomio : 3x^2+2x+1\n");
    printf("Eval en x : %g\n", x);
    printf("Obtenido  : %g\n", res_eval);
    printf("Esperado  : 17\n");
    if (res_eval == 17.0f) {
        printf("ESTADO    : [EXITO]\n\n");
    } else {
        printf("ESTADO    : [FALLO]\n\n");
    }
    
    destruirPolinomio(p_eval);

    printf("***************************************************\n");
    printf("*  Finalizamos todsas las puebas!!!!                  *\n");
    printf("***************************************************\n");

    return 0;
}
