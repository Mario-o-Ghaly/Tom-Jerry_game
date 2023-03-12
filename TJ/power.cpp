#include "power.h"

power::power(int row, int column)
{
    QPixmap power("power");
    power = power.scaledToHeight(50);
    power = power.scaledToWidth(50);
    setPixmap(power);

    setPos(50 + column*50, 50 + row*50);

}
