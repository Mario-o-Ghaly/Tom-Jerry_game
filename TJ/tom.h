#ifndef TOM_H
#define TOM_H
#include <QtCore>
#include <QVector>

#include "jerry.h"
#include "cheese.h"
#include "score.h"

const int N = 107;
const int INF = 99999;

class tom: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int board[15][15];
    int rows, columns;
    QImage image;
    int lives;
    score *a[3];
    QTimer *timer;
    int adjacency[N][N];
    jerry *jojo;
    QGraphicsView *views;

public:
    tom(int mazeData[15][15], int Size, score *arr[3], jerry *jerr, QGraphicsView* view);

    void move(int row, int column);

    void mirroring();

    void matrix(int maze[15][15]);

    QVector<int> Dijkstra(int Graph[N][N], int startVertex, int endVertex);

public slots:
    void Tommovement();

    void video();
};

#endif // TOM_H
