#pragma once
#include <iostream>
#include "Card.h"
#include<string>
#include "Player.h"

/*
Declaration of testCards free function
It creates 50 random Cards and adds the to the Deck* x
Calls the draw method on the Deck 50 times, adding them to the Hand
Calls the play method on every Card, deleting them from the Hand and adding them to the Deck
*/
void testCards();