#ifndef SHERWOOD_H
#define SHERWOOD_H
#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class sherwood;
}

class QApplication; // Предварительное объявление класса QApplication

class sherwood : public QMainWindow
{
    Q_OBJECT
public:
    explicit sherwood(QApplication *app, QWidget *parent = nullptr);
    void mainp();
    ~sherwood();
private:
    QApplication *m_app; // Указатель на QApplication
protected:
    int sherwoodBinarySearch(const QVector<int>& arr, int value, QTextEdit *outputTextEdit);
};

#endif // SHERWOOD_H
