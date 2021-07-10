#include <iostream>
#include <Windows.h>
#include <string>

#define UNLEN 256

using namespace std;

int main()
{
	char username[UNLEN+1];
	DWORD username_len = UNLEN+1;
	GetUserName(username, &username_len);
	
	cout << username << endl;
	return 0;
}