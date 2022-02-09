#ifndef PUZZLE_H
#define PUZZLE_H

#include <QObject>
#include <QBrush>
#include <QFont>
#include "piece.h"
#include <button.h>


class Puzzle : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Puzzle(QGraphicsItem* parent = nullptr);
    ~Puzzle() override;

    Button* quitButton;

public slots:
    void score_update(int pieces_left);

private:
    Piece * piece [6][10];
    QBrush brush;
    QGraphicsRectItem * puzzle_bg;
    QGraphicsTextItem * puzzle_tip;
    QGraphicsRectItem * score_bg;
    QGraphicsTextItem * score;
    QString score_str = "<p style=\"text-align:center;\">Осталось собрать деталей:<br>%1</p>";
};

#endif // PUZZLE_H
