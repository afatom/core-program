#ifndef __RECEIVER_H_
#define __RECEIVER_H_

#include "cdr.h"
#include "channel.h"
typedef struct Receiver Receiver;


Receiver* ReceiverCreate(size_t _threadsNum);


void ReceiverDestroy(Receiver* _receiver);



Receiver_Status ReceiverGetMessages(Receiver* _receiver, Channel* _channel);




#endif /*#ifndef __RECEIVER_H_*/
