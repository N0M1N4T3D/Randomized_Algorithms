#include "sherwood.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
#include <QVector>

sherwood::sherwood(QWidget *parent)
    : QMainWindow(parent)
{
    int main(int argc, char *argv[]);
    int sherwoodBinarySearch(const QVector<int>& arr, int value, QTextEdit *outputTextEdit);
}


int sherwood::sherwoodBinarySearch(const QVector<int>& arr, int value, QTextEdit *outputTextEdit) {
    int left = 0;
    int right = arr.size() - 1;
    int count = 0;
    while (left <= right) {
        count++;
        int mid = left + rand() % (right - left + 1);
        QString stepInfo = QString("Проход №: %1 Элемент: %2").arg(arr[count - 1]).arg(mid);
        outputTextEdit->append(stepInfo);
        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}


int sherwood::main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создание главного окна
    QWidget window;
    window.setWindowTitle("Шервудский бинарный поиск");
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Создание элементов интерфейса
    QLabel *labelUpper = new QLabel("Введите верхнюю границу массива (максимальное число):");
    QLineEdit *lineEditUpper = new QLineEdit;
    QLabel *labelTarget = new QLabel("Введите целевое число для поиска:");
    QLineEdit *lineEditTarget = new QLineEdit;
    QPushButton *searchButton = new QPushButton("Поиск");
    QTextEdit *resultTextEdit = new QTextEdit;
    resultTextEdit->setReadOnly(true);

    layout->addWidget(labelUpper);
    layout->addWidget(lineEditUpper);
    layout->addWidget(labelTarget);
    layout->addWidget(lineEditTarget);
    layout->addWidget(searchButton);
    layout->addWidget(resultTextEdit);

    // Соединение кнопки с функцией поиска
    QObject::connect(searchButton, &QPushButton::clicked, [&](){
        QString upperText = lineEditUpper->text();
        QString targetText = lineEditTarget->text();
        bool ok1, ok2;
        int upperBound = upperText.toInt(&ok1);
        int target = targetText.toInt(&ok2);
        if (ok1 && ok2 && upperBound > 0 && target > 0 && target <= upperBound) {
            QVector<int> arr;
            for (int i = 1; i <= upperBound; i++) {
                arr.append(i);
            }
            int index = sherwoodBinarySearch(arr, target, resultTextEdit);
            if (index != -1) {
                resultTextEdit->append(QString("Элемент %1 найден по индексу: %2").arg(target).arg(index));
            } else {
                resultTextEdit->append(QString("Элемент %1 не найден в массиве.").arg(target));
            }
        } else {
            resultTextEdit->append("Введите корректные значения верхней границы и целевого числа.");
        }
    });

    // Отображение главного окна
    window.setLayout(layout);
    window.show();

    return app.exec();
}


sherwood::~sherwood()
{
    // Освобождение памяти, выделенной для интерфейса
    // Например: delete ui;
}

