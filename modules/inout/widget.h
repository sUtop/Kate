#ifndef WIDGET_H
#define WIDGET_H

//#include "include/glew.h"
//#include

#include <QtGui>
#include <QGLWidget>
#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include <cmath>

#include "keyboard.h"

#define AR_TO_X 0x0001
#define AR_TO_Y 0x0002
#define AR_TO_Z 0x0003

//0x0fffffff


struct vector{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

class Widget : public QGLWidget
{
public:
    Widget(QWidget *parent = 0);


protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);   // нажатие на клавишу мыши
    void mouseMoveEvent(QMouseEvent* pe);    // перемещение мыши
//    void mouseReleaseEvent(QMouseEvent* pe);
//    void mouseReleaseEvent(QMouseEvent* pe); // отжатие клавиши мыши
    void wheelEvent(QWheelEvent *);          // вращение колесика
    void keyPressEvent ( QKeyEvent *);      // Ќажатие клавиш
    void keyReleaseEvent(QKeyEvent *);      // ќтпускание кнопки

private:
    int xRotation,yRotation,zRotation;
    float scale;
    QPoint mousePos;
    void drawAxis();
    void drawCube(vector v,float size,QColor clr);
    void drawCubeGLU(vector v,float size,QColor clr);
    // Вектор дальней точки, размер и ось по которой строим
    void drawRectangle(vector v,float size,char axis,int tap);
    void drawRectangleTop(vector v,float size,char axis);
    void drawRectangleFront(vector v,float size,char axis);
    void makeTone(char u);
    vector Cross(vector  vVector1, vector vVector2, vector  vVector3);

    Keyboard keyb;
    
    void render_text(const char *text, float x, float y, float sx, float sy);

    QFont font;
    QColor c;
    QString strText;




};

#endif // WIDGET_H
