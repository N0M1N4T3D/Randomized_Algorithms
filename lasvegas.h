#ifndef LASVEGAS_H
#define LASVEGAS_H

#include <QWidget>
#include <vector>

class lasvegas : public QWidget
{
    Q_OBJECT

public:
    explicit lasvegas(QWidget *parent = nullptr);
    void placeQueen(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<std::pair<int, int>> queenPositions;
};

#endif // CHESSBOARDWIDGET_H
