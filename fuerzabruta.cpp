// fuerzabruta.cpp
#include "lec_cos.h"

Resultado FuerzaBruta(string S1, string S2, int i, int j) {
    Resultado resultado;
    if (i == S1.length() && j == S2.length()) {
        resultado.costo = 0;
        return resultado;
    }
    if (i == S1.length()) {
        resultado = FuerzaBruta(S1, S2, i, j + 1);
        resultado.costo += costo_ins(S2[j]);
        resultado.operaciones.push_back("Costo de insertar '" + string(1, S2[j]) + "': " + to_string(costo_ins(S2[j])));
        return resultado;
    }
    if (j == S2.length()) {
        resultado = FuerzaBruta(S1, S2, i + 1, j);
        resultado.costo += costo_del(S1[i]);
        resultado.operaciones.push_back("Costo de eliminar '" + string(1, S1[i]) + "': " + to_string(costo_del(S1[i])));
        return resultado;
    }

    // Sustitución
    Resultado sustitucion = FuerzaBruta(S1, S2, i + 1, j + 1);
    sustitucion.costo += costo_sub(S1[i], S2[j]);
    if (S1[i] != S2[j]) {
        sustitucion.operaciones.push_back("Costo de sustituir '" + string(1, S1[i]) + "' por '" + string(1, S2[j]) + "': " + to_string(costo_sub(S1[i], S2[j])));
    }

    // Inserción
    Resultado insercion = FuerzaBruta(S1, S2, i, j + 1);
    insercion.costo += costo_ins(S2[j]);
    insercion.operaciones.push_back("Costo de insertar '" + string(1, S2[j]) + "': " + to_string(costo_ins(S2[j])));

    // Eliminación
    Resultado eliminacion = FuerzaBruta(S1, S2, i + 1, j);
    eliminacion.costo += costo_del(S1[i]);
    eliminacion.operaciones.push_back("Costo de eliminar '" + string(1, S1[i]) + "': " + to_string(costo_del(S1[i])));

    // Transposición
    Resultado transposicion;
    transposicion.costo = INT_MAX;
    if (i + 1 < S1.length() && j + 1 < S2.length() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        transposicion = FuerzaBruta(S1, S2, i + 2, j + 2);
        transposicion.costo += costo_trans(S1[i], S1[i + 1]);
        transposicion.operaciones.push_back("Costo de transponer '" + string(1, S1[i]) + "' y '" + string(1, S1[i + 1]) + "': " + to_string(costo_trans(S1[i], S1[i + 1])));
    }

    // Encontrar el mínimo costo
    Resultado minimo = sustitucion;
    if (insercion.costo < minimo.costo) {
        minimo = insercion;
    }
    if (eliminacion.costo < minimo.costo) {
        minimo = eliminacion;
    }
    if (transposicion.costo < minimo.costo) {
        minimo = transposicion;
    }

    return minimo;
}
Resultado distancia_minima_edicion_fb(string s1, string s2) {
    return FuerzaBruta(s1, s2, 0, 0);
}

int main() {
    int opcion;
    cout << "Fuerza bruta" << endl;
    cout << "----------------------" << endl;
    cout << "Ingrese una opción: " << endl;
    cout << "1. Costos variables" << endl;
    cout << "2. Costos fijos" << endl;
    cin >> opcion;
    if (opcion == 1) {
        matriz_costos("generadores/res/cost_replace.txt", 's');
        tabla_costos("generadores/res/cost_insert.txt", 'i');
        tabla_costos("generadores/res/cost_delete.txt", 'd');
        matriz_costos("generadores/res/cost_transpose.txt", 't');
    } else {
        matriz_costos("generadores/res/costos_const_st.txt", 's');
        matriz_costos("generadores/res/costos_const_st.txt", 't');
        tabla_costos("generadores/res/costos_const_id.txt", 'i');
        tabla_costos("generadores/res/costos_const_id.txt", 'd');
    }
    procesar_archivo_cadenas("generadores/res/cadenas_random.txt", "generadores/salida_bf.txt", distancia_minima_edicion_fb);
    cout << "Diríjase a generadores/salida_bf.txt para ver los resultados" << endl;
    return 0;
}
