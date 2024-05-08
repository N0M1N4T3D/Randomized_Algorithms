#include "montecarlo.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <cstdlib>
#include <cmath>

MonteCarlo::MonteCarlo(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Тест Миллера-Рабина на простоту числа");
    setMinimumSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("<h2>Тест Миллера-Рабина на простоту числа</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QLineEdit *numberInput = new QLineEdit;
    numberInput->setPlaceholderText("Введите число");
    layout->addWidget(numberInput);

    QLineEdit *repeatInput = new QLineEdit;
    repeatInput->setPlaceholderText("Введите количество повторений");
    layout->addWidget(repeatInput);

    QLineEdit *iterationsInput = new QLineEdit;
    iterationsInput->setPlaceholderText("Введите количество итераций в тесте");
    layout->addWidget(iterationsInput);

    QPushButton *checkButton = new QPushButton("Запустить алгоритм");
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
            QMessageBox::warning(this, "Ошибка!", "Введено некорректное число");
            return;
        }

        int repeat = repeatStr.toInt(&ok);
        if (!ok || repeat <= 0) {
            QMessageBox::warning(this, "Ошибка", "Введено некорректное количество повторений алгоритма");
            return;
        }

        int iterations = iterationsStr.toInt(&ok);
        if (!ok || iterations <= 0) {
            QMessageBox::warning(this, "Ошибка", "Введено некорректное количество итераций");
            return;
        }

        QString resultText;
        for (int i = 0; i < repeat; ++i) {
            if (miller_rabin_test(number, iterations))
                resultText += QString("Тест %1: %2 возможно простое\n").arg(i + 1).arg(number);
            else
                resultText += QString("Тест %1: %2 составное\n").arg(i + 1).arg(number);
        }
        resultOutput->setText(resultText);
    });

    setLayout(layout);
}

long long MonteCarlo::power_mod(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1)
            result = (result * a) % m;
        b >>= 1;
        a = (a * a) % m;
    }
    return result;
}


bool MonteCarlo::miller_rabin_test(long long n, int k) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        long long x = power_mod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool prime = false;
        for (int j = 1; j < s; j++) {
            long long r = pow(2,j) * d;
            x = power_mod(a,r,n);
            if (x == 1) {
                return false;
            }
            else {
                prime = true;
                break;
            }
        }
        if (!prime)
            return false;
    }
    return true;
}
