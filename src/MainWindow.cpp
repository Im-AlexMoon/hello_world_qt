#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      label_(new QLabel("Texto inicial", this)),
      button_(new QPushButton("Presióname", this)),
      lineEdit_(new QLineEdit(this)),
      textEdit_(new QTextEdit(this))
{
    // 1) Configurar la ventana principal
    setWindowTitle("Ejemplo Qt – Controles Básicos");
    resize(600, 400);

    // 2) Barra de menú con acción "Salir"
    QMenu *fileMenu = menuBar()->addMenu("&Archivo");
    QAction *exitAction = fileMenu->addAction("Salir");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // 3) Barra de estado
    statusBar()->showMessage("Listo");

    // 4) Barra de herramientas que reutiliza la acción "Salir"
    QToolBar *toolbar = addToolBar("Principal");
    toolbar->addAction(exitAction);

    // 5) Conectar el botón al slot
    connect(button_, &QPushButton::clicked, this, &MainWindow::on_buttonClicked);

    // 6) Crear un widget central con layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Layout vertical principal
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label_);

    // Layout horizontal para QLabel + QLineEdit + QPushButton
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Ingresa texto:", this));
    hbox->addWidget(lineEdit_);
    hbox->addWidget(button_);
    vbox->addLayout(hbox);

    // QLabel y QTextEdit para mostrar líneas
    vbox->addWidget(new QLabel("Editor de Texto:", this));
    vbox->addWidget(textEdit_);

    central->setLayout(vbox);
}

MainWindow::~MainWindow()
{
    // Qt libera los hijos automáticamente
}

void MainWindow::on_buttonClicked()
{
    QString input = lineEdit_->text();
    if (input.isEmpty())
    {
        QMessageBox::warning(this, "Advertencia", "El campo de texto está vacío.");
        return;
    }

    // Actualizar QLabel e insertar línea en QTextEdit
    label_->setText("Último ingreso: " + input);
    textEdit_->append("Ingresaste: " + input);
    lineEdit_->clear();
}
