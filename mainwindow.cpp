#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "numerical_probabilistic.h"
#include "lasvegas.h"
#include "sherwood.h"
#include "montecarlo.h"
double n;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // Создаем новый экземпляр окна MonteCarlo
    numerical_probabilistic *newWindow = new numerical_probabilistic();

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


void MainWindow::on_pushButton_5_clicked() {
    // Создание и открытие нового диалогового окна для теста
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Miller-Rabin Primality Test");
    dialog->setMinimumSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *titleLabel = new QLabel("<h2>Miller-Rabin Primality Test</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QLineEdit *numberInput = new QLineEdit;
    numberInput->setPlaceholderText("Enter a number");
    layout->addWidget(numberInput);

    QLineEdit *repeatInput = new QLineEdit;
    repeatInput->setPlaceholderText("Enter number of repetitions");
    layout->addWidget(repeatInput);

    QLineEdit *iterationsInput = new QLineEdit;
    iterationsInput->setPlaceholderText("Enter number of iterations per test");
    layout->addWidget(iterationsInput);

    QPushButton *checkButton = new QPushButton("Run Test");
    layout->addWidget(checkButton);

    QTextEdit *resultOutput = new QTextEdit;
    resultOutput->setReadOnly(true);
    layout->addWidget(resultOutput);

    connect(checkButton, &QPushButton::clicked, [=]() {
        QString numberStr = numberInput->text();
        QString repeatStr = repeatInput->text();
        QString iterationsStr = iterationsInput->text();

        bool ok;
        long long number = numberStr.toLongLong(&ok);
        if (!ok || number <= 0) {
            QMessageBox::warning(dialog, "Error", "Invalid number input");
            return;
        }

        int repeat = repeatStr.toInt(&ok);
        if (!ok || repeat <= 0) {
            QMessageBox::warning(dialog, "Error", "Invalid number of repetitions");
            return;
        }

        int iterations = iterationsStr.toInt(&ok);
        if (!ok || iterations <= 0) {
            QMessageBox::warning(dialog, "Error", "Invalid number of iterations");
            return;
        }

        QString resultText;
        MonteCarlo monteCarlo;
        for (int i = 0; i < repeat; ++i) {
            if (monteCarlo.millerRabinTest(number, iterations))
                resultText += QString("Test %1: %2 is probably prime\n").arg(i + 1).arg(number);
            else
                resultText += QString("Test %1: %2 is composite\n").arg(i + 1).arg(number);
        }
        resultOutput->setText(resultText);
    });

    dialog->setLayout(layout);
    dialog->exec(); // Открываем диалоговое окно
}
