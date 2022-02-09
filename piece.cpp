#include "piece.h"
#include <QDebug>
#include <qmath.h>
#include <game.h>

extern Game * game;

Piece::Piece(int x, int y, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    if (y < 9) {
        QString str = ":/images/piece-%1%2.png";
        char ch = x + 65;
        setPixmap(QPixmap(str.arg(ch).arg(y+1)));
        correct_place = {static_cast<qreal>(x) * 200/3, static_cast<qreal>(y) * 200/3};
        ++pieces_left;

        if ((x%2 == 1 && y%2 == 0) || (x%2 == 0 && y%2 == 1)) {
            if (x > 0) correct_place -= {24, 0};
        } else if ((x%2 == 1 && y%2 == 1) || (x%2 == 0 && y%2 == 0)) {
            if (y > 0) correct_place -= {0, 24};
        }
    } else {
        QString str = ":/images/piece-%1";
        id = x + 65;
        setPixmap(QPixmap(str.arg(id)+"5-reversed.png"));
        reversed = true;
        correct_place = {static_cast<qreal>(x) * 200/3, static_cast<qreal>(y - 5) * 200/3};

        if (x%2 == 1) {
            correct_place -= {24, 0};
        } else if (x%2 == 0) {
            correct_place -= {0, 24};
        }
    }

    if (x > 0) correct_place -= {3, 0};
    if (y > 0) correct_place -= {0, 2};

    setAcceptHoverEvents(true);
}

void Piece::flip() {
    QString str = ":/images/piece-%1";
    setPixmap(QPixmap(str.arg(id)+"5-open.png"));
    reversed = false;
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!placed) {
        setPos(mapToScene(event->pos() + m_shiftMouseCoords));
    }
}

int Piece::pieces_left = 0;

bool Piece::part2_started = false;

void Piece::game_reset() {
    part2_started = false;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_shiftMouseCoords = pos() - mapToScene(event->pos());
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    QPointF diff = pos() - correct_place;
    qreal delta = sqrt(diff.x()*diff.x() + diff.y()*diff.y());
    if (!placed && !reversed && delta < 5) {
        setPos(correct_place);
        placed = true;
        setAcceptHoverEvents(false);
        setZValue(0);
        --pieces_left;

        if (pieces_left == 0) {
            if (!part2_started) {
                part2_started = true;
                game->dialogbox->getBox(3,4);
            } else game->dialogbox->getBox(7,8);
        }
        emit piece_placed(pieces_left);
    }

    if (x() > 800 - boundingRect().width()*0.75) {
        setX(800 - boundingRect().width()*0.75);
    } else if (x() < -boundingRect().width()*0.25) {
        setX(-boundingRect().width()*0.25);
    }
    if (y() > 600 - boundingRect().height()*0.75) {
        setY(600 - boundingRect().height()*0.75);
    } else if (y() < -boundingRect().height()*0.25) {
        setY(- boundingRect().height()*0.25);
    }
    setCursor(QCursor(Qt::ArrowCursor));
}

void Piece::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    if (!part2_started || !reversed) {
        return;
    } else flip();

    if (pieces_left == 0) {
        game->dialogbox->getBox(5,6);
    }
}

void Piece::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Piece::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}
