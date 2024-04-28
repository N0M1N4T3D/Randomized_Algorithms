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


int *gridSearch(int n)
{
    // Allocate memory
    int *solution = new int[n];
    memset(solution, 0, n * sizeof(int));

    int    fail = TRUE;
    short *blocked = NULL;

    while (fail)
    {
        int row, col, k, d;

        if (blocked)
            delete blocked; blocked = NULL;
        // Initially all false
        blocked = new short[n * n];
        memset(blocked, 0, n * n * sizeof(short));
        nTrials++; // Number of trials plus one

        for (row = 0; row < n; row++)
        {
            col = nextInt(n); // Get next column number as a random integer
            for (k = 0; blocked[row*n + col] && k < n; k++)
                col = (col + 1) % n;
            if (blocked[row*n + col])
                break;
            solution[row] = col;
            for (k = row + 1; k < n; k++)
            {
                blocked[k*n + col] = TRUE;
                // row - col
                d = k - (row - col);
                if (d >= 0 && d < n)
                    blocked[k*n + d] = TRUE;
                // row + col
                d = (row + col) - k;
                if (d >= 0 && d < n)
                    blocked[k*n + d] = TRUE;
            } // end for k
        } // end for row
        fail = row < n;
    } // end while fail
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
    int gridSize = width() / N;


    QPixmap image("/Users/n0m1n4t3d/Downloads/queen.jpg");
    // Рисуем шахматную доску
    int   *solution; // This is an array to store the solution in a permutation of [0, 1, 2, ..., N]
    std::vector<std::pair<int,int>> queens = {};
    srand((int)time(NULL)); // Initialize the random sequence

    solution = gridSearch(N); // Find a valid solution by Probabilistic Algorithm

    // Print the valid board
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
            if (queens[queens.size() - 1].first == row and queens[queens.size() - 1].second == col) {
                QColor color = Qt::white;
                painter.fillRect(col * gridSize, row * gridSize, gridSize, gridSize, color);
                painter.drawPixmap(col * gridSize, row * gridSize, gridSize, gridSize, image);
                queens.pop_back();
            }
            else {
                QColor color = (row + col) % 2 == 0 ? Qt::white : Qt::darkGray;
                painter.fillRect(col * gridSize, row * gridSize, gridSize, gridSize, color);
            }
        }
    }

    // Рисуем границы доски
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width() - 1, height() - 1);
}


