#include "score.h"

score::score(){
    QPixmap heart("heart");
    heart = heart.scaledToHeight(40);
    heart = heart.scaledToWidth(40);
    setPixmap(heart);
}

score::score(int row, int column)
{
    QPixmap heart("heart");
    heart = heart.scaledToHeight(40);
    heart = heart.scaledToWidth(40);
    setPixmap(heart);

    setPos(50 + column*50, 50 + row*50);
}
