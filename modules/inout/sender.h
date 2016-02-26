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
     ~sender();
    void sendtic();
    void addconnect(Widget &w);
    
signals:
    void mailto();
};



#endif	/* SENDER_H */

