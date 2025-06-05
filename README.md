# Hello World con Qt
# Instructivo para clonar, configurar y compilar **hello\_world\_qt** en VS Code

## 1. Estructura del repositorio

Al clonar o descargar el proyecto, la carpeta raíz debe tener exactamente esta jerarquía:

```
hello_world_qt/
├── include/
│   └── MainWindow.h
├── src/
│   ├── MainWindow.cpp
│   └── main.cpp
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── tasks.json
│   └── launch.json
├── hello_world_qt.pro
└── README.md        ← (este archivo)
```

* **`include/`**: contiene el encabezado `MainWindow.h`.
* **`src/`**: contiene los fuentes C++ (`MainWindow.cpp` y `main.cpp`).
* **`.vscode/`**: contiene tres archivos de configuración de VS Code (IntelliSense, tareas de compilación y depuración).
* **`hello_world_qt.pro`**: archivo de proyecto de qmake para Qt 6.9.0.
* **`README.md`**: este instructivo.

---

## 2. Requisitos previos

1. **Sistema operativo**

   * **Windows 11** 
   * **macOS** 

2. **Instalaciones necesarias**

   * **Qt 6.9.0**

     * En **Windows**, debe instalarse la versión **MinGW 64-bit** de Qt 6.9.0. Con ella se instala, además de la biblioteca Qt, el compilador **MinGW-g++** que se usará.
     * En **macOS**, instalar la versión **Qt 6.9.0** para macOS (Xcode/Clang).
   * **Visual Studio Code**

     * Asegúrate de tener instalada la extensión **C/C++** (Microsoft) en VS Code.
   * **Variables de entorno**

     * En Windows, el instalador de Qt ya agrega (o permite agregar) la carpeta `C:\Qt\6.9.0\mingw_64\bin` al `PATH`. Comprueba que, en una terminal (CMD o PowerShell), al escribir

       ```
       qmake --version
       mingw32-make --version
       ```

       obtienes versión de Qt 6.9.0 y del “mingw32-make” que viene con Qt.
     * En macOS, asegúrate de que:

       ```
       qmake --version
       ```

       apunte a la instalación de Qt 6.9.0 (por ejemplo `/usr/local/opt/qt@6/bin/qmake` si usaste Homebrew). Y que el compilador `clang++` esté en tu `PATH`.

3. **VS Code: Extensión C/C++**

   * Abre VS Code → pestaña **Extensiones** (Ctrl+Shift+X) → busca “C/C++” (Microsoft) y pulsa **Instalar**.
   * Esta extensión habilita IntelliSense, resaltado de sintaxis, navegación de símbolos y depuración C++ en VS Code.

---

## 3. Configuración de IntelliSense en VS Code (`c_cpp_properties.json`)

Este archivo le indica al editor dónde buscar los headers de Qt y tus propias cabeceras para que el autocompletado funcione correctamente.

> **Ruta**: `hello_world_qt/.vscode/c_cpp_properties.json`

### Contenido (Windows y macOS)

```json
{
  "version": 4,
  "configurations": [
    {
      "name": "Windows-Mingw",
      "intelliSenseMode": "windows-gcc-x64",
      "compilerPath": "C:/Qt/6.9.0/mingw_64/bin/g++.exe",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "includePath": [
        "${workspaceFolder}/include",
        "C:/Qt/6.9.0/mingw_64/include",
        "C:/Qt/6.9.0/mingw_64/include/QtWidgets",
        "C:/Qt/6.9.0/mingw_64/include/QtCore",
        "C:/Qt/6.9.0/mingw_64/include/QtGui"
      ],
      "defines": [
        "UNICODE",
        "_UNICODE"
      ],
      "browse": {
        "path": [
          "${workspaceFolder}/include",
          "C:/Qt/6.9.0/mingw_64/include"
        ]
      }
    },
    {
      "name": "macOS-Clang",
      "intelliSenseMode": "macos-clang-x64",
      "compilerPath": "/usr/bin/clang++",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "includePath": [
        "${workspaceFolder}/include",
        "/usr/local/opt/qt@6/include",
        "/usr/local/opt/qt@6/include/QtWidgets",
        "/usr/local/opt/qt@6/include/QtCore",
        "/usr/local/opt/qt@6/include/QtGui"
      ],
      "defines": [],
      "browse": {
        "path": [
          "${workspaceFolder}/include",
          "/usr/local/opt/qt@6/include"
        ]
      }
    }
  ]
}
```

* **`compilerPath`**

  * En **Windows**: apunta a `C:/Qt/6.9.0/mingw_64/bin/g++.exe`.
  * En **macOS**: apunta a `/usr/bin/clang++` (u otro clang++ que use Qt).
* **`includePath`**:

  * Siempre incluye `${workspaceFolder}/include` (donde está `MainWindow.h`).
  * Rutas a los headers de Qt según tu instalación:

    * Windows (MinGW): `C:/Qt/6.9.0/mingw_64/include/…`
    * macOS (Homebrew o pkg): `/usr/local/opt/qt@6/include/…` (o la ruta correcta si instalaste Qt en otra carpeta).
* Duplica la sección para Windows y macOS; VS Code elegirá la que corresponda según el `compilerPath` activo.

---

## 4. Configuración de compilación en VS Code (`tasks.json`)

La tarea predeterminada de VS Code (“build active file”) solo compila un `.cpp` aislado. Nosotros queremos que:

1. Primero invoque `qmake` para generar el `Makefile` de Qt.
2. Luego ejecute `mingw32-make release` (o `make release` en macOS) para compilar todo el proyecto en modo Release.

> **Ruta**: `hello_world_qt/.vscode/tasks.json`

### Contenido completo

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "qmake",
      "type": "shell",
      "command": "qmake",
      "args": [
        "-spec",
        "win32-g++",
        "hello_world_qt.pro",
        "-o",
        "Makefile"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": []
    },
    {
      "label": "build (mingw32-make)",
      "type": "shell",
      "command": "mingw32-make",
      "args": [
        "release"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": [
        "$gcc"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "dependsOn": "qmake"
    },
    {
      "label": "build active file (no Qt)",
      "type": "cppbuild",
      "command": "C:\\Program Files (x86)\\MinGW\\bin\\g++.exe",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": [
        "$gcc"
      ],
      "group": {
        "kind": "none"
      },
      "detail": "Solo compila un archivo .cpp suelto sin Qt"
    }
  ]
}
```

**Qué hace cada tarea**:

1. **`"qmake"`**

   * Invoca:

     ```
     qmake -spec win32-g++ hello_world_qt.pro -o Makefile
     ```
   * Lee `hello_world_qt.pro` y genera un `Makefile` apropiado para Qt 6.9.0/MinGW.
   * No produce salida visible en VS Code (identa “problemMatcher”: `[]`).

2. **`"build (mingw32-make)"`**

   * **Depende de** `"qmake"`, así que primero genera/actualiza el `Makefile`.
   * Luego ejecuta:

     ```
     mingw32-make release
     ```

     (en Windows) para compilar en modo Release (es decir, el ejecutable quedará en `release/hello_world_qt.exe`).
   * Está marcado como tarea `"isDefault": true` en el grupo `"build"`, por lo que **al presionar Ctrl+Shift+B** se ejecutará siempre esta tarea.

3. **`"build active file (no Qt)"`**

   * Corresponde a la tarea que genera la extensión C/C++ (“build active file”).
   * La dejamos en `"group": { "kind": "none" }` para que **no interfiera**, pero si quisieran compilar un `.cpp` aislado sin Qt podrían invocarla manualmente.

---

## 5. Configuración de depuración en VS Code (`launch.json`)

Al presionar **F5**, queremos que VS Code:

1. Ejecute la tarea `"build (mingw32-make)"` (recompila si hay cambios).
2. Arranque el ejecutable resultante (en `release/hello_world_qt.exe`).
3. Inicie GDB (en Windows) o LLDB (en macOS) para depurar.

> **Ruta**: `hello_world_qt/.vscode/launch.json`

### Contenido completo

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Depurar Qt (Windows-Mingw)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/release/hello_world_qt.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "C:/Qt/6.9.0/mingw_64/bin/gdb.exe",
      "preLaunchTask": "build (mingw32-make)",
      "setupCommands": [
        {
          "description": "Habilitar pretty-printing en GDB",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    },
    {
      "name": "Depurar Qt (macOS-Clang)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/release/hello_world_qt.app/Contents/MacOS/hello_world_qt",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "lldb",
      "miDebuggerPath": "/usr/bin/lldb",
      "preLaunchTask": "build (mingw32-make)"
    }
  ]
}
```

* **Configuración “Depurar Qt (Windows-Mingw)”**

  * **`program`**: apunta a `${workspaceFolder}/release/hello_world_qt.exe`.
  * **`miDebuggerPath`**: ruta a `gdb.exe` que viene con Qt MinGW.
  * **`preLaunchTask`**: `"build (mingw32-make)"`, para compilar antes de depurar.

* **Configuración “Depurar Qt (macOS-Clang)”**

  * En macOS, al compilar en Release, Qt genera (por defecto) un `.app`. Por ejemplo `release/hello_world_qt.app`.
  * **`program`** debe apuntar al ejecutable interno:

    ```
    ${workspaceFolder}/release/hello_world_qt.app/Contents/MacOS/hello_world_qt
    ```
  * **`MIMode: "lldb"`** y **`miDebuggerPath: "/usr/bin/lldb"`** para depurar con LLDB.

---

## 6. Pasos finales para tus alumnos

### 6.1. Clonar el repositorio

En la terminal (cmd, PowerShell o Terminal de macOS), pídele que ejecuten:

```bash
git clone https://github.com/<tu_usuario>/hello_world_qt.git
cd hello_world_qt
```

> Sustituye la URL de ejemplo por la de tu repositorio real.

### 6.2. Abrir en VS Code

1. Desde la raíz de la carpeta `hello_world_qt`, ejecuta:

   ```bash
   code .
   ```

   Esto abrirá VS Code en el directorio del proyecto.

2. Si VS Code pregunta “Which compiler to use for IntelliSense?”, que elijan:

   * En **Windows**: `C:\Qt\6.9.0\mingw_64\bin\g++.exe`
   * En **macOS**: `/usr/bin/clang++` (o el `clang++` adecuado que use Qt).

### 6.3. Verificar que Qt y MinGW estén en el PATH

* **Windows**:
  Abrir Terminal integrado (Ctrl+ñ) y ejecutar:

  ```bash
  qmake --version
  mingw32-make --version
  ```

  Deben verse versiones correspondientes a Qt 6.9.0 y MinGW de Qt.
  Si no, agregar `C:\Qt\6.9.0\mingw_64\bin` a la variable de entorno `PATH`.

* **macOS**:
  En Terminal integrado, ejecutar:

  ```bash
  qmake --version
  ```

  Debe apuntar a la instalación de Qt 6.9.0. Si usaron Homebrew, puede ser en `/usr/local/opt/qt@6/bin/qmake`.
  Asegurarse de que `clang++` esté disponible (viene con Xcode Command Line Tools).

### 6.4. Compilar con “Ctrl+Shift+B”

1. Presionan **Ctrl+Shift+B**.
2. VS Code ejecuta automáticamente la tarea **“build (mingw32-make)”**, que primero corre `qmake` y luego `mingw32-make release`.
3. Al finalizar, verán en la terminal integrada algo como:

   ```
   qmake -spec win32-g++ hello_world_qt.pro -o Makefile
   mingw32-make release
   ```

   Y, al final, sin errores, aparecerá:

   ```
   mingw32-make[1]: Entering directory 'C:/Proyectos_Qt/hello_world_qt'
   g++ ... -o release/hello_world_qt.exe ... -lQt6Widgets -lQt6Core -lQt6Gui ...
   mingw32-make[1]: Leaving directory 'C:/Proyectos_Qt/hello_world_qt'
   mingw32-make: *** [Makefile:45: release] Error 0
   ```

   — O equivalente en macOS usando `make release`.
4. En la carpeta `release/` ahora estará el ejecutable:

   * **Windows**: `release\hello_world_qt.exe`.
   * **macOS**: `release/hello_world_qt.app` (ejecutable interno en `Contents/MacOS/hello_world_qt`).

### 6.5. Ejecutar la aplicación

* **Windows**:

  * En la terminal integrada:

    ```bash
    cd release
    .\hello_world_qt.exe
    ```
  * O hacer doble clic sobre `release\hello_world_qt.exe` en el Explorador de archivos.

* **macOS**:

  * En la terminal integrada:

    ```bash
    cd release/hello_world_qt.app/Contents/MacOS
    ./hello_world_qt
    ```
  * O hacer doble clic en `release/hello_world_qt.app` desde Finder.

Deberían ver una ventana Qt con el texto “¡Hola Mundo!” centrado.

---

## 7. Depurar con F5

1. En VS Code, abre cualquiera de los archivos `.cpp` y coloca un breakpoint (por ejemplo, en la línea `QApplication app(argc, argv);` de `main.cpp`).
2. Presiona **F5** o ve a la pestaña “Run and Debug” → selecciona “Depurar Qt (Windows-Mingw)” (o “Depurar Qt (macOS-Clang)” en Mac).
3. VS Code volverá a ejecutar la tarea `build (mingw32-make)` (gracias a `"preLaunchTask"`) y luego lanzará el depurador GDB/LLDB apuntando al binario recién compilado.
4. El programa se detendrá en el breakpoint y podrán inspeccionar variables, step-in/step-out, etc.

---

## 8. Errores comunes y soluciones rápidas

1. **“`qmake` no se reconoce como comando interno”**

   * Añade al `PATH` (Variables de entorno) en Windows:

     ```
     C:\Qt\6.9.0\mingw_64\bin
     ```
   * En macOS, asegúrate de que `qmake` esté en `/usr/local/opt/qt@6/bin` o la ruta de tu instalación Qt, y agrega esa carpeta a tu `PATH`.

2. **“`mingw32-make` no se reconoce”**

   * En Windows, verifica que en `C:\Qt\6.9.0\mingw_64\bin` exista `mingw32-make.exe`.
   * Agrega `C:\Qt\6.9.0\mingw_64\bin` al `PATH`, cierra y reabre VS Code.

3. **“`QApplication: No such file or directory`”**

   * Asegúrate de que el archivo `c_cpp_properties.json` incluya correctamente:

     ```
     "C:/Qt/6.9.0/mingw_64/include",
     "C:/Qt/6.9.0/mingw_64/include/QtWidgets",
     "C:/Qt/6.9.0/mingw_64/include/QtCore",
     "C:/Qt/6.9.0/mingw_64/include/QtGui"
     ```
   * Revisa que `MainWindow.h` esté en `hello_world_qt/include/`.

4. **“`undefined reference to qMain(int, char**)`”**

   * Significa que `main.cpp` no está en `SOURCES +=` dentro de `hello_world_qt.pro`.
   * Verifica que en tu `.pro` estén las líneas:

     ```pro
     SOURCES += \
         src/main.cpp \
         src/MainWindow.cpp
     HEADERS += \
         include/MainWindow.h
     ```
   * Luego regenera el Makefile con `qmake` y compila de nuevo.

5. **Problemas con espacios en la ruta del proyecto**

   * Si tu carpeta está dentro de un directorio con espacios (p. ej. OneDrive), mueve el proyecto a una ruta sin espacios, por ejemplo:

     ```
     C:\Proyectos_Qt\hello_world_qt
     ```

---

## 9. Resumen de comandos clave

1. Clonar y abrir:

   ```bash
   git clone https://github.com/<tu_usuario>/hello_world_qt.git
   cd hello_world_qt
   code .
   ```
2. Verificar que Qt y MinGW estén en el `PATH`:

   * Windows:

     ```bat
     qmake --version
     mingw32-make --version
     ```
   * macOS:

     ```zsh
     qmake --version
     ```
3. Compilar desde VS Code:

   * Presiona **Ctrl+Shift+B** (ejecuta “build (mingw32-make)”).
4. Ejecutar:

   * Windows:

     ```bat
     cd release
     .\hello_world_qt.exe
     ```
   * macOS:

     ```zsh
     cd release/hello_world_qt.app/Contents/MacOS
     ./hello_world_qt
     ```
5. Depurar:

   * En VS Code, coloca breakpoint → presiona **F5**.

# FAQ

## 1. ¿El compilador integrado de Qt sustituye a MinGW genérico?

No exactamente. El MinGW que incluye Qt (por ejemplo, en `C:/Qt/6.9.0/mingw_64/bin/g++.exe`) es **una distribución completa de MinGW**, empaquetada junto con las librerías y encabezados de Qt. Esto significa que:

* **No está limitado a proyectos Qt**: puede compilar cualquier programa C/C++ estándar (por ejemplo, un `hello.cpp` que use solo `<iostream>`).
* **Está optimizado para Qt**: todas las rutas de include y las bibliotecas (`.a`/`.dll.a`) de Qt ya están alineadas con esa versión específica de g++, evitando incompatibilidades de ABI o errores de enlace.
* **No reemplaza permanentemente a otras versiones de MinGW**: si tú ya tienes una instalación separada de MinGW en, por ejemplo, `C:/MinGW/bin/g++`, ambas coexisten. Quien esté primero en tu `PATH` (o al que apuntes explícitamente en VS Code) será el compilador que se use.

## 2. ¿Puede el MinGW que trae Qt compilar código estándar C++?

Sí. Ese `g++` incluido en `…/mingw_64/bin/` es **idéntico** en funcionalidad a cualquier otro MinGW. Puedes hacer, por ejemplo:

```bash
C:\Qt\6.9.0\mingw_64\bin\g++.exe -std=c++17 -O2 hello.cpp -o hello.exe
```

y obtendrás `hello.exe` sin necesidad de Qt en el código. En resumen, es un compilador “genérico” que además sabe dónde buscar las cabeceras de Qt cuando escribes `#include <QApplication>`.

## 3. ¿Por qué conviene usar el MinGW incluido en Qt para proyectos Qt?

1. **Compatibilidad de rutas**: sus rutas de include (`…/Qt/6.9.0/mingw_64/include/…`) y lib (`…/Qt/6.9.0/mingw_64/lib/…`) ya están configuradas para esa versión de Qt.
2. **Evitas errores de ABI**: si usaras un MinGW diferente al que Qt fue compilado con, podrías encontrar fallos de “incompatibilidad de versión de libstdc++” o símbolos faltantes.
3. **Depuración unificada**: el GDB que acompaña a ese MinGW está compilado junto con la misma versión de Qt, lo que garantiza que los símbolos Qt (.pdb/.dbg) se resuelvan correctamente al depurar.

Sin embargo, **si solo haces un proyecto C++ sin Qt**, puedes usar cualquier MinGW que prefieras; no estás “obligado” a usar el que trae Qt.

---

## 4. ¿Cómo estructurar proyectos Qt con varios archivos `.cpp` y `.h`?

Para proyectos más grandes (varias clases, formularios `.ui`, recursos `.qrc`) lo más común es usar **qmake** (sin necesidad de CMake). A continuación el flujo y la configuración mínima:

### 4.1. Estructura de carpetas recomendada

```
hello_world_qt/
├── include/              # Todos tus *.h (p. ej. MainWindow.h, ClaseA.h, ClaseB.h…)
│   └── MainWindow.h
├── src/                  # Todos tus *.cpp (p. ej. main.cpp, MainWindow.cpp, ClaseA.cpp…)
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── ClaseA.cpp
│   └── ClaseB.cpp
├── resources/            # Opcional: .qrc, iconos, etc.
│   └── icons.qrc
├── forms/                # Opcional: archivos .ui creados con Qt Designer
│   └── mainwindow.ui
├── hello_world_qt.pro    # Archivo qmake que describe SOURCES, HEADERS, FORMS, RESOURCES…
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── tasks.json
│   └── launch.json
└── README.md             # Instructivo completo (este FAQ y los pasos)
```

### 4.2. Ejemplo de `hello_world_qt.pro`

```pro
##########################################################
# Definición básica
##########################################################
TEMPLATE = app
TARGET = hello_world_qt

QT += core gui widgets

CONFIG += c++17 console

##########################################################
# Rutas adicionales de include (asegura que MainWindow.h se encuentre)
##########################################################
INCLUDEPATH += $$PWD/include

##########################################################
# Archivos fuente, cabeceras y forms
##########################################################
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/ClaseA.cpp \
    src/ClaseB.cpp

HEADERS += \
    include/MainWindow.h \
    include/ClaseA.h \
    include/ClaseB.h

FORMS += \
    forms/mainwindow.ui

RESOURCES += \
    resources/icons.qrc
```

* **`TEMPLATE = app`**: proyecto de aplicación.
* **`QT += ...`**: módulos Qt que vas a usar (aquí `core gui widgets`).
* **`CONFIG += c++17 console`**: indica estándar C++17 y que haya consola (útil para printf/logs).
* **`INCLUDEPATH += $$PWD/include`**: fuerza incluir la carpeta `include/` absoluta.
* **`SOURCES`, `HEADERS`, `FORMS`, `RESOURCES`**: listan todos los archivos de tu proyecto. Si agregas más clases o formularios, añádelos aquí.

### 4.3. Generar el Makefile

Desde la terminal (o VS Code) en la carpeta raíz:

```bash
qmake -spec win32-g++ hello_world_qt.pro -o Makefile
```

Esto genera un `Makefile` que sabe cómo invocar `moc`, `uic` y `rcc` en el orden correcto, así como compilar cada `.cpp` y enlazar con las librerías Qt (p. ej. `-lQt6Widgets`, `-lQt6Core`, …).

### 4.4. Compilar con `mingw32-make`

```bash
mingw32-make release
```

* Crea la carpeta `release/` y coloca ahí el binario `hello_world_qt.exe`.
* Si quieres compilar en modo Debug, puedes usar `mingw32-make debug` (qmake genera reglas para ambas configuraciones).

---

## 5. Configuración necesaria en VS Code para proyectos con varios `.cpp`

Para que VS Code reconozca tu proyecto Qt con múltiples fuentes y pueda compilar/depurarlo con un simple “Ctrl+Shift+B” y “F5”, debes tener en `.vscode/` estos archivos:

### 5.1. `c_cpp_properties.json`

```json
{
  "version": 4,
  "configurations": [
    {
      "name": "Windows-Mingw",
      "intelliSenseMode": "windows-gcc-x64",
      "compilerPath": "C:/Qt/6.9.0/mingw_64/bin/g++.exe",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "includePath": [
        "${workspaceFolder}/include",
        "C:/Qt/6.9.0/mingw_64/include",
        "C:/Qt/6.9.0/mingw_64/include/QtWidgets",
        "C:/Qt/6.9.0/mingw_64/include/QtCore",
        "C:/Qt/6.9.0/mingw_64/include/QtGui"
      ],
      "defines": [ "UNICODE", "_UNICODE" ],
      "browse": {
        "path": [
          "${workspaceFolder}/include",
          "C:/Qt/6.9.0/mingw_64/include"
        ]
      }
    },
    {
      "name": "macOS-Clang",
      "intelliSenseMode": "macos-clang-x64",
      "compilerPath": "/usr/bin/clang++",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "includePath": [
        "${workspaceFolder}/include",
        "/usr/local/opt/qt@6/include",
        "/usr/local/opt/qt@6/include/QtWidgets",
        "/usr/local/opt/qt@6/include/QtCore",
        "/usr/local/opt/qt@6/include/QtGui"
      ],
      "defines": [],
      "browse": {
        "path": [
          "${workspaceFolder}/include",
          "/usr/local/opt/qt@6/include"
        ]
      }
    }
  ]
}
```

* **`${workspaceFolder}/include`**: tus encabezados personalizados.
* **Rutas Qt**: aseguran que IntelliSense encuentre `<QApplication>`, `<QLabel>`, `<QMainWindow>`, etc.
* VS Code seleccionará la configuración adecuada según detecte tu compilador activo (g++ en Windows, clang++ en macOS).

### 5.2. `tasks.json`

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "qmake",
      "type": "shell",
      "command": "qmake",
      "args": [
        "-spec", "win32-g++",
        "hello_world_qt.pro",
        "-o", "Makefile"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": []
    },
    {
      "label": "build (mingw32-make)",
      "type": "shell",
      "command": "mingw32-make",
      "args": [ "release" ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": [ "$gcc" ],
      "group": { "kind": "build", "isDefault": true },
      "dependsOn": "qmake"
    },
    {
      "label": "build active file (no Qt)",
      "type": "cppbuild",
      "command": "C:\\Program Files (x86)\\MinGW\\bin\\g++.exe",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe"
      ],
      "options": { "cwd": "${fileDirname}" },
      "problemMatcher": [ "$gcc" ],
      "group": { "kind": "none" },
      "detail": "Compila un solo .cpp sin Qt"
    }
  ]
}
```

* **`"build (mingw32-make)"`** es la tarea por defecto.
* Al pulsar **Ctrl+Shift+B**, VS Code corre `qmake` (genera el Makefile) y luego `mingw32-make release` (compila en modo Release).
* La tarea “build active file” se pone en `{"kind":"none"}` para no interferir con el flujo Qt.

### 5.3. `launch.json`

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Depurar Qt (Windows-Mingw)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/release/hello_world_qt.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "C:/Qt/6.9.0/mingw_64/bin/gdb.exe",
      "preLaunchTask": "build (mingw32-make)",
      "setupCommands": [
        {
          "description": "Enable pretty-printing",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    },
    {
      "name": "Depurar Qt (macOS-Clang)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/release/hello_world_qt.app/Contents/MacOS/hello_world_qt",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "lldb",
      "miDebuggerPath": "/usr/bin/lldb",
      "preLaunchTask": "build (mingw32-make)"
    }
  ]
}
```

* En **Windows**, se depura con **GDB** incluido en Qt MinGW.
* En **macOS**, se depura con **LLDB** (Xcode Command Line Tools).
* Ante cualquier cambio en el código, al pulsar **F5** VS Code reedita y recompila (gracias a `"preLaunchTask"`).
