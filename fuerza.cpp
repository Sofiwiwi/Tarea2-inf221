// fuerzabruta.cpp
#include "lec_cos.h"

Resultado min_dis_fb(string s1, string s2, int i, int j) {
    if (i == s1.size() && j == s2.size()) {
        return {0, {}};
    }
    if (i == s1.size()) {
        Resultado res = min_dis_fb(s1, s2, i, j + 1);
        res.costo += costo_ins(s2[j]);
        res.operaciones.push_back("Costo de insertar '" + string(1, s2[j]) + "': " + to_string(costo_ins(s2[j])));
        return res;
    }
    if (j == s2.size()) {
        Resultado res = min_dis_fb(s1, s2, i + 1, j);
        res.costo += costo_del(s1[i]);
        res.operaciones.push_back("Costo de eliminar '" + string(1, s1[i]) + "': " + to_string(costo_del(s1[i])));
        return res;
    }

    Resultado sustitucion;
    if (i < s1.size() && j < s2.size() && s1[i] != ' ' && s2[j] != ' ') { 
        sustitucion = min_dis_fb(s1, s2, i + 1, j + 1);
        sustitucion.costo += costo_sub(s1[i], s2[j]);
        if (costo_sub(s1[i], s2[j]) != 0)
            sustitucion.operaciones.push_back("Costo de sustituir '" + string(1, s1[i]) + "' por '" + string(1, s2[j]) + "': " + to_string(costo_sub(s1[i], s2[j])));
    } else {
        sustitucion = {INT_MAX, {}};
    }
    Resultado insercion = min_dis_fb(s1, s2, i, j + 1);
    insercion.costo += costo_ins(s2[j]);
    insercion.operaciones.push_back("Costo de insertar '" + string(1, s2[j]) + "': " + to_string(costo_ins(s2[j])));

    Resultado eliminacion = min_dis_fb(s1, s2, i + 1, j);
    eliminacion.costo += costo_del(s1[i]);
    eliminacion.operaciones.push_back("Costo de eliminar '" + string(1, s1[i]) + "': " + to_string(costo_del(s1[i])));

    Resultado transposicion = {INT_MAX, {}};
    // 
    if (i + 1 < s1.size() && j + 1 < s2.size() && s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
        transposicion = min_dis_fb(s1, s2, i + 2, j + 2);
        transposicion.costo += costo_trans(s1[i], s1[i + 1]);
        transposicion.operaciones.push_back("Costo de transponer '" + string(1, s1[i]) + "' y '" + string(1, s1[i + 1]) + "': " + to_string(costo_trans(s1[i], s1[i + 1])));
    }
    int minimo = min({sustitucion.costo, insercion.costo, eliminacion.costo, transposicion.costo});
    if (minimo == transposicion.costo) return transposicion;
    if (minimo == insercion.costo) return insercion;
    if (minimo == eliminacion.costo) return eliminacion;
    return sustitucion;
}

Resultado distancia_minima_edicion_fb(string s1, string s2) {
    return min_dis_fb(s1, s2, 0, 0);
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
