#ifndef SHERWOOD_H
#define SHERWOOD_H
#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class sherwood;
}

class sherwood : public QMainWindow
{
    Q_OBJECT
public:
    explicit sherwood(QWidget *parent = nullptr);
    ~sherwood();
protected:
    int main(int argc, char *argv[]);
    int sherwoodBinarySearch(const QVector<int>& arr, int value, QTextEdit *outputTextEdit);
};

#endif // SHERWOOD_H
