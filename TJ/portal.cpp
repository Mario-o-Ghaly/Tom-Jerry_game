#include "portal.h"

portal::portal(int row, int column)
{
    QPixmap portals("firering");
    portals = portals.scaledToHeight(50);
    portals = portals.scaledToWidth(50);
    setPos(50 + 50*column, 50 + 50*row);
    rows = row; columns = column;
    setPixmap(portals);
}
