#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "button.h"
#include "puzzle.h"
#include "speechline.h"
#include "dialogbox.h"

class Game: public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget * parent = nullptr);

    QGraphicsScene * scene;
    DialogBox * dialogbox;
    Button* playButton;
    Button* quitButton;
    Puzzle * puzzle;

    QMediaPlaylist * music;
    QMediaPlayer * current_music;

    const static QVector<Speechline> speech;

public slots:
    void puzzle_start();
    void displayMainMenu();
};

#endif // GAME_H

