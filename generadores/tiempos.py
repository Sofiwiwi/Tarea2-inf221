def tiempo(archivo):
    f = open(archivo, 'r')
    c=0
    for line in f:
        if 'Tiempo' in line:
            c+=int(line.split()[-2])
    f.close()
    return c

print(tiempo('salida_bf.txt')*(10**-9))
print(tiempo('salida_pd.txt')*(10**-9))