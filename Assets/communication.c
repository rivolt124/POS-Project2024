#include "communication.h"

void send_msg(int shmid)
{
	int msgid;
	msg_buff message;

	msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
	if (msgid == -1) {
		fprintf(stderr, "Failed to prep the message...");
		exit(1);
	}

	message.mtype = 1;
	message.shmid = shmid;

	if (msgsnd(msgid, &message, sizeof(message.shmid), 0) == -1) {
		fprintf(stderr, "Failed to send the message...");
		exit(1);
	}
}

int receive_msg()
{
	int msgid;
	msg_buff message;

	msgid = msgget(MSG_KEY, 0666);
	if (msgid == -1) {
		fprintf(stderr, "Failed to prep the message...");
		return -1;
	}

	if (msgrcv(msgid, &message, sizeof(message.shmid), 1, IPC_NOWAIT) == -1) {
		fprintf(stderr, "\nNo games available...\n");
		return -1;
	}

	return message.shmid;
}