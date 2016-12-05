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
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
using namespace std;
using namespace boost;
#define END "THISISTHEENDOFOUTPUT"
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
	for (it= token.begin(); it != token.end(); ++it) {
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
         unsigned i=0;
	for(i=0;i<input.size();i++){
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
	for(unsigned i=0;i<input.size()-1;i++){
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



//get the command with ()
void parsing_pare(string input,string output[]){
	int j=0;
	input=dealwithPound(input);
	for (unsigned i=0;i<input.size();i++){
		if(input[i]=='('){
			int k=0;
			for (k=i+1;input[k]!=')';k++){
				output[j]=output[j]+input[k];
			}
			i=k;
			j++;

		}else{
			output[j]=input[i];
			j++;
		}
		
	}
	output[j]=END;
}
// get all the command and the connector
void parsing(string input,string &connector,string command[]){
	string output[500];
	// string connector;
	// string command[input.size()];
	parsing_pare(input,output);
	// int flag=0;
	for(unsigned i=0;output[i]!=END;i++){
		if(output[i]=="&"&&output[i+1]=="&"){
			connector=connector+"&";
		}else if(output[i]=="|"&&output[i+1]=="|"){
			connector=connector+"|";
		}else if(output[i]==";"){
			connector=connector+";";
		}
	}
	int j=0;
	for (unsigned i=0;output[i]!=END;i++){
		if (output[i]==";"){
			j++;
		}else if(output[i]=="&"&&output[i+1]=="&"){
			j++;
			i++;
		}else if(output[i]=="|"&&output[i+1]=="|"){
			j++;
			i++;
		}else if(output[i].size()>1){
			command[j]=output[i];
		}else{
			command[j]=command[j]+output[i];
		}
	}
	command[j+1]=END;
	
}
//second :test
int parsingSlash(string cmd, char* argv[]){
	int s = 0;
	char_separator<char> slash("/");
	tokenizer< char_separator<char> > token(cmd, slash);
	tokenizer< char_separator<char> >::iterator it = token.begin();
	for (it= token.begin(); it != token.end(); ++it) {
		string mystring = *it;
		char* temp = new char[mystring.size() + 1];
		strcpy(temp, mystring.c_str());
		argv[s] = temp;
		s++;
	}
	return s;
}
//command: [ ]
string parentheses(string command){
	size_t i=0,j=0;
	i=command.find('[');
	j=command.find(']');
	if(i!=string::npos && j!=string::npos){
		string t="test ";
		command=t+command.substr(i+1,j-i-1);
		
	}
	return command;
}
// add "-e" command: test path
string pre_test(string command){
	char* argv_space[101];
	int s_space=parsingSpace(command,argv_space);
	if(s_space==2){
		string left=argv_space[0];
     	string right=argv_space[1];
     	string additon=" -e ";
		command=left+additon+right;
	}
	return command;
}
void test(string command){
	command=pre_test(command);
	//substract "test" these four letters in the front
	char* argv_space[101];
	parsingSpace(command,argv_space);
	string path=argv_space[2];
    struct stat info;
    int result;
    result = stat (path.c_str(), &info);
    if(result!=0){
    	cout<<"(False)"<<endl;
    }
    else if(strcmp(argv_space[1],"-e")==0&&(S_ISREG(info.st_mode)||S_ISDIR(info.st_mode))){
    	cout<<"(True)"<<endl;
    }
    else if(strcmp(argv_space[1],"-d")==0&&(S_ISDIR(info.st_mode))){
    	cout<<"(True)"<<endl;
    }
    else if(strcmp(argv_space[1],"-f")==0&&(S_ISREG(info.st_mode))){
    	cout<<"(True)"<<endl;
    }else{
    	cout<<"(False)"<<endl;
    }

}

bool checktest(string command){
	//deal with space in front of the command
	unsigned i=0;
	while(i<command.size()&&command[i]==' '){
		i++;
	}
	command=command.substr(i);
	if(command.substr(0,4)=="test"){
		return true;
	}else{
		return false;
	}
}

///using to caculate &&, ||,; ,# .by setting flag
int caculator(string input,int status){
	bool flag=0;
	// input=dealwithPound(input);
	string connector=getConnector(input);
	char_separator<char> seperator("|&;");
	tokenizer< char_separator<char> > mytoken(input, seperator);
	tokenizer< char_separator<char> >::iterator it = mytoken.begin();
	int i=0;
	for (it=mytoken.begin(); it != mytoken.end(); ++it) {
		string command=*it;
		command=parentheses(command);
		if (flag==0){
		
			if(checktest(command)){
			test(command);
		}else{
			executer(command,status);
			}
			
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
	return status;
}
void caculate2(string command[],string connector,int &status){
	bool flag=0;
	if (connector.size()==0){
		caculator(command[0],status);
	}else {
		for (unsigned i=0;command[i]!=END;i++) {
			if (flag==0){
				status=caculator(command[i],status);
			}
			if(connector[i]==';'){
				flag=0;
			}else if(connector[i]=='&'&&status!=0){
				flag=1;
			}else if(connector[i]=='|'&&status==0){
				flag=1;
			}
			
		}
	}
}
