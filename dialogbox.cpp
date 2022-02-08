#include "dialogbox.h"
#include "game.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

extern Game * game; // there is an external global object called game

int DialogBox::start = 0;
int DialogBox::end = 0;

DialogBox::DialogBox(QGraphicsItem * parent) : QObject(), QGraphicsRectItem (parent)
{
    // set the brush
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);

    setRect(0,450,800,150);
    setBrush(brush);
    setZValue(1);

    line = new QGraphicsTextItem(this);
    avatar = new QGraphicsPixmapItem(this);

    line->setDefaultTextColor(Qt::white);
    line->setFont({"Comic Sans", 16});
    line->setTextWidth(640);

    setEnabled(true);

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(dialog_recharge()));

    hide();
}

DialogBox::~DialogBox() {
    delete line;
    delete avatar;
    delete timer;
}

void DialogBox::dialog_recharge() {
    ready_to_change = true;
}

void DialogBox::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Space && ready_to_change) {

        if (start == end) {
            hide();
            switch (end) {
            case 6:
                Piece::pieces_left = 6;
                game->puzzle->score_update(Piece::pieces_left);
                break;
            case 8:
                game->puzzle->quitButton->show();
                break;
            }

        } else {
            ++start;
            getBox(start, end);
        }

    }
}

void DialogBox::getBox(int in_start, int in_end) {
    ready_to_change = false;
    timer->start(750);

    start = in_start;
    end = in_end;

    int xPos = 0, yPos = 450;

    avatar->setPixmap(QPixmap(game->speech[start].speaker));

    if (game->speech[start].speaker.contains("player")) {
        avatar->setPos(xPos+650,yPos);
        line->setHtml(right_aligned_str.arg(game->speech[start].line));
        line->setPos(xPos+10,yPos+10);
    } else {
        avatar->setPos(xPos,yPos);
        line->setHtml(game->speech[start].line);
        line->setPos(xPos+150,yPos+10);
    }

    show();
    grabKeyboard();
    grabMouse();
}
