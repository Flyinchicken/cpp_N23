#include "Orders.h"

#include <iostream>

using std::cout;
using std::endl;

int Order::order_id = 0;
Order::Order()
{
  order_id++;
  this->id = new int(order_id);
  this->order_type = new string("Undefined Type");
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

int Order::getId()
{
  return *this->id;
}

string Order::getType()
{
  return *this->order_type;
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
    strm << i + 1 << ". " << curr_ptr << endl;
  }
  return strm;
}