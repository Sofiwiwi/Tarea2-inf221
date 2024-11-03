// lec_cos.cpp
#include "lec_cos.h"

unordered_map<char, CostData> costos;

void matriz_costos(const string& archivo, char tipo_costo) {
    ifstream file(archivo);
    if (!file) {
        cout << "Error al abrir el archivo " << archivo << endl;
        exit(1);
    }
    string linea;
    int fila = 0;
    while(getline(file, linea)){
        istringstream ss(linea);
        int valor;
        int col = 0;
        while(ss >> valor){
            char letra_fila = 'a' + fila;
            char letra_col = 'a' + col;
            if (tipo_costo == 's') {
                costos[letra_fila].costo_sub[letra_col] = valor;
                costos[letra_col].costo_sub[letra_fila] = valor;
            } else if (tipo_costo == 't') {
                costos[letra_fila].costo_trans[letra_col] = valor;
                costos[letra_col].costo_trans[letra_fila] = valor;
            }
            col++;
        }
        fila++;
    }
    file.close();
}


void tabla_costos(const string& archivo, char tipo_costo) {
    ifstream file(archivo);
    if (!file) {
        cout << "Error al abrir el archivo " << archivo << endl;
        exit(1);
    }
    string linea;
    vector<char> letras;

    while(getline(file, linea)) {
        istringstream ss(linea);
        char letra;
        ss >> letra;
        letras.push_back(letra);
        int valor;
        ss >> valor;
        if (tipo_costo == 'i') {
            costos[letra].costo_ins = valor;
        } else if (tipo_costo == 'd') {
            costos[letra].costo_del = valor;
        }
    }
    file.close();
}


int costo_sub(char a, char b) {
    if (a == b) return 0;
    return costos[a].costo_sub[b];
}

int costo_ins(char b) {
    return costos[b].costo_ins;
}

int costo_del(char a) {
    return costos[a].costo_del;
}

int costo_trans(char a, char b) {
    if (a == b) return 0;
    return costos[a].costo_trans[b];
}

void procesar_archivo_cadenas(string nombre_archivo, string nombre_salida, Resultado (*calcular_distancia)(string, string)) {
    ifstream archivo(nombre_archivo);
    ofstream salida(nombre_salida);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    if (!salida.is_open()) {
        cout << "Error al abrir el archivo de salida." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find("\"");
        size_t pos2 = linea.find("\"", pos1 + 1);
        size_t pos3 = linea.find("\"", pos2 + 1);
        size_t pos4 = linea.find("\"", pos3 + 1);

        string s1 = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string s2 = linea.substr(pos3 + 1, pos4 - pos3 - 1);

        auto inicio = chrono::high_resolution_clock::now();
        Resultado resultado = calcular_distancia(s1, s2);
        auto fin = chrono::high_resolution_clock::now();
        auto tiempo =abs( chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count());
        salida << "La distancia de edición mínima entre \"" << s1 << "\" y \"" << s2 << "\" es: " << resultado.costo << endl;
        salida << "Tiempo de ejecución: " << tiempo << " nanosegundos" << endl;
        salida << "Operaciones utilizadas: " << endl;
        for (const string& op : resultado.operaciones) {
            salida << op << endl;
        }
        salida << "----------------------" << endl;
    }

    archivo.close();
    salida.close();
}