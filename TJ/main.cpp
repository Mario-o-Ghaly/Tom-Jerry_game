#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QtCore/QCoreApplication>
#include <stack>
#include "jerry.h"
#include "cheese.h"
#include "tom.h"
#include "home.h"
#include "power.h"
#include "portal.h"
#include "score.h"

#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QWidget>

using namespace Qt;

void scaling(QPixmap *pic, int size){
    *pic = pic->scaledToHeight(size);
    *pic = pic->scaledToWidth(size);
}

void addText(QGraphicsScene *scene){
    QGraphicsTextItem *txt = new QGraphicsTextItem("Lives: ");
    txt->setPos(50, 3);
    txt->setDefaultTextColor(Qt::black);
    QFont font;
    font.setPixelSize(30);
    font.setBold(true);
    txt->setFont(font);
    scene->addItem(txt);
}

int main(int argc, char *argv[]){
    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgmusic.mp3"));
    music->setVolume(50);
    music->setPosition(100);
    music->play();

    QApplication game(argc,argv);
    QGraphicsScene scene;
    QGraphicsView view;
    view.setFixedSize(900,900);
    view.setWindowTitle("TJ Maze");

    const int Size = 15;
    int boardData[Size][Size];

    QFile file("Maze.txt");
    file.open(QIODevice::ReadOnly);

    QTextStream stream(&file);
    QString temp;
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            stream>>temp;
            boardData[i][j]=temp.toInt();
        }
    }

    QPixmap bricksImage("bricks");
    QPixmap grassImage("grasss");

    scaling(&bricksImage, 50);
    scaling(&grassImage, 50);


    QGraphicsPixmapItem boardItems[Size][Size];
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(boardData[i][j] == -1)
                boardItems[i][j].setPixmap(bricksImage);
            else boardItems[i][j].setPixmap(grassImage);

            boardItems[i][j].setPos(50 + j*50, 50 + i*50);
            scene.addItem(&boardItems[i][j]);
        }
    }

    home slot1(6,6);
    home slot2(6,8);
    home slot3(8,6);
    home slot4(8,8);
    scene.addItem(&slot1);
    scene.addItem(&slot2);
    scene.addItem(&slot3);
    scene.addItem(&slot4);

    Cheese cheese1(1, 1);
    Cheese cheese2(1, 13);
    Cheese cheese3(13, 1);
    Cheese cheese4(13, 13);
    scene.addItem(&cheese1);
    scene.addItem(&cheese2);
    scene.addItem(&cheese3);
    scene.addItem(&cheese4);

    power p1(3,11);
    power p2(8,3);
    scene.addItem(&p1);
    scene.addItem(&p2);

    jerry player(boardData, Size, &view, music);
    scene.addItem(&player);
    player.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    player.setFocus();

    addText(&scene);  //A function to add the text lives
    score *lives[3] = { new score(-1,2), new score(-1,3), new score(-1,4) };
    for(int i=0; i<3; i++){
        scene.addItem(lives[i]);
    }

    tom enemy(boardData, Size, lives, &player, &view);
    scene.addItem(&enemy);

    portal gate1(5, 0);
    portal gate2(5, 14);
    scene.addItem(&gate1);
    scene.addItem(&gate2);

    view.setScene(&scene);
    view.show();
    return game.exec();
}
