#include "numerical_probabilistic.h".h"
#include "ui_numerical_probabilistic.h".h"
#include <QApplication>
#include <QtWidgets>
#include <QPainter>
#include <QtMath>
#include <QInputDialog>
using namespace std;
extern long long n;

numerical_probabilistic::numerical_probabilistic(QWidget *parent)
    : QMainWindow(parent)
{
    void getNValue();
    void paintEvent(QPaintEvent *event);
}

void numerical_probabilistic::paintEvent(QPaintEvent *event) {
    int seed = time(NULL);
    srand(seed);
    QRectF rectangle(-600.0, 50.0, 1300.0, 1300.0), polygon(-600.0, 50.0, 1300.0, 1300.0);
    QPainter p(this);
    p.setPen(QPen(QColor("blue"),Qt::SolidLine));
    p.drawEllipse(rectangle);
    p.setPen(QPen(QColor("red"),Qt::SolidLine));
    p.drawPolygon(polygon);
    p.setPen(QPen(QColor("black"),Qt::SolidLine));
    p.drawLine(50, 25, 50, 750);
    p.drawLine(0, 700, 730, 700);
    p.drawLine(50, 25, 50, 750);
    p.drawLine(0, 700, 730, 700);
    p.drawText(QRect(30,0,20,100), Qt::AlignCenter, "1");
    p.drawText(QRect(690,347,20,730), Qt::AlignCenter, "1");
    double x, y, z, pi;
    long long count = 0;
    for (long long d = 0; d < n; d++)
    {
        x = (float)rand() / RAND_MAX;
        y = (float)rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1) {
            p.setPen(QPen(QColor("blue"),Qt::SolidLine));
            p.drawPoint(x * 650 + 50, 650 - y * 650 + 50);
            count++;
        }
        else {

            p.setPen(QPen(QColor("red"),Qt::SolidLine));
            p.drawPoint(x * 650 + 50,650 - y * 650 + 50);
        }
    }
    pi = 4.0 * count / n;
    p.setPen (QPen(Qt::black,Qt::SolidLine));
    p.drawText(QRect(0, 0, width()/ 3 * 4, 25), Qt::AlignCenter,
    "Количество испытаний (n): " + QString::number(n, 'd', 0));
    p.drawText(QRect(0, 25, width()/ 3 * 4, 25), Qt::AlignCenter,
    "Приближенное значение числа Пи: " + QString::number(pi, 'f', 10));
}

numerical_probabilistic::~numerical_probabilistic()
{
    // Освобождение памяти, выделенной для интерфейса
    // Например: delete ui;
}


