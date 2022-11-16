#pragma once

#include <string>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "LoggingObserver.h"

using std::string;
using std::vector;

class Territory;
class Player;
class GameEngine;
// Each kind of order is implemented as a subclass of the Order class.
// classes must implement a correct copy constructor,
// assignment operator,
// and stream insertion operator.
// using destructor to avoid memory leaks
class Order : public Subject, public ILoggable
{
public:
	Order();
	virtual ~Order(); // destructor should be virtual since the order class is abstract now
	Order(Player*);
	Order(const Order& order);            // copy constructor
	Order& operator=(const Order& order); // assignment operator
	int getId() const;
	string getType() const;
	int setId();
	string setType(string type);
	// add the player to the order
	Player* player;
	Player* get_player() const;
	string getOrderEffect();
	void setOrderEffect(string);

	// define virtual function of validate and execute,
	// allow calling this function of a subclass with a pointer to the base class
	virtual bool validate();
	virtual void execute() = 0;

	string stringToLog();
	// This is use save alliance and advance
	static GameEngine* game;

private:
	// friend stream insertion operator to the class to access private member
	friend std::ostream& operator<<(std::ostream&, const Order&);
	static int order_id; // static variable use to automatic generate id for all objects
	int id;              // store the id of the order (Each order have one unique id)
	string order_type;
	string order_effect;
};

// The OrdersList class contains a list of Order objects.
class OrdersList : public Subject, public ILoggable
{
public:
	OrdersList();
	~OrdersList();
	OrdersList(const OrdersList& orders_List);
	OrdersList& operator=(const OrdersList& orders_List);
	void remove(int anOrder_id);
	void move(int old_position, int new_position);
	void push_back(Order* order);
	void print();
	vector<Order*> order_list;
	string stringToLog();
	void addOrder(Order* order);
	Order* getAddedOrder();

private:
	// friend stream insertion operator to the class to access private member
	friend std::ostream&
		operator<<(std::ostream&, const OrdersList&);
	Order* addedOrder;
	// All data members of user-defined class type must be of pointer type.
};

// The different kinds of orders are:
// deploy, advance, bomb, blockade, airlift, and negotiate.
class Deploy : public Order
{
public:
	Deploy();
	Deploy(Player* player, int numberOfArmyUnits, Territory* targetTerritory);
	~Deploy();
	Deploy(const Deploy& deploy);
	Deploy& operator=(const Deploy& deploy);

	bool validate();
	void execute();

	int getNumberOfArmyUnits();
	Territory* getTargetTerritory();

private:
	int numberOfArmyUnits;
	Territory* targetTerritory;
	friend std::ostream& operator<<(std::ostream&, const Deploy&);
};

class Advance : public Order
{
public:
	Advance();
	Advance(Player* player, Territory* sourceTerritory, Territory* targetTerritory, int numberOfArmies);
	~Advance();
	Advance(const Advance& advance);
	Advance& operator=(const Advance& advance);

	bool validate();
	void execute();

	Territory* getSourceTerritory();
	Territory* getTargetTerritory();
	int getNumberOfArmies();
	string getAdvanceType();
	void setAdvanceType(string type);

private:
	Territory* sourceTerritory;
	Territory* targetTerritory;
	int numberOfArmies;
	string advanceType = "Attack";
	friend std::ostream& operator<<(std::ostream&, const Advance&);
};

class Bomb : public Order
{
public:
	Bomb();
	Bomb(Player* player, Territory* targetTerritory);
	~Bomb();
	Bomb(const Bomb& bomb);
	Bomb& operator=(const Bomb& bomb);

	bool validate();
	void execute();

private:
	Territory* targetTerritory;
	friend std::ostream& operator<<(std::ostream&, const Bomb&);
};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(Player* player, Territory* targetTerritory);
	~Blockade();
	Blockade(const Blockade& blockade);
	Blockade& operator=(const Blockade& blockade);

	bool validate();
	void execute();

private:
	Territory* targetTerritory;
	friend std::ostream& operator<<(std::ostream&, const Blockade&);
};

class Airlift : public Order
{
public:
	Airlift();
	Airlift(Player* player, Territory* sourceTerritory, Territory* targetTerritory, int numberOfArmies);
	~Airlift();
	Airlift(const Airlift& airlift);
	Airlift& operator=(const Airlift& airlift);

	bool validate();
	void execute();

private:
	Territory* sourceTerritory;
	Territory* targetTerritory;
	int numberOfArmies;
	friend std::ostream& operator<<(std::ostream&, const Airlift&);
};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(Player* player, Player* targetPlayer);
	~Negotiate();
	Negotiate(const Negotiate& negotiate);
	Negotiate& operator=(const Negotiate& negotiate);

	bool validate();
	void execute();

private:
	Player* targetPlayer;
	friend std::ostream& operator<<(std::ostream&, const Negotiate&);
};