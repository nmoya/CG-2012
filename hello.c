#include <stdio.h>

#define N 8

void printHelloN(int n){
	int i;
	for(i=0;i<n;i++){
		printf("Hello! ");
	}
	printf("\n");
}

void printMensagemN(char* msg, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%s",msg);
	}
}

void printHello2(){
	printf("Hello world... 2!\n");
}
void printPT()
{
	printf("Ola mundo\n");
}
void printES()
{
	printf("Holla mundo! Viva la Revolucion!\n");
}

int main(){
	int i=0;
	printf("Hello world!\n");
	printES();
	printPT();
	printMensagemN("Hello world troll!\n",N);
	
}