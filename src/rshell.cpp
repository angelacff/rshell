#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
using namespace std;
using namespace boost;
//desigh the prompt
void prompt(){
	struct passwd *username = getpwuid(geteuid());
	if (!username)
		perror("getUsername");
	char machine[65];
	if (-1 == gethostname(machine, 65))
		perror("getHostname");
	cout << username->pw_name << "@" << machine << "$ ";
}
//parsing one line by space;
int parsingSpace(string cmd, char* argv[]){
	int s = 0;
	char_separator<char> space(" ");
	tokenizer< char_separator<char> > token(cmd, space);
	tokenizer< char_separator<char> >::iterator it = token.begin();
	for (it; it != token.end(); ++it) {
		string mystring = *it;
		char* temp = new char[mystring.size() + 1];
		strcpy(temp, mystring.c_str());
		argv[s] = temp;
		s++;
	}
	return s;
}
//using to execute one command
void executer(string cmd, int &status) {
	char* argv[101];
	int a = parsingSpace(cmd, argv);
	argv[a] = NULL;
	if (strcmp(argv[0], "exit") == 0) {
		exit(0);
	}
	int pid = fork();
	//child fuction is running
	if (pid==0){
		status=execvp(argv[0],argv);
	}
	else if(pid==-1){
		perror("execvp");
		exit(status);
	}else{
		if(wait(&status) == -1)
		perror("wait");
	}
}
//use to deal with pound
string dealwithPound(string input){
	for(int i=0;i<input.size();i++){
		if(input[i]=='#'){
			input=input.substr(0,i);
		}
	}
	return input;
}
//get all the needed connector in the input like '/','&',';','#'
//and '#'should be coped before
string getConnector(string input){
	string connector;
	for(int i=0;i<input.size()-1;i++){
		if(input[i]=='&'&&input[i+1]=='&'){
			connector=connector+"&";
		}else if(input[i]=='|'&&input[i+1]=='|'){
			connector=connector+"|";
		}else if(input[i]==';'){
			connector=connector+";";
		}
	}
	return connector;
}
//using to caculate &&, ||,; ,# .by setting flag
void caculator(string input,int status){
	bool flag=0;
	input=dealwithPound(input);
	string connector=getConnector(input);
	char_separator<char> seperator("|&;");
	tokenizer< char_separator<char> > mytoken(input, seperator);
	tokenizer< char_separator<char> >::iterator it = mytoken.begin();
	int i=0;
	for (it; it != mytoken.end(); ++it) {
		string command=*it;
		if (flag==0){
			executer(command,status);
		}
		if(connector[i]==';'){
			flag=0;
		}else if(connector[i]=='&'&&status!=0){
			flag=1;
		}else if(connector[i]=='|'&&status==0){
			flag=1;
		}
		i++;
	}
}
int main(){
	string input;
	int status=0;
	while(1){
		prompt();
		getline(cin,input);
		caculator(input,status);
	}
}
