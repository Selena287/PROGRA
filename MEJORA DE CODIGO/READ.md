MAURA SELENA VELASQUEZ ORTEGA. CARNE: 9941-24-14056. 
1) por qué cargar todos los clientes en memoria puede ser un problema: Porque puede agotar la memoria disponible.
   
2)por qué usar listas con búsqueda lineal no es eficiente: Mientras más datos hay, el tiempo crece de forma desproporcionada.

3)Qué estructura de datos sería más adecuada para agrupar campañas: seria HashMap<String, List<Cliente>> porque permite acceso directo por clave la cual seria el tipo de campaña.

4)cómo afecta el tamaño del JSON al consumo de memoria: Un JSON grande ocupa más espacio en RAM al cargarse, cada cliente del JSON se convierte en un objeto, JSONs con muchos campos generan más objetos internos.

El programa era ineficiente porque se volvia muy lento con grandes volúmenes de datos, repetia búsquedas completas para cada elemento, duplicaba esfuerzos en cada iteración. En cambio el programa optimizado permite procesar mayores datos sin que se tarde demasiado y realice busquedas más fáciles. 

Este programa ahora es más eficiente y fácil de usar ya que procesa más fácilmente una gran cantidad de datos.
