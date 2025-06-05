#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // 1. Crear el objeto QApplication
    QApplication app(argc, argv);

    // 2. Crear la ventana principal
    MainWindow window;
    window.show();

    // 3. Ejecutar el bucle de eventos
    return app.exec();
}
