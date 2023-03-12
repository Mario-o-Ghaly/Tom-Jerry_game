#include "home.h"

home::home(int row, int column)
{
    QPixmap homeimage("home");
    homeimage = homeimage.scaledToWidth(50);
    homeimage = homeimage.scaledToHeight(50);
    setPixmap(homeimage);
    setPos(50 + 50*column , 50+ 50*row);

    rows = row; columns = column;
    cheeseExist = false;
}

bool home::exist(){
    return cheeseExist;
}

void home::makeExist(){
    cheeseExist = true;
}

int home::getRow(){
    return rows;
}

int home::getColumn(){
    return columns;
}
