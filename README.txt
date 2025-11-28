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
- entities .h/.c
Estos archivos poseen toda la información para el manejo de las entidades y su comportamiento, a excepción del comportamiento de ALIEN_GUARD. Es recomendable revisar estos archivos primero para entender el resto del código.
En entities.h se encuentra la definicion de los structs como textures, Entity y entity_array y en entities.c las funciones relacionadas.

- player .h/.c 
Estos archivos contienen la inicialización del jugador y los controles de movimiento.
Además contiene el movimiento del alien ALIEN_GUARD el cual deambula hasta encontrar el jugador y lo persigue.

- splash_screen .h/.c
Estos archivos implementan la lógica del splash screen del juego. Controla el ciclo completo de la pantalla de presentación, incluyendo la carga del recurso gráfico, las transiciones de fade in, espera, y fade out, así como el cambio de estado hacia la pantalla de loading. También gestiona el alpha de la imagen y asegura que la textura se cargue y descargue correctamente para evitar uso innecesario de memoria.

- map_render .h/.c
 Estos archivos se encargan de renderizar el mapa del nivel. Recorre la matriz de tiles definida en LevelData y dibuja en pantalla cada celda según su tipo, usando la textura de pared o de piso correspondiente. El mapa se renderiza en una cuadrícula de 16×16 píxeles por tile, permitiendo mostrar de forma eficiente la estructura del nivel durante el juego.

- game_data .h/.c
Estos archivos gestionan toda la carga, almacenamiento y liberación de datos de nivel. Incluye funciones para construir la ruta del archivo de nivel, leer la información del mapa desde un archivo .lvl, cargar las dimensiones del mapa, la matriz de tiles y las oleadas de enemigos (batches). También maneja la reserva y liberación de memoria dinámica para los datos de niveles y enemigos, e incluye una función utilitaria para imprimir información del nivel con fines de depuración.

- logo_screen.c
Estos archivos controlan la pantalla de presentación del logo, manejando su ciclo completo de aparición: fade-in, visualización completa y fade-out. Gestiona la carga diferida de la textura del logo, ajusta su opacidad según el tiempo transcurrido y, una vez finalizada la animación, libera la textura y cambia el estado del juego hacia la pantalla de splash. La función se centra únicamente en la lógica de actualización; el dibujo se realiza externamente.

- colisions .h/.c 
Contiene un simple algoritmo de colisiones.

- colision_wall .h/.c
Estos archivos implementan el sistema de detección de colisiones contra el mapa utilizando la matriz de tiles del nivel. Incluye funciones para verificar si una posición puntual choca con un tile sólido y para comprobar colisiones rectangulares de entidades (incluyendo al jugador). El sistema evalúa las esquinas del dest_rect de cada entidad y determina si alguna intersecta un tile de tipo bloqueante. También maneja límites del mapa para evitar desbordes y garantizar detección robusta.

- update_entities .h/.c
Estos archivos centralizan toda la lógica de actualización del juego relacionada con el jugador, los enemigos, los proyectiles y las colisiones. Administra el movimiento del jugador utilizando la cámara, gestiona los cooldowns de disparo y de ataque melee, y se encarga de crear y actualizar proyectiles. También procesa el comportamiento de los enemigos según su tipo (ALIEN_PATROL o ALIEN_GUARD), aplica daño cuando interactúan con proyectiles o ataques melee, y controla sus colisiones con el mapa. Además, verifica colisiones entre el jugador y los enemigos, aplicando daño e invulnerabilidad temporal. La función incluye también el dibujo de entidades, proyectiles y ataques en pantalla utilizando Raylib.

- main.c
Archivo principal del proyecto. Se encarga de inicializar la ventana, cargar los recursos gráficos y configurar el render target para el motor de pixel-art. Implementa la máquina de estados del juego (logo, splash, carga, juego, pausa y game over) y contiene el bucle principal donde se actualiza y dibuja cada frame.
También prepara el world inicial: configura la cámara, crea al jugador, el arma melee, los arreglos dinámicos de proyectiles y enemigos, y agrega las entidades iniciales al nivel.
Durante la ejecución en modo PLAYING, coordina el renderizado del mapa, la actualización de entidades mediante update_entities(), el seguimiento de cámara y la visualización del HUD. Finalmente, realiza la liberación completa de texturas, memoria dinámica y recursos de Raylib antes de cerrar la aplicación.
