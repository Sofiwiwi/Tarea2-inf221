import random
import string

def generador_cadenas(minimo, maximo):
    letras = string.ascii_lowercase
    palabra = ''.join(random.choice(letras) for i in range(random.randint(minimo, maximo)))
    return palabra

def generar_par_trans(palabra, cantidad):
    palabra = list(palabra)
    longitud = len(palabra)
    t = 0
    if len(palabra) >= 2:
        while t < cantidad:
            indice = random.randint(0, longitud - 2)
            palabra[indice], palabra[indice+1] = palabra[indice+1], palabra[indice]
            t += 1
    return ''.join(palabra)

def generar_lista_cadenas(cantidad, minimo, maximo, primera, segunda, trans, mismo, corta, larga):
    palabras = []
    for i in range(cantidad):
        palabra = generador_cadenas(minimo, maximo)
        if primera:
            palabra = ""
            palabra2 = generador_cadenas(minimo, maximo)
        elif segunda:
            palabra2 = ""
        elif trans:
            cantidad2 = random.randint(2, 5)
            palabra2 = generar_par_trans(palabra, cantidad2)
        elif mismo:
            palabra2 = generador_cadenas(len(palabra), len(palabra))
        elif corta:
            # Genera una palabra más larga que 'palabra' para asegurarse de que tienen diferente tamaño
            palabra2 = generador_cadenas(len(palabra) + 1, maximo + 5)
        elif larga:
            # Genera una palabra más corta que 'palabra' para asegurarse de que tienen diferente tamaño
            max_length = max(1, len(palabra) - 1)
            palabra2 = generador_cadenas(1, max_length)
        l = [palabra, palabra2]
        palabras.append(l)
    return palabras

cantidad = 20

# la primera cadena vacía
palabras = generar_lista_cadenas(cantidad, 1, 10, True, False, False, False, False, False)
# la segunda cadena vacía
palabras += generar_lista_cadenas(cantidad, 1, 10, False, True, False, False, False, False)
# transposición necesaria
palabras += generar_lista_cadenas(cantidad, 2, 10, False, False, True, False, False, False)
# mismo largo
palabras += generar_lista_cadenas(cantidad, 1, 10, False, False, False, True, False, False)
# primera cadena más corta
palabras += generar_lista_cadenas(cantidad, 1, 10, False, False, False, False, True, False)
# segunda cadena más corta
palabras += generar_lista_cadenas(cantidad, 2, 10, False, False, False, False, False, True)

with open('res/cadenas_random.txt', 'w') as archivo:
    for i in range(len(palabras)):
        archivo.write(f'["{palabras[i][0]}", "{palabras[i][1]}"]\n')
