import cv2
import numpy as np
import scipy.sparse as sp
import matplotlib.pyplot as plt

def image_to_sparse_matrix(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    image_array = np.array(image)
    sparse_matrix = sp.coo_matrix(image_array)
    return sparse_matrix

sparse_matrix1 = image_to_sparse_matrix('1.png')
sparse_matrix2 = image_to_sparse_matrix('2.png')

plt.figure(figsize=(10, 10), facecolor='black')

plt.subplot(2, 2, 1)
plt.title('Matriz dispersa de la Imagen 1')
plt.spy(sparse_matrix1, markersize=1, color='white')
plt.axis('off')

plt.subplot(2, 2, 2)
plt.title('Matriz dispersa de la Imagen 2')
plt.spy(sparse_matrix2, markersize=1, color='white')
plt.axis('off')

plt.tight_layout()
plt.show()
print("Esta es la matriz sparce 1")
print(sparse_matrix1)
print("Esta es la matriz sparce 2")
print(sparse_matrix2)