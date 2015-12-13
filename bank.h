#ifndef BANK_H
#define BANK_H
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>



struct bankAccount {
	
	char* accountName;
	float balance;
	int in_session;
//	pthread_mutex_t mutex;
};

struct bank{
	struct bankAccount** accounts;
//	pthread_mutex_t mutex;
	int numAccounts;
};


struct bank* createBank ();
void destroyBank(struct bank* bank);
struct bankAccount* createAccount(char* name);
void destroyAccount(struct bankAccount* account);
void credit( struct bankAccount* account,float amount);
void debit(struct bankAccount* account,float amount);
struct bankAccount* findAccount(struct bank* b, char* name;

#endif

