#include "cheese.h"

Cheese::Cheese(int row, int column): rows(row), columns(column)
{
    QPixmap cheese("cheese");
    cheese = cheese.scaledToHeight(50);
    cheese = cheese.scaledToWidth(50);
    pix.swap(cheese);
    setPixmap(pix);

    setPos(50 + column*50, 50 + row*50);

    atHome = false;
}

bool Cheese::IsAtHome(){
    return atHome;
}

void Cheese::makeAtHome(){
    atHome = true;
}

void Cheese::smallify(){
    pix = pix.scaledToHeight(30);
    pix = pix.scaledToWidth(30);
    setPixmap(pix);
}
