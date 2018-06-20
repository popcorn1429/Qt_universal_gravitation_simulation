#ifndef NODE_H
#define NODE_H

#include <QVector>
class Finger;

class Node
{
public:
    Node();
    Node(double x, double y, double r);

    double getPosX() const {return pos_x;}
    double getPosY() const {return pos_y;}
    double getRadius() const { return radius; }

    void update(const QVector<Finger>& fingers, bool attract, double ratio, double elapsed);

    /*
     * 当Node跑到了画布范围外面的时候，将其反弹/穿越到画布内
     */
    void adjust(int left, int right, int up, int down, bool reject);

private:

    void update(const Finger& finger, bool attract, double* vecStrengths);

    void restrictMaxStrength(double* vecStrengths);

private:
    double pos_x;
    double pos_y;
    double speed_x;
    double speed_y;

    double radius;//半径，与质量关联（质量与半径的三次方成正比）
    double resistance_ratio;
};

#endif // NODE_H
