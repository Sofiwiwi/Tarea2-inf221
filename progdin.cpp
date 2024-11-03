#include "lec_cos.h"

Resultado distancia_minima_prog_din(string s1, string s2){
    int m = s1.size();
    int n = s2.size();

    vector<vector<Resultado>> dp(m + 1, vector<Resultado>(n + 1, {0, {}}));

    for (int i = 1; i <= m; i++) {
        dp[i][0].costo = dp[i - 1][0].costo + costo_del(s1[i - 1]);
        dp[i][0].operaciones = dp[i - 1][0].operaciones;
        dp[i][0].operaciones.push_back("Costo de eliminar '" + string(1, s1[i - 1]) + "': " + to_string(costo_del(s1[i - 1])));
    }
    for (int j = 1; j <= n; j++) {
        dp[0][j].costo = dp[0][j - 1].costo + costo_ins(s2[j - 1]);
        dp[0][j].operaciones = dp[0][j - 1].operaciones;
        dp[0][j].operaciones.push_back("Costo de insertar '" + string(1, s2[j - 1]) + "': " + to_string(costo_ins(s2[j - 1])));
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            Resultado sustitucion = dp[i - 1][j - 1];
            if (s1[i - 1] != ' ' && s2[j - 1] != ' ') { 
                sustitucion.costo += costo_sub(s1[i - 1], s2[j - 1]);
                if (s1[i - 1] != s2[j - 1]) {
                    sustitucion.operaciones.push_back("Costo de sustituir '" + string(1, s1[i - 1]) + "' por '" + string(1, s2[j - 1]) + "': " + to_string(costo_sub(s1[i - 1], s2[j - 1])));
                }
            } else {
                sustitucion.costo = INT_MAX; 
            }
            Resultado insercion = dp[i][j - 1];
            insercion.costo += costo_ins(s2[j - 1]);
            insercion.operaciones.push_back("Costo de insertar '" + string(1, s2[j - 1]) + "': " + to_string(costo_ins(s2[j - 1])));
            Resultado eliminacion = dp[i - 1][j];
            eliminacion.costo += costo_del(s1[i - 1]);
            eliminacion.operaciones.push_back("Costo de eliminar '" + string(1, s1[i - 1]) + "': " + to_string(costo_del(s1[i - 1])));
            Resultado transposicion = {INT_MAX, {}};
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                transposicion = dp[i - 2][j - 2];
                transposicion.costo += costo_trans(s1[i - 2], s1[i - 1]);
                transposicion.operaciones.push_back("Costo de transponer '" + string(1, s1[i - 2]) + "' y '" + string(1, s1[i - 1]) + "': " + to_string(costo_trans(s1[i - 2], s1[i - 1])));
            }
            dp[i][j] = transposicion;
            if (insercion.costo < dp[i][j].costo) dp[i][j] = insercion;
            if (eliminacion.costo < dp[i][j].costo) dp[i][j] = eliminacion;
            if (sustitucion.costo < dp[i][j].costo) dp[i][j] = sustitucion;
        }
    }
    return dp[m][n];
}

int main() {
    int opcion;
    cout << "Programación dinámica" << endl;
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
    procesar_archivo_cadenas("generadores/res/cadenas_random.txt", "generadores/salida_pd.txt", distancia_minima_prog_din);
    cout << "Diríjase a generadores/salida_pd.txt para ver los resultados" << endl;
    return 0;
}