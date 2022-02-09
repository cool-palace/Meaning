#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "QCursor"

class Piece : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(int x, int y, QGraphicsItem * parent = nullptr);
    ~Piece() override = default;

    QPointF correct_place;
    static int pieces_left;

public slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void flip();
    static void game_reset();

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
