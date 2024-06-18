import cv2
import numpy as np
import scipy.sparse as sp
import multiprocessing as mp
from numba import jit

def image_to_sparse_matrix(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if image is None:
        raise ValueError(f"Image at path '{image_path}' could not be loaded.")
    image_array = np.array(image, dtype=np.float64)
    sparse_matrix = sp.coo_matrix(image_array)
    return sparse_matrix.tocsc()

def save_sparse_matrix_to_file(sparse_matrix, file_path):
    """
    Guarda una matriz dispersa en un archivo de texto.
    """
    # Convertir la matriz dispersa a formato COO
    sparse_matrix = sparse_matrix.tocoo()
    
    with open(file_path, 'w') as file:
        # Escribir los valores no nulos
        for i, j, value in zip(sparse_matrix.row, sparse_matrix.col, sparse_matrix.data):
            file.write(f"{i} {j} {value}\n")

# Convertir y guardar las imágenes en archivos de texto
sparse_matrix1 = image_to_sparse_matrix('1a.png')
save_sparse_matrix_to_file(sparse_matrix1, '1.txt')

sparse_matrix2 = image_to_sparse_matrix('2a.png')
save_sparse_matrix_to_file(sparse_matrix2, '2.txt')
