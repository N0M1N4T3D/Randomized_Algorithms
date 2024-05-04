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
    setWindowTitle("Miller-Rabin Primality Test");
    setMinimumSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

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
            QMessageBox::warning(this, "Error", "Invalid number input");
            return;
        }

        int repeat = repeatStr.toInt(&ok);
        if (!ok || repeat <= 0) {
            QMessageBox::warning(this, "Error", "Invalid number of repetitions");
            return;
        }

        int iterations = iterationsStr.toInt(&ok);
        if (!ok || iterations <= 0) {
            QMessageBox::warning(this, "Error", "Invalid number of iterations");
            return;
        }

        QString resultText;
        for (int i = 0; i < repeat; ++i) {
            if (miller_rabin_test(number, iterations))
                resultText += QString("Test %1: %2 is probably prime\n").arg(i + 1).arg(number);
            else
                resultText += QString("Test %1: %2 is composite\n").arg(i + 1).arg(number);
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
        if (x == 1 || x == n - 1)
            continue;
        bool prime = false;
        for (int j = 1; j < s; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                prime = true;
                break;
            }
        }
        if (!prime)
            return false;
    }
    return true;
}
