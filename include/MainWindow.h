#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_buttonClicked();

private:
    QLabel *label_;
    QPushButton *button_;
    QLineEdit *lineEdit_;
    QTextEdit *textEdit_;
};
