#ifndef CHEESE_H
#define CHEESE_H
#include "home.h"

class Cheese: public QGraphicsPixmapItem
{
    int rows, columns;
    bool atHome;

    QPixmap pix;
public:
    Cheese(int row, int column);

    bool IsAtHome();

    void makeAtHome();

    void smallify();

public slots:
};

#endif // CHEESE_H
