#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <QMainWindow>

namespace Ui {
class MonteCarlo;
}

class MonteCarlo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MonteCarlo(QWidget *parent = nullptr);
    ~MonteCarlo();

protected:
    void paintEvent(QPaintEvent *event) override; // Объявление метода paintEvent
    double getNValue();
};

#endif // MONTECARLO_H
