#include "puzzle.h"
#include "game.h"

extern Game * game;

Puzzle::Puzzle(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    puzzle_bg = new QGraphicsRectItem(this);
    puzzle_bg->setRect(0,0, 400, 600);
    puzzle_bg->setBrush(brush);

    puzzle_tip = new QGraphicsTextItem(this);
    QString cond = "Собери пазл здесь";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    puzzle_tip->setHtml(str1.arg(cond));
    puzzle_tip->setFont({"Comic Sans", 14});
    puzzle_tip->setTextWidth(400);
    puzzle_tip->setPos(0,300);

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 10; ++j) {
            piece[i][j] = new Piece(i, j, this);
            piece[i][j]->setPos(rand()%300+400, rand()%350+150);

//            The following lines are used to simplify the testing process
//            if (j < 9) {
//                piece[i][j]->setPos(piece[i][j]->correct_place);
//            } else piece[i][j]->setPos(rand()%300+400, rand()%350+150);

            piece[i][j]->setZValue(rand()%10+1);
            connect(piece[i][j],SIGNAL(piece_placed(int)),this,SLOT(score_update(int)));
        }
    }

    score_bg = new QGraphicsRectItem(this);
    score_bg->setRect(450,50, 300, 100);
    score_bg->setBrush(brush);

    score = new QGraphicsTextItem(this);
    score->setHtml(score_str.arg(Piece::pieces_left));
    score->setFont({"Comic Sans", 14});
    score->setTextWidth(300);
    score->setPos(450,75);

    quitButton = new Button(QString("Выйти"), this);
    int qxPos = 600 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),game,SLOT(displayMainMenu()));
    quitButton->hide();
}

Puzzle::~Puzzle() {
    delete puzzle_bg;
    delete puzzle_tip;
    delete score_bg;
    delete score;
    delete quitButton;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 10; ++j) {
            delete piece[i][j];
        }
    }
}

void Puzzle::score_update(int pieces_left) {
    score->setHtml(score_str.arg(pieces_left));
}
