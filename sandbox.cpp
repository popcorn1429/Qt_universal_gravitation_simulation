#include "sandbox.h"
#include <QPainter>

Sandbox::Sandbox(double l, double width, double u, double heigth, double i, bool a, bool j) :
    left(l), right(l+width), up(u), down(u+heigth), ratio(i), attract(a), reject(j)
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
}

void Sandbox::initialize(int row_num, int col_num)
{
    nodes.clear();

    double row_len = (down-up)/row_num;
    double col_len = (right-left)/col_num;
    for (int row = 1; row < row_num; ++row) {
        for (int col = 1; col < col_num; ++col) {
            nodes.push_back(Node(left+col_len*col, up+row_len*row, qrand()%3+2));
        }
    }
}

void Sandbox::updateNodes(const QVector<Finger> &fingers, double elapsed)
{
    for (int i = 0; i < nodes.size(); ++i) {
        nodes[i].update(fingers, attract, ratio, elapsed);
        nodes[i].adjust(left, right, up, down, reject);
    }
}

void Sandbox::paint(QPainter *painter)
{
    painter->fillRect(QRectF(left, up, right-left, down-up), background);

    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    for (int i = 0; i < nodes.size(); ++i) {
        painter->drawEllipse(QRectF(nodes[i].getPosX()-nodes[i].getRadius(), nodes[i].getPosY()-nodes[i].getRadius(), nodes[i].getRadius()*2, nodes[i].getRadius()*2));
    }
}


