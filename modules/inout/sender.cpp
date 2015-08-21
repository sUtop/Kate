#include "sender.h"

sender::sender(){};

sender::~sender(){};

void sender::addconnect(Widget &w){
connect(this, SIGNAL(mailto()), &w, SLOT(getmail()));
}
void sender::sendtic(){emit mailto();};
