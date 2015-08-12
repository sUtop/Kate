#include "widget.h"
#include <iostream>
#include <string>
#include "string.h"
//#include "wingdi.h"

float ambient[4] = {1.5, 1.5, 1.5, 1};

//GLfloat mat_diffuse[]={0.1,0.5,0.8,1.0};
GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
//GLfloat low_shininess[]={5.0};

char sphere[] = {
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,1,1,1,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,1,1,1,0,0,
    0,1,1,1,1,1,0,
    0,0,1,1,1,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,

    0,0,0,1,0,0,0,
    0,0,1,1,1,0,0,
    0,1,1,1,1,1,0,
    1,1,1,1,1,1,1,
    0,1,1,1,1,1,0,
    0,0,1,1,1,0,0,
    0,0,0,1,0,0,0,

    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,1,1,1,0,0,
    0,1,1,1,1,1,0,
    0,0,1,1,1,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,1,1,1,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,


};

//#define numRandBox 5000
//                // 5000 - комфортное
//                // 200000 - максимум
//float shiftx[numRandBox];
//float shifty[numRandBox];
//float shiftz[numRandBox];

//GLubyte tone[128];

//GLubyte halftone[] = {
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
//      0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55
//   };


Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    resize(600,600);

    keyb.hight = 1.0f;
//    for(int i=0;i<numRandBox;i++){
//        shiftx[i] = (0.5 - ((float)rand())/RAND_MAX)*2;
//        shifty[i] = (0.5 - ((float)rand())/RAND_MAX)*2;
//        shiftz[i] = (0.5 - ((float)rand())/RAND_MAX)*2;
//    }

    for(int i=0;i<AR_KEYS;i++) keyb.keys_mask[i] = 0;
}

void Widget::initializeGL()
{
   qglClearColor(Qt::black);
   glEnable(GL_DEPTH_TEST); // “ест последовательности рисования полигонов

   glEnable(GL_CULL_FACE);

//       GLfloat mat_specular[] = {1,1,1,1};
          glEnable(GL_COLOR_MATERIAL_FACE);
          glEnable(GL_COLOR_MATERIAL);

          // ѕлоская заливка!
          glShadeModel(GL_FLAT);


       QFont font("OldEnglish", 10, QFont::Bold);
       QColor c(255, 128, 64);

//defaultScene();


//Включаем нужные механизмы
glEnable(GL_LIGHTING);
//glEnable(GL_LIGHT0);

//...и модель двухстороннего освещения
//GLfloat lmodel_ambient[]={1.0,1.0,1.0,1.0};
//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

//... и для обратных

//GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
//GLfloat mat_shininess[]={50.0};
//GLfloat light_position[]={1.0,1.0,1.0,0.0};
//GLfloat white_light[]={0.5,0.5,0.5,1.0};

//glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_shininess);
//glLightfv(GL_LIGHT0,GL_POSITION,light_position);
//glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
//glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(10, 10, nWidth-10, nHeight-10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Widget::paintGL() // рисование
{
    keyb.to_paint();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- Готовый поворот
    glRotatef(keyb.xRot,1.0,0.0,0.0);
    glRotatef(keyb.yRot,0.0,1.0,0.0);
    glRotatef(keyb.zRot,0.0,0.0,1.0);
    // --- Готовое смещение
    glTranslatef(keyb.xTra,keyb.yTra,keyb.zTra);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-keyb.hight/7 * ((float)width())/((float)height()),
               keyb.hight/7 * ((float)width())/((float)height()),
              -keyb.hight/8,     keyb.hight/6,        4*keyb.hight/6,      keyb.hight*10);

    drawAxis();


    glEnable(GL_POLYGON_STIPPLE);
//   makeTone(8);
//   glPolygonStipple(tone);
//   glPolygonStipple(halftone);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);


    glBegin(GL_QUADS);
    vector v={0,0,0},v_;

for(int m=0;m<10;m++)
    for(int l=0;l<5;l++){
    for(int j=0;j<5;j++){
    for(int k=0;k<5;k++){
    int posx=0,posy=0,posz=0;
    for(int i=0;i<7*7*7;i++){
       posx=i%7;
       posy=(i/7)%7;
       posz=(i/7/7)%7;
//       v_.z = 0;

       if(sphere[posx + posy*7 + posz*7*7]){
           v_.x = m * 5 + k + posx / 7.0;
           v_.y = j + posy / 7.0;
           v_.z = l + posz / 7.0;
           QColor clr(abs((posx/7.0)* 127), abs((posy/7.0) * 127), abs((posz/7.0) * 127), 255);
           drawCube(v_,1/7.0 + 0.001,clr);
       }
    }
    }
    }
}

    glEnd();


    //Ќастраиваем источник света
    GLfloat light_position[]={0.1,0.1,-1.0,0.0};
    GLfloat white_light[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
//    glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
//    glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
//    glLightfv(GL_LIGHT0,GL_AMBIENT,white_light);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
    GLfloat spot_direction[] = {0.0, 0.0, 1.0}; // Ќаправление на
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 2.0);


    GLfloat light_ambient[]={0.6,0.6,0.6,1.0};
    GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};
    GLfloat light_specular[]={0.2,0.2,0.2,1.0};
    GLfloat light_position1[]={2.0,2.0,0.4,1.0};
    GLfloat spot_direction1[]={-1.0,-1.0,0.0};

//    glLightfv(GL_LIGHT1,GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1,GL_SPECULAR, light_diffuse);
    glLightfv(GL_LIGHT1,GL_POSITION, light_position1);
    glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION, 0.3);
    glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 20.0);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, spot_direction1);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 8.0);

    glEnable(GL_LIGHT1);



    char str[30];
    sprintf(str," xRot = %f \t xTra = %f ",keyb.xRot,keyb.xTra);
    renderText(10,10,QString::fromStdString(str));
    for(int i=0;i<30;i++)str[i]=0;
    sprintf(str," yRot = %f \t yTra = %f ",keyb.yRot,keyb.yTra);
    renderText(10,20,QString::fromStdString(str));
    for(int i=0;i<30;i++)str[i]=0;
    sprintf(str," zRot = %f \t zTra = %f ",keyb.zRot,keyb.zTra);
    renderText(10,30,QString::fromStdString(str));
    sprintf(str,"mouseX = %f \t mouseY = %f  ",keyb.ptrMousePosition.x(),keyb.ptrMousePosition.y());
    renderText(10,40,QString::fromStdString(str));
    sprintf(str," hight = %f ---- ",keyb.hight);
    renderText(10,50,QString::fromStdString(str));


// ptrMousePosition
    glFlush();
}

//void Widget::mouseReleaseEvent(QMouseEvent *pe)
//{
////     updateGL(); // обновляем изображение
//}

void Widget::drawRectangle(vector v,float size,char axis,int tap)
{
    switch (axis){
    case AR_TO_X : {
        switch (tap) {
            case 1:{for(int i=0;i<4;i++){
                        glVertex3f( v.x
                                   ,v.y - ((i == 1)||(i == 2)) * size
                                   ,v.z - ((i == 2)||(i == 3)) * size);}
                     break;}
            case -1:{for(int i=0;i<4;i++){
                        glVertex3f( v.x
                                   ,v.y - ((i == 2)||(i == 3)) * size
                                   ,v.z - ((i == 1)||(i == 2)) * size);}
                    break;}
            }
        break;
    }
    case AR_TO_Y : {
            switch (tap){
            case 1:{for(int i=0;i<4;i++){
                glVertex3f( v.x - ((i == 1)||(i == 2)) * size
                           ,v.y
                           ,v.z - ((i == 2)||(i == 3)) * size);}
                break;}
            case -1:{for(int i=0;i<4;i++){
                glVertex3f( v.x - ((i == 2)||(i == 3)) * size
                           ,v.y
                           ,v.z - ((i == 1)||(i == 2)) * size);}
                break;}
            }
        break;
    }
    case AR_TO_Z:{
            switch (tap){
                case 1:{
                    for(int i=0;i<4;i++){
                        glVertex3f( v.x - ((i == 1)||(i == 2)) * size
                                   ,v.y - ((i == 2)||(i == 3)) * size
                                   ,v.z);}
                    break;}
            case -1:{
                for(int i=0;i<4;i++){
                    glVertex3f( v.x - ((i == 2)||(i == 3)) * size
                               ,v.y - ((i == 1)||(i == 2)) * size
                               ,v.z);}
                break;}
            }
        break;
    }
    }
}// void Widget::drawRectangle(vector v,float size,char axis)

void Widget::drawRectangleTop(vector v,float size,char axis)
{
    vector v1={0,0,0},v2={0,0,0},v3={0,0,0};
    switch (axis){
    case AR_TO_X : {
        for(int i=0;i<4;i++){
            glVertex3f(  v.x
                        ,v.y - ((i == 1)||(i == 2)) * size
                        ,v.z - ((i == 2)||(i == 3)) * size);
            if(i==0) {v1.x =  v.x; v1.y = v.y - ((i == 1)||(i == 2)) * size; v1.z = v.z - ((i == 2)||(i == 3)) * size;};
            if(i==1) {v2.x =  v.x; v2.y = v.y - ((i == 1)||(i == 2)) * size; v2.z = v.z - ((i == 2)||(i == 3)) * size;};
            if(i==3) {v3.x =  v.x; v3.y = v.y - ((i == 1)||(i == 2)) * size; v3.z = v.z - ((i == 2)||(i == 3)) * size;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    case AR_TO_Y : {
        for(int i=0;i<4;i++){
            glVertex3f(  v.x - ((i == 2)||(i == 3)) * size
                        ,v.y
                        ,v.z - ((i == 1)||(i == 2)) * size);
            if(i==0) {v1.x =  v.x - ((i == 2)||(i == 3)) * size; v1.y = v.y; v1.z = v.z - ((i == 1)||(i == 2)) * size;};
            if(i==1) {v2.x =  v.x - ((i == 2)||(i == 3)) * size; v2.y = v.y; v2.z = v.z - ((i == 1)||(i == 2)) * size;};
            if(i==3) {v3.x =  v.x - ((i == 2)||(i == 3)) * size; v3.y = v.y; v3.z = v.z - ((i == 1)||(i == 2)) * size;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    case AR_TO_Z:{
        for(int i=0;i<4;i++){
            glVertex3f(  v.x - ((i == 1)||(i == 2)) * size
                        ,v.y - ((i == 2)||(i == 3)) * size
                        ,v.z);
            if(i==0) {v1.x = v.x - ((i == 1)||(i == 2)) * size; v1.y = v.y - ((i == 2)||(i == 3)) * size; v1.z = v.z;};
            if(i==1) {v2.x = v.x - ((i == 1)||(i == 2)) * size; v2.y = v.y - ((i == 2)||(i == 3)) * size; v2.z = v.z;};
            if(i==3) {v3.x = v.x - ((i == 1)||(i == 2)) * size; v3.y = v.y - ((i == 2)||(i == 3)) * size; v3.z = v.z;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    }
}// void Widget::drawRectangleTop(vector v,float size,char axis)

void Widget::drawRectangleFront(vector v,float size,char axis)
{
    vector v1={0,0,0},v2={0,0,0},v3={0,0,0};
    switch (axis){
    case AR_TO_X : {
        for(int i=0;i<4;i++){
            glVertex3f(  v.x
                        ,v.y - ((i == 2)||(i == 3)) * size
                        ,v.z - ((i == 1)||(i == 2)) * size);
            if(i==0) {v1.x =  v.x; v1.y = v.y - ((i == 2)||(i == 3)) * size; v1.z = v.z - ((i == 1)||(i == 2)) * size;};
            if(i==1) {v2.x =  v.x; v2.y = v.y - ((i == 2)||(i == 3)) * size; v2.z = v.z - ((i == 1)||(i == 2)) * size;};
            if(i==3) {v3.x =  v.x; v3.y = v.y - ((i == 2)||(i == 3)) * size; v3.z = v.z - ((i == 1)||(i == 2)) * size;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    case AR_TO_Y : {
        for(int i=0;i<4;i++){
            glVertex3f(  v.x - ((i == 1)||(i == 2)) * size
                        ,v.y
                        ,v.z - ((i == 2)||(i == 3)) * size);
            if(i==0) {v1.x =  v.x - ((i == 1)||(i == 2)) * size; v1.y = v.y; v1.z = v.z - ((i == 2)||(i == 3)) * size;};
            if(i==1) {v2.x =  v.x - ((i == 1)||(i == 2)) * size; v2.y = v.y; v2.z = v.z - ((i == 2)||(i == 3)) * size;};
            if(i==3) {v3.x =  v.x - ((i == 1)||(i == 2)) * size; v3.y = v.y; v3.z = v.z - ((i == 2)||(i == 3)) * size;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    case AR_TO_Z:{
        for(int i=0;i<4;i++){
            glVertex3f(  v.x - ((i == 2)||(i == 3)) * size
                        ,v.y - ((i == 1)||(i == 2)) * size
                        ,v.z);
            if(i==0) {v1.x = v.x - ((i == 2)||(i == 3)) * size; v1.y = v.y - ((i == 1)||(i == 2)) * size; v1.z = v.z;};
            if(i==1) {v2.x = v.x - ((i == 2)||(i == 3)) * size; v2.y = v.y - ((i == 1)||(i == 2)) * size; v2.z = v.z;};
            if(i==3) {v3.x = v.x - ((i == 2)||(i == 3)) * size; v3.y = v.y - ((i == 1)||(i == 2)) * size; v3.z = v.z;};
        }
        vector norm = Cross(v1,v2,v3);
        glNormal3f(norm.x,norm.y,norm.z);
        break;
    }
    }
}// void Widget::drawRectangleFront(vector v,float size,char axis)

void Widget::drawCube(vector v,float size,QColor clr)
{
glColorMaterial(GL_FRONT, GL_DIFFUSE);
glColorMaterial(GL_FRONT, GL_AMBIENT);
glColorMaterial(GL_FRONT, GL_SPECULAR);
    qglColor(clr);
//    glColor4f(clr.1.00f, 1.00f, 1.00f, 1.0f); // устанавливается цвет последующих линий

//float size = 0.3;

    // Верхняя сторона (вокруг оси Z)
//    glBegin(GL_POLYGON);
    vector vzt = {v.x + size/2,v.y + size/2,v.z + size/2};
    drawRectangleTop(vzt,size,AR_TO_Z);
//    glEnd();

    // Ќижняя сторона (вокруг оси Z)
//    glBegin(GL_POLYGON);
    vector vzb = {v.x + size/2,v.y + size/2,v.z - size/2};
    drawRectangleFront(vzb,size,AR_TO_Z);
//    glEnd();

    // Ћевая сторона (вокруг оси Y)
//    glBegin(GL_POLYGON);
    vector vyb = vzt;
    drawRectangleTop(vyb,size,AR_TO_Y);
//    glEnd();

    // ѕравая сторона (вокруг оси Y)
//    glBegin(GL_POLYGON);
    vector vyt = {v.x + size/2,v.y - size/2,v.z + size/2};
    drawRectangleFront(vyt,size,AR_TO_Y);
//    glEnd();

    // ѕередняя сторона (вокруг оси X)
//    glBegin(GL_POLYGON);
    vector vxb = vzt;
    drawRectangleTop(vxb,size,AR_TO_X);
//    glEnd();

    // «адняя сторона (вокруг оси X)
//    glBegin(GL_POLYGON);
    vector vxt = {v.x - size/2,v.y + size/2,v.z + size/2};
    drawRectangleFront(vxt,size,AR_TO_X);
//    glEnd();

}

void Widget::drawAxis()
{
    glLineWidth(2.5f); // устанавливаем ширину линии

    // ось x
    qglColor(Qt::white);    // Ѕелая
    glBegin(GL_LINES); // построение линии
        glVertex3f( 200.0f,  0.0f,  0.0f);
        glVertex3f(-200.0f,  0.0f,  0.0f);
    glEnd();

//    QColor halfGreen(0, 128, 0, 255);
    qglColor(Qt::green);
    glBegin(GL_LINES);
        // ось y
        glVertex3f( 0.0f,  200.0f,  0.0f);
        glVertex3f( 0.0f, -200.0f,  0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f); //синяя
        // ось z
    qglColor(Qt::blue);
        glVertex3f( 0.0f,  0.0f,  200.0f);
        glVertex3f( 0.0f,  0.0f, -200.0f);
    glEnd();

    // «асечки на осях
    glBegin(GL_LINES);
    // X
    qglColor(Qt::white);    // Ѕелая
    glVertex3f( 1.0f,  -0.1f,  0.0f);
    glVertex3f( 1.0f,  0.1f,  0.0f);
    // ќсь Y
    qglColor(Qt::green);
    glVertex3f( 0.1f,  1.0f,  0.0f);
    glVertex3f( -0.1f,  1.0f,  0.0f);
    // Z
    qglColor(Qt::blue);
    glVertex3f( 0.1f,  0.0f,  1.0f);
    glVertex3f( -0.1f, 0.0f,  1.0f);
    glEnd();
}

vector Widget::Cross(vector  vVector1, vector vVector2, vector  vVector3)
{
    // Cross находит вектор, перпендикулярный плоскости, составляемой 2мя векторами.
    vector vNormal={0,0,0};                       // результирующий вектор

    vector vtmp1={0,0,0},vtmp2={0,0,0};
    vtmp1.x = vVector2.x - vVector1.x;
    vtmp1.y = vVector2.y - vVector1.y;
    vtmp1.z = vVector2.z - vVector1.z;

    vtmp2.x = vVector3.x - vVector2.x;
    vtmp2.y = vVector3.y - vVector2.y;
    vtmp2.z = vVector3.z - vVector2.z;

    // «начение X для векторы вычисляется так:  (V1.y * V2.z) - (V1.z * V2.y)
    vNormal.x = -((vtmp1.y * vtmp2.z) - (vtmp1.z * vtmp2.y));

    // «начение Y для векторы вычисляется так:  (V1.z * V2.x) - (V1.x * V2.z)
    vNormal.y = -((vtmp1.z * vtmp2.x) - (vtmp1.x * vtmp2.z));

    // «начение Z для векторы вычисляется так:  (V1.x * V2.y) - (V1.y * V2.x)
    vNormal.z = -((vtmp1.x * vtmp2.y) - (vtmp1.y * vtmp2.x));

    return vNormal;  // Возвращаем результат (направление, куда направлен полигон - нормаль)
}

void Widget::mousePressEvent(QMouseEvent* pe)
{
   keyb.mousePressEvent(pe);
   updateGL();
}

void Widget::mouseMoveEvent(QMouseEvent* pe)
{
    keyb.mouseMoveEvent(pe,height(),width());
   updateGL();
}

void Widget::wheelEvent(QWheelEvent *we)
{
    keyb.wheelEvent(we);
   updateGL();    
};          // вращение колесика


void Widget::keyPressEvent(QKeyEvent *ke)
{
   keyb.keyPressEvent(ke);
//   updateGL();
   };

void Widget::keyReleaseEvent(QKeyEvent *ke)
{
   keyb.keyReleaseEvent(ke);
//   updateGL();
   }


void Widget::getmail(){
   updateGL();
   keyb.xRot *= 1.001;
};

