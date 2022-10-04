#include <iostream>
#include "MapLoader.h"

using namespace std;
int main()
{
    cout << "Welcome everyone!" << endl;
    MapLoader mapLoader;

    Graph map = mapLoader.LoadMap();
}