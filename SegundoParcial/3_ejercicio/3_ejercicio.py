import cv2              
import numpy as np      

img1 = cv2.imread('1.png')
img2 = cv2.imread('2.png')


res1 = cv2.resize(img1, (300, 300), interpolation=cv2.INTER_CUBIC)
res2 = cv2.resize(img2, (300, 300), interpolation=cv2.INTER_CUBIC)
suma_final = cv2.add(res1, res2)


cv2.imshow('Imagen final suma', suma_final)
cv2.waitKey(0)
cv2.destroyAllWindows()

resta1 = cv2.subtract(res1, res2)
resta2 = cv2.subtract(res2, res1)
resta = cv2.add(resta1, resta2)

# Mostrar las imágenes
cv2.imshow('Imagen final resta', resta)
cv2.waitKey(0)
cv2.destroyAllWindows()