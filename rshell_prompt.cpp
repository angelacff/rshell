#include <rshell.h>
using namespace std;
const int max_len=256;
void rshell_prompt(char *prompt);
void rshell_prompt(char *prompt)
{
	extern struct passwd *pwd;
	char mchid[max_len];	
	pwd=getpwuid(getuid());
	gethostname(mchid,max_len);
//	prompt=pwd+"@"+mchid+"$"+prompt;
	cout<<pwd<<"@"<<mchid<<"$"<<endl;
	//sprintf(pwd+mchid+prompt,"$");
	return;
}
int main()
{
	char *a="aaaaaaa";
	rshell_prompt(a);
	return 0;
}
