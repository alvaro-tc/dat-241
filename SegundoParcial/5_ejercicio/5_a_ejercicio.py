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

@jit(nopython=True)
def multiply_row_by_column(row, sparse_matrix2_data, sparse_matrix2_indices, sparse_matrix2_indptr, result_row, n_cols):
    for col in range(n_cols):
        sum_val = 0.0
        for k in range(sparse_matrix2_indptr[col], sparse_matrix2_indptr[col + 1]):
            sum_val += row[sparse_matrix2_indices[k]] * sparse_matrix2_data[k]
        result_row[col] = sum_val

def worker(row, sparse_matrix2_data, sparse_matrix2_indices, sparse_matrix2_indptr, n_cols):
    result_row = np.zeros(n_cols, dtype=np.float64)
    multiply_row_by_column(row, sparse_matrix2_data, sparse_matrix2_indices, sparse_matrix2_indptr, result_row, n_cols)
    return result_row

def sparse_matrix_multiply_parallel(sparse_matrix1, sparse_matrix2):
    if sparse_matrix1.shape[1] != sparse_matrix2.shape[0]:
        raise ValueError("Number of columns in sparse_matrix1 must be equal to number of rows in sparse_matrix2 for multiplication.")
    
    sparse_matrix2 = sparse_matrix2.tocsc()
    sparse_matrix2_data = sparse_matrix2.data
    sparse_matrix2_indices = sparse_matrix2.indices
    sparse_matrix2_indptr = sparse_matrix2.indptr
    
    rows = [sparse_matrix1.getrow(i).toarray().flatten() for i in range(sparse_matrix1.shape[0])]
    n_cols = sparse_matrix2.shape[1]
    
    with mp.Pool(4) as pool:
        results = pool.starmap(worker, [(row, sparse_matrix2_data, sparse_matrix2_indices, sparse_matrix2_indptr, n_cols) for row in rows])
    
    result_matrix = np.vstack(results)
    
    return result_matrix

if __name__ == "__main__":
    # Ejemplo de uso
    sparse_matrix1 = image_to_sparse_matrix('1a.png')
    sparse_matrix2 = image_to_sparse_matrix('2a.png')

    result = sparse_matrix_multiply_parallel(sparse_matrix1, sparse_matrix2)
    print("Resultado de la multiplicación de matrices dispersas:")
    print(result)
