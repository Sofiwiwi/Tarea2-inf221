import random
import string

def constante_matriz():
    letras = list(string.ascii_lowercase)
    tamaño = len(letras)
    matriz = [[1 for j in range(tamaño)] for i in range(tamaño)]
    return letras, matriz

def constante_tabla():
    letras = list(string.ascii_lowercase)
    tamaño = len(letras)
    valores = [1 for i in range(tamaño)]
    return letras, valores

def generar_tabla():
    letras = list(string.ascii_lowercase)
    tamaño = len(letras)
    valores = []
    for i in range(tamaño):
        valor = random.randint(1, 9)
        valores.append(valor)
    return letras, valores

def generar_matriz_simetrica():
    # Definir el tamaño de la matriz y las letras del abecedario
    letras = list(string.ascii_lowercase)
    tamaño = len(letras)
    matriz = [[0 if i == j else None for j in range(tamaño)] for i in range(tamaño)]
    for i in range(tamaño):
        for j in range(i + 1, tamaño):
            valor = random.randint(1, 9)
            matriz[i][j] = valor
            matriz[j][i] = valor
    return letras, matriz

def guardar_matriz_en_archivo(letras, matriz, nombre_archivo):
    with open(nombre_archivo, "w") as archivo:
        for i, letra in enumerate(letras):
            fila = [str(matriz[i][j]) for j in range(len(letras))]
            # sólo escribir los valores de la fila
            if i == len(letras) - 1:
                archivo.write(f"{' '.join(fila)}")
                break
            archivo.write(f"{' '.join(fila)}\n")


def guardar_tabla_en_archivo(letras, valores, nombre_archivo):
    with open(nombre_archivo, "w") as archivo:
        for i in range(len(letras)):
            if i == len(letras) - 1:
                archivo.write(f"{letras[i]} {valores[i]}")
                break
            archivo.write(f"{letras[i]} {valores[i]}\n")


# Generar la matriz y guardarla en un archivo
letras, matriz = constante_matriz()
guardar_matriz_en_archivo(letras, matriz, "res/costos_const_st.txt")

letras, valores = constante_tabla()
guardar_tabla_en_archivo(letras, valores, "res/costos_const_id.txt")

letras, matriz = generar_matriz_simetrica()
guardar_matriz_en_archivo(letras, matriz, "res/cost_replace.txt")

letras, matriz = generar_matriz_simetrica()
guardar_matriz_en_archivo(letras, matriz, "res/cost_transpose.txt")

letras, valores = generar_tabla()
guardar_tabla_en_archivo(letras, valores, "res/cost_delete.txt")

letras, valores = generar_tabla()
guardar_tabla_en_archivo(letras, valores, "res/cost_insert.txt")
