#include "jerry.h"

jerry::jerry(int mazeData[15][15], int Size, QGraphicsView *view, QMediaPlayer *music){
    setImage("jerrys");
    setPos(50 + 50*7,50 + 50*7);
    setPosition(7, 7);

    for(int i=0; i<Size; i++){
        for(int j=0; j<Size; j++)
            board[i][j] = mazeData[i][j];
    }

    direction = true;
    heldCheese = NULL;
    powered = false;
    cheeseWin = 0;

    views = view;
    background = music;
}

void jerry::keyPressEvent(QKeyEvent * event){
    if(event->key() == Key_Up && (board[rows-1][columns] >= 0||board[rows-1][columns] == -2) )
        rows--;

    else if(event->key() == Key_Down && (board[rows+1][columns] >= 0||board[rows+1][columns] == -2) )
        rows++;

    else if(event->key() == Key_Left && (board[rows][columns-1] >= 0||board[rows][columns-1] == -2) ){
        columns--;
        mirroring();
        direction = false;
    }

    else if(event->key() == Key_Right && (board[rows][columns+1] >= 0 || board[rows][columns+1] == -2)){
        columns++;
        setPixmap(QPixmap::fromImage(image));  //return the setPixmap to image instead of mirror_image
        direction = true;
    }

    setPos(50 + 50 * columns,50 + 50 * rows);

    QList<QGraphicsItem*> items = collidingItems();
       for (int i = 0; i < items.size(); i++)
       {
           cheeseCollision(items[i]);

           homeCollision(items[i]);

           powerCollision(items[i]);

           portalCollision(items[i]);
       }

}

void jerry::cheeseCollision(QGraphicsItem *item){
    if (typeid(*item) == typeid(Cheese)){
        //Picking cheese
        if(heldCheese == NULL){                             //jerry is not holding a cheese
            heldCheese = dynamic_cast<Cheese*>(item);   //heldCheese pointer is now pointing at cheese

            if(heldCheese->IsAtHome())    //don't pick cheese at home
                heldCheese = NULL;

            else
            {
                scene()->removeItem(item);   //remove the cheese picture
                if(Ispowered())
                    setImage("jerry_c_p3");
                else
                    setImage("jerry_c");
            }
        }
    }
}

void jerry::homeCollision(QGraphicsItem *item){
    if(typeid(*item) == typeid(home)){
        home* h = dynamic_cast<home*>(item);
        if(heldCheese != nullptr && !h->exist()){   //jerry is holding a cheese, and there is no cheese at this home slot

            //set the cheese that jerry is carrying at this home slot and add it to the scene
            heldCheese->smallify();
            heldCheese->setPos(60 + h->getColumn() * 50, 65 + h->getRow() * 50);
            scene()->addItem(heldCheese);

            //Make the cheese at home, so jerry cannot pick it up again
            heldCheese->makeAtHome();

            //Make the home slot contains cheese
            h->makeExist();

            //Jerry is not holding a cheese now
            heldCheese = NULL;

            if(Ispowered())
                setImage("jerry_p3");
            else
                setImage("jerrys");

            cheeseWin++;

            QMediaPlayer *one = new QMediaPlayer();
            one->setMedia(QUrl("qrc:/cheeseSound.mp3"));
            one->setPosition(85);
            one->play();
        }

        if(win()){         //A function returns true if jerry returned all 4 cheeses at home
            stopBGmusic(); //A function to stop the background music when jerry wins
            QTimer::singleShot(500, this, SLOT(video()));
        }
    }
}

void jerry::powerCollision(QGraphicsItem *item){
    if (typeid(*item) == typeid(power)){
    {
        powered = true;
        scene()->removeItem(item);

        if (heldCheese == nullptr) //not holding cheese
            setImage("jerry_p3");

        else                       //holding cheese
            setImage("jerry_c_p3");

        //Jerry is now powered, and after 5 seconds he will return normal again
        QTimer::singleShot(5000, this, SLOT(delay()));
    }
}
}

void jerry::portalCollision(QGraphicsItem *item){
    if (typeid(*item) == typeid(portal))
    {
        if(item->x() == 50){
            setX(50*14);
            setPosition(5, 13);
        }
        else{
            setX(50*2);
            setPosition(5, 1);
        }
    }
}


void jerry::setImage(QString name){
    QImage image1(name);                  //It is like a temp image1 to insert jerry in image
    image1 = image1.scaledToWidth(50);    //set size
    image1 = image1.scaledToHeight(50);
    image.swap(image1);                   //insert image1 in image
    setPixmap(QPixmap::fromImage(image)); //this prototype is for converting QImage into QPixmap
    if(!direction)
        mirroring();
}

void jerry::mirroring(){
    QImage mirror;                         //create anothe QImage of jerry and flip it
    mirror = image.scaledToWidth(50);      //set its size equal to image size
    mirror = image.scaledToHeight(50);
    mirror = image.mirrored(true,false);   //mirror
    setPixmap(QPixmap::fromImage(mirror)); //setPixmap now the mirrored image
}

bool jerry::holdingCheese(){
    if (heldCheese == nullptr)
        return false;
    else
        return true;
}

void jerry :: nullify_ptr(){
    scene()->addItem(heldCheese);
    heldCheese = nullptr;
    setImage("jerrys");
}

void jerry::setPosition(int row, int column){
    rows = row; columns = column;
}

bool jerry::Ispowered()
{
    return powered;
}

int jerry::getRow(){
    return rows;
}

int jerry::getColumn(){
    return columns;
}

void jerry::delay(){
    if(heldCheese != NULL){
        setImage("jerry_c");
    }
    else
        setImage("jerrys");

    powered = false;
}

bool jerry::win(){
    if(cheeseWin == 4)
        return true;
    return false;
}

void jerry::stopBGmusic(){
    background->stop();
}


void jerry::video(){
    QMediaPlayer *mMediaPlayer = new QMediaPlayer(this);
    mMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile("C:/Users/DELL/Desktop/TJ project/TJ/jojo.mp4")));

    QVideoWidget *mVideoWidget = new QVideoWidget(views);
    mMediaPlayer->setVideoOutput(mVideoWidget);
    scene()->addWidget(mVideoWidget);
    mVideoWidget->resize(900, 900);
    mVideoWidget->show();
    mMediaPlayer->play();
}
