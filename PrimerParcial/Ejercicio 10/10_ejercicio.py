# Genere la serie 2, 4, 6, 8, 10, 12, 14, 16, 18… en M vectores(procesadores) para N términos con Mutiprocessing.
import multiprocessing as mp

def generar_serie_pares(inicio, fin):
   serie = []
   for i in range(inicio, fin + 1):
      serie.append(2 * i)
   return serie

def main():
   # Definir el número de términos en la serie y el número de procesos (vectores)
   N = 36  # número de términos
   M = mp.cpu_count()  # número de procesos
   print(M)
   
   # Calcular cuántos términos le corresponden a cada proceso
   terminos_por_procesador = N // M

   # Iniciar los procesos
   pool = mp.Pool(processes=M)
   
   resultados = []
   for i in range(M):
      inicio = i * terminos_por_procesador + 1
      fin = (i + 1) * terminos_por_procesador if i < M - 1 else N
      resultados.append(pool.apply_async(generar_serie_pares, args=(inicio, fin)))
   # Recopilar los resultados de los procesos
   series = [resultado.get() for resultado in resultados]

   # Imprimir las series generadas por cada proceso
   for i, serie in enumerate(series):
      print(f"Serie del procesador {i}: {serie}")
      
   series_final = sum(series, [])

   print(series_final)
if __name__ == "__main__":
   main()
