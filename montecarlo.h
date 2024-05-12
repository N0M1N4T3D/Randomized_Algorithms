#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <QWidget>

class MonteCarlo : public QWidget {
    Q_OBJECT

public:
    explicit MonteCarlo(QWidget *parent = nullptr);

private:
    unsigned long long power_mod(unsigned long long a, unsigned long long d, unsigned long long n);
    bool miller_rabin_test(unsigned long long n, int k);

signals:

};

#endif // MONTECARLO_H
