#include "Orders.h"
#include <string>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;

int Order::order_id = -1;
Order::Order() : player()
{
  setId();
  setType("Undefined Type");
}

Order::Order(Player *player)
{
  this->player = player;
}

Order::~Order()
{
  order_id--;
  this->player = nullptr;
}

Order::Order(const Order &order)
{
  order_id++;
  this->id = order_id;
  this->order_type = order.order_type;
  this->player = new Player(*(order.player));
  cout << "copy constructor called!!!" << endl;
}

Order &Order::operator=(const Order &order)
{
  this->order_type = order.order_type;
  this->player = new Player(*(order.player));
  return *this;
}

int Order::getId() const
{
  return this->id;
}

string Order::getType() const
{
  return this->order_type;
}

int Order::setId()
{
  order_id++;
  return this->id = order_id;
}

string Order::setType(string type)
{
  return this->order_type = type;
}

Player *Order::get_player() const
{
  return this->player;
}

string Order::getOrderEffect()
{
    return this->order_effect;
}

void Order::setOrderEffect(string effect)
{
    this->order_effect = effect;
}

bool Order::validate()
{
  cout << "This is the validate method of order class." << endl;
  return false;
}

//DON'T NEED SINCE PURE VIRTUAL METHOD
/*void Order::execute()
{
  if (validate())
  {
    cout << "This order is valid and prepare to execute." << endl;
    setOrderEffect(this->getType() + " is valid and prepare to execute.");
  }
  else
  {
    cout << "Error: this is an invalid order." << endl;
    setOrderEffect(this->getType() + " is an invalid order.");
  }
}*/

std::ostream &operator<<(std::ostream &strm, const Order &order)
{
  return strm << "Order ID: " << order.id << " --- "
              << "Order Type: " << order.order_type << endl;
}

string Order::stringToLog()
{
    return this->getOrderEffect();
}

// implement of OrdersList class
OrdersList::OrdersList()
{
  // create an empty vector
  vector<Order *> orders;
  this->order_list = orders;
}

OrdersList::~OrdersList()
{
  // delete every element in the vector
  for (int i = 0; i < this->order_list.size(); i++)
  {
    delete this->order_list[i];
    this->order_list[i] = nullptr;
  }
  this->order_list.clear();
}

OrdersList::OrdersList(const OrdersList &orders_List)
{
  order_list = orders_List.order_list;
}

OrdersList &OrdersList ::operator=(const OrdersList &orders_List)
{
  if (&orders_List != this)
  {
    this->order_list = orders_List.order_list;
  }
  return *this;
}

void OrdersList::addOrder(Order* order)
{
    order_list.push_back(order);
    notify(this);
}

void OrdersList::remove(int anOrder_id)
{
  for (int i = 0; i < order_list.size(); i++)
  {
    if (order_list[i]->getId() == anOrder_id)
    {
      order_list.erase(order_list.begin() + i);
      return;
    }
  }
  cout << "Error: no such order." << endl;
  return;
}

//   void move(int old_position, int new_position);
void OrdersList::move(int old_position, int new_position)
{
  // check if the move request is valid
  if (old_position < 0 || old_position >= order_list.size() || new_position < 0 || new_position >= order_list.size())
  {
    cout << "Error: Order not exist." << endl;
    return;
  }
  Order *temp_ptr = order_list[old_position];
  order_list.erase(order_list.begin() + old_position);
  order_list.insert(order_list.begin() + new_position, temp_ptr);
}

void OrdersList::push_back(Order *order)
{
  order_list.push_back(order);
}

// print out the value of each order in the list
void OrdersList::print()
{
  Order *curr;
  int i = 0;
  for (vector<Order *>::iterator it = order_list.begin(); it < order_list.end(); ++it)
  {
    curr = *it;
    i++;
    cout << "order: " << (*it)->getId() << " " << (*it)->getType() << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const OrdersList &order_List)
{
  strm << "Order list(orders address):" << endl;
  for (int i = 0; i < order_List.order_list.size(); i++)
  {
    Order *curr_ptr = order_List.order_list.at(i);
    strm << i << ". " << curr_ptr << endl;
  }
  return strm;
}

Order* OrdersList::getAddedOrder() {
    return this->addedOrder;
}

//Return the added Order's name
string OrdersList::stringToLog()
{
    return this->addedOrder->getType();
}

// implement of Deploy class
Deploy::Deploy() : Order()
{
  this->numberOfArmyUnits = 0;
  this->targetTerritory = NULL;
  // setId();
  setType("Deploy");
}

Deploy::Deploy(Player *player, int armyUnits, Territory *territory) : Order(player)
{
  this->numberOfArmyUnits = armyUnits;
  this->targetTerritory = territory;
  // setId();
  setType("Deploy");
}

Deploy::~Deploy()
{
  this->targetTerritory = nullptr;
}

Deploy::Deploy(const Deploy &deploy)
{
  // setId();
  setType("Deploy");
  this->player = new Player(*(deploy.player));
  this->numberOfArmyUnits = deploy.numberOfArmyUnits;
  this->targetTerritory = new Territory(*(deploy.targetTerritory));
}

Deploy &Deploy::operator=(const Deploy &deploy)
{
  // this->order_type = deploy.order_type;
  this->player = new Player(*(deploy.player));
  this->numberOfArmyUnits = deploy.numberOfArmyUnits;
  this->targetTerritory = new Territory(*(deploy.targetTerritory));
  return *this;
}

int Deploy::getNumberOfArmyUnits()
{
  return this->numberOfArmyUnits;
}

Territory *Deploy::getTargetTerritory()
{
  return this->targetTerritory;
}

bool Deploy::validate()
{
  if (get_player() == targetTerritory->getOwner())
  {
    cout << "Valid Deploy Order." << endl;
    return true;
  }
  cout << "Error, invalid deploy order." << endl;
  return false;
}

void Deploy::execute()
{
  if (validate())
  {
    cout << " Current Armies of  " << targetTerritory->getTerritoryName() << " : " << targetTerritory->getArmyNumber() << endl;
    int previousArmyInReinforcementPool = player->getReinforcementPool();
    int currentArmyInReinforcementPool = previousArmyInReinforcementPool - numberOfArmyUnits;
    player->setReinforcementPool(currentArmyInReinforcementPool);
    targetTerritory->addArmy(numberOfArmyUnits);
    ostringstream oss;
    oss << " Deploying " << numberOfArmyUnits << " armies to " << targetTerritory->getTerritoryName() << "." << endl;
    string effect = oss.str();
    cout << effect << endl;
    setOrderEffect(this->getType() + " is valid. " + effect);
  }
  else
  {
    cout << "Invalid deploy order. Cannot execute this deploy order. " << endl;
    setOrderEffect("Invalid deploy order. Cannot execute this deploy order. ");
  }
  notify(this);
}

std::ostream &operator<<(std::ostream &strm, const Deploy &deploy)
{
  return strm << "Order ID: " << deploy.getId() << " --- "
              << "Order Type: " << deploy.getType() << endl;
}

// implement of Advance class
Advance::Advance() : Order()
{
  // setId();
  setType("Advance");
  this->sourceTerritory = NULL;
  this->targetTerritory = NULL;
}

Advance::Advance(Player *player, Territory *source, Territory *target, int numberOfArmies) : Order(player)
{
  // setId();
  setType("Advance");
  this->sourceTerritory = source;
  this->targetTerritory = target;
  this->numberOfArmies = numberOfArmies;
}

Advance::~Advance()
{
  this->sourceTerritory = nullptr;
  this->targetTerritory = nullptr;
}

Advance::Advance(const Advance &advance)
{
  // setId();
  setType("Advance");
  this->sourceTerritory = new Territory(*(advance.sourceTerritory));
  this->targetTerritory = new Territory(*(advance.targetTerritory));
  this->player = new Player(*(advance.player));
  this->numberOfArmies = advance.numberOfArmies;
}

Advance &Advance::operator=(const Advance &advance)
{
  // this->order_type = deploy.order_type;
  this->sourceTerritory = new Territory(*(advance.sourceTerritory));
  this->targetTerritory = new Territory(*(advance.targetTerritory));
  this->player = new Player(*(advance.player));
  this->numberOfArmies = advance.numberOfArmies;
  return *this;
}

Territory *Advance::getSourceTerritory()
{
  return this->sourceTerritory;
}

Territory *Advance::getTargetTerritory()
{
  return this->targetTerritory;
}

int Advance::getNumberOfArmies()
{
  return this->numberOfArmies;
}

bool Advance::validate()
{
  cout << "This is the validate method of Advance class." << endl;
  return true;
}

void Advance::execute()
{
  if (validate())
  {
    ostringstream oss;
    oss << "This advance order is valid to execute." << endl; //TO CHANGE, NEED TO INCLUDE SOURCE + TARGET TERRITORY
    string effect = oss.str();
    cout << effect << endl;
    setOrderEffect(this->getType() + " is valid. " + effect);
  }
  else
  {
    cout << "Error, invalid advance order." << endl;
    setOrderEffect("Error, invalid advance order.");
  }
  notify(this);
}

std::ostream &operator<<(std::ostream &strm, const Advance &advance)
{
  return strm << "Order ID: " << advance.getId() << " --- "
              << "Order Type: " << advance.getType() << endl;
}

// implement of Bomb class
Bomb::Bomb() : Order()
{
  // setId();
  setType("Bomb");
}

Bomb::Bomb(Player *player, Territory *targetTerritory) : Order(player)
{
  setType("Bomb");
  this->targetTerritory = targetTerritory;
}

Bomb::~Bomb()
{
  this->targetTerritory = nullptr;
}

Bomb::Bomb(const Bomb &bomb)
{

  // setId();
  setType("Bomb");
  this->targetTerritory = new Territory(*(bomb.targetTerritory));
  this->player = new Player(*(bomb.player));
}

Bomb &Bomb::operator=(const Bomb &bomb)
{
  this->targetTerritory = new Territory(*(bomb.targetTerritory));
  this->player = new Player(*(bomb.player));
  return *this;
}

bool Bomb::validate()
{
  bool isAdjacent = false;
  for (auto iter : player->toAttack()) // Need to check this method when toAttack is done.
  {
    if (targetTerritory == iter)
    {
      isAdjacent = true;
      break;
    }
  };
  if (get_player() != targetTerritory->getOwner() && isAdjacent)
  {
    cout << "Valid Bomb Order." << endl;
    return true;
  }
  cout << "Error, invalid Bomb order." << endl;
  return false;
}

void Bomb::execute()
{
  if (validate())
  {
    int currentArmyInTargetTerr = targetTerritory->getArmyNumber();
    targetTerritory->removeArmy(currentArmyInTargetTerr / 2);

    ostringstream oss;
    oss << "Bomb order execute:  " << endl << "Previous army in target territory: " << currentArmyInTargetTerr << endl << "Current army in target territory: " << targetTerritory->getArmyNumber() << endl;
    string effect = oss.str();
    cout << effect << endl;
    setOrderEffect(this->getType() + " is valid. " + effect);
  }
  else
  {
    cout << "Invalid bomb order. Cannot execute this bomb order." << endl;
    setOrderEffect("Invalid bomb order. Cannot execute this bomb order.");
  }
  notify(this);
}

std::ostream &operator<<(std::ostream &strm, const Bomb &bomb)
{
  return strm << "Order ID: " << bomb.getId() << " --- "
              << "Order Type: " << bomb.getType() << endl;
}

// implement of Blockade class
Blockade::Blockade() : Order()
{
  // setId();
  setType("Blockade");
}

Blockade::Blockade(Player *player, Territory *targetTerritory) : Order(player)
{
  setType("Blockade");
  this->targetTerritory = targetTerritory;
}

Blockade::~Blockade()
{
  this->targetTerritory = nullptr;
}

Blockade::Blockade(const Blockade &blockade)
{

  // setId();
  setType("Blockade");
  this->targetTerritory = new Territory(*(blockade.targetTerritory));
  this->player = new Player(*(blockade.player));
}

Blockade &Blockade::operator=(const Blockade &blockade)
{
  // this->order_type = deploy.order_type;
  this->targetTerritory = new Territory(*(blockade.targetTerritory));
  this->player = new Player(*(blockade.player));
  return *this;
}

bool Blockade::validate()
{
  if (get_player() == targetTerritory->getOwner())
  {
    cout << "Valid Blockade Order." << endl;
    return true;
  }
  cout << "Error, invalid Blockade order." << endl;
  return false;
}

void Blockade::execute()
{
  if (validate())
  {
    cout << "Blockade order execute:  " << endl;
    cout << "Previous number of armies of " << targetTerritory << " : " << targetTerritory->getArmyNumber() << endl;
    targetTerritory->setArmyNumber((targetTerritory->getArmyNumber()) * 2);
    targetTerritory->setOwner(new Player("Neutral player"));
    cout << "Current number of armies of " << targetTerritory << " : " << targetTerritory->getArmyNumber() << endl;
    cout << "Current owner of " << targetTerritory << " : " << *(targetTerritory->getOwner()) << endl;

    std::ostringstream oss;
    oss << "Blockade order execute:  " 
        << endl << "Previous number of armies of " << targetTerritory << " : " 
        << targetTerritory->getArmyNumber() << endl 
        << "Current number of armies of " << targetTerritory << " : " 
        << targetTerritory->getArmyNumber() << endl 
        << "Current owner of " << targetTerritory << " : " << *(targetTerritory->getOwner()) << endl;
    std::string effect = oss.str();
    setOrderEffect(this->getType() + " is valid. " + effect);
    //cout << effect << endl;
  }
  else
  {
    cout << "Invalid Blockade order. Cannot execute this Blockade order." << endl;
    setOrderEffect("Invalid Blockade order. Cannot execute this Blockade order.");
  }
}

std::ostream &operator<<(std::ostream &strm, const Blockade &blockade)
{
  return strm << "Order ID: " << blockade.getId() << " --- "
              << "Order Type: " << blockade.getType() << endl;
}

// implement of Airlift class
Airlift::Airlift()
{
  // setId();
  setType("Airlift");
}

Airlift::~Airlift()
{
}

Airlift::Airlift(const Airlift &airlift)
{

  // setId();
  setType("Airlift");
  // TODO: need to figure out other data member of Airlift
}

Airlift &Airlift::operator=(const Airlift &airlift)
{
  // this->order_type = deploy.order_type;
  return *this;
}

bool Airlift::validate()
{
  cout << "This is the validate method of Airlift class." << endl;
  return true;
}

void Airlift::execute()
{
  if (validate())
  {
    cout << "This Airlift order is valid to execute." << endl;
    std::ostringstream oss;
    oss << "This Airlift order is valid to execute."; //TO CHANGE
    std::string effect = oss.str();
    setOrderEffect(this->getType() + " is valid. " + effect);
  }
  else
  {
    cout << "Error, invalid Airlift order." << endl;
    setOrderEffect("Error, invalid Airlift order.");
  }
}

std::ostream &operator<<(std::ostream &strm, const Airlift &airlift)
{
  return strm << "Order ID: " << airlift.getId() << " --- "
              << "Order Type: " << airlift.getType() << endl;
}

// implement of Negotiate class
Negotiate::Negotiate()
{
  // setId();
  setType("Negotiate");
}

Negotiate::~Negotiate()
{
}

Negotiate::Negotiate(const Negotiate &negotiate)
{

  // setId();
  setType("Negotiate");
  // TODO: need to figure out other data member of Negotiate
}

Negotiate &Negotiate::operator=(const Negotiate &negotiate)
{
  // this->order_type = deploy.order_type;
  return *this;
}

bool Negotiate::validate()
{
  cout << "This is the validate method of Negotiate class." << endl;
  return true;
}

void Negotiate::execute()
{
  if (validate())
  {
    cout << "This Negotiate order is valid to execute." << endl;
    std::ostringstream oss;
    oss << "This Negotiate order is valid to execute."; //TO CHANGE
    std::string effect = oss.str();
    setOrderEffect(this->getType() + " is valid. " + effect);
  }
  else
  {
    cout << "Error, invalid Negotiate order." << endl;
    setOrderEffect("Error, invalid Negotiate order.");
  }
}

std::ostream &operator<<(std::ostream &strm, const Negotiate &negotiate)
{
  return strm << "Order ID: " << negotiate.getId() << " --- "
              << "Order Type: " << negotiate.getType() << endl;
}