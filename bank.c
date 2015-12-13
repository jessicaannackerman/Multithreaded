#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "bank.h"
#include <pthread.h>


struct bank* createBank(){
	struct bank* tmp;
	tmp = (struct bank*)malloc(sizeof(struct bank));
	if(tmp == NULL){
		puts("could not create bank");
		return NULL;
	}
	//allocate memory for 20 accounts
	tmp->accounts = (struct bankAccount**)malloc(20*sizeof(struct bankAccount*))
		if(tmp->accounts == NULL){
			puts("could not create list of bank accounts");
			return NULL;
		}
	memset(tmp->accounts,0,sizeof(tmp->accounts));
	tmp->numAccounts = 0;

	return tmp;

}

void destroyBank(struct bank* bank){
	if(bank == NULL){
		return;
	}
	int i;
	struct bankAccount* del;
	for(i = 0;i < 20; i++){
		del = bank->accounts[i];
		destroyAccount(del);
	}
	free(bank->accounts);
	free(bank);
	return;
}

struct bankAccount* createAccount(char* name){
	struct bankAccount* tmp;
	//max size of account name is 100 chars
	if(name == NULL || strlen(name)>100){
		puts("either name is NULL or accountname is too big");
		return NULL;
	}
	tmp = (struct bankAccount*)malloc(sizeof(struct bankAccount));
	if(tmp == NULL){
		puts("could not create bank account");
		return NULL;
	}
	tmp->accountName = (char*)malloc(sizeof(char)*strlen(name));
	if(tmp->accountName == NULL){
		puts("could not set account name");
		free(tmp);
		return NULL;
	}
	strcpy(tmp->accountName, name);
	tmp->balance = 0;
	tmp->in_session = 0;
	return tmp;

}

void destroyAccount(struct bankAccount* account){
	if(account == NULL){
		return;
	}
	free(account->accountName);
	free(account);
}

void credit(struct bankAccount account,float amount)){
	if(account == NULL){
		puts("account is NULL");
	}
	if(amount < 0 ){
		puts("invalid amount");
	}
	account-balance += amount;
	puts("credit successful");

}
void debit(struct bankAccount* account,float amount){
	if(account == NULL){
		puts("account is NULL");
	}
	if(amount < 0 ){
		puts("invalid amount");
	}
	account->balance -= amount;
	puts("debit successful");
}


struct bankAccount* findAccount(struct bank* b, char* name){
	if(b == NULL){
		puts("bank is NULL");
		return NULL;
	}
	int i;
	for(i = 0; i<20; i++){
		if(strcmp(b->accounts[i]->accountName, name) == 0){
			puts("found account");
			return b->accounts[i];
		}
	}
	puts("account does not exist");
	return NULL;


}


int main(int argc, char** argv){
	return 0;
}
