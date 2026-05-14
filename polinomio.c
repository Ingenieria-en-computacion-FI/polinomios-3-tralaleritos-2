//Equipo Tralaleritos, Enrique, German, Ena, NAndo. -__- 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "polinomio.h"

Polinomio* crearPolinomio() {
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));
    if (p != NULL) {
        p->cabeza = NULL;
        p->cola = NULL;
    }
    return p;
}

void destruirPolinomio(Polinomio* p) {
    if (p == NULL) return;
    Nodo* actual = p->cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(p);
}

void eliminarNodo(Polinomio* p, Nodo* actual) {
    if (actual->anterior != NULL) {
        actual->anterior->siguiente = actual->siguiente;
    } else {
        p->cabeza = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        actual->siguiente->anterior = actual->anterior;
    } else {
        p->cola = actual->anterior;
    }

    free(actual);
}

void insertarTermino(Polinomio* p, float coef, int exp) {
    if (coef == 0.0f) return;

    Nodo* actual = p->cabeza;
    
    while (actual != NULL && actual->termino.exponente > exp) {
        actual = actual->siguiente;
    }

    if (actual != NULL && actual->termino.exponente == exp) {
        actual->termino.coeficiente += coef;
        
        if (actual->termino.coeficiente == 0.0f) {
            eliminarNodo(p, actual);
        }
        return;
    }

    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->termino.coeficiente = coef;
    nuevo->termino.exponente = exp;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    if (p->cabeza == NULL) { 
        p->cabeza = nuevo;
        p->cola = nuevo;
    } else if (actual == p->cabeza) { 
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
    } else if (actual == NULL) { 
        p->cola->siguiente = nuevo;
        nuevo->anterior = p->cola;
        p->cola = nuevo;
    } else { 
        nuevo->siguiente = actual;
        nuevo->anterior = actual->anterior;
        actual->anterior->siguiente = nuevo;
        actual->anterior = nuevo;
    }
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* suma = crearPolinomio();
    
    Nodo* actual = p1->cabeza;
    while (actual != NULL) {
        insertarTermino(suma, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }
    
    actual = p2->cabeza;
    while (actual != NULL) {
        insertarTermino(suma, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }
    
    return suma;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* mult = crearPolinomio();
    
    Nodo* n1 = p1->cabeza;
    while (n1 != NULL) {
        Nodo* n2 = p2->cabeza;
        while (n2 != NULL) {
            float nuevoCoef = n1->termino.coeficiente * n2->termino.coeficiente;
            int nuevoExp = n1->termino.exponente + n2->termino.exponente;
            insertarTermino(mult, nuevoCoef, nuevoExp);
            n2 = n2->siguiente;
        }
        n1 = n1->siguiente;
    }
    
    return mult;
}

float evaluarPolinomio(Polinomio* p, float x) {
    float res = 0.0f;
    Nodo* actual = p->cabeza;
    while (actual != NULL) {
        res += actual->termino.coeficiente * pow(x, actual->termino.exponente);
        actual = actual->siguiente;
    }
    return res;
}

char* polinomioToString(Polinomio* p) {
    if (p == NULL || p->cabeza == NULL) {
        char* str = (char*)malloc(2);
        strcpy(str, "0");
        return str;
    }

    char buffer[1024] = "";
    Nodo* actual = p->cabeza;
    
    while (actual != NULL) {
        char termStr[64] = "";
        float c = actual->termino.coeficiente;
        int e = actual->termino.exponente;

        if (c > 0 && actual != p->cabeza) {
            strcat(buffer, "+");
        }
        
        if (e == 0) {
            snprintf(termStr, sizeof(termStr), "%g", c);
        } else if (e == 1) {
            snprintf(termStr, sizeof(termStr), "%gx", c);
        } else {
            snprintf(termStr, sizeof(termStr), "%gx^%d", c, e);
        }
        
        strcat(buffer, termStr);
        actual = actual->siguiente;
    }
    
    char* resultado = (char*)malloc(strlen(buffer) + 1);
    strcpy(resultado, buffer);
    return resultado;
}
