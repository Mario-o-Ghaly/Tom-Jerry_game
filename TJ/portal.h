#ifndef PORTAL_H
#define PORTAL_H
#include <QGraphicsPixmapItem>

class portal: public QGraphicsPixmapItem
{
private:
    int rows, columns;
public:
    portal(int row, int column);
};

#endif // PORTAL_H
