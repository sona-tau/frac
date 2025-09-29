# Frac

Este proyecto busca crear un una imagen del Mandelbrot set. Hay informacion buena en:
- https://en.wikipedia.org/wiki/Mandelbrot_set

## Compilar

Pasos para crear imagen:
1. Crear una funcion para generar la imagen, en este caso: `mandelbrot_func`.
2. Crear un canvas.
3. Pasar `mandelbrot_func` al metodo `construct` del canvas.
4. Guardar canvas a un archivo, con `save_to_ppm`.

 ## Formato

 La imagen que genera es de formato `ppm`. Para mas informacion, visitar:
 - https://en.wikipedia.org/wiki/Netpbm
