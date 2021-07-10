
#include <iostream>
#include <Windows.h>

#define LIVE_TIME_THRESHOLD 15			// unit: minutes

using namespace std;

int main()
{
	unsigned int live_time = GetTickCount()/(1000 * 60);  // get and convert to minutes
	cout << live_time << " minutes" << endl;
	
	if (live_time < LIVE_TIME_THRESHOLD)
		cout << "Do nothing" << endl;
	else
	{
		cout << "System lives more than threshold" << endl;
		cout << "--> DO EVIL";
	}
	return 0;
}
