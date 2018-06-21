#include "sandbox.h"
#include "constants.h"
#include <QPainter>

Sandbox::Sandbox(double l, double width, double u, double heigth, double i, bool a, bool j) :
    left(l), right(l+width), up(u), down(u+heigth), ratio(i), attract(a), reject(j)
{
    background = QBrush(QColor(BACKGROUD_COLOR_R,BACKGROUD_COLOR_G,BACKGROUD_COLOR_B));
    basicNodeColor = QColor(INIT_BASIC_NODE_COLOR_R,INIT_BASIC_NODE_COLOR_G,INIT_BASIC_NODE_COLOR_B);
    circleBrush = QBrush(basicNodeColor);
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
            nodes.push_back(Node(left+col_len*col, up+row_len*row, qrand()%2+1));
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

void Sandbox::setBackgroundColor(const QColor &c)
{
    background.setColor(c);
}

void Sandbox::setBasicNodeColor(const QColor &c)
{
    basicNodeColor = c;
}

void Sandbox::paint(QPainter *painter)
{
    painter->fillRect(QRectF(left, up, right-left, down-up), background);

    //painter->setBrush(circleBrush);
    //painter->setPen(circlePen);

    for (int i = 0; i < nodes.size(); ++i) {
        int node_speed = nodes[i].getSpeed() * 10000;
        circleBrush.setColor(QColor((basicNodeColor.red()+node_speed/3)%256, (basicNodeColor.green()+node_speed/10)%256, (basicNodeColor.blue()+node_speed/5)%256));
        circlePen.setColor(circleBrush.color());
        painter->setBrush(circleBrush);
        painter->setPen(circlePen);
        painter->drawEllipse(QRectF(nodes[i].getPosX()-nodes[i].getRadius(), nodes[i].getPosY()-nodes[i].getRadius(), nodes[i].getRadius()*2, nodes[i].getRadius()*2));
    }
}


