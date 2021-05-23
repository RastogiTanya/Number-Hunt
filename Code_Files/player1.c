#include <stdio.h>
#include<string.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mystring.c"

FILE* fp;
int noOfTurns=10,p2_num=0,pid=0;


void signal_handler(int signum)
{
	if(signum==SIGUSR1)
	{
		int fd[2];
		pipe(fd);
		
		if(fork()==0)//child
		{
			close(fd[0]);//closing unused end ,read end
			
			fp=fopen("player2_guess.txt","r");//reading from the file
			if(fp==NULL)
			{
				printf("Error while opening file..  \n");
				kill(getppid(),SIGINT);//signal for parent
				
				exit(0);
			}
			int count=5;//player 2 doesn't write  in file
			do
			{
				fscanf(fp,"%d|%d",&pid,&p2_num);
				fseek(fp,0,SEEK_SET);//setting offset everytime at 0
				count--;
			} while(p2_num==0 && count>0);

			//wasn't able to read data then
			if(count==0)
			{
				printf("Error while reading file..\n");
				kill(getpid(),SIGINT);
			}
			//if data is read 
			char* p = convertIntegerToChar(pid);//in dynamic library 
			char* g = convertIntegerToChar(p2_num);
			char str[50];
			strcpy(str,p);
			strcat(str,"|");
			strcat(str,g);
			free(p);
			free(g);
			write(fd[1],str,50);
			close(fd[1]);//closing used end
			fclose(fp);
			exit(1);
		}//1234 | 24
		else//parent
		{
			close(fd[1]);//closing unused end
			char str[50];
			int status;
			wait(&status);
			read(fd[0],str,50);
			char * p = strtok(str,"|"); //separating pid and number using delimeter
			char * g = strtok(NULL,"|");
			pid = atoi(p); //converting to integer
			p2_num=atoi(g);
			printf("Player2 PID = %d\n",pid);
			int num_guessed;
			do
			{
				printf("Enter a number: ");
				scanf("%d", &num_guessed);
				if(num_guessed<p2_num)
					printf("Entered number is too low\n");
				else if(num_guessed>p2_num)
					printf("Entered number is too high\n");
				noOfTurns--;
			}while(num_guessed!=p2_num && noOfTurns>0);
			if(num_guessed==p2_num)//number guessed
			{
				kill(pid,SIGUSR1);
				printf("You Won \n");
			}
			if(noOfTurns==0)//out of turns
				kill(getpid(),SIGUSR2);
			close(fd[0]);//closing used end
		}
	}
	else if(signum==SIGUSR2)
	{
		if(noOfTurns==0)
			printf("\nYou lost \n");
		else
			printf("\nOther player won , you lost \n");
	}
	else if(signum==SIGABRT)
		printf("\nOther Player Left the Game, You Won \n");
	else
	{
		
		printf("\n ");
		remove("player1_guess.txt");
		remove("player2_guess.txt");
		if(pid!=0)//not child
		{
			kill(pid,SIGABRT);
		}
	}
	exit(0);
}
int main( int argc, char *argv[] ) 
{ 
	if(argc!=2)
	{
		printf("./player1.out <enter the number to be hunt>\n");
		exit(0);
	}
	int  status; 
	int org_num = atoi(argv[1]); //returns the integer representation of a string
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGABRT, signal_handler);
	fp = fopen("player1_guess.txt","w"); //opening file in write mode	
	fprintf(fp,"%d|%d",getpid(),org_num); //formated write, writing the the number 
	//to be hunt and pid of the process
	fclose(fp);
	printf("Player1 PID = %d\n",getpid());
	sleep(20);//waiting for player 2
	
} 
