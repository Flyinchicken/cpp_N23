#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

// Each kind of order is implemented as a subclass of the Order class.
// classes must implement a correct copy constructor,
// assignment operator,
// and stream insertion operator.
// using destructor to avoid memory leaks
class Order
{
public:
  Order();
  ~Order();
  Order(const Order &order);            // copy constructor
  Order &operator=(const Order &order); // assignment operator
  int getId();
  string getType();

  // define virtual function of validate and execute,
  // so subclasses of Order can overwrite this two functions
  virtual bool validate();
  virtual void execute();

private:
  // friend stream insertion operator to the class to access private member
  friend std::ostream &operator<<(std::ostream &, const Order &);
  static int order_id; // static variable use to automatic generate id for all objects
  int *id;             // use to store id of the order
  string *order_type;
};

// The OrdersList class contains a list of Order objects.
class OrdersList
{
public:
  OrdersList();
  ~OrdersList();
  OrdersList(const OrdersList &orders_List);
  OrdersList &operator=(const OrdersList &orders_List);
  void remove(int anOrder_id);
  void move(int old_position, int new_position);
  void push_back(Order *order);
  void print();

private:
  // friend stream insertion operator to the class to access private member
  friend std::ostream &
  operator<<(std::ostream &, const OrdersList &);
  // All data members of user-defined class type must be of pointer type.
  vector<Order *> order_list;
};

// The different kinds of orders are:
// deploy, advance, bomb, blockade, airlift, and negotiate.
// class Deploy
// {
// public:
// private:
// };