#include "montecarlo.h"
#include <cstdlib>
#include <cmath>
#include <QMessageBox>

MonteCarlo::MonteCarlo(QObject *parent) : QObject(parent)
{

}

// Функция для вычисления (a^b) % m используя быстрое возведение в степень
long long MonteCarlo::powerMod(long long a, long long b, long long m) {
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

// Метод для проверки числа на простоту с использованием теста Миллера-Рабина
bool MonteCarlo::millerRabinTest(long long n, int k) {
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
        long long x = powerMod(a, d, n);
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
