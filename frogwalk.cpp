#include <iostream.h>
#include "dice.h"

// simulate one-dimensional random walk
// borrowed from Owen Astrachan

int main()
{int position = 0;		// "frog" starts at position 0
 Dice coin(2);			// used for "coin flipping"
 int k;
 int numSteps;
 
	cout << "Enter number of steps: ";
	cin >> numSteps;
 
    for(k=0; k < numSteps; k++)
    {
        if (coin.Roll() == 1)
            position++;    // step to the right
        else
            position--;    // step to the left
    }
    
    cout << "final position = " << position << endl;
    
    return 0;
}
