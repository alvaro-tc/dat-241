# Con mutiprocessing realizar el cálculo de PI
import multiprocessing

def calcular_pi(num_iteraciones, inicio, fin):
    pi_local = 0.0

    for i in range(inicio, fin):
        termino = 1 / (2 * i + 1)
        if i % 2 == 0:
            pi_local += termino
        else:
            pi_local -= termino

    return pi_local

if __name__ == '__main__':
    num_procesos = multiprocessing.cpu_count()  # Obtener el número de procesadores disponibles
    num_iteraciones = 1000000  # Número de iteraciones

    pool = multiprocessing.Pool(processes=num_procesos)  # Crear un grupo de procesos

    # Calcular el rango de iteraciones para cada proceso
    rango_iteraciones = num_iteraciones // num_procesos
    rangos = [(rango_iteraciones, i * rango_iteraciones, (i + 1) * rango_iteraciones) for i in range(num_procesos)]

    resultados = pool.starmap(calcular_pi, rangos)

    pi = sum(resultados) * 4  # Sumar los resultados de cada proceso y multiplicar por 4

    print("El valor aproximado de pi es:", pi)