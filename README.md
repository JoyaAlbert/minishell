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
