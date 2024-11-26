#ifndef CALC6_H
#define CALC6_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "calculator.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class calc6;
}
QT_END_NAMESPACE

class calc6 : public QMainWindow
{
    Q_OBJECT

public:
   explicit calc6(QWidget *parent = nullptr);
    ~calc6();

private slots:

    void on_Cos_clicked();

    void on_Equals_clicked();

    void on_GraphWindowB_clicked();

    void on_Log_clicked();

    void on_Negative_clicked();

    void on_PI_clicked();

    void on_Sin_clicked();

    void on_Sqrt_clicked();

    void on_Squared_clicked();

    void on_Tan_clicked();

    void on_clear_clicked();

    void on_euler_clicked();

    void on_natLog_clicked();

    void on_ClearGraphLines_clicked();

    void Mousepointer(QMouseEvent * event);

    void changeStartRange(const QString &text);

    void changeEndRange(const QString &text);

    void on_number_clicked();

    void implicitMulti(QString &text);

    void on_ParaPlot_clicked();

    void on_Power_clicked();

    void appendToActiveLine(const QString &text);


    bool processVar(QString & input, char var, QString & varString, double &VarVal);

    void appendToActiveLine(const QString &parseString, const QString &displayString);

    void on_inverseTangent_clicked();

    void on_inverseCosine_clicked();

    void on_inverseSine_clicked();

    void on_radToggle_toggled(bool checked);

    void on_degToggle_toggled(bool checked);



private:
    Ui::calc6 *ui;

    QLineEdit *activeLineEdit; // Tracks currently focused QLineEdit

    QString inputString, temp;

    QString varAText, varADisplay;

    QString varBText, varBDisplay;

    QString varFText, varFDisplay;

    QString xExprText, xExprDisplay;

    QString yExprText, yExprDisplay;

    QString tMinD, tMaxD;

    QString xRangeSD, xRangeED;

    QCustomPlot *customPlot;
    QString tempX, tempY;

    bool angle;


    double x; //x axis value
    double a,b,c;// user defined vars
    double start,end; // used for specifying x range
    double t;//Parameter for the parametric equation

    QCPItemTracer *tracer;
    QCPItemText *coordinateLabel;
    Validate validate;
    Converter converter;
    Solver solver;

    QCPCurve *curve = nullptr;


};




#endif // CALC6_H
