# Proyecto Programación bajo Plataformas Abiertas: Videojusgo escrito en C con la biblioteca Raylib

## 1. Descripción del Proyecto
Este repositorio contiene el código fuente del proyecto final para el curso de Programación Bajo Plataformas Abiertas, que consiste en un juego de combate con perspectiva top-down 2D. El objetivo principal fue crear una primera demostración del juego, que sea una base sólida si se quisiera expandir el juego y añadir niveles. El tema del juego está amboientado dentro de una nave espacial alienígena, después que los aliens secuestran a fifi, el gato del personaje principal. 

## 2. Dependencias e Instalación
Para compilar y ejecutar este proyecto, necesitará las siguientes dependencias instaladas en su sistema:
**Dependencias Principales:**
- Compilador de C: Se requiere un compilador compatible con C, específicamente GCC. 
- Sistema de Construcción: Se utiliza un Makefile para la compilación.
- Raylib: La biblioteca usada viene incluida en la carpeta lib del repositorio. Esta no fue creada por nosotros y todos los derechos se encuentran bajo sus creadores. EL link a su repositorio es: https://github.com/raysan5/raylib La versión utilizada es: 5.5

**Instalación:**
``` 
# Clonar el repositorio
git clone [URL_DE_SU_REPOSITORIO]
cd [nombre-del-directorio-del-proyecto]

#ejecutar el Makefile
make
```


# 3. Pasos para ejecución: 
Una vez ejecutado el Makefile, se puede correr el ejecutable **main**. 
**Juego:**
Movimiento: WASD
Ataques: Q - ataque a corta distancia, E - proyectil
Los enemigos son aliens, contacto con ellos genera daño al jugador. 

# 4. Descripción del diseño del proyecto.
La información más detallada sobre el diseño, arquitectura interna y características específicas puede encontrarse en la Wiki del Repositorio.
