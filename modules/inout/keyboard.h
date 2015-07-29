/* 
 * File:   keyboard.h
 * Author: utop
 *
 * Created on 22 июля 2015 г., 1:35
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include <qevent.h>
//#include <Qevent.h>
//#include <gltypes.h>
//#include "GL/gl.h"
#include <QtOpenGL>
//#include "gl.h"
#include <cmath>


#define AR_Key_Up 0
#define AR_Key_Down 1
#define AR_Key_Left 2
#define AR_Key_Right 3
#define AR_Key_W 4
#define AR_Key_A 5
#define AR_Key_S 6
#define AR_Key_D 7
#define AR_Key_Q 8
#define AR_Key_E 9
#define AR_Key_Space 10
#define AR_Key_Escape 11
#define AR_Key_Plus 12
#define AR_Key_Equal 13
#define AR_Key_Minus 14

#define AR_KEYS  50


struct Keyboard{
void keyPressEvent(QKeyEvent* pe);
void keyReleaseEvent(QKeyEvent *pe);
void wheelEvent(QWheelEvent* pe);
void mousePressEvent(QMouseEvent* pe);
void mouseMoveEvent(QMouseEvent*,int,int);

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();
    void translate_left();
    void translate_right();
    void translate_front();
    void translate_back();
    void to_paint();
    
    QPoint ptrMousePosition;
    GLfloat xRot;//поворот камеры относительно X
    GLfloat yRot;//поворот камеры относительно Y
    GLfloat zRot;//поворот камеры относительно Z
    GLfloat xTra;// перемещение камеры по оси X( происходит перд поворотом)
    GLfloat yTra;// перемещение камеры по оси Y( происходит перд поворотом)
    GLfloat zTra;// перемещение камеры по оси Z( происходит перд поворотом)

    float hight; // Высота наблюдателя
    
    char keys_mask[AR_KEYS];
};

#endif	/* KEYBOARD_H */

