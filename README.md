# Frac


Este proyecto busca crear un render basico del Mandelbrot set.
Para aprender mas sobre el Mandelbrot set puedes verificar la pagina de WikiPedia:
- https://en.wikipedia.org/wiki/Mandelbrot_set

Pasos para crear imagen:
1. se crea la funcion de Mandelbrot:
    - en este caso se llama `mandelbrot_func`.
2. se crea un canvas
    - encima de este canvas se creara la imagen.
3. para crear la imagen se utiliza un metodo llamado `construct`.
4. Finalmente, para guardar el archivo tenemos que llamar la funcion `save_to_ppm`.
