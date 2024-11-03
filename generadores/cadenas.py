def generar_archivo_cadenas(nombre_archivo, casos_prueba):
    with open(nombre_archivo, 'w') as archivo:
        # recorre cada combinacion de cadenas
        for i in range(len(casos_prueba)):
            for j in range(len(casos_prueba)):
                archivo.write(f'["{casos_prueba[i][0]}", "{casos_prueba[j][1]}"]\n')

casos = [
    ("", ""), 
    ("hola", "mundo"), 
    ("kiwi", "whisky"),
    ("xilo", "xilofono"),
    ("cada", "casa"),
    ("feliz", "felix"), 
    ("que", "so"),
    ("jalar", "jaalr"),
    ("abcdario", "acbdairo"),
    ("blanco", "balcon"),
    ("mish", "mish"), 
    ("reventar", "tomate"), 
    ("ay", "ya"),
]


nombre = "res/cadenas.txt"
generar_archivo_cadenas(nombre, casos)