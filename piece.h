#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "QCursor"

class Piece : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Piece(int x, int y, QGraphicsItem * parent = nullptr);
    ~Piece();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void flip();
    static void game_reset();
    QPointF correct_place;
    static int pieces_left;

private:

    static bool part2_started;
    char id = '0';
    QPointF center;

    QPointF m_shiftMouseCoords;
    bool placed = false;
    bool reversed = false;

signals:
    void piece_placed(int);
};

#endif // PIECE_H
