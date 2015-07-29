/* 
 * File:   sender.h
 * Author: utop
 *
 * Created on 30 июля 2015 г., 2:22
 */

#ifndef SENDER_H
#define	SENDER_H

#include "widget.h"
#include <QObject>


class sender: public QObject{
    Q_OBJECT
public:
    sender();

public:
//    int m_value;
     ~sender();
//    virtual bool event(QEvent *){};
//    virtual bool eventFilter(QObject *, QEvent *){};
    
//public:
//    int value() const { return m_value; }
//public slots:
//    void mailfrom(){};
//    Try to add 
//    virtual destructor to your class. 
//    CCNode propably contains  some virtual methods and your compiler failed cope with it.
//    class MissionController: public CCNode     
//    {        public:          MissionController();         virtual ~MissionController();     };
    
    
public:
    void sendtic();
    void addconnect(Widget &w);
public:
    
signals:
    void mailto();
};



#endif	/* SENDER_H */

