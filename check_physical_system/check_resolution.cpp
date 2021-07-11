// references: https://stackoverflow.com/a/8690641
// https://www.bleepingcomputer.com/news/security/trickbot-malware-now-checks-screen-resolution-to-evade-analysis/

#include "wtypes.h"
#include <iostream>

using namespace std;

const int NOT_COMMON_RESOLUTION[] = {800*600, 1024*768};
 
// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

int is_suspicios_resolution(int h, int v)
{
	//int len = sizeof(NOT_COMMON_RESOLUTION);
	if (h < v)
		return false;
	for(int res:NOT_COMMON_RESOLUTION)
		if(h * v == res)
			return true;
	return false;		
}

int main()
{  
	     
   int horizontal = 0;
   int vertical = 0;
   GetDesktopResolution(horizontal, vertical);
   cout << horizontal << '\n' << vertical << '\n';
	if(is_suspicios_resolution(horizontal, vertical))
		cout << "Could be sandbox" << endl;
	else
		cout << "Not be common sandbox resolution" << endl;
	
   return 0;
}