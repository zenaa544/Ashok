Question 2 – Minimum streets lights
Problem Statement -: Street Lights are installed at every position along a 1-D road of length n. Locations[] (an array)
 represents the coverage limit of these lights. The ith light has a coverage limit of locations[i] that can range from 
 the position max((i – locations[i]), 1) to min((i + locations[i]), n ) (Closed intervals). Initially all the lights are switched off. 
 Find the minimum number of fountains that must be switched on to cover the road.

Jump Game II

Video Stitching

Minimum Taps

Interval Covering

Example

n = 3

locations[] = {0, 2, 13}then

For position 1: locations[1] = 0, max((1 – 0),

1) to mini (1+0), 3) gives range = 1 to 1

For position 2: locations[2] = 2, max((2-2),

1) to min( (2+2), 3) gives range = 1 to 3

For position 3: locations[3] = 1, max( (3-1),

1) to min( (3+1), 3) gives range = 2 to 3

For the entire length of this road to be covered, only the light at position 2 needs to be activated.

Returns:

int : the minimum number of street lights that must be activated

Constraints :

1<_n<_ 10^5
 O<_locations[i] <_ mini (n,100) (where 1 <_1<_10^5)
Sample Input For Custom Testing :

3 ->locations[] size n = 3

1 ->locations[] [1, 1, 1]

1 ->Sample Output

Sample Output :

1

#include <bits/stdc++.h>
using namespace std;

/*
 Problem:
 Street lights are placed at positions 1..n.
 locations[i] tells how far the lamp at position (i+1) can light.
 Each lamp covers a continuous range on the road.
 We want the MINIMUM number of lamps to cover the entire road [1..n].
*/

int minStreetLamps(vector<int>& locations) {
    
    int n = locations.size();

    /*
     maxReach[L] = the farthest right position (R)
     that any lamp can cover IF its lighting starts at position L.

     We use size n+2 to:
     - safely use 1-based indexing (1..n)
     - avoid boundary issues for i+1
    */
    vector<int> maxReach(n + 2, 0);

    // Step 1: Convert each lamp into a range [L, R]
    for (int i = 1; i <= n; i++) {
        int L = max(1, i - locations[i-1]);  // left boundary of lamp i
        int R = min(n, i + locations[i-1]);  // right boundary of lamp i

        // For this starting point L,
        // store the best (farthest) right coverage.
        maxReach[L] = max(maxReach[L], R);
    }

    /*
     lamps      = how many lamps we have turned on so far
     currentEnd = the farthest point that is ALREADY lit
     farthest   = the farthest point we COULD reach
                  using the best lamp seen so far
    */
    int lamps = 0;
    int currentEnd = 0;
    int farthest = 0;

    /*
     We now simulate walking along the road
     from position 1 to position n.
    */
    for (int i = 1; i <= n; i++) {

        // At position i:
        // check if any lamp starts lighting from here.
        // If yes, update our best possible future reach.
        farthest = max(farthest, maxReach[i]);

        /*
         If i is greater than currentEnd,
         it means we have stepped into a DARK area.
         The previously chosen lamps no longer cover us.

         So we are FORCED to turn on a new lamp.
        */
        if (i > currentEnd) {

            lamps++;                // we turn on one more lamp
            currentEnd = farthest;  // extend light as far as possible
        }

        /*
         If even after considering all lamps so far,
         the farthest we can reach is still before i,
         then position i can NEVER be lit.
         There is a gap in coverage → impossible.
        */
        if (farthest < i)
            return -1;
    }

    // If we successfully covered positions 1..n
    return lamps;
}
