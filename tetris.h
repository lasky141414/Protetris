#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QWidget>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class tetris; }
QT_END_NAMESPACE

class tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit tetris(QWidget *parent = 0);
    ~tetris();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
    void down();
    bool candown();
    bool canleft();
    bool canright();
    void dispel();
    void dropad();

private:
    Ui::tetris *ui;
    QImage background;
    QImage T;
    QImage I;
    int row,col;
    int wall[20][10];
};
#endif // TETRIS_H
