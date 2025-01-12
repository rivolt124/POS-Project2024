#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "utils.h"

void send_msg(int shmid);
int receive_msg();

#endif