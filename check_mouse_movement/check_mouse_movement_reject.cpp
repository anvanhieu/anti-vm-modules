//wait 5s, mouse not move --> exit >< do evil

#include <iostream>
#include <windows.h>

#define WAIT_TIME 5000


using namespace std;

int main()
{
	bool isMouseMove = false;
	POINT cursor_pos1, cursor_pos2;
	GetCursorPos(&cursor_pos1);	//get position of time A
	Sleep(WAIT_TIME);
	GetCursorPos(&cursor_pos2); //get position of time (A + 5s)
		
	if(cursor_pos1.x ==	cursor_pos2.x && cursor_pos1.y == cursor_pos2.y)
		cout << "Could be sandbox. Reject!!" << endl; 
	else
		cout << "Mouse was Moved. Do Evil" << endl;
	
	
	return 0;
}