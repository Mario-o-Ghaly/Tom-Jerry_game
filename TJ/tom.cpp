#include "tom.h"

tom::tom(int mazeData[15][15], int Size, score *arr[3], jerry *jerr, QGraphicsView* view){
    QImage image1("tom");
    image1 = image1.scaledToWidth(50);
    image1 = image1.scaledToHeight(50);
    image.swap(image1);
    setPixmap(QPixmap::fromImage(image));

    rows = 13, columns = 7;              //tom's start position
    setPos(50 + 50*7,50 + 50*13);

    for(int i=0; i<Size; i++){           //Stting the board as the textfile
        for(int j=0; j<Size; j++)
            board[i][j] = mazeData[i][j];
    }

    lives = 3;
    a[0]= new score(-1,3);
    for(int i=1; i<lives; i++)
        a[i] = arr[i];

    jojo = jerr;                   //pointer to jerry to access its functions later

    matrix(board);
    views = view;

    timer = new QTimer(this);       //Tom's movement
    connect (timer, SIGNAL(timeout()),this, SLOT(Tommovement()));
    timer->start(350);

}

void tom::Tommovement()
{
    if(jojo->win()){   //Tom will stop moving whne jerry winsrr
        timer->stop();
        jojo->clearFocus();
    }

    //board[(int) (jojo->y()/50.0 -1)][(int) (jojo->x()/50.0 -1)]
    QVector <int> path = Dijkstra(adjacency, board[rows][columns], board[jojo->getRow()][jojo->getColumn()]);
    if(path.size() > 1)  //check if a path is present , tom is not on jerry
    {
    if(path[1] == board[rows-1][columns])  //up
        move(rows-1, columns);             //move function for setting the position

    if(path[1] == board[rows+1][columns])  //down
        move(rows+1, columns);

    if(path[1] == board[rows][columns+1]){ //right
        move(rows, columns+1);
        mirroring();
    }

    if(path[1] == board[rows][columns-1]){ //left
        move(rows, columns-1);
        setPixmap(QPixmap::fromImage(image));
    }
    }

    QList<QGraphicsItem*> items = collidingItems();
       for (int i = 0; i < items.size(); i++){
           if(typeid(*items[i]) == typeid(jerry)  )
           {
                //Check Jerry is powered or not
               if (jojo->Ispowered() == false)
               {
                   //cheese back at corner
                   if(jojo->holdingCheese())   //returns true if jerry hold cheese
                       jojo->nullify_ptr();    //returns cheese at corner

                   //jerry back at Home
                    jojo->setPos(50+ 50*7 , 50 + 50*7);
                    jojo->setPosition(7,7);

                   //tom back at place
                    move(13, 7);

                   //pop a heart, and decrement a live
                    scene()->removeItem(a[--lives]);

                    if(lives!=0){
                    QMediaPlayer *trial = new QMediaPlayer();
                    trial->setMedia(QUrl("qrc:/scream.mp3"));
                    trial->setPosition(50);
                    trial->play();
                    }

           }
               //lost all lives, game over
               if (lives == 0){
                   timer->stop();
                   jojo->clearFocus();
                   jojo->stopBGmusic();
                   QTimer::singleShot(500, this, SLOT(video()));
               }
           }
       }
}

void tom::move(int row, int column){
    setPos(50 + 50*column, 50 + 50*row);
    rows=row; columns=column;
}

void tom::mirroring(){
    QImage mirror;
    mirror = image.scaledToWidth(50);
    mirror = image.scaledToHeight(50);
    mirror = image.mirrored(true,false);
    setPixmap(QPixmap::fromImage(mirror));
}


void tom::matrix(int maze[15][15]){
    for(int i=0; i<N; i++)     //intialzing the matrix = 0
          for(int j=0; j<N; j++)
              adjacency[i][j] = 0;

    int k=0; //keep track of the source vertex

    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            if(maze[i][j] >= 0)    //this is a grass so it's a vertex in the adjacency matrix
            {
                //check whether the adjacent slots are avalible for movement
                //so it sets connections between the source and slot

                if(maze[i-1][j] >= 0)   //up
                    adjacency[k][maze[i-1][j] ] = 1;

                if(maze[i+1][j] >= 0)   // down
                    adjacency[k][maze[i+1][j] ] = 1; // 1  2/1

                if(maze[i][j+1] >= 0)   //right
                    adjacency[k][maze[i][j+1] ] = 1;

                if(maze[i][j-1] >= 0)   //left
                    adjacency[k][maze[i][j-1] ] = 1;
                k++;
            }
        }
    }
}

QVector<int> tom::Dijkstra(int Graph[N][N], int startVertex, int endVertex)
{
    if(endVertex == -2)
        endVertex = 56;   //if jerry is staying at home, make tom go to the middle

    bool done[N];
    int previous[N];
    int cost[N];

    int temp[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (Graph[i][j] == 0)
                temp[i][j] = INF;
            else
                temp[i][j] = Graph[i][j];

    for (int i = 0; i < N; i++)
    {
        if (i == startVertex)
        {
            done[i] = true;
            previous[i] = -1;
            cost[i] = 0;
        }
        else
        {
            done[i] = false;
            previous[i] = startVertex;
            cost[i] = temp[startVertex][i];
        }
    }
    int count = 1;
    while (count < N)
    {
        int minimum = INF;
        int currentVertex;
        for (int i = 0; i < N; i++)
        {
            if (done[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                currentVertex = i;
            }
        }
        done[currentVertex] = true;

        for (int i = 0; i < N; i++)
        {
            if (done[i] == false)
            {
                int value = cost[currentVertex] + temp[currentVertex][i];
                if (value < cost[i])
                {
                    cost[i] = value;
                    previous[i] = currentVertex;
                }
            }
        }
        count++;
    }

    QVector <int> path;
    int j = endVertex;     //returns only one path to the end vertex

        path.push_back(endVertex);
        while (j != startVertex)
        {
            path.insert(path.begin(), previous[j]);
            j = previous[j];
        }

    return path;
}

void tom::video(){
    QMediaPlayer *mMediaPlayer = new QMediaPlayer(this);
    mMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile("C:/Users/DELL/Desktop/TJ project/TJ/tommy.mp4")));

    QVideoWidget *mVideoWidget = new QVideoWidget(views);
    mMediaPlayer->setVideoOutput(mVideoWidget);
    scene()->addWidget(mVideoWidget);
    mVideoWidget->resize(900, 900);
    mVideoWidget->show();
    mMediaPlayer->play();
}
