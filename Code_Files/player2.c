#include <stdio.h>
#include<string.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int noOfTurns=10,pid;

void signal_handler(int signum)
{
	if(signum==SIGUSR1){
		if(noOfTurns==0)
			printf("\nYou lost \n");
		else
			printf("\nOther player won , you lost \n");
	}
	else if(signum==SIGABRT)
		printf("\nOther Player has Left the Game, You Won\n");
	else
	{
		printf("\n");
		remove("player1_guess.txt");
		remove("player2_guess.txt");
		printf("player 2 file %d \n",pid);
		kill(pid,SIGABRT);
	}
	exit(0);
}

int main( int argc, char *argv[] ) 
{
	if(argc!=2)
	{
		printf("./player2.out <enter the number to be hunt>\n");
		exit(0);
	}
	int org_num = atoi(argv[1]);
	signal(SIGUSR1, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGABRT, signal_handler);
	FILE* fp = fopen("player1_guess.txt","r");
	if(fp==NULL)
	{
		printf("Error while opening file..\n");
		exit(0);
	}
	int p1_num;
	fscanf(fp,"%d|%d",&pid,&p1_num); //reading from file of player 1
	fclose(fp);
	printf("Player1 PID = %d\n",pid);
	kill(pid,SIGUSR1);
	fp = fopen("player2_guess.txt","w");
	fprintf(fp,"%d|%d",getpid(),org_num);
	printf("Player2 PID = %d\n",getpid());
	fclose(fp); 
	
	int num_entered;
	do
	{
		printf("Enter a number: ");
		scanf("%d", &num_entered);
		if(num_entered<p1_num)
			printf("Entered number is too low\n");
		else if(num_entered>p1_num)
			printf("Entered number is too high\n");
		noOfTurns--;
	}while(num_entered!=p1_num && noOfTurns>0);
	if(num_entered==p1_num)
	{
		kill(pid,SIGUSR2);
		printf("You Won\n");
	}
	if(noOfTurns==0)
		kill(getpid(),SIGUSR1);
} 






