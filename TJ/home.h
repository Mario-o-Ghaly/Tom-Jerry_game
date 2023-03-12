#ifndef HOME_H
#define HOME_H
#include <QGraphicsPixmapItem>

class home : public QGraphicsPixmapItem
{
    int rows, columns;
    bool cheeseExist;
public:
    home(int rows, int columns);

    bool exist();
    void makeExist();

    int getRow();
    int getColumn();

public slots:
};
#endif // HOME_H
