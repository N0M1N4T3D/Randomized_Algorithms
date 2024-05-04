#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <QWidget>

class MonteCarlo : public QWidget {
    Q_OBJECT

public:
    explicit MonteCarlo(QWidget *parent = nullptr);

private:
    long long power_mod(long long a, long long b, long long m);
    bool miller_rabin_test(long long n, int k);

signals:

};

#endif // MONTECARLO_H
