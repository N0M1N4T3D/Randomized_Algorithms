#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include "montecarlo.h"
#include "lasvegas.h"
#include "sherwood.h"
double n;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // Создаем новый экземпляр окна MonteCarlo
    MonteCarlo *newWindow = new MonteCarlo();

    bool ok;
    n = QInputDialog::getDouble(this, "Введите число", "Введите значение n:", 100000, 0, 100000000, 2, &ok);
    if (ok) {
        // Устанавливаем параметры нового окна
        newWindow->setFixedSize(800, 800);
        newWindow->move(100, 100);
        newWindow->setWindowTitle("Алгоритм Монте-Карло: Нахождение числа Pi");

        // Устанавливаем стили для нового окна
        QPalette palette;
        newWindow->setAutoFillBackground(true);
        newWindow->setPalette(palette);

        // Отображаем новое окно
        newWindow->show();
    }
    if (!ok) {

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    lasvegas *newWindow = new lasvegas();
    newWindow->setWindowTitle("Алгоритм Лас-Вегаса: Решение N-queens");
    bool ok;
    n = QInputDialog::getDouble(this, "Введите число", "Введите значение n:", 8, 4, 300, 2, &ok);
    if (ok) {
        QPalette palette;
        newWindow->setAutoFillBackground(true);
        newWindow->setPalette(palette);
        newWindow->show();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    sherwood *newWindow = new sherwood(qApp); // Передаем указатель на QApplication
    newWindow->setWindowTitle("Шервудский алгоритм: Бинарный поиск");
    newWindow->mainp(); // Вызываем метод для создания интерфейса
}


void MainWindow::on_pushButton_4_clicked()
{
    QCoreApplication::quit(); // Выход из приложения
}

