#include "mainwindow.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <exception>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QGroupBox *groupInput = new QGroupBox("Входные данные");
    QVBoxLayout *layoutInput = new QVBoxLayout(groupInput);

    QHBoxLayout *rowA = new QHBoxLayout();
    rowA->addWidget(new QLabel("Вектор A:"));
    editVecA = new QLineEdit("1, 2, 3");
    rowA->addWidget(editVecA);

    QHBoxLayout *rowB = new QHBoxLayout();
    rowB->addWidget(new QLabel("Вектор B:"));
    editVecB = new QLineEdit("4, 5, 6");
    rowB->addWidget(editVecB);

    QHBoxLayout *rowS = new QHBoxLayout();
    rowS->addWidget(new QLabel("Скаляр k:"));
    editScalar = new QLineEdit("2");
    rowS->addWidget(editScalar);

    layoutInput->addLayout(rowA);
    layoutInput->addLayout(rowB);
    layoutInput->addLayout(rowS);

    QGroupBox *groupOps = new QGroupBox("Операции");
    QGridLayout *layoutOps = new QGridLayout(groupOps);

    QPushButton *btnAdd = new QPushButton("A + B");
    QPushButton *btnMul = new QPushButton("A * k");
    QPushButton *btnNorm = new QPushButton("|A| Норма");
    QPushButton *btnDot = new QPushButton("A · B Скалярное");
    QPushButton *btnRange = new QPushButton("Range(1, k)");
    QPushButton *btnBool = new QPushButton("Boolean(A) [первые 5]");
    QPushButton *btnSubs = new QPushButton("Подпоследовательности [первые 10]");
    QPushButton *btnClear = new QPushButton("Очистить лог");

    QPushButton *btnShowAllBool = new QPushButton("Показать ВСЕ подмножества");
    QPushButton *btnShowAllSubs = new QPushButton("Показать ВСЕ подпоследовательности");

    layoutOps->addWidget(btnAdd, 0, 0);
    layoutOps->addWidget(btnMul, 0, 1);
    layoutOps->addWidget(btnNorm, 1, 0);
    layoutOps->addWidget(btnDot, 1, 1);
    layoutOps->addWidget(btnRange, 2, 0);
    layoutOps->addWidget(btnBool, 2, 1);
    layoutOps->addWidget(btnSubs, 3, 0, 1, 2);
    layoutOps->addWidget(btnShowAllBool, 4, 0);
    layoutOps->addWidget(btnShowAllSubs, 4, 1);
    layoutOps->addWidget(btnClear, 5, 0, 1, 2);

    QGroupBox *groupLog = new QGroupBox("Результаты");
    QVBoxLayout *layoutLog = new QVBoxLayout(groupLog);
    textLog = new QTextEdit();
    textLog->setReadOnly(true);
    layoutLog->addWidget(textLog);

    mainLayout->addWidget(groupInput);
    mainLayout->addWidget(groupOps);
    mainLayout->addWidget(groupLog, 1);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onBtnAdd);
    connect(btnMul, &QPushButton::clicked, this, &MainWindow::onBtnMul);
    connect(btnNorm, &QPushButton::clicked, this, &MainWindow::onBtnNorm);
    connect(btnDot, &QPushButton::clicked, this, &MainWindow::onBtnDot);
    connect(btnRange, &QPushButton::clicked, this, &MainWindow::onBtnRange);
    connect(btnBool, &QPushButton::clicked, this, &MainWindow::onBtnBool);
    connect(btnSubs, &QPushButton::clicked, this, &MainWindow::onBtnSubs);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onBtnClear);
    connect(btnShowAllBool, &QPushButton::clicked, this, &MainWindow::onBtnShowAllBool);
    connect(btnShowAllSubs, &QPushButton::clicked, this, &MainWindow::onBtnShowAllSubs);
}

// === Вспомогательные функции ===

Vector<int> MainWindow::parseVector(const QString &str)
{
    if (str.trimmed().isEmpty())
    {
        throw std::invalid_argument("Поле ввода вектора пусто");
    }
    std::vector<int> data;
    QStringList parts = str.split(',', Qt::SkipEmptyParts);
    for (const QString &part : parts)
    {
        bool ok;
        int val = part.trimmed().toInt(&ok);
        if (!ok)
        {
            throw std::invalid_argument(std::string("Некорректный элемент в векторе: '") + part.toStdString() + "'");
        }
        data.push_back(val);
    }
    if (data.empty())
    {
        throw std::invalid_argument("Вектор не содержит корректных чисел");
    }
    return Vector<int>(data.data(), data.size());
}

QString MainWindow::vecToStr(const Vector<int> &v)
{
    QString res = "[";
    for (size_t i = 0; i < v.GetLength(); ++i)
    {
        res += QString::number(v.Get(i));
        if (i < v.GetLength() - 1)
            res += ", ";
    }
    res += "]";
    return res;
}

void MainWindow::printLog(const QString &msg)
{
    textLog->append(msg);

    QTextCursor cursor = textLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    textLog->setTextCursor(cursor);
}


void MainWindow::onBtnAdd()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        Vector<int> b = parseVector(editVecB->text());
        Vector<int> res = a + b;
        printLog("A + B = " + vecToStr(res));
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка сложения: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при сложении.");
    }
}

void MainWindow::onBtnMul()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        bool ok;
        int k = editScalar->text().toInt(&ok);
        if (!ok)
            throw std::invalid_argument("Некорректный скаляр");

        Vector<int> res = a * k;
        printLog("A * k = " + vecToStr(res));
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка умножения: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при умножении.");
    }
}

void MainWindow::onBtnNorm()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        double n = a.Norm();
        printLog("|A| = " + QString::number(n, 'f', 4));
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка нормы: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при вычислении нормы.");
    }
}

void MainWindow::onBtnDot()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        Vector<int> b = parseVector(editVecB->text());
        int res = a.ScalarProduct(b);
        printLog("A·B = " + QString::number(res));
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка скалярного произведения: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при скалярном произведении.");
    }
}

void MainWindow::onBtnRange()
{
    try
    {
        bool ok;
        int n = editScalar->text().toInt(&ok);
        if (!ok)
            throw std::invalid_argument("Некорректное число в поле Скаляр");
        if (n < 1)
            throw std::invalid_argument("N должно быть >= 1 для Range(1, N)");

        Vector<int> r = Vector<int>::Range(1, n);
        printLog("Range(1, " + QString::number(n) + ") = " + vecToStr(r));
        editVecA->setText(vecToStr(r).replace("[", "").replace("]", ""));
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка Range: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при генерации Range.");
    }
}

void MainWindow::onBtnBool()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        lastBoolVector = a;

        if (a.GetLength() > 15)
        {
            printLog("Слишком много элементов");
        }

        auto *ps = a.Boolean();
        QString msg = "Boolean(A) кол-во подмножеств: " + QString::number(ps->GetLength()) + "\nПервые 5:\n";

        size_t limit = std::min(ps->GetLength(), (size_t)5);
        for (size_t i = 0; i < limit; ++i)
        {
            Vector<int> *sub = dynamic_cast<Vector<int> *>(ps->Get(i));
            if (sub)
            {
                msg += "   " + vecToStr(*sub) + "\n";
                delete sub;
            }
        }
        if (ps->GetLength() > 5)
        {
            msg += "   ... и ещё " + QString::number(ps->GetLength() - 5) + " подмножеств\n";
        }

        delete ps;
        printLog(msg);
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка Boolean: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Неизвестная ошибка при вычислении Boolean.");
    }
}

void MainWindow::onBtnShowAllBool()
{
    if (lastBoolVector.GetLength() == 0)
    {
        printLog("Сначала выполните 'Boolean(A)'");
        return;
    }

    try
    {
        auto *ps = lastBoolVector.Boolean();
        QString msg = "ВСЕ подмножества (" + QString::number(ps->GetLength()) + " шт):\n";

        for (size_t i = 0; i < ps->GetLength(); ++i)
        {
            Vector<int> *sub = dynamic_cast<Vector<int> *>(ps->Get(i));
            if (sub)
            {
                msg += "   " + vecToStr(*sub) + "\n";
                delete sub;
            }
        }

        delete ps;
        printLog(msg);
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка при показе всех подмножеств: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при показе всех подмножеств.");
    }
}

void MainWindow::onBtnSubs()
{
    try
    {
        Vector<int> a = parseVector(editVecA->text());
        lastSubsVector = a;

        auto *subs = a.AllSubsequences();
        QString msg = "AllSubsequences(A) кол-во: " + QString::number(subs->GetLength()) + "\nПервые 10:\n";

        size_t limit = std::min(subs->GetLength(), (size_t)10);
        for (size_t i = 0; i < limit; ++i)
        {
            Vector<int> *sub = dynamic_cast<Vector<int> *>(subs->Get(i));
            if (sub)
            {
                msg += "   " + vecToStr(*sub) + "\n";
                delete sub;
            }
        }
        if (subs->GetLength() > 10)
        {
            msg += "   ... и ещё " + QString::number(subs->GetLength() - 10) + " подпоследовательностей\n";
        }

        delete subs;
        printLog(msg);
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка подпоследовательностей: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при вычислении подпоследовательностей.");
    }
}

void MainWindow::onBtnShowAllSubs()
{
    if (lastSubsVector.GetLength() == 0)
    {
        printLog("Сначала выполните 'Подпоследовательности'");
        return;
    }

    try
    {
        auto *subs = lastSubsVector.AllSubsequences();
        QString msg = "ВСЕ подпоследовательности (" + QString::number(subs->GetLength()) + " шт):\n";

        for (size_t i = 0; i < subs->GetLength(); ++i)
        {
            Vector<int> *sub = dynamic_cast<Vector<int> *>(subs->Get(i));
            if (sub)
            {
                msg += "   " + vecToStr(*sub) + "\n";
                delete sub;
            }
        }

        delete subs;
        printLog(msg);
    }
    catch (const std::exception &e)
    {
        printLog("Ошибка при показе всех подпоследовательностей: " + QString(e.what()));
    }
    catch (...)
    {
        printLog("Ошибка при показе всех подпоследовательностей");
    }
}

void MainWindow::onBtnClear()
{
    textLog->clear();
}