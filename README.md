# Minishell

<img width="950" height="500" alt="image" src="https://github.com/user-attachments/assets/3f44a254-e724-4573-89b5-84635a2c49d5" />

Un shell simple e interactivo implementado en C como parte del curriculum de **42 School**.

[![42 School](https://img.shields.io/badge/42-minishell-000000?style=flat&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-90-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success)](https://github.com/42School/norminette)

## Tabla de Contenidos

- [Descripción](#descripción)
- [Características](#características)
- [Instalación](#instalación)
- [Uso](#uso)
- [Funcionalidades](#funcionalidades)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Recursos](#recursos)
- [Requisitos Específicos de 42 School](#requisitos-específicos-de-42-school)

## Descripción

Minishell es una implementación simplificada de un shell de Unix/Linux. Este proyecto forma parte del curriculum de 42 School y tiene como objetivo familiarizar a los estudiantes con:

- Procesamiento de línea de comandos
- Manejo de procesos y señales
- Redirecciones y pipes
- Variables de entorno
- Gestión de memoria en C

## Características

### 1. Entrada y Manejo Básico
- **Prompt interactivo**: Línea de entrada esperando comandos
- **Historial**: Historial funcional de comandos

### 2. Ejecución de Comandos
- **Búsqueda en PATH**: Localizar ejecutables basado en variable PATH
- **Rutas**: Ejecutar usando rutas relativas o absolutas

### 3. Manejo de Señales
- **Variable global única**: Solo para indicar número de señal recibida
- **Acceso restringido**: Evitar acceso del gestor a estructuras principales
- **Ctrl-C**: Nueva línea de entrada
- **Ctrl-D**: Terminar el shell
- **Ctrl-\\**: No realizar ninguna acción

### 4. Manejo de Cadenas y Metacaracteres
- **Comillas simples** (`'`): Evita interpretación de metacaracteres
- **Comillas dobles** (`"`): Evita metacaracteres excepto `$`
- **Comillas sin cerrar**: No interpretar
- **Caracteres especiales**: No interpretar `\` o `;`

### 5. Redirecciones
- **`<`**: Redirigir entrada
- **`>`**: Redirigir salida
- **`<<`**: Heredoc hasta delimitador (sin actualizar historial)
- **`>>`**: Redirigir salida en modo append

### 6. Pipes
- **`|`**: Conectar output de un comando al input del siguiente

### 7. Variables y Expansiones
- **Variables de entorno**: Expansión de `$VAR`
- **Exit status**: Expansión de `$?` al estado del último comando

### 8. Built-ins (sin opciones adicionales)
- **`echo`**: Con opción `-n` únicamente
- **`cd`**: Solo rutas relativas o absolutas
- **`pwd`**: Mostrar directorio actual
- **`export`**: Gestionar variables de entorno
- **`unset`**: Eliminar variables de entorno
- **`env`**: Mostrar variables de entorno
- **`exit`**: Terminar el shell

## Instalación

### Prerrequisitos
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install gcc make libreadline-dev

# macOS (con Homebrew)
brew install readline

# Arch Linux
sudo pacman -S gcc make readline
```

### Compilación
```bash
# Clonar el repositorio
git clone https://github.com/tu-usuario/minishell.git
cd minishell

# Compilar
make

# Ejecutar
./minishell
```

### Comandos del Makefile
```bash
make        # Compilar el proyecto
make clean  # Limpiar archivos objeto
make fclean # Limpiar todo
make re     # Recompilar desde cero
```

## Uso

### Inicio básico
```bash
$ ./minishell
サ » echo "Hola Mundo"
Hola Mundo
サ » pwd
/home/usuario/minishell
サ » ls -la | grep minishell
```

### Ejemplos de funcionalidades

#### Variables de entorno
```bash
サ » export MI_VAR="valor"
サ » echo $MI_VAR
valor
サ » echo $?
0
```

#### Redirecciones
```bash
サ » echo "contenido" > archivo.txt
サ » cat < archivo.txt
contenido
サ » ls >> listado.txt
```

#### Pipes
```bash
サ » ls -la | grep ".c" | wc -l
サ » cat /etc/passwd | head -5
```

#### Heredoc
```bash
サ » cat << EOF
> Primera línea
> Segunda línea
> EOF
Primera línea
Segunda línea
```

### Testing

#### Script de pruebas automatizado para pipeline
```bash
# Hacer el script ejecutable
chmod +x testPIpe.sh

# Ejecutar pruebas
./testPIpe.sh
```


## Funcionalidades

| Requisito | Estado | Descripción |
|-----------|--------|-------------|
| **1. Entrada y manejo básico** |
| Prompt interactivo | Implementado | Línea de comandos con readline |
| Historial funcional | Implementado | Navegación con ↑/↓ |
| **2. Ejecución de comandos** |
| Búsqueda en PATH | Implementado | Localizar ejecutables automáticamente |
| Rutas relativas/absolutas | Implementado | Ejecutar con cualquier tipo de ruta |
| **3. Manejo de señales** |
| Variable global única | Implementado | Solo número de señal |
| Ctrl-C (nueva línea) | Implementado | Funciona correctamente |
| Ctrl-D (terminar shell) | Implementado | Funciona correctamente |
| Ctrl-\\ (sin acción) | Implementado | Funciona correctamente |
| **4. Cadenas y metacaracteres** |
| Comillas simples `'` | Implementado | No interpreta metacaracteres |
| Comillas dobles `"` | Implementado | Interpreta solo `$` |
| Comillas sin cerrar | Implementado | No interpreta |
| Caracteres especiales | Implementado | No interpreta `\\` o `;` |
| **5. Redirecciones** |
| `<` (entrada) | Implementado | Funciona |
| `>` (salida) | Implementado | Funciona |
| `<<` (heredoc) | Implementado | Sin actualizar historial |
| `>>` (append) | Implementado | Funciona |
| **6. Pipes** |
| `\|` simple | Implementado | Conecta comandos |
| **7. Variables y expansiones** |
| `$VAR` | Implementado | Expansión de variables |
| `$?` | Implementado | Estado del último comando |
| **8. Built-ins** |
| `echo` (solo `-n`) | Implementado | Verificar solo opción `-n` |
| `cd` | Implementado | Rutas relativas/absolutas |
| `pwd` | Implementado | Directorio actual |
| `export` | Implementado | Sin opciones adicionales |
| `unset` | Implementado | Error por revisar |
| `env` | Implementado | Mostrar variables |
| `exit` | Implementado | Terminar shell |




## Estructura del Proyecto

```
minishell/
├── minishell.c              # Función principal
├── minishell.h              # Header principal
├── Makefile                 # Configuración de compilación
├── README.md                # Este archivo
├── testPIpe.sh              # Script de pruebas
├── 0funcionesprueba.c       # Archivo auxiliar / pruebas
│
├── Core functionality
│   ├── parser.c             # Análisis de comandos
│   ├── parser_aux.c         # Auxiliares del parser
│   ├── prompt.c             # Manejo del prompt
│   ├── exect.c              # Ejecución de comandos
│   ├── error.c              # Manejo de errores
│   ├── signal_handler.c     # Gestión de señales (handler)
│   ├── signals.c            # Funciones relacionadas con señales
│   ├── exit_status.c        # Gestión de códigos de salida
│   └── heredoc.c            # Heredoc (<<) implementation
│
├── Built-in commands
│   ├── cd.c                 # cd
│   ├── cd_echo.c            # cd y echo (implementación)
│   ├── cd_echo_aux.c        # Auxiliares para cd/echo
│   ├── env_pwd.c            # env y pwd
│   ├── export.c             # export
│   ├── export_aux.c         # Auxiliares export
│   ├── export_utils.c       # Utilidades para export
│   ├── variables.c          # Manejo de variables
│   ├── variables_aux.c      # Auxiliares variables
│   └── unset.c              # unset
│
├── Advanced features
│   ├── pipelinig.c          # Implementación de pipes
│   ├── pipe_aux.c           # Funciones auxiliares pipes
│   ├── pipe_child.c         # Lógica de procesos hijos en pipes
│   ├── redirections.c       # Redirecciones
│   ├── redirections_parsing.c # Parsing de redirecciones
│   ├── redirections_aux.c   # Auxiliares de redirecciones
│   ├── quotes.c             # Manejo de comillas
│   ├── quotes_expansion.c   # Expansión dentro de comillas
│   ├── quotes_processing.c  # Procesamiento de comillas
│   ├── paths.c              # Resolución de rutas
│   └── matrix.c             # Operaciones con arrays / matrices
│
├── Utils/
│   ├── utils.h              # Header de utilidades
│   ├── lib_ft.c             # Funciones libft parte 1
│   ├── lib_ft1.c            # Funciones libft parte 2
│   ├── ft_split.c           # Función split
│   ├── ft_atoi.c            # String to integer
│   ├── ft_itoa.c            # Integer to string
│   └── split_outside_quotes.c # Split respetando comillas
```


## Recursos

### Documentación oficial
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [POSIX Shell Standard](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html)
- [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Requisitos Específicos de 42

### Restricciones Técnicas
- **Una sola variable global**: Exclusivamente para el número de señal recibida
- **Sin acceso a estructuras principales**: El gestor de señales no debe acceder a estructuras de datos principales
- **Sin estructuras tipo "norm" globales**: Restricción de estructuras globales
- **Built-ins sin opciones**: Los comandos internos no deben aceptar opciones adicionales (excepto `echo -n`)

### Comportamiento Específico
- **Heredoc (`<<`)**: No debe actualizar el historial de comandos
- **Comillas**: Manejo estricto según especificación
- **Variables**: Solo `$` seguido de caracteres válidos
- **Metacaracteres**: No interpretar `\`, `;` y otros no especificados


---

