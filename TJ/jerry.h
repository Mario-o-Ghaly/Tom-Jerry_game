#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QList>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

#include "cheese.h"
#include "power.h"
#include "portal.h"

using namespace Qt;

class jerry: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int board[15][15];
    int rows, columns;
    QImage image;            //Declaration of image here to use it in case of movement
    bool direction;          //true is for right, and false is for left
    Cheese* heldCheese;
    bool powered;
    int cheeseWin;
    QGraphicsView *views;
    QMediaPlayer *background;

public:
    jerry(int mazeData[15][15], int Size,  QGraphicsView *view, QMediaPlayer *music);

    void setImage(QString name);

    void mirroring();

    bool holdingCheese();

    void nullify_ptr();

    void setPosition(int row, int column);

    bool Ispowered();

    int getRow();

    int getColumn();

    void cheeseCollision(QGraphicsItem *item);

    void homeCollision(QGraphicsItem *item);

    void powerCollision(QGraphicsItem *item);

    void portalCollision(QGraphicsItem *item);

    bool win();

    void stopBGmusic();

public slots:
    void keyPressEvent(QKeyEvent *event);

    void delay();

    void video();
};
#endif // JERRY_H
