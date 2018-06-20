#ifndef FINGER_H
#define FINGER_H


class Finger
{
public:
    Finger();
    Finger(double s, double x, double y);

    double getStrength() const {return strength;}
    void setStrength(double s) {strength = s;}

    double getPosX() const {return posX;}
    void setPosX(double x) {posX = x;}

    double getPosY() const {return posY;}
    void setPosY(double y) {posY = y;}

    bool isPressed() const { return pressed; }
    void press() { pressed = true; }
    void release() { pressed = false; }

private:
    double strength;
    double posX;
    double posY;

    bool   pressed;
};

#endif // FINGER_H
