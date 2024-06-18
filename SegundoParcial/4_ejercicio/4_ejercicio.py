import cv2
import numpy as np
import scipy.sparse as sp
from numba import jit

def image_to_sparse_matrix(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if image is None:
        raise ValueError(f"Image at path '{image_path}' could not be loaded.")
    image_array = np.array(image, dtype=np.float64)
    sparse_matrix = sp.coo_matrix(image_array)
    return sparse_matrix.tocsc()

@jit(nopython=True)
def multiply_matrices(sparse_matrix1_data, sparse_matrix1_indices, sparse_matrix1_indptr,
                      sparse_matrix2_data, sparse_matrix2_indices, sparse_matrix2_indptr,
                      result, n_rows, n_cols):
    for row in range(n_rows):
        for i in range(sparse_matrix1_indptr[row], sparse_matrix1_indptr[row + 1]):
            col1 = sparse_matrix1_indices[i]
            val1 = sparse_matrix1_data[i]
            for j in range(sparse_matrix2_indptr[col1], sparse_matrix2_indptr[col1 + 1]):
                col2 = sparse_matrix2_indices[j]
                val2 = sparse_matrix2_data[j]
                result[row, col2] += val1 * val2

def sparse_matrix_multiply(sparse_matrix1, sparse_matrix2):
    if sparse_matrix1.shape[1] != sparse_matrix2.shape[0]:
        raise ValueError("Numero de columnas debe ser igual al numero de filas")
    sparse_matrix1 = sparse_matrix1.tocsr()
    sparse_matrix2 = sparse_matrix2.tocsc()
    result = np.zeros((sparse_matrix1.shape[0], sparse_matrix2.shape[1]), dtype=np.float64)
    multiply_matrices(sparse_matrix1.data, sparse_matrix1.indices, sparse_matrix1.indptr,
                      sparse_matrix2.data, sparse_matrix2.indices, sparse_matrix2.indptr,
                      result, sparse_matrix1.shape[0], sparse_matrix2.shape[1])
    
    return result

if __name__ == "__main__":
    # Ejemplo de uso
    sparse_matrix1 = image_to_sparse_matrix('1.png')
    sparse_matrix2 = image_to_sparse_matrix('2.png')

    result = sparse_matrix_multiply(sparse_matrix1, sparse_matrix2)
    print("Resultado de la multiplicación de matrices dispersas:")
    print(result)
