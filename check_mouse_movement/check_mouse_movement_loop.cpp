#include <iostream>
#include <windows.h>

#define WAIT_TIME 5000

using namespace std;

int main()
{
	bool isMouseMove = false;
	while(!isMouseMove)
	{
		POINT cursor_pos1, cursor_pos2;
		GetCursorPos(&cursor_pos1);	//get position of time A
		Sleep(WAIT_TIME);
		GetCursorPos(&cursor_pos2); //get position of time (A + 5s)
		
		if(cursor_pos1.x ==	cursor_pos2.x && cursor_pos1.y == cursor_pos2.y)
		{
			cout << "Do nothing" << endl; 
			continue;
		}
		else
			isMouseMove = true;
	}
	
	cout << "Mouse was Moved. Do Evil" << endl;
	
	
	return 0;
}