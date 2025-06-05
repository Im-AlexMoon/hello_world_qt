#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Crear un QLabel con el texto "¡Hola Mundo!" y centrarlo
    QLabel *label = new QLabel("¡Hola Mundo!", this);
    label->setAlignment(Qt::AlignCenter);

    // Establecer como widget central de la ventana
    setCentralWidget(label);

    // Opcional: establecer tamaño mínimo de la ventana
    this->setMinimumSize(400, 200);
}

MainWindow::~MainWindow() {
    // Qt se encarga de eliminar los widgets hijos automáticamente
}
