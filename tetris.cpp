#include "tetris.h"
#include "ui_tetris.h"
#include <QPainter>

//构造函数
tetris::tetris(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tetris)
{
    ui->setupUi(this);
    //设置窗口样式
    background.load("../pic/tetris.png");
    T.load("../pic/T.png");
    I.load("../pic/I.png");
    this->resize(background.width(),background.height());
    row = 0;col = 4;
    this->startTimer(200);
    for (int i=0;i<20;i++) {
        for (int j=0;j<10;j++) {
            wall[i][j] = 0;

        }

    }
}

tetris::~tetris()
{
    delete ui;
}

void tetris::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0,0,background);
    p.drawText(320,170,"SCORE");
    p.translate(15,15);
    for(int i=0;i<=10;i++){
        p.drawLine(i*26,0,i*26,20*26);
    }
    for(int j=0;j<=20;j++){
        p.drawLine(0,j*26,10*26,j*26);
    }
    p.drawImage(col*26,row*26,I);
    for (int i=0;i<20;i++) {
        for (int j=0;j<10;j++) {
            if(wall[i][j] == 1){
                p.drawImage(j*26,i*26,I);
            }

        }

    }

}

void tetris::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    if(key == Qt::Key_Left){
        if(canleft()){
            --col;
        }
    }if(key == Qt::Key_Right){
        if(canright()){
            ++col;
        }
    }if(key == Qt::Key_Up){
        --row;
    }if(key == Qt::Key_Down){
        down();
    }if(key == Qt::Key_Space){
        while(candown()){
            down();
        }
    }
    update();
}



void tetris::timerEvent(QTimerEvent *){
    down();
    update();
}

void tetris::down(){
    dispel();
    if(candown()){
        ++row;
    }else {
        wall[row][col] = 1;
        row = 0,col = 4;
    }
}

bool tetris::candown(){
    if(wall[row+1][col] == 1)
        return false;
    if(row >= 19)
        return false;
    return true;
}

bool tetris::canleft(){
    if(col <= 0)
        return false;
    if(wall[row][col-1] == 1)
        return false;
    return true;
}

bool tetris::canright(){
    if(col >= 9)
        return false;
    if(wall[row][col+1] == 1)
        return false;
    return true;
}

void tetris::dispel(){
    int count = 0;
    for (int i=19;i>0;i--) {
        for (int j=0;j<10;j++) {
            if(wall[i][j] == 1){
                count++;
            }
            if(count == 10){
                for (int l=0;l<10;l++){
                    wall[i][l] = 0;
                }dropad();
            }
        }count = 0;
    }
    update();
}

void tetris::dropad(){
    for (int m=19;m>0;m--) {
        for (int n=0;n<10;n++) {
            wall[m][n] = wall[m-1][n];
        }
    }
}
