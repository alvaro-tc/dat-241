# Realice el cálculo de Fibonacci con Multiprocessing de al menos 1000 términos divididos por procesador de manera dinámica.
import multiprocessing

# Función para calcular el término de Fibonacci utilizando la fórmula explícita
def fibonacci(n):
    phi = (1 + 5 ** 0.5) / 2
    return int(round(phi ** n / 5 ** 0.5))

if __name__ == '__main__':
    num_terms = 1000  # Número de términos de Fibonacci a calcular
    num_processes = multiprocessing.cpu_count()  

    terminos_por_procesador = num_terms // num_processes 
    terminos_adicionales = num_terms % num_processes  


    pool = multiprocessing.Pool(processes=num_processes)

    results = []

 
    for i in range(num_processes):
        start = i * terminos_por_procesador + min(i, terminos_adicionales)
        end = start + terminos_por_procesador + (1 if i < terminos_adicionales else 0)
        result = pool.map(fibonacci, range(start, end))
        results.extend(result)


    pool.close()
    pool.join()

  
    for i, result in enumerate(results):
        print("Término", i, ":", result)