// sherwood.cpp

#include "sherwood.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox> // Для вывода сообщений об ошибке

sherwood::sherwood(QApplication *app, QWidget *parent)
    : QMainWindow(parent), m_app(app)
{
    // Конструктор принимает указатель на QApplication и сохраняет его
}

void sherwood::mainp()
{
    // Создание главного окна
    QWidget *window = new QWidget();
    window->setWindowTitle("Шервудский бинарный поиск");

    // Создание элементов интерфейса
    QVBoxLayout *layout = new QVBoxLayout(window);
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
    connect(searchButton, &QPushButton::clicked, [=]() {
        QString upperText = lineEditUpper->text();
        QString targetText = lineEditTarget->text();

        bool ok1, ok2;
        int upperBound = upperText.toInt(&ok1);
        int target = targetText.toInt(&ok2);

        if (ok1 && ok2 && upperBound > 0 && target > 0 && target <= upperBound) {
            // Создаем массив для поиска
            QVector<int> arr;
            for (int i = 1; i <= upperBound; ++i) {
                arr.append(i);
            }

            // Выполняем бинарный поиск
            int index = sherwoodBinarySearch(arr, target, resultTextEdit);
            if (index != -1) {
                resultTextEdit->append(QString("Элемент %1 найден по индексу: %2").arg(target).arg(index));
            } else {
                resultTextEdit->append(QString("Элемент %1 не найден в массиве.").arg(target));
            }
        } else {
            // Выводим сообщение об ошибке, если ввод некорректен
            QMessageBox::warning(window, "Ошибка", "Введите корректные значения верхней границы и целевого числа.");
        }
    });

    // Установка макета для главного окна и его отображение
    window->setLayout(layout);
    window->show();
}

int sherwood::sherwoodBinarySearch(const QVector<int> &arr, int value, QTextEdit *outputTextEdit)
{
    int left = 0;
    int right = arr.size() - 1;
    int count = 0;

    while (left <= right) {
        count++;
        int mid = left + rand() % (right - left + 1);
        QString stepInfo = QString("Проход №: %1 Элемент: %2").arg(count).arg(arr[mid]);
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

sherwood::~sherwood()
{
    // Освобождение памяти, выделенной для интерфейса
    delete m_app; // Необходимо освободить ресурсы QApplication
}
