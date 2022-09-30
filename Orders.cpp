#include "Orders.h"

#include <iostream>

using std::cout;
using std::endl;

int Order::order_id = -1;
Order::Order()
{
  setId();
  setType("Undefined Type");
}

Order::~Order()
{
  order_id--;
}

Order::Order(const Order &order)
{
  order_id++;
  this->id = new int(order_id);
  this->order_type = new string(*(order.order_type));
  cout << "copy constructor called!!!" << endl;
}

Order &Order::operator=(const Order &order)
{
  this->order_type = new string(*(order.order_type));
  return *this;
}

int Order::getId() const
{
  return *this->id;
}

string Order::getType() const
{
  return *this->order_type;
}

int *Order::setId()
{
  order_id++;
  return this->id = new int(order_id);
}

string *Order::setType(string type)
{
  return this->order_type = new string(type);
}

bool Order::validate()
{
  cout << "This is the validate method of order class." << endl;
  return false;
}

void Order::execute()
{
  if (validate())
  {
    cout << "This order is valid and prepare to execute." << endl;
  }
  else
  {
    cout << "Error: this is an invalid order." << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const Order &order)
{
  return strm << "Order ID: " << *order.id << " --- "
              << "Order Type: " << *order.order_type << endl;
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

void OrdersList ::remove(int anOrder_id)
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
  if (old_position < 0 || old_position > order_list.size() || new_position < 0 || new_position > order_list.size())
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

// implement of Deploy class
Deploy::Deploy()
{
  setId();
  setType("Deploy");
}

Deploy::~Deploy()
{
}

Deploy::Deploy(const Deploy &deploy)
{

  setId();
  setType("Deploy");
  // TODO: need to figure out other data member of deploy
}

Deploy &Deploy::operator=(const Deploy &deploy)
{
  // this->order_type = deploy.order_type;
  return *this;
}

bool Deploy::validate()
{
  cout << "This is the validate method of Deploy class." << endl;
  return true;
}

void Deploy::execute()
{
  if (validate())
  {
    cout << "This deploy order is valid to execute." << endl;
  }
  else
  {
    cout << "Error, invalid deploy order." << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const Deploy &deploy)
{
  return strm << "Order ID: " << deploy.getId() << " --- "
              << "Order Type: " << deploy.getType() << endl;
}

// implement of Advance class
Advance::Advance()
{
  setId();
  setType("Advance");
}

Advance::~Advance()
{
}

Advance::Advance(const Advance &advance)
{

  setId();
  setType("Advance");
  // TODO: need to figure out other data member of Advance
}

Advance &Advance::operator=(const Advance &advance)
{
  // this->order_type = deploy.order_type;
  return *this;
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
    cout << "This advance order is valid to execute." << endl;
  }
  else
  {
    cout << "Error, invalid advance order." << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const Advance &advance)
{
  return strm << "Order ID: " << advance.getId() << " --- "
              << "Order Type: " << advance.getType() << endl;
}

// implement of Bomb class
Bomb::Bomb()
{
  setId();
  setType("Bomb");
}

Bomb::~Bomb()
{
}

Bomb::Bomb(const Bomb &bomb)
{

  setId();
  setType("Bomb");
  // TODO: need to figure out other data member of bomb
}

Bomb &Bomb::operator=(const Bomb &bomb)
{
  // this->order_type = deploy.order_type;
  return *this;
}

bool Bomb::validate()
{
  cout << "This is the validate method of Bomb class." << endl;
  return true;
}

void Bomb::execute()
{
  if (validate())
  {
    cout << "This bomb order is valid to execute." << endl;
  }
  else
  {
    cout << "Error, invalid bomb order." << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const Bomb &bomb)
{
  return strm << "Order ID: " << bomb.getId() << " --- "
              << "Order Type: " << bomb.getType() << endl;
}

// implement of Blockade class
Blockade::Blockade()
{
  setId();
  setType("Blockade");
}

Blockade::~Blockade()
{
}

Blockade::Blockade(const Blockade &blockade)
{

  setId();
  setType("Blockade");
  // TODO: need to figure out other data member of Blockade
}

Blockade &Blockade::operator=(const Blockade &blockade)
{
  // this->order_type = deploy.order_type;
  return *this;
}

bool Blockade::validate()
{
  cout << "This is the validate method of Blockade class." << endl;
  return true;
}

void Blockade::execute()
{
  if (validate())
  {
    cout << "This Blockade order is valid to execute." << endl;
  }
  else
  {
    cout << "Error, invalid Blockade order." << endl;
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
  setId();
  setType("Airlift");
}

Airlift::~Airlift()
{
}

Airlift::Airlift(const Airlift &airlift)
{

  setId();
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
  }
  else
  {
    cout << "Error, invalid Airlift order." << endl;
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
  setId();
  setType("Negotiate");
}

Negotiate::~Negotiate()
{
}

Negotiate::Negotiate(const Negotiate &negotiate)
{

  setId();
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
  }
  else
  {
    cout << "Error, invalid Negotiate order." << endl;
  }
}

std::ostream &operator<<(std::ostream &strm, const Negotiate &negotiate)
{
  return strm << "Order ID: " << negotiate.getId() << " --- "
              << "Order Type: " << negotiate.getType() << endl;
}