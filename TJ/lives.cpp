lives::lives(){}

lives::lives(int row, int column): rows(row), columns(column)
{
    QPixmap heart("firering");
    heart = heart.scaledToHeight(40);
    heart = heart.scaledToWidth(40);
    setPixmap(heart);

    setPos(50 + column*50, 50 + row*50);

}
/*From Rowan Zakaria to Everyone 11:43 PM
#include "heart.h"

heart::heart(int row, int column): rows(row), columns(column)
{
    QPixmap heart("heart");
    heart = heart.scaledToHeight(40);
    heart = heart.scaledToWidth(40);
    setPixmap(heart);

    setPos(50 + column*50, 50 + row*50);

}
// heart .h #ifndef HEART_H
#define HEART_H
#include <QGraphicsPathItem>


class heart: public QGraphicsPixmapItem
{
    int rows, columns;
 public:
    heart(int row,int column);
   public slots:
};







#endif // HEART_H
// main :  heart heart1(-1, 3);
    heart heart2(-1, 2);
    heart heart3(-1, 4);


    scene.addItem(&heart1);
    scene.addItem(&heart2);
    scene.addItem(&heart3);
heart hrt(10,10);
    scene.addItem(&hrt);
    scene.addItem(&hrt);
*/
