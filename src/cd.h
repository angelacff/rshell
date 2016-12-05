void cd(string input)
{
	char *cd		= new char[3];
	char *spa		= new char[3];

	strcpy(cd,"cd");
	strcpy(spa," ");
	char *inputchar = new char [input.length()+1];
	strcpy(inputchar,input.c_str());
	
	char **argvIN     = new char*[strlen(inputchar)];
	char **argvSPACE  = new char*[strlen(inputchar)];
	int sz;
	initial(inputchar,argvIN); 
	checker(argvIN,argvSPACE,spa,sz);
	string checker=argvSPACE[0];
	if (checker!="cd" || sz>2)
	{
		cout << "Error: invalid call of the cd command" << endl;
		delete[] cd;
		delete[] spa;
		
		delete[] inputchar;
		delete[] argvIN;
		delete[] argvSPACE;
		return;
	}

	char* pPath;
	char* cwd;
	char buff[PATH_MAX + 1];
	
	if(argvSPACE[1]==NULL)
	{
		cwd = getcwd( buff, PATH_MAX + 1 );
		if( cwd == NULL )
			perror("getcwd");
		if(-1==setenv("OLDPWD",cwd,1))
			perror("setenv");

		pPath=getenv("HOME");
		if(pPath==NULL)
			perror("getenv");
		if(-1==chdir(pPath))
			perror("chdir");
		if(-1==setenv("PWD",pPath,1))
			perror("setenv");
			pPath = getenv("OLDPWD");

		delete cd;
		delete spa;
		
		delete[] inputchar;
		delete[] argvIN;
		delete[] argvSPACE;
		return;

	}

	checker = argvSPACE[1];
	if(checker=="-")//case where it is cd -
	{
		cwd=getcwd(buff,PATH_MAX+1);
		if(cwd==NULL)
			perror("getcwd");
		pPath=getenv("OLDPWD");
		if(pPath==NULL)
			perror("getenv");

		if(-1==chdir(pPath))
			perror("chdir");
		if(-1==setenv("PWD",pPath,1))
			perror("setenv");
		if(-1==setenv("OLDPWD",cwd,1))
			perror("setenv");

	}
	else //case where it is cd <pathname>
	{
		cwd = getcwd( buff, PATH_MAX + 1 );
		if( cwd == NULL )
			perror("getcwd");
		if(-1==setenv("OLDPWD",cwd,1))
			perror("setenv");
		if(checker=="~")
		{
			pPath = getenv("HOME");
			if(pPath==NULL)
				perror("getenv");
			checker=pPath;
		}
		if(-1==chdir(checker.c_str()))
			perror("chdir");
		cwd = getcwd(buff,PATH_MAX+1);
		if(cwd==NULL)
			perror("getcwd");
		if(-1==setenv("PWD",cwd,1))
			perror("setenv");
	}

	delete cd;
	delete spa;
	
	delete inputchar;
	delete[] argvIN;
	delete[] argvSPACE;



}

void executer(char **argv,int& status)
{
	
	int pid=fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid ==0){
	
		if(-1==execvp(argv[0],argv))
		{
			status = -1;
			perror("execvp");
		}
		exit (1);
	}
	else if (pid >0)
	{
		
		sigignore(SIGINT);
		if (-1 == wait(&status))
		{
			perror("wait");
			exit(1);
		}
		struct sigaction sa1;
		memset(&sa1, 0, sizeof(sa1));

		sa1.sa_handler = handler1;
		if(sigaction(SIGINT,&sa1,NULL)==-1)
			perror("sigaction");


	}
}

