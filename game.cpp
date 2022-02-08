#include "game.h"

Game::Game(QWidget* parent)
{
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(scene->width(),scene->height());

    music = new QMediaPlaylist();
    music->addMedia(QUrl("qrc:/sounds/music.mp3"));

    music->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    current_music = new QMediaPlayer();
    current_music->setPlaylist(music);
    current_music->setVolume(100);
    current_music->play();

}


void Game::displayMainMenu(){

    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Смысл"));
    QFont titleFont("Comic Sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button

    playButton = new Button(QString("Играть"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(puzzle_start()));
    scene->addItem(playButton);

    // create the quit button
    quitButton = new Button(QString("Выйти"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);


}

void Game::puzzle_start() {

    scene->clear();

    puzzle = new Puzzle();
    scene->addItem(puzzle);

    Piece::game_reset();

    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);
    dialogbox->getBox(0,2);

    show();
}

const QVector<Speechline> Game::speech = {
    {":/images/deadman.png", "Говорят, что жизнь напоминает сбор пазла. События и факты набираются тысячами тысяч маленьких кусочков, сложить цельную картину из которых бывает непросто..."}, //0//
    {":/images/deadman.png", "Впрочем, даже за один день может произойти многое, верно? Тем более, если и сам день особенный."},
    {":/images/deadman.png", "Сегодня как раз такой. Перед тобой лежат кусочки пазла одного дня твоей жизни. Попробуй собрать их в единое целое."},
    {":/images/deadman.png", "Хм... Похоже, остались лишние детали.<br>Они явно никуда не подходят...<br>Может ли в них быть какой-то смысл? И должен ли он быть?"},
    {":/images/deadman.png", "Думаю, мы не узнаем, пока не проверим сами. Может быть,<br>двойной клик по оставшимся кусочкам поможет что-то понять?"},
    {":/images/deadman.png", "Кажется, это сработало!<br>Давай перевернём теперь и остальные!"},
    {":/images/deadman.png", "Кстати, если приглядеться, то перевёрнутый кусочек очень похож на один из уже существующих элементов пазла.<br>Что если мы попробуем поставить его на то же место?"},
    {":/images/deadman.png", "Поздравляю! У тебя всё получилось! Видишь ли ты теперь смысл в этих странных кусочках?)"},
    {":/images/deadman.png", "Надеюсь, что да и что ты хорошо отметила этот день.<br>С днём рождения!)"},
};
