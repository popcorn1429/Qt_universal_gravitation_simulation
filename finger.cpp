#include "finger.h"

Finger::Finger() :
    strength(0), posX(0), posY(0), pressed(false)
{
}

Finger::Finger(double s, double x, double y) :
    strength(s), posX(x), posY(y), pressed(true)
{

}
