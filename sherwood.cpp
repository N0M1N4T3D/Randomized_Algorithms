#include "sherwood.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>

sherwood::sherwood(QApplication *app, QWidget *parent)
    : QMainWindow(parent), m_app(app) {
}

void sherwood::mainp()
{
    QWidget *window = new QWidget();
    window->setWindowTitle("Шервудский бинарный поиск");

    QVBoxLayout *layout = new QVBoxLayout(window);

    QLabel *labelUpper = new QLabel("Введите верхнюю границу массива (максимальное число):");
    QLineEdit *lineEditUpper = new QLineEdit;
    layout->addWidget(labelUpper);
    layout->addWidget(lineEditUpper);

    QLabel *labelLower = new QLabel("Введите нижнюю границу массива (минимальное число):");
    QLineEdit *lineEditLower = new QLineEdit;
    layout->addWidget(labelLower);
    layout->addWidget(lineEditLower);

    QLabel *labelTarget = new QLabel("Введите целевое число для поиска:");
    QLineEdit *lineEditTarget = new QLineEdit;
    layout->addWidget(labelTarget);
    layout->addWidget(lineEditTarget);

    QPushButton *searchButton = new QPushButton("Поиск");
    layout->addWidget(searchButton);

    QTextEdit *resultTextEdit = new QTextEdit;
    resultTextEdit->setReadOnly(true);
    layout->addWidget(resultTextEdit);
    // Соединение кнопки с функцией поиска
    connect(searchButton, &QPushButton::clicked, [=]() {
        QString upperText = lineEditUpper->text();
        QString lowerText = lineEditLower->text();
        QString targetText = lineEditTarget->text();

        bool ok1, ok2, ok3;
        int upperBound = upperText.toInt(&ok1);
        int lowerBound = lowerText.toInt(&ok2);
        int target = targetText.toInt(&ok3);

        if (ok1 && ok2 && ok3 && upperBound >= 0 && lowerBound >= 0 && target >= 0 &&
            lowerBound <= upperBound && target >= lowerBound && target <= upperBound) {
            QVector<int> arr;
            for (int i = lowerBound; i <= upperBound; ++i) {
                arr.append(i);
            }

            int index = sherwoodBinarySearch(arr, target, resultTextEdit);
            if (index != -1) {
                resultTextEdit->append(QString("Элемент %1 найден по индексу: %2").arg(target).arg(index));
            } else {
                resultTextEdit->append(QString("Элемент %1 не найден в массиве.").arg(target));
            }
        } else {
            QMessageBox::warning(window, "Ошибка", "Введите корректные значения границ и целевого числа.");
        }
    });

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
    delete m_app;
}
