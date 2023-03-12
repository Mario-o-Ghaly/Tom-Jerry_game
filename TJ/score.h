#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsPixmapItem>

class score: public QGraphicsPixmapItem
{
private:
    int rows, columns;
public:
    score();

    score(int row, int column);
};

#endif // SCORE_H
