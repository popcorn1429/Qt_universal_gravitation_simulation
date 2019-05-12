#ifndef SANDBOX_H
#define SANDBOX_H

#include <QWidget>
#include <QBrush>
#include <QPen>

#include <QVector>

#include "node.h"
#include "finger.h"

class Sandbox
{
public:
    Sandbox(double l, double width, double u, double heigth, double i, bool j);

    void setAttract(bool a) { attract = a; }
    void setReject(bool j) { reject = j;}
    void setRatio(double i) { ratio = i; }

    void initialize(int row_num, int col_num);

    void updateNodes(const QVector<Finger>& fingers, double elapsed);

    void setBackgroundColor(const QColor& c);

    void setBasicNodeColor(const QColor& c);
public:
    void paint(QPainter *painter);

private:
    QBrush background;
    QBrush circleBrush;
    QPen   circlePen;

    QColor basicNodeColor;

    double left;
    double right;
    double up;
    double down;

    double ratio;

    bool attract;
    bool reject;

    QVector<Node> nodes;
};

#endif // SANDBOX_H
