#ifndef PLAYER_H
#define PLAYER_H

#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include <string>
#include <list>
#include <vector>
#include <ostream>
#include <algorithm>
#include <set>
#include "GameEngine.h"
using namespace std;

class Territory;
class OrdersList;
class Hand;
class PlayerStrategy;

extern int finishedPlayers;
extern GameEngine* ge;

class Player
{
private:
	//stream operator to access private members
	friend ostream& operator<<(ostream& outs, Player& theObject);

	//Player object members
	string name;
	OrdersList* orderslist;
	vector<Territory*> territories;
	Hand* hand;
	int reinforcementPool = 0;
	bool turnCompleted = false;
    bool canBeAttacked = true;
    bool canAttack = true;

	// Strategy for how issueOrder, toAttack, and toDefend will behave
	PlayerStrategy *playerStrategy;
public:

	int numAttacks = 0;
	int numDefense = 0;
	
	// TODO: How init Strategy?
	Player();
	~Player();
	//copy constructor
	Player(const Player& player);
	//assignment operator
	Player& operator=(const Player& player);
	Player(string name);
	Player(string playerName, Hand* newHand, OrdersList* newOrdersList, vector<Territory*> newTerritories);

	//Player's actions
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	void addTerritory(Territory* territory);
	void removeTerritory(Territory* territory);

	//helper method
	void cardOrder(int);
	int getContinentsBonus();

	//getters
	string getName() const;
	OrdersList* getOrdersList() const;
	Hand* getHand();
	vector<Territory*> getTerritories() const;
	int getReinforcementPool();
	bool getTurn();
	PlayerStrategy* getPlayerStrategy();

	//setters
	void setName(string name);
	void setOrdersList(OrdersList* list);
	void setHand(Hand* hand);
	void setTerritories(vector<Territory*> territories);
	void setReinforcementPool(int pool);
	void setTurn(bool turn);
	void setPlayerStrategy(PlayerStrategy*);
};
#endif