#include "lasvegas.h"
#include "ui_lasvegas.h"
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <iostream>
#include <ctime>
#include <vector>
extern double n;
#define N n
using namespace std;
enum { FALSE, TRUE };
int nTrials = 0;

int nextInt(int n) // Generate a random number between 0 ~ n
{
    double rtn;

    rtn = n * (rand() / (1.0 + RAND_MAX));
    if (rtn >= n)
        return n - 1;
    else
        return (int)rtn;
}

int *las_vegas(int n)
{
    int *solution = new int[n];
    fill(solution, solution + n, 0); //массив решений, индекс - строка; значение - столбец
    int fail = TRUE; //алгоритм работает, пока не найдет решение
    int *blocked = NULL; //клетки, в которые нельзя поставить ферзя
    while (fail)
    {
        int row, col, k, d;
        if (blocked) { //если решение не найдено - алгоритм начинает сначала
            delete blocked;
            blocked = NULL;
        }
        blocked = new int[n * n];
        fill(blocked, blocked + n * n, 0);
        nTrials++; // Количество проходов увеличивается
        for (row = 0; row < n; row++)
        {
            col = nextInt(n); // выбираем случайный столбец
            for (k = 0; blocked[row*n + col] && k < n; k++) { //если клетка занята - выбирается следующий столбец
                col = (col + 1) % n;
            }
            if (blocked[row*n + col]) {
                break;
            }
            solution[row] = col;
            for (k = row + 1; k < n; k++)
            {
                blocked[k*n + col] = TRUE; //блокировка по столбцу
                d = k - (row - col);
                if (d >= 0 && d < n)
                    blocked[k*n + d] = TRUE; //блокировка по диагонали
                d = (row + col) - k;
                if (d >= 0 && d < n)
                    blocked[k*n + d] = TRUE; //блокировка по другой диагонали
            }
        }
        fail = row < n;
    }
    return solution;
}

int valid(int *board, int size)
{
    int row;
    // Take advantage of initialization to false
    int *diagChk = new int[2 * size - 1];
    memset(diagChk, 0, (2 * size - 1) * sizeof(int));
    int *antiChk = new int[2 * size - 1];
    memset(antiChk, 0, (2 * size - 1) * sizeof(int));

    //    mark (0, board[0], TRUE);
    diagChk[0 - board[0] + size - 1] = TRUE;
    antiChk[0 + board[0]] = TRUE;

    for (row = 1; row < size; row++)
        if ((diagChk[row - board[row] + size - 1] || antiChk[row + board[row]]))
            return FALSE;
        else
            //          mark (row, board[row], TRUE);
            diagChk[row - board[row] + size - 1] =
                antiChk[row + board[row]] = TRUE;
    return TRUE;
}

lasvegas::lasvegas(QWidget *parent) : QWidget(parent)
{
    setFixedSize(700, 700); // Устанавливаем размер виджета
}



void lasvegas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    double gridSize = width() / N;
    QPixmap image("/Users/n0m1n4t3d/Downloads/queen.png");
    int   *solution;
    std::vector<std::pair<int,int>> queens = {};
    srand((int)time(NULL));

    solution = las_vegas(N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == solution[i]) {
                queens.push_back(pair(i,j));
            }
        }
    }

    std::sort(queens.begin(), queens.end(), std::greater<>());
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            QColor color = (row + col) % 2 == 0 ? Qt::white : Qt::darkGray;
            if (queens[queens.size() - 1].first == row and queens[queens.size() - 1].second == col) {
                painter.fillRect(col * gridSize, row * gridSize, gridSize, gridSize, color);
                painter.drawPixmap(col * gridSize, row * gridSize, gridSize, gridSize, image);
                queens.pop_back();
            }
            else {
                painter.fillRect(col * gridSize, row * gridSize, gridSize, gridSize, color);
            }
        }
    }

    // Рисуем границы доски
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width() - 1, height() - 1);
}


