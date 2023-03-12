//#include "functions.h"
////cheese functions
//bool Cheese::IsAtHome(){
//    return atHome;
//}
//void Cheese::makeAtHome(){
//    atHome = true;
//}
//void Cheese::smallify(){
//    pix = pix.scaledToHeight(30);
//    pix = pix.scaledToWidth(30);
//    setPixmap(pix);
//}

////home functions
//bool home::exist(){
//    return cheeseExist;
//}
//void home::makeExist(){
//    cheeseExist = true;
//}
//int home::getRow(){
//    return rows;
//}
//int home::getColumn(){
//    return columns;
//}

////jerry functions
//void jerry::cheeseCollision(QGraphicsItem *item){
//    if (typeid(*item) == typeid(Cheese)){
//        //Picking cheese
//        if(heldCheese == NULL){                             //jerry is not holding a cheese
//            heldCheese = dynamic_cast<Cheese*>(item);   //heldCheese pointer is now pointing at cheese

//            if(heldCheese->IsAtHome())    //don't pick cheese at home
//                heldCheese = NULL;

//            else{
//                scene()->removeItem(item);   //remove the cheese picture
//                if(Ispowered())
//                    setImage("jerry_c_p3");
//                else
//                    setImage("jerry_c");
//            }
//        }
//    }
//}
//void jerry::homeCollision(QGraphicsItem *item){
//    if(typeid(*item) == typeid(home)){
//        home* h = dynamic_cast<home*>(item);
//        if(heldCheese != nullptr && !h->exist()){   //jerry is holding a cheese, and there is no cheese at this home slot

//            //set the cheese that jerry is carrying at this home slot and add it to the scene
//            heldCheese->smallify();
//            heldCheese->setPos(60 + h->getColumn() * 50, 65 + h->getRow() * 50);
//            scene()->addItem(heldCheese);

//            //Make the cheese at home, so jerry cannot pick it up again
//            heldCheese->makeAtHome();

//            //Make the home slot contains cheese
//            h->makeExist();

//            //Jerry is not holding a cheese now
//            heldCheese = NULL;

//            if(Ispowered())
//                setImage("jerry_p3");
//            else
//                setImage("jerrys");

//            cheeseWin++;

//            QMediaPlayer *one = new QMediaPlayer();
//            one->setMedia(QUrl("qrc:/cheeseSound.mp3"));
//            one->setPosition(85);
//            one->play();
//        }

//        if(win()){         //A function returns true if jerry returned all 4 cheeses at home
//            stopBGmusic(); //A function to stop the background music when jerry wins
//            QTimer::singleShot(200, this, SLOT(video()));
//        }
//    }
//}
//void jerry::powerCollision(QGraphicsItem *item){
//    if (typeid(*item) == typeid(power)){
//    {
//        powered = true;
//        scene()->removeItem(item);

//        if (heldCheese == nullptr) //not holding cheese
//            setImage("jerry_p3");

//        else                       //holding cheese
//            setImage("jerry_c_p3");

//        //Jerry is now powered, and after 5 seconds he will return normal again
//        QTimer::singleShot(5000, this, SLOT(delay()));
//    }
//}
//}
//void jerry::portalCollision(QGraphicsItem *item){
//    if (typeid(*item) == typeid(portal))
//    {
//        if(item->x() == 50){
//            setX(50*14);
//            setPosition(5, 13);
//        }
//        else{
//            setX(50*2);
//            setPosition(5, 1);
//        }
//    }
//}
//void jerry::setImage(QString name){
//    QImage image1(name);                  //It is like a temp image1 to insert jerry in image
//    image1 = image1.scaledToWidth(50);    //set size
//    image1 = image1.scaledToHeight(50);
//    image.swap(image1);                   //insert image1 in image
//    setPixmap(QPixmap::fromImage(image)); //this prototype is for converting QImage into QPixmap
//    if(!direction)
//        mirroring();
//}
//void jerry::mirroring(){
//    QImage mirror;                         //create anothe QImage of jerry and flip it
//    mirror = image.scaledToWidth(50);      //set its size equal to image size
//    mirror = image.scaledToHeight(50);
//    mirror = image.mirrored(true,false);   //mirror
//    setPixmap(QPixmap::fromImage(mirror)); //setPixmap now the mirrored image
//}
//bool jerry::holdingCheese(){
//    if (heldCheese == nullptr)
//        return false;
//    else
//        return true;
//}
//void jerry :: nullify_ptr(){
//    scene()->addItem(heldCheese);
//    heldCheese = nullptr;
//    setImage("jerrys");
//}
//void jerry::setPosition(int row, int column){
//    rows = row; columns = column;
//}
//bool jerry::Ispowered(){
//    return powered;
//}
//int jerry::getRow(){
//    return rows;
//}
//int jerry::getColumn(){
//    return columns;
//}
//bool jerry::win(){
//    if(cheeseWin == 4)
//        return true;
//    return false;
//}
//void jerry::stopBGmusic(){
//    background->stop();
//}


////tom functions
//void tom::move(int row, int column){
//    setPos(50 + 50*column, 50 + 50*row);
//    rows=row; columns=column;
//}
//void tom::mirroring(){
//    QImage mirror;
//    mirror = image.scaledToWidth(50);
//    mirror = image.scaledToHeight(50);
//    mirror = image.mirrored(true,false);
//    setPixmap(QPixmap::fromImage(mirror));
//}
//void tom::Nourhan(int maze[15][15]){
//    for(int i=0; i<N; i++)     //intialzing the matrix = 0
//          for(int j=0; j<N; j++)
//              adjacency[i][j] = 0;

//    int k=0; //keep track of the source vertex

//    for(int i=0; i<15; i++){
//        for(int j=0; j<15; j++){
//            if(maze[i][j] >= 0)    //this is a grass so it's a vertex in the adjacency matrix
//            {
//                //check whether the adjacent slots are avalible for movement
//                //so it sets connections between the source and slot

//                if(maze[i-1][j] >= 0)   //up
//                    adjacency[k][maze[i-1][j] ] = 1;

//                if(maze[i+1][j] >= 0)   // down
//                    adjacency[k][maze[i+1][j] ] = 1; // 1  2/1

//                if(maze[i][j+1] >= 0)   //right
//                    adjacency[k][maze[i][j+1] ] = 1;

//                if(maze[i][j-1] >= 0)   //left
//                    adjacency[k][maze[i][j-1] ] = 1;
//                k++;
//            }
//        }
//    }
//}
//QVector<int> tom::Dijkstra(int Graph[N][N], int startVertex, int endVertex)
//{
//    if(endVertex == -2)
//        endVertex = 56;   //if jerry is staying at home, make tom go to the middle

//    bool done[N];
//    int previous[N];
//    int cost[N];

//    int temp[N][N];
//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < N; j++)
//            if (Graph[i][j] == 0)
//                temp[i][j] = INF;
//            else
//                temp[i][j] = Graph[i][j];

//    for (int i = 0; i < N; i++)
//    {
//        if (i == startVertex)
//        {
//            done[i] = true;
//            previous[i] = -1;
//            cost[i] = 0;
//        }
//        else
//        {
//            done[i] = false;
//            previous[i] = startVertex;
//            cost[i] = temp[startVertex][i];
//        }
//    }
//    int count = 1;
//    while (count < N)
//    {
//        int minimum = INF;
//        int currentVertex;
//        for (int i = 0; i < N; i++)
//        {
//            if (done[i] == false && cost[i] < minimum)
//            {
//                minimum = cost[i];
//                currentVertex = i;
//            }
//        }
//        done[currentVertex] = true;

//        for (int i = 0; i < N; i++)
//        {
//            if (done[i] == false)
//            {
//                int value = cost[currentVertex] + temp[currentVertex][i];
//                if (value < cost[i])
//                {
//                    cost[i] = value;
//                    previous[i] = currentVertex;
//                }
//            }
//        }
//        count++;
//    }

//    QVector <int> path;
//    int j = endVertex;     //returns only one path to the end vertex

//        path.push_back(endVertex);
//        while (j != startVertex)
//        {
//            path.insert(path.begin(), previous[j]);
//            j = previous[j];
//        }

//    return path;
//}

////main functions
//void scaling(QPixmap *pic, int size){
//    *pic = pic->scaledToHeight(size);
//    *pic = pic->scaledToWidth(size);
//}

//void addText(QGraphicsScene *scene){
//    QGraphicsTextItem *txt = new QGraphicsTextItem("Lives: ");
//    txt->setPos(50, 3);
//    txt->setDefaultTextColor(Qt::black);
//    QFont font;
//    font.setPixelSize(30);
//    font.setBold(true);
//    txt->setFont(font);
//    scene->addItem(txt);
//}

