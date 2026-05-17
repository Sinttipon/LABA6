#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QString>
#include "ADT/Vector.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onBtnAdd();
    void onBtnMul();
    void onBtnNorm();
    void onBtnDot();
    void onBtnRange();
    void onBtnBool();
    void onBtnSubs();
    void onBtnClear();
    void onBtnShowAllBool();
    void onBtnShowAllSubs();

private:
    QLineEdit *editVecA;
    QLineEdit *editVecB;
    QLineEdit *editScalar;
    QTextEdit *textLog;

    Vector<int> lastBoolVector;
    Vector<int> lastSubsVector;

    Vector<int> parseVector(const QString &str);
    QString vecToStr(const Vector<int> &v);

    void printLog(const QString &msg);
};

#endif 