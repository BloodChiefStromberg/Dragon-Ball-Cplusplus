//unit_test.cpp: testing unit
#include "DungeonLevel.h"
#include <vector>
#include <string>

int g_iID = 0;

using namespace std;

// Practicum 8 : Implement this method
void markPosition(vector<string> & vLevel, int x, int y)
{
	//Check to see if x and y are in bounds
	if (x > vLevel[y].size() || y > vLevel.size())
	{
		return;
	}
	else if (vLevel[y][x] != '#' && vLevel[y][x] != '.' && vLevel[y][x] != '<' && vLevel[y][x] != '>')
	{
		return;
	}
	else
	{
		if (vLevel[y][x] != '>' && vLevel[y][x] != '<')
			vLevel[y][x] = 'X';
		markPosition(vLevel, x + 1, y);
		markPosition(vLevel, x - 1, y);
		markPosition(vLevel, x, y + 1);
		markPosition(vLevel, x, y - 1);
	}
	return;
}


bool testLevel(vector<string>& vLevel, DungeonLevel& dlLevel)
{
	// Display the initial state
	cout << "Initial state: " << endl;
	for( auto itOuter = vLevel.begin(); itOuter != vLevel.end(); itOuter++ )
	{
		for( auto itInner = (*itOuter).begin(); itInner != (*itOuter).end(); itInner++ )
		{
			cout << (*itInner);
		}
		cout << endl;
	}

	int iTotalRoomTiles = 0;
	int iCounter = 0;

	//Check for overlapping squares
	vector<Point*> vRoomPoints = dlLevel.getRoomPoints();
	for (auto itr = vRoomPoints.begin(); itr != vRoomPoints.end(); itr++ )
	{
		int iCounter = 0;
		Point* pCurrent = (*itr);
		for (auto itr = vRoomPoints.begin(); itr != vRoomPoints.end(); itr++ )
		{
			if (pCurrent->getX() == (*itr)->getX() && pCurrent->getY() == (*itr)->getY())
				iCounter++;
			if (iCounter >= 2)
			{
				cout << "Found two of the same point! Aarons a bozo!" << endl;
				return false;
			}
		}
	}

	cout << endl << "No overlapping walls! Great!" << endl;
	cout << "Total room tiles (including walls): " << vRoomPoints.size() << endl;

	cout << endl;

	int x = -1;
	int y = -1;

	// pick a starting position
	for( int i = 0; i < vLevel.size(); i++ )
	{
		for( int j = 0; j < vLevel[i].size(); j++ )
		{
			if( vLevel[i][j] == '.' || vLevel[i][j] == '#' )
			{
				// Starting position just has to be a room or
				// tunnel tile
				x = j;
				y = i;
			}
		}
	}

	if( x == -1 )
	{
		cout << "Unable to find starting position!" << endl;
		return false;
	}

	// Call the function which actually marks the tiles -- it should mark
	// the starting tile, then any adjacent to it, etc -- so after it's done,
	// everything that can be connected to the starting tile should be
	// marked.
	markPosition(vLevel, x, y);

	bool bCorrect = true;
	bool bFoundUpStairs = false;
	bool bFoundDownStairs = false;

	cout << endl << "Marked state: " << endl;
	// Outer loop
	for( auto itOuter = vLevel.begin(); itOuter != vLevel.end(); itOuter++ )
	{
		// Inner loop
		for( auto itInner = (*itOuter).begin(); itInner != (*itOuter).end(); itInner++ )
		{
			cout << (*itInner);


			// Now, test if it's a room/tunnel tile -- if it's still
			// one after we've
			if( (*itInner) == '.' || (*itInner) == '#' )
			{
				bCorrect = false;
			}
			if ((*itInner) == '<')
				bFoundUpStairs = true;
			if ((*itInner) == '>')
				bFoundDownStairs = true;
		}

		cout << endl;
	}

	cout << endl;

	if( !bCorrect )
	{
		cout << "Unreached room/tunnel tile detected!" << endl;
	}

	if (!(bFoundUpStairs && bFoundDownStairs))
	{
		cout << "Didn't find stairs!" << endl;
		bCorrect = false;
	}

	return bCorrect;
}


int main(int argc, char* argv[])
{
	int iRuns = atoi(argv[1]);
	cout << "iRuns = " << iRuns << endl; //debug
	int iNumOfTests = 20;
	for(int i = 0; i < iRuns; i++)
	{
		DungeonLevel dlLevel = DungeonLevel(79, 20);
		vector<string> dlLevelString = dlLevel.toString();
		if (!testLevel(dlLevelString, dlLevel))
		{
			cout << "Test failed. Aaron sucks." << endl;
			return 1;
		}
		char temp;
		cout << "This is a pause to try and ensure randomness. Press enter to continue, hold enter to zip through all tests." << endl;
		temp = cin.get();
	}
	cout << "All tests passed! Aaron is king, and worked really hard. Give him an A." << endl;
	return 0;
}
