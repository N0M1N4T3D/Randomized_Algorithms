#ifndef NUMERICAL_PROBABILISTIC_H
#define NUMERICAL_PROBABILISTIC_H

#include <QMainWindow>

namespace Ui {
class numerical_probabilistic;
}

class numerical_probabilistic : public QMainWindow
{
    Q_OBJECT

public:
    explicit numerical_probabilistic(QWidget *parent = nullptr);
    ~numerical_probabilistic();

protected:
    void paintEvent(QPaintEvent *event) override; // Объявление метода paintEvent
    double getNValue();
private:

};

#endif // NUMERICAL_PROBABILISTIC_H
