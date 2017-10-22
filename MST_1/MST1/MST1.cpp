
#include "MainHeader.h"
#include <string>
#include "IOSwitcher.h"


int main()
{
	CIOSwitcher IOSwitcher(true, "Pd/pub01.in");

	string line;
	int count = 0;
	while (count < 3 && IOSwitcher.getline(line))  //input from the file in.txt
	{
		//if (count == 0)
			//cerr << line;
		count++;
	}

	cout << count;

    return 0;
}

