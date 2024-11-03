// lec_cos.h
#ifndef LEC_COS_H
#define LEC_COS_H

#include <bits/stdc++.h>
using namespace std;

struct CostData {
    int costo_ins;
    int costo_del;
    unordered_map<char, int> costo_sub;
    unordered_map<char, int> costo_trans;
};

struct Resultado {
    int costo;
    vector<string> operaciones;
};

extern unordered_map<char, CostData> costos;

void matriz_costos(const string& archivo, char tipo_costo);
void tabla_costos(const string& archivo, char tipo_costo);

int costo_sub(char a, char b);
int costo_ins(char b);
int costo_del(char a);
int costo_trans(char a, char b);

void procesar_archivo_cadenas(string nombre_archivo, string nombre_salida, Resultado (*calcular_distancia)(string, string));

#endif
