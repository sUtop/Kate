#include "keyboard.h"

void Keyboard::keyPressEvent(QKeyEvent* pe)
{
//    if( !pe->isAutoRepeat() )
//        std::cout<<" + Pressed key "<<pe->key()<<'\n';
//    std::cout<<" Pressed key "<<(int)pe->key()<<'\n';
//    keys_mask[pe->key()] =1;

//    if( !pe->isAutoRepeat() )
    switch (pe->key())
    {
    case Qt::Key_Up:
       keys_mask[AR_Key_Up] =1;
    break;
    case Qt::Key_Down:
       keys_mask[AR_Key_Down] =1;
    break;
    case Qt::Key_Left:
      keys_mask[AR_Key_Left] =1;
    break;
    case Qt::Key_Right:
        keys_mask[AR_Key_Right] =1;
    break;
    case Qt::Key_W:
        keys_mask[AR_Key_W] =1;
    break;
    case Qt::Key_A:
        keys_mask[AR_Key_A] =1;
    break;
    case Qt::Key_S:
        keys_mask[AR_Key_S] =1;
    break;
    case Qt::Key_D:
        keys_mask[AR_Key_D] =1;
    break;
    case Qt::Key_Q:
        keys_mask[AR_Key_Q] =1;
    break;
    case Qt::Key_E:
        keys_mask[AR_Key_E] =1;
    break;
    case Qt::Key_Space:
        keys_mask[AR_Key_Space] =1;
    break;
    case Qt::Key_Escape:
        keys_mask[AR_Key_Escape] =1;
    break;
    case Qt::Key_Plus:
        keys_mask[AR_Key_Plus] =1;
    break;
    case Qt::Key_Equal:
        keys_mask[AR_Key_Equal] =1;
    break;
    case Qt::Key_Minus:
        keys_mask[AR_Key_Minus] =1;
    break;
 }
}


void Keyboard::keyReleaseEvent(QKeyEvent *pe){

//    if( !pe->isAutoRepeat() )
//        std::cout<<" - Release key "<<pe->key()<<'\n';

//    for(int i=0;i<AR_KEYS;i++) keys_mask[i] = 0;
//    memcpy(keys_mask,0,sizeof(keys_mask));
    if( !pe->isAutoRepeat() )
    switch (pe->key())
    {
    case Qt::Key_Up:
       keys_mask[AR_Key_Up] =0;
    break;
    case Qt::Key_Down:
       keys_mask[AR_Key_Down] =0;
    break;
    case Qt::Key_Left:
      keys_mask[AR_Key_Left] =0;
    break;
    case Qt::Key_Right:
        keys_mask[AR_Key_Right] =0;
    break;
    case Qt::Key_W:
        keys_mask[AR_Key_W] =0;
    break;
    case Qt::Key_A:
        keys_mask[AR_Key_A] =0;
    break;
    case Qt::Key_S:
        keys_mask[AR_Key_S] =0;
    break;
    case Qt::Key_D:
        keys_mask[AR_Key_D] =0;
    break;
    case Qt::Key_Q:
        keys_mask[AR_Key_Q] =0;
    break;
    case Qt::Key_E:
        keys_mask[AR_Key_E] =0;
    break;
    case Qt::Key_Space:
        keys_mask[AR_Key_Space] =0;
    break;
    case Qt::Key_Escape:
        keys_mask[AR_Key_Escape] =0;
    break;
    case Qt::Key_Plus:
        keys_mask[AR_Key_Plus] =0;
    break;
    case Qt::Key_Equal:
        keys_mask[AR_Key_Equal] =0;
    break;
    case Qt::Key_Minus:
        keys_mask[AR_Key_Minus] =0;
    break;
 }

}// ќтпускание кнопки

void Keyboard::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();
}

void Keyboard::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void Keyboard::mouseMoveEvent(QMouseEvent* pe,int height,int width)
{

   xRot  += 180*(GLfloat)(pe->y()-ptrMousePosition.y())/height;
   zRot  -= 180*(GLfloat)(pe->x()-ptrMousePosition.x())/width;

   if(xRot > 180) xRot = -180;
   if(xRot < -180) xRot = 180;
   if(zRot > 180) zRot = -180;
   if(zRot < -180) zRot = 180;

   ptrMousePosition = pe->pos();

}


void Keyboard::scale_plus()
{
    hight += 0.1f;
}

void Keyboard::scale_minus()
{
    hight -= 0.1f;
}

void Keyboard::rotate_up()
{
    xRot -= 1.0;
    if(xRot < -180) xRot = 180;
}

void Keyboard::rotate_down()
{
    xRot += 1.0;
    if(xRot > 180) xRot = -180;
}

void Keyboard::rotate_left()
{
    zRot += 1.0;
    if(zRot > 180) zRot = -180;
}

void Keyboard::rotate_right()
{
    zRot -= 1.0;
    if(zRot < -180) zRot = 180;
}

void Keyboard::translate_down()
{
    zTra -= 0.05;
}

void Keyboard::translate_up()
{
    zTra += 0.05;
}

void Keyboard::translate_left()
{
    xTra += (float)cos(zRot*M_PI/180) /** sin(xRot*M_PI/180) */ * 0.05f;
    yTra -= (float)sin(zRot*M_PI/180) /** sin(xRot*M_PI/180) */ * 0.05f;
}

void Keyboard::translate_right()
{
    xTra -= (float)cos(zRot*M_PI/180) /** sin(xRot*M_PI/180) */ * 0.05f;
    yTra += (float)sin(zRot*M_PI/180) /** cos(xRot*M_PI/180) */ * 0.05f;
}

void Keyboard::translate_front(){
    xTra += (float)sin(zRot*M_PI/180) * sin(xRot*M_PI/180) * 0.05f;
    yTra += (float)cos(zRot*M_PI/180) * sin(xRot*M_PI/180) * 0.05f;
    zTra += (float)/*sin(zRot*M_PI/180) **/ cos(xRot*M_PI/180) * 0.05f;
}

void Keyboard::translate_back(){
    xTra -= (float)sin(zRot*M_PI/180) * sin(xRot*M_PI/180) * 0.05f;
    yTra -= (float)cos(zRot*M_PI/180) * sin(xRot*M_PI/180) * 0.05f;
    zTra -= (float)/*sin(zRot*M_PI/180) * */cos(xRot*M_PI/180) * 0.05f;
}



void Keyboard::to_paint(){
    if (keys_mask[AR_Key_Plus])
       scale_plus();
    if (keys_mask[AR_Key_Equal])
       scale_plus();
    if (keys_mask[AR_Key_Minus])
       scale_minus();
    if (keys_mask[AR_Key_Up])
       rotate_up();
    if (keys_mask[AR_Key_Down])
       rotate_down();
    if (keys_mask[AR_Key_Left])
      rotate_left();
    if (keys_mask[AR_Key_Right])
       rotate_right();
    if (keys_mask[AR_Key_S])
     translate_back();
    if (keys_mask[AR_Key_W])
     translate_front();
    if (keys_mask[AR_Key_A])
     translate_left();
    if (keys_mask[AR_Key_D])
     translate_right();
    if (keys_mask[AR_Key_Q])
     translate_down();
    if (keys_mask[AR_Key_E])
     translate_up();
    if (keys_mask[AR_Key_Space])
     defaultScene();
//    if (keys_mask[AR_Key_Escape])
//     exit();

}

void Keyboard::defaultScene()
{
   xRot=0; yRot=0; zRot=0;
   xTra=0; yTra=0; zTra=0;

//    xRot = 609.954;
//    yRot = 0;
//    zRot = 177.315;
//    xTra = 0.2;
//    yTra = -1.35;
//    zTra = -0.550003;

}

