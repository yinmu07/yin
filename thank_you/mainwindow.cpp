#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    //定义棋盘大小
    this->resize((CHESS_C + 1)*MAX_X,(CHESS_R + 1)*MAX_Y);
    this->setMaximumSize((CHESS_C + 1)*MAX_X,(CHESS_R + 1)*MAX_Y);
    this->setMinimumSize((CHESS_C + 1)*MAX_X,(CHESS_R + 1)*MAX_Y);
    this->setWindowTitle("你好五子棋！");

    b_black = false;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    DrawChessBoard();
    DrawHandChess();
    DrawChessItem();

    update();//强制更新界面
}

void MainWindow::DrawChessBoard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);//防止棋盘变形
    painter.setPen(QPen(QColor(Qt::black),2));//给边框线颜色和大小
    painter.setBrush(Qt::yellow);//给棋盘格子颜色
    //遍历绘制棋盘的所有的格子
    for(int i=0;i<CHESS_C;i++){
        for(int j=0;j<CHESS_R;j++){
            //绘制矩形(棋盘的格子)
            painter.drawRect((i+0.5)*MAX_X,(j+0.5)*MAX_Y,MAX_X,MAX_Y);
        }
    }
}

void MainWindow::DrawHandChess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if(b_black)
    {
        painter.setBrush(Qt::black);
    }else
    {
        painter.setBrush(Qt::white);
    }
    //获取鼠标位置(圆的半径)
    painter.drawEllipse(mapFromGlobal(QCursor::pos()),MAX_X/2,MAX_Y/2);
}

void MainWindow::DrawChessItem()
{
        QPainter painter(this);
        painter.setPen(QPen(QColor(Qt::transparent)));//给棋子边框说明
        //painter.setBrush((Qt::black));
        //painter.drawEllipse(65,65,50,50);
        //遍历棋子，它有就进行绘制
        for(int i=0;i<p_ChessItem.size();i++)
        {
            ChessItem item = p_ChessItem[i];//当前棋子的样式和位置赋值给棋子的这个类
            if(item._black)
            {
                painter.setBrush((Qt::black));
            }
            else
            {
                painter.setBrush((Qt::white));
            }
            DrawChessAtPoint(painter,item._pt);
        }
}

void MainWindow::DrawChessAtPoint(QPainter &painter,QPoint &point)
{
    //获取棋子的摆放位置
    QPoint ptCenter((point.x() + 0.5)*MAX_X,(point.y() + 0.5)*MAX_Y);
    painter.drawEllipse(ptCenter,MAX_X/2,MAX_Y/2);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //获取鼠标点击的位置
    qDebug()<<event->pos()<<endl;

    //定义点位
    QPoint pt;
    pt.setX((event->pos().x())/MAX_X);
    pt.setY((event->pos().y())/MAX_Y);

    //判断棋子是否存在
    for(int i= 0;i< p_ChessItem.size();i++){
        ChessItem item = p_ChessItem[i];
        if(item._pt == pt)
        {
            return;//如果存在就不做任何显示
        }
    }

    //如果不存在，则进行绘制，并且判断五子是否连接
    ChessItem item(pt,b_black);
    p_ChessItem.append(item);

    //统计四个点位是否连接
    int nLeft      = CountNearItem(item,QPoint(-1, 0));
    int nLeftUp    = CountNearItem(item,QPoint(-1,-1));
    int nLeftDown  = CountNearItem(item,QPoint(-1, 1));
    int nUp        = CountNearItem(item,QPoint( 0,-1));
    int nRight     = CountNearItem(item,QPoint( 1, 0));
    int nRightUp   = CountNearItem(item,QPoint( 1,-1));
    int nRightDown = CountNearItem(item,QPoint( 1, 1));
    int nDown      = CountNearItem(item,QPoint( 0, 1));

    if(
              (nLeft + nRight) >= 4
            ||(nLeftUp + nRightDown) >=4
            ||(nUp + nDown) >=4
            ||(nRightUp + nLeftDown) >=4
       )
    {
        QString str = b_black?"Black victory":"White victory";
        QMessageBox::information(NULL,"GAME OVER",str,QMessageBox::Yes);
        p_ChessItem.clear();
        return;
    }

    //该下一方下棋了
    b_black = !b_black;
}

int MainWindow::CountNearItem(ChessItem item,QPoint pt)
{
    int nCount = 0;

    item._pt += pt;
    while(p_ChessItem.contains(item))
    {
        nCount++;
        item._pt += pt;
    }

    return nCount;
}














