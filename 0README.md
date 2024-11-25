```
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗             ██╗  ██╗██████╗ 
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║             ██║  ██║╚════██╗
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║             ███████║ █████╔╝
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║             ╚════██║██╔═══╝
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗             ██║███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝             ╚═╝╚══════╝

```
## **1. Entrada y manejo básico**
- Mostrar una línea de entrada mientras espera comandos.
- Implementar un historial funcional de comandos.

## **2. Ejecución de comandos**
- Localizar y ejecutar el ejecutable correcto:
  - Basado en la variable `PATH`.
  - Usando rutas relativas o absolutas.

## **3. Manejo de señales**
- Usar **una sola variable global** exclusivamente para indicar la recepción de señales:
  - La variable debe contener únicamente el número de la señal recibida.
  - Evitar el acceso del gestor de señales a estructuras de datos principales.
- Restringir el uso de estructuras de tipo "norm" como globales.

## **4. Manejo de cadenas y metacaracteres**
- No interpretar:
  - Comillas sin cerrar.
  - Caracteres especiales no especificados (como `\` o `;`).
- Gestionar comillas:
  - **`'`**: Evita que el shell interprete metacaracteres en su contenido.
  - **`"`**: Evita interpretar metacaracteres excepto `$` (variable de entorno).

## **5. Redirecciones**
- Implementar:
  - **`<`**: Redirigir entrada.
  - **`>`**: Redirigir salida.
  - **`<<`**: Recibir un delimitador y leer hasta encontrar una línea con solo el delimitador (sin actualizar historial).
  - **`>>`**: Redirigir salida en modo "append".

## **6. Pipes**
- Implementar pipes (`|`):
  - Conectar el output de un comando al input del siguiente en la pipeline.

## **7. Variables y expansiones**
- Gestionar variables de entorno (`$` seguidos de caracteres) y expandirlas a sus valores.
- Expandir **`$?`** al estado de salida del último comando ejecutado en la pipeline.

## **8. Manejo de combinaciones de teclas**
- Comportamiento interactivo para:
  - **`Ctrl-C`**: Imprimir una nueva línea de entrada.
  - **`Ctrl-D`**: Terminar el shell.
  - **`Ctrl-\`**: No realizar ninguna acción.

## **9. Built-ins**
- Implementar los siguientes comandos internos sin opciones adicionales:
  - **`echo`**: Con la opción `-n`.
  - **`cd`**: Solo con rutas relativas o absolutas.
  - **`pwd`**: Mostrar el directorio actual.
  - **`export`**: Gestionar variables de entorno.
  - **`unset`**: Eliminar variables de entorno.
  - **`env`**: Mostrar variables de entorno.
  - **`exit`**: Terminar el shell.

## **10. Comportamiento interactivo especial**
- **Cuando sea interactivo:**
  - **`Ctrl-C`**: Iniciar una nueva línea de entrada.
  - **`Ctrl-D`**: Cerrar el shell.
  - **`Ctrl-\`**: No realizar ninguna acción.



| **Función**       | **Descripción Breve**                                                                                     |
|--------------------|---------------------------------------------------------------------------------------------------------|
| **readline**       | Lee una línea completa desde la entrada estándar con funcionalidades como historial y edición de línea. |
| **rl_clear_history** | Limpia el historial de comandos almacenados por `readline`.                                            |
| **rl_on_new_line**  | Notifica a `readline` que se inicia una nueva línea para manejar correctamente el historial y edición.  |
| **rl_replace_line** | Reemplaza la línea actual con una nueva cadena en el contexto de `readline`.                           |
| **rl_redisplay**    | Redistribuye la línea actual, útil después de cambios en el texto de entrada con `readline`.           |
| **add_history**     | Añade una línea al historial gestionado por `readline`.                                                |
| **printf**          | Imprime un formato especificado en la salida estándar.                                                |
| **malloc**          | Asigna dinámicamente un bloque de memoria en el heap.                                                |
| **free**            | Libera un bloque de memoria previamente asignado con `malloc`.                                        |
| **write**           | Escribe datos desde un buffer a un archivo o descriptor de archivo.                                   |
| **access**          | Verifica los permisos de acceso a un archivo o directorio.                                            |
| **open**            | Abre un archivo y devuelve un descriptor de archivo.                                                 |
| **read**            | Lee datos desde un archivo o descriptor de archivo.                                                  |
| **close**           | Cierra un descriptor de archivo.                                                                      |
| **fork**            | Crea un nuevo proceso duplicando el proceso actual.                                                  |
| **wait**            | Espera a que un proceso hijo termine.                                                                 |
| **waitpid**         | Espera específicamente a que un proceso hijo con un PID particular termine.                           |
| **wait3**           | Similar a `waitpid`, pero incluye información adicional del uso de recursos del proceso hijo.         |
| **wait4**           | Igual que `wait3`, pero más configurable en términos de argumentos.                                   |
| **signal**          | Configura una acción para señales específicas del sistema.                                            |
| **sigaction**       | Maneja señales con mayor control que `signal`.                                                        |
| **kill**            | Envía una señal a un proceso, comúnmente usada para terminar procesos.                                |
| **exit**            | Finaliza el programa de manera controlada.                                                           |
| **getcwd**          | Obtiene el directorio de trabajo actual.                                                              |
| **chdir**           | Cambia el directorio de trabajo actual.                                                              |
| **stat**            | Recupera información sobre un archivo o directorio.                                                  |
| **lstat**           | Igual que `stat`, pero para enlaces simbólicos.                                                      |
| **fstat**           | Recupera información de un archivo usando un descriptor de archivo.                                  |
| **unlink**          | Elimina un archivo.                                                                                   |
| **execve**          | Reemplaza el programa actual con otro programa ejecutable.                                           |
| **dup**             | Duplica un descriptor de archivo.                                                                    |
| **dup2**            | Duplica un descriptor de archivo en un número de descriptor específico.                              |
| **pipe**            | Crea un canal de comunicación (pipe) entre procesos.                                                 |
| **opendir**         | Abre un directorio para lectura.                                                                     |
| **readdir**         | Lee las entradas de un directorio abierto.                                                           |
| **closedir**        | Cierra un directorio abierto.                                                                        |
| **strerror**        | Devuelve una cadena con la descripción de un error basado en un código de error.                     |
| **perror**          | Imprime un mensaje de error correspondiente al valor de `errno`.                                      |
| **isatty**          | Verifica si un descriptor de archivo corresponde a un terminal.                                      |
| **ttyname**         | Devuelve el nombre del terminal asociado con un descriptor de archivo.                               |
| **ttyslot**         | Devuelve el número de terminal asociado con la sesión del proceso.                                   |
| **ioctl**           | Realiza operaciones de entrada/salida en dispositivos (por ejemplo, terminales).                     |
| **getenv**          | Recupera el valor de una variable de entorno.                                                        |
| **tcsetattr**       | Configura los atributos de una terminal.                                                             |
| **tcgetattr**       | Obtiene los atributos actuales de una terminal.                                                      |
| **tgetent**         | Inicializa información del terminal desde la base de datos terminfo.                                 |
| **tgetflag**        | Recupera el valor de una bandera en terminfo.                                                        |
| **tgetnum**         | Recupera un valor numérico de terminfo.                                                              |
| **tgetstr**         | Recupera una cadena de terminfo.                                                                     |
| **tgoto**           | Construye una cadena de control para mover el cursor en la terminal.                                 |
| **tputs**           | Envía cadenas de control de terminfo a la terminal.                                                 |
