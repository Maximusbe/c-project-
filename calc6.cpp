#include "calc6.h"
#include "ui_calc6.h"
#include <string>
#include <QRegularExpression>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QApplication>
#include <QDateTime>




calc6::calc6(QWidget *parent): QMainWindow(parent), ui(new Ui::calc6), activeLineEdit(nullptr), customPlot(new QCustomPlot(this))
{
    // initializes all the elements created in the QT design editor

    ui->setupUi(this);

    // Connects to the instance and listens for a focus change signal(when a user clicks on a new text field),
    // then changes current input field to that of the new qline holding focus.
    connect(qApp, &QApplication::focusChanged, this, [this](QWidget *old, QWidget *now)
            {
                QLineEdit *lineEdit = qobject_cast<QLineEdit *>(now);
                if (lineEdit) {
                    activeLineEdit = lineEdit; // Update active QLineEdit
                }
            });

    // sets the mode to radians by default
    angle = true;
    ui->radToggle->setChecked(true);

    // sets up a layout, which is a space being used to hold a plot for graphing
    ui-> GraphViewer->setLayout(new QVBoxLayout);
    ui->GraphViewer->layout()->addWidget(customPlot);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    //allows the user to move, and, scroll around the graph
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    customPlot->axisRect()->setRangeZoomFactor(0.9);
    customPlot->setMouseTracking(true);

    // Creates a red circle and places it in the graphing plot.
    tracer = new QCPItemTracer(customPlot);
    tracer->setStyle(QCPItemTracer::tsCircle);
    tracer->setPen(QPen(Qt::red));
    tracer->setBrush(Qt::red);
    tracer->setSize(7);

    // Creates a text field that will hold coordinates of the mouse cursor when
    // Hovering over the graphing window
    coordinateLabel = new QCPItemText(customPlot);
    coordinateLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);
    coordinateLabel->position->setType(QCPItemPosition::ptPlotCoords);
    coordinateLabel->setText("");
    coordinateLabel->setColor(Qt::white);
    coordinateLabel->setBrush(QBrush(Qt::black));
    coordinateLabel->setPadding(QMargins(5, 5, 5, 5));

    // Connects to the plotting widget, and, listens for mouse movements signals,
    // which then calls the mousepointer function.
    connect(customPlot, &QCustomPlot::mouseMove, this, &calc6::Mousepointer);


    // applies a default range for the main graphing function.
    start=-20.0;// ranges for x values
    end=20.0;
    ui->xRangeStart->setText(QString::number(start));
    ui->xRangeEnd->setText(QString::number(end));


    varAText = "";
    varBText = "";
    varFText = "";


    // connects to the x range fields, listens for text changing signals
    //which then calls the fuction changeStarRange, changeEndRange
    connect(ui->xRangeStart, &QLineEdit::textChanged, this, &calc6::changeStartRange);
    connect(ui->xRangeEnd, &QLineEdit::textChanged, this, &calc6::changeEndRange);

    // connects to the various text fields, listens for a button press signal,
    // which then calls the on_number_clicked function
    connect(ui->Zero, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->One, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Two, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Three, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Four, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Five, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Six, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->seven, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Eight, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Nine, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Add, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Subtraction, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Divsion, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Multiplication, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->Decimal, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->varX, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->varT, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->varAComp, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->varBComp, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->varFComp, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->OpeningBrace, &QPushButton::clicked, this, &calc6::on_number_clicked);
    connect(ui->closingBrace, &QPushButton::clicked, this, &calc6::on_number_clicked);

}

calc6::~calc6(){ delete ui; }

void calc6::changeStartRange(const QString &text) { start = text.toDouble(); }

void calc6::changeEndRange(const QString &text){end = text.toDouble();       }

void calc6::on_Cos_clicked(){                appendToActiveLine("C(", "cos(");        }

void calc6::on_Log_clicked(){                appendToActiveLine("L(", "log(");        }

void calc6::on_PI_clicked(){                 appendToActiveLine("3.14159", "PI");     }

void calc6::on_Negative_clicked(){           appendToActiveLine("(-", "(-");          }

void calc6::on_Sin_clicked(){                appendToActiveLine("S(", "sin(");        }

void calc6::on_Sqrt_clicked(){               appendToActiveLine("R(", "sqrt(");       }

void calc6::on_Squared_clicked(){            appendToActiveLine("^2", "^2");          }

void calc6::on_Tan_clicked(){                appendToActiveLine("T(", "tan(");        }

void calc6::on_euler_clicked(){              appendToActiveLine("2.71828^", "e^");    }

void calc6::on_natLog_clicked(){             appendToActiveLine("N(", "ln(");         }

void calc6::on_Power_clicked(){              appendToActiveLine("^", "^");            }

void calc6::on_inverseTangent_clicked(){     appendToActiveLine("t(", "tan⁻¹(");       }

void calc6::on_inverseCosine_clicked(){      appendToActiveLine("c(", "cos⁻¹(");       }

void calc6::on_inverseSine_clicked(){        appendToActiveLine("s(", "sin⁻¹(");       }

void calc6::on_Equals_clicked()
{
    // Check to prevent the use of the x variable
    if (!inputString.contains('X')){
        try {
                implicitMulti(inputString);
            if (!inputString.contains('+') && !inputString.contains('-') && !inputString.contains('*') && !inputString.contains('/') &&!inputString.contains('^')
                &&!inputString.contains("c(") &&!inputString.contains("s(") &&!inputString.contains("t(")
                &&!inputString.contains("C(") &&!inputString.contains("S(") &&!inputString.contains("T(")
                &&!inputString.contains("L(") &&!inputString.contains("N(") &&!inputString.contains("R("))
            {
                ui->Display->setText("Error: Input must contain an operator.\n");
                return; //
            }

            // looks for implicit multiplication, and converts it to explicit multiplication
            implicitMulti(varAText);
            implicitMulti(varBText);
            implicitMulti(varFText);

            // Check to see if a variable is defined,
            // and if defined compute it, and then replace the char variable (a,b,f) with the computed result
            if (processVar(inputString, 'a', varAText, a) ||
                processVar(inputString, 'b', varBText, b) ||
                processVar(inputString, 'f', varFText, c))
            {
                return;
            }

            double FinalResult = solver.calculatePostfix(converter.infixToPostfix(validate.validateEquation(inputString.toStdString())), angle);

            // Display result in GUI
            ui->Display->setText(QString::number(FinalResult,'g', 16));
            ui->Display->update();

            // Clear input for next calculation
            inputString.clear();
            temp.clear();
        } catch(const MathException& e)
        {
            ui->Display->setText(QString::fromStdString(std::string("Error: ") + e.what() + "\n"));
        }
    }
    else
        ui->Display->setText(QString::fromStdString("X is restricted to the graph button"));
}

// graphs a user defined equation by calculating x values then replace the char 'x' with this new value in the user defined equation,
// and then, use this new equation to calculate the y values.
void calc6::on_GraphWindowB_clicked()
{

    // looks for implicit multiplication, and converts it to explicit multiplication
    implicitMulti(varAText);
    implicitMulti(varBText);
    implicitMulti(varFText);

    if (start > end)
    {
        ui->Display->setText("x's Maximum range, must be greater then the Minimum Range");
        return;
    }

    try
    {

        // Check to see if a variable is defined,
        // and if defined compute it, and then replace the char variable (a,b,f) with the computed result
        if (processVar(inputString, 'a', varAText, a) ||
            processVar(inputString, 'b', varBText, b) ||
            processVar(inputString, 'f', varFText, c))
        {
            return;
        }

        implicitMulti(inputString);

        // adds the graph to the plot on the gui
        customPlot->addGraph();

        QString tempEq = inputString;

        //size is used for scaling the graph to the user defined results
        int size = ((end - start) / 0.1) + 1;

        // hold all teh x and y values
        QVector<double> hor(size), vert(size);

        for (int idx = 0; idx < hor.size(); idx++)
        {
            // calculates x in .1 increments
            x = start + idx * 0.1;

            // replaces x with the latest x value
            tempEq.replace("X", "(" + QString::number(x, 'g', 6) + ")");

            // stores the x and y values in a vector
            hor[idx] = x;
            vert[idx] = solver.calculatePostfix(converter.infixToPostfix(validate.validateEquation(tempEq.toStdString())),angle);

            // resets the string to bring back char x
            tempEq = inputString;
        }

        // Set graph data from the vector, and replots
        customPlot->graph(customPlot->graphCount() - 1)->setData(hor, vert);
        customPlot->replot();
    }
    catch (const MathException& e)
    {
        ui->Display->setText(QString::fromStdString("Error: " + std::string(e.what()) + "\n"));
    }
}

//clears the current selected input field
void calc6::on_clear_clicked()
{
    if (activeLineEdit == ui->Display)
    {
        inputString.clear();
        temp.clear();
        ui->Display->clear();
    }
    else if (activeLineEdit == ui->xFunct)
    {
        xExprText.clear();
        xExprDisplay.clear();
        ui->xFunct->clear();
    }
    else if (activeLineEdit == ui->yFunct)
    {
        yExprText.clear();
        yExprDisplay.clear();
        ui->yFunct->clear();
    }
    else if (activeLineEdit == ui->tMin)
    {
        tMinD.clear();
        ui->tMin->clear();
    }
    else if (activeLineEdit == ui->tMax)
    {
        tMaxD.clear();
        ui->tMax->clear();
    }
    else if (activeLineEdit == ui->xRangeStart)
    {
        xRangeSD.clear();
        ui->xRangeStart->clear();
    }
    else if (activeLineEdit == ui->xRangeEnd)
    {
        xRangeED.clear();
        ui->xRangeEnd->clear();
    }
    else if (activeLineEdit == ui ->varA)
    {
        varAText.clear();
        varADisplay.clear();
        ui->varA->clear();
    }
    else if (activeLineEdit == ui ->varB)
    {
        varBText.clear();
        varBDisplay.clear();
        ui->varB->clear();
    }
    else if (activeLineEdit == ui ->varC)
    {
        varFText.clear();
        varFDisplay.clear();
        ui->varC->clear();
    }
}

//clears the entire graphing window/widget
void calc6::on_ClearGraphLines_clicked()
{
    customPlot->clearGraphs(); // Clear all QCPGraph objects

    // Remove the parametric curve
    if (curve != nullptr)
    {
        customPlot->removePlottable(curve); // Remove the curve from the plot
        curve = nullptr;
    }
    else
    {
    }

    customPlot->replot(); // Refresh the plot
}

// tracks the mouse and convert its pixel positions to coordinate points when hovering over the
// graphing window, it select the pair that has the closes x values to the mouse
void calc6::Mousepointer(QMouseEvent * event)
{
    if(!customPlot->graphCount()) //check to make sure there is a graph.
        return;

    // return x cord of the mouse relative to the graph window.
    double x = customPlot ->xAxis->pixelToCoord(event->pos().x());

    // QCPGraph allows access to points on graph, each graph is stored in a list that can be acessed by its index
    QCPGraph *graph = customPlot->graph(customPlot->graphCount() - 1);

    // this is a "container" it holds all the key values (key = x, value = y)
    QSharedPointer<QCPGraphDataContainer> dataContainer = graph->data();

    // will be used to keep track of the closest key values to the mouse.
    double closestX, closestY;
    double minDistance = 1000000;

    //iterates through points on the graph until it finds the closest x value.
    for (QList <QCPGraphData>::ConstIterator it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it)
    {
        double currentX = it->key; // grabs the x for each iteration
        double distance = std::abs(x-currentX);
        if(distance < minDistance) // this is only false when the distance between current x is farther from the mouse then the last x value
        {
            closestX = currentX;
            closestY = it->value;
            minDistance = distance;
        }
        else
            break;
    }

    tracer->position->setCoords(closestX, closestY); //sets the location of the red dot to the closest point to the mouse.
    coordinateLabel->position->setCoords(closestX, closestY);//sets the text location to the point
    coordinateLabel->setText(QString("(%1, %2)").arg(closestX).arg(closestY));
    customPlot->replot();
}

// uses the button text to append it to the current input field string
void calc6::on_number_clicked()
{
    QString text = qobject_cast<QPushButton *>(sender())->text();
    appendToActiveLine(text);
}

//uses argument sent in values, to constrain what a user can put in each field.
void calc6::appendToActiveLine(const QString &text)
{
    if (activeLineEdit)
    {
        // Handle Display-specific behavior
        if (activeLineEdit == ui->Display)
        {
            // Allow a, b, c, X but not t
            if (!text.contains('t'))
            {
                inputString += text; // Parser-specific string
                temp += text;        // Display-friendly string
                ui->Display->setText(temp);
            }
        }
        // Handle varA varB varC
        else if (activeLineEdit == ui->varA || activeLineEdit == ui->varB || activeLineEdit == ui->varC)
        {
            // Disallow 'a', 'b', 'f', 'x', and 't'
            if (!text.contains('a') && !text.contains('b') && !text.contains('f') &&
                !text.contains('x') && !text.contains('t') && !text.contains('X'))
            {
                if (activeLineEdit == ui->varA)
                {
                    varAText += text;
                    varADisplay += text;
                    ui->varA->setText(varADisplay);
                }
                else if (activeLineEdit == ui->varB)
                {
                    varBText += text;
                    varBDisplay += text;
                    ui->varB->setText(varBDisplay);
                }
                else if (activeLineEdit == ui->varC)
                {
                    varFText += text;
                    varFDisplay += text;
                    ui->varC->setText(varFDisplay);
                }
            }
        }
        // Handle xFunct and yFunct
        else if (activeLineEdit == ui->xFunct || activeLineEdit == ui->yFunct)
        {
            if (!text.isEmpty() && !text.contains('X'))
            {
                if (activeLineEdit == ui->xFunct)
                {
                    xExprText += text;
                    xExprDisplay  += text;
                    ui->xFunct->setText(xExprDisplay);
                }
                else if (activeLineEdit == ui->yFunct)
                {
                    yExprText += text;
                    yExprDisplay  += text;
                    ui->yFunct->setText(yExprDisplay);
                }
            }
        }
        // Handle other fields with specific restrictions
        else
        {
            // Restrict a, b, c, t, and X for these fields
            if (!text.contains('a') && !text.contains('b') && !text.contains('f') &&
                !text.contains('t') && !text.contains('X') &&
                !text.contains('+') && !text.contains('/') && !text.contains('*')
                && !text.contains('(') && !text.contains(')'))
            {
                if (activeLineEdit == ui->tMin)
                {
                    tMinD += text;
                    ui->tMin->setText(tMinD);
                }
                else if (activeLineEdit == ui->tMax)
                {
                    tMaxD += text;
                    ui->tMax->setText(tMaxD);
                }
                else if (activeLineEdit == ui->xRangeStart)
                {
                    xRangeSD += text;
                    ui->xRangeStart->setText(xRangeSD);
                }
                else if (activeLineEdit == ui->xRangeEnd)
                {
                    xRangeED += text;
                    ui->xRangeEnd->setText(xRangeED);
                }
            }
        }
    }
}

void calc6::appendToActiveLine(const QString &parseString, const QString & displayString)
{
    if (activeLineEdit)
    {
        if (activeLineEdit == ui ->Display)
        {
            inputString += parseString;
            temp += displayString;
            ui->Display->setText(temp);
        }
        else if (activeLineEdit == ui ->xFunct)
        {
            xExprText += parseString;
            xExprDisplay += displayString;
            ui->xFunct->setText(xExprDisplay);
        }
        else if (activeLineEdit == ui ->yFunct)
        {
            yExprText += parseString;
            yExprDisplay += displayString;
            ui->yFunct->setText(yExprDisplay);;
        }
        else if(activeLineEdit == ui ->varA)
        {
            varAText += parseString;
            varADisplay += displayString;
            ui ->varA ->setText(varADisplay);
        }
        else if(activeLineEdit == ui ->varB)
        {
            varBText += parseString;
            varBDisplay += displayString;
            ui ->varB ->setText(varBDisplay);
        }
        else if(activeLineEdit == ui ->varC)
        {
            varFText += parseString;
            varFDisplay += displayString;
            ui ->varC ->setText(varFDisplay);
        }
    }
}

void calc6::implicitMulti(QString &text)
{
    std::string implicit = text.toStdString();
    size_t idx = 0;

    while (idx < implicit.size())
    {
        // Case 1: Digit or closing parenthesis followed by variable or opening parenthesis
        if (idx > 0 && (std::isdigit(implicit[idx - 1]) || implicit[idx - 1] == ')') &&
            (std::isalpha(implicit[idx]) || implicit[idx] == '('))
        {
            implicit.insert(idx, 1, '*'); // Insert '*' for implicit multiplication
            ++idx; // Skip the inserted '*'
        }
        // Case 2: Variable or closing parenthesis followed by a digit
        else if (idx > 0 && std::isalpha(implicit[idx - 1]) && std::isdigit(implicit[idx]))
        {
            implicit.insert(idx, 1, '*'); // Insert '*' for implicit multiplication
            ++idx; // Skip the inserted '*'
        }
        // Case 3: Closing parenthesis followed by a digit (but not part of a valid grouping)
        else if (idx > 0 && implicit[idx - 1] == ')' && std::isdigit(implicit[idx]))
        {
            // Ensure this isn't part of a valid function-like grouping
            size_t openingParen = implicit.rfind('(', idx - 1);
            if (openingParen == std::string::npos || openingParen == 0 || !std::isalpha(implicit[openingParen - 1]))
            {
                implicit.insert(idx, 1, '*'); // Insert '*' for implicit multiplication
                ++idx; // Skip the inserted '*'
            }
        }

        ++idx;
    }

    text = QString::fromStdString(implicit);
}

// graphs parametric equations, from the x(t) and y(t) fields over the range of tmin to tmax
void calc6::on_ParaPlot_clicked()
{
    if (!angle)
    {
        ui->Display->setText("degrees for parametric is not supported");
        return;
    }
    implicitMulti(xExprText);
    implicitMulti(yExprText);

        try {

            // valdiate variables
            if (processVar(xExprText, 'a', varAText, a) ||
                processVar(xExprText, 'b', varBText, b) ||
                processVar(xExprText, 'f', varFText, c) ||

                processVar(yExprText, 'a', varAText, a) ||
                processVar(yExprText, 'b', varBText, b) ||
                processVar(yExprText, 'f', varFText, c) )
            {
                return;
            }

            // Remove the existing curve if it exists
            if (curve != nullptr)
            {
                customPlot->removePlottable(curve);
                curve = nullptr;
            };

            // Parse tMin and tMax
            double tMinValue = tMinD.toDouble();
            double tMaxValue = tMaxD.toDouble();
            if (tMinValue >= tMaxValue)
            {
                ui->Display->setText("Error: tMax should  be greater then tMin, or tmin and tmax are undefined.");
                return;
            }

            const int pointCount = 500;
            QVector<QCPCurveData> dataPoints(pointCount);

            for (int idx = 0; idx < pointCount; ++idx)
            {   // gets the string from gui
                tempX= xExprText;
                tempY= yExprText;

                //assigns t a value, then replaces the character 't' in the strings x and y, with the numerical representation of t.
                t = tMinD.toDouble() + idx / static_cast<double>(pointCount - 1) * (tMaxD.toDouble() - tMinD.toDouble());
                tempX.replace("t",QString::number(t, 'g', 16));
                tempY.replace("t",QString::number(t, 'g', 16));

                // calculates the string
                double x = solver.calculatePostfix(converter.infixToPostfix(validate.validateEquation(tempX.toStdString())), angle);
                double y = solver.calculatePostfix(converter.infixToPostfix(validate.validateEquation(tempY.toStdString())), angle);

                //stores the values generated by the x and y equations
                dataPoints[idx] = QCPCurveData(idx, x, y);
            }

            // Create the new curve
            curve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

            //plots the stored key values.
            curve->data()->set(dataPoints, true);
            customPlot->replot();
        } catch(const MathException& e)
        {
            ui->Display->setText(QString::fromStdString(std::string("Error: ") + e.what() + "\n"));
        }
}


bool calc6::processVar(QString & input, char var, QString & varString, double &VarVal)
{
    qDebug()<< "before anything input" << input;
    if (input.contains(var))
    {
        qDebug() << varString;
    input.replace(var, varString);
    qDebug() << input;
    }
    return false;
}

void calc6::on_radToggle_toggled(bool checked)
{
    if(checked)
    {
        angle = true;
        ui->degToggle->setChecked(false);
    }
}

void calc6::on_degToggle_toggled(bool checked)
{
    if(checked)
    {
        angle = false;
        ui->radToggle->setChecked(false);

    }
}

