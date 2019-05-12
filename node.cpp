#include "node.h"
#include "finger.h"
#include <QtCore>

const double MAX_STRENGTH = .4;

Node::Node():
    pos_x(0), pos_y(0), speed_x(0.0), speed_y(0), resistance_ratio(1),radius(1)
{

}

Node::Node(double x, double y, double r) :
    pos_x(x), pos_y(y), speed_x(0.0), speed_y(0), resistance_ratio(1), radius(r)
{

}

double Node::getSpeed() const
{
    return qSqrt(speed_x*speed_x + speed_y*speed_y);
}

void Node::update(const QVector<Finger> &fingers, bool attract, double ratio, double elapsed)
{
    double vecStrengths[2] = {0.0,0.0};
    for (int i = 0; i < fingers.size(); ++i) {
        update(fingers[i], attract, vecStrengths);
    }

    //resistance
    double speed = qSqrt(speed_x*speed_x + speed_y*speed_y);
    vecStrengths[0] += -ratio*qPow(radius, 3.0)*speed*speed_x*resistance_ratio;
    vecStrengths[1] += -ratio*qPow(radius, 3.0)*speed*speed_y*resistance_ratio;

    //update position
    pos_x += speed_x*elapsed;
    pos_y += speed_y*elapsed;

    //restrict the max strength
    restrictMaxStrength(vecStrengths);

    speed_x += vecStrengths[0]/qPow(radius, 3.0);
    speed_y += vecStrengths[1]/qPow(radius, 3.0);
}

void Node::adjust(int left, int right, int up, int down, bool reject)
{
    int width = right - left;
    int height = down - up;
    if (reject) {
        if (pos_x < left) {
            pos_x = 2*left-pos_x;
            speed_x = -speed_x;
        }
        else if (pos_x > right) {
            pos_x = 2*right-pos_x;
            speed_x = -speed_x;
        }

        if (pos_y < up) {
            pos_y = 2*up-pos_y;
            speed_y = -speed_y;
        }
        else if (pos_y > down) {
            pos_y = 2*down - pos_y;
            speed_y = -speed_y;
        }
    }
    else {
        while (pos_x < left) pos_x += width;
        while (pos_x > right) pos_x -= width;

        while (pos_y < up) pos_y += height;
        while (pos_y > down) pos_y -= height;
    }
}

void Node::update(const Finger &finger, bool attract, double *vecStrengths)
{
    if (!finger.isPressed())
        return ;

    double distanceX = finger.getPosX()-pos_x;
    double distanceY = finger.getPosY()-pos_y;
    double distance =  qSqrt(distanceX*distanceX + distanceY*distanceY);
    double strength = finger.getStrength()*qPow(radius,3.0);
    vecStrengths[0] = strength*distanceX / qPow(distance, 3.0);
    vecStrengths[1] = strength*distanceY / qPow(distance, 3.0);
    if (!attract) {
        vecStrengths[0] = -vecStrengths[0];
        vecStrengths[1] = -vecStrengths[1];
    }
}

void Node::restrictMaxStrength(double *vecStrengths)
{
    double force = qSqrt(vecStrengths[0]*vecStrengths[0] + vecStrengths[1]*vecStrengths[1]);
    if (force > MAX_STRENGTH) {
        vecStrengths[0] = MAX_STRENGTH*vecStrengths[0]/force;
        vecStrengths[1] = MAX_STRENGTH*vecStrengths[1]/force;
    }
}
