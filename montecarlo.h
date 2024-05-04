#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <QObject>

class MonteCarlo : public QObject
{
    Q_OBJECT

public:
    explicit MonteCarlo(QObject *parent = nullptr);

    // Метод для проведения теста Миллера-Рабина
    bool millerRabinTest(long long n, int k);

private:
    // Вспомогательная функция для вычисления (a^b) % m
    long long powerMod(long long a, long long b, long long m);
};

#endif // MONTECARLO_H
