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
#include "pipe.h"
#include "cd.h"
#include "cal.h"


int main()
{
		struct sigaction sa1;
		memset(&sa1, 0, sizeof(sa1));

		sa1.sa_handler = handler1;
		
		if(sigaction(SIGINT,&sa1,NULL)==-1)
			perror("sigaction");

		char* cwd;

		char buff[PATH_MAX + 1];

		cwd = getcwd( buff, PATH_MAX + 1 );
		if( cwd == NULL )
			perror("getcwd");
		
		if(-1==setenv("OLDPWD",cwd,1))
			perror("setenv");

	int status=0;

	while (1)
	{
		// to change the host and the filename everytime
		cin.clear();
		string prompt; 
		char host[400];
		char *login = getlogin();	
		prompt = login;

		if (!login) 
			perror("getlogin"); //if its not there error

		if (gethostname(host,300) !=0) //get host info
			perror("gethostname");  // error otherwise
	
		char* pPath1;
		pPath1 = getenv ("HOME");
		if (pPath1==NULL)
			perror("getenv");

		char* cwd;

		char buff[PATH_MAX + 1];

		cwd = getcwd( buff, PATH_MAX + 1 );
		if( cwd == NULL )
			perror("getcwd");
		string tpath = pPath1;
		string tpath2 = cwd;
		string prompt1;
		if(tpath2.find(tpath)!=string::npos)
		{
			prompt1 = tpath2.substr(tpath.size(),tpath2.size());
			prompt1 = "~" + prompt1;
		}
		else
		{
			prompt1 = tpath2;
		}


		if (login && host!=NULL)
		{
			for (int i=0;i<50;i++)
			{
				if (host[i]=='.')
					host[i]='\0'; 
			}

			prompt = prompt+"@"+host+ prompt1 + " $ "; 
		}
		else 
		{
			prompt = prompt1 + "$ ";

		}
		string input;
		number_of_io_redirections=0;
		cout << prompt;
		
		getline(cin,input);
	    // chech the #
		if (input.find("#") != string::npos)
		{
			input.resize(input.find("#"));
		}
		
		bool cd_check = false;
			
		if(input.find("cd")!=string::npos)
		{
			char *spa		= new char[3];
			strcpy(spa," ");
			char *inputchar = new char [input.length()+1];
			strcpy(inputchar,input.c_str());
			
			char **argvIN     = new char*[strlen(inputchar)];
			char **argvSPACE  = new char*[strlen(inputchar)];
			int sz;
			initial(inputchar,argvIN); 
			checker(argvIN,argvSPACE,spa,sz);
			string checker=argvSPACE[0];
			if(checker == "cd")
			{
				cd_check = true;
				cd(input);
			}

			delete[] spa;
			delete[] inputchar;
			delete[] argvIN;
			delete[] argvSPACE;
		}
		if(!cd_check)
		{
		    string connector;
		    string command[500];
		    parsing(input,connector,command);
	 	    caculate2(command,connector,status);

		}
	}
		return 0;
}

