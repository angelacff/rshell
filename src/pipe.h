#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <string>
#include <fstream>
#include <signal.h>
#include <csignal>
#include <limits.h>
using namespace std;

void handler1(int signum)
{
	if(signum==SIGINT)
	{
		cout << endl<<flush;
	}
}

void initial(char *inputchar,  char** argv)
{

	char *word = strtok(inputchar,"");
	int i =0;
	while (word != NULL)
	{
		argv[i] = word;
		
		word = strtok(NULL, "");
		i++;
	}
	argv[i]=0;
	delete[] word;
}
void checker(char** argvIN,char **argvOUT,char* ops,int& sz)
{
	int j=0;
	char *word= strtok(argvIN[0],ops);
	
	while (word!=NULL)
	{
		argvOUT[j] = word;

		word = strtok(NULL, ops);
		j++;
	}
	argvOUT[j]=0;
	sz=j;							
	delete[] word;				
}


int number_of_io_redirections =0;
