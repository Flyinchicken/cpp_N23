#include "Player.h"

using namespace std;
#include <iostream>
extern Map* worldMap;

// Default constructor
Player::Player()
{
    this->name = "Player";
    this->orderslist = new OrdersList();
    this->hand = new Hand();
    this->territories = vector<Territory*>();
}

// Non-default constructor accepting a player name
// The Hand and list of territories are created using the setter to avoid ambiguous behavior (infinite loop)
Player::Player(string playerName)
{
    this->name = playerName;
    this->orderslist = new OrdersList();
}

// Non-default constructor accepting all members
Player::Player(string playerName, Hand* newHand, OrdersList* newOrdersList, vector<Territory*> newTerritories)
{
    this->name = playerName;
    this->orderslist = newOrdersList;
    this->hand = newHand;
    this->territories = newTerritories;
}

// Destructor deleting all pointer members
Player::~Player()
{
    delete this->orderslist;
    delete this->hand;
    for (int i = 0; i < this->territories.size(); i++)
    {
        delete this->territories[i];
        this->territories[i] = nullptr;
    }
    this->territories.clear();
}

// Copy constructor
Player::Player(const Player& player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory*>(player.territories);
    this->reinforcementPool = player.reinforcementPool;
}

// Assignment operator
Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory*>(player.territories);
    this->reinforcementPool = player.reinforcementPool;

    return *this;
}

// name getter returning the name of the player
string Player::getName() const
{
    return name;
}

// ordersList getter returning the player's list of orders
OrdersList Player::getOrdersList() const
{
    return *orderslist;
}

// hand getter returning the player's hand
Hand* Player::getHand()
{
    return hand;
}

// territories getter returning the player's owned countries
vector<Territory*> Player::getTerritories() const
{
    return territories;
}

int Player::getReinforcementPool()
{
    return reinforcementPool;
}

// name setter
void Player::setName(string newName)
{
    name = newName;
}

// orderslist setter
void Player::setOrdersList(OrdersList* newList)
{
    this->orderslist = newList;
}

// hand setter
void Player::setHand(Hand* newHand)
{
    this->hand = newHand;
}

// territories setter
void Player::setTerritories(vector<Territory*> newTerritories)
{
    this->territories = newTerritories;
}

void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
}

void Player::removeTerritory(Territory* territory)
{
    for (int i = 0; i < territories.size(); i++)
    {
        if (territories.at(i) == territory)
        {
            territories.erase(territories.begin() + i);
            return;
        }
    }

    cout << "Player: " << this->getName() << " does not own " << territory->getTerritoryName() << endl;
}

void Player::setReinforcementPool(int pool)
{
    this->reinforcementPool = reinforcementPool;
}

void Player::setTurn(bool turn)
{
    this->turnCompleted = turn;
}

bool Player::getTurn()
{
    return this->turnCompleted;
}

// orders created adding to the player's orderslist
void Player::issueOrder()
{
    if (this->getReinforcementPool() > 4)
    {
        vector<Territory*> outposts = this->toDefend();
        int random = rand() % outposts.size();
        this->orderslist->addOrder(new Deploy(this, 5, outposts.at(random))); // Deploy order, should take certain params
        this->setReinforcementPool(this->getReinforcementPool() - 5);
        cout << "Deploy order of 5 issued by player " << this->getName() << " onto territory " << outposts.at(random) << ". \nCurrent reinforcement pool = " << this->getReinforcementPool() << endl;
    }
    else if (this->getReinforcementPool() > 0)
    {
        int tempRein = this->getReinforcementPool();
        vector<Territory*> outposts = this->toDefend();
        int random = rand() % outposts.size();
        this->orderslist->addOrder(new Deploy(this, this->getReinforcementPool(), outposts.at(random))); // Deply order but now with the rest of the reinforcement pool
        this->setReinforcementPool(0);
        cout << "Deploy order of " << tempRein << " issued by player " << this->getName() << " onto territory " << outposts.at(random) << ". \nCurrent reinforcement pool = " << this->getReinforcementPool() << endl;
    }
    else
    {
        vector<Territory*> potentialAttacks = this->toAttack();
        vector<Territory*> outposts = this->toDefend();
        vector<Territory*> reinforcers = outposts;
        reverse(reinforcers.begin(), reinforcers.end());

        if (potentialAttacks.size() > numAttacks)
        { // If we can attack any territory that we have not yet attacked

            cout << "Player has targets to attack. Player has attacked " << numAttacks << " territories this turn" << endl;

            Territory* target = potentialAttacks.at(numAttacks);

            for (Territory* p : reinforcers)
            {
                vector<Territory*> adj = worldMap->getNeighboursPtr(*p->getTerritoryName()); //VERIFY WORLD

                vector<Territory*>::iterator it = find(adj.begin(), adj.end(), target); // Tries to find which territory should be the source
                
                if (it != adj.end())
                {
                    Territory* source = p; // Source territory
                    this->orderslist->addOrder(new Advance(this, source, target, source->getArmyNumber() - 1));  // VERIFY ORDER
                    numAttacks++;

                    cout << "Attack Order from territory " << source->getTerritoryName() << " to territory " << target->getTerritoryName() << endl;
                    break;
                }
            }
        }
        else
        { // If it can't attack it will try to defend

            cout << "No new targets to attack. So we try to defend " << endl;
            bool hasDefended = false;

            for (int i = numDefense; i < outposts.size(); i++)
            {
                if (hasDefended)
                {
                    return;
                }

                Territory* target = outposts.at(i);
            
                for (Territory* tempRe : reinforcers)
                {
                    vector<Territory*> adj = worldMap->getNeighboursPtr(*tempRe->getTerritoryName()); //VERIFY WORLD
                    vector<Territory*>::iterator it = find(adj.begin(), adj.end(), target); // Tries to find where it can take troops from to defend from the territory with the most troops
                    if (it != adj.end())
                    {
                        Territory* source = tempRe;
                        this->orderslist->addOrder(new Advance(this, source, target, source->getArmyNumber() / 2)); // VERIFY ORDER
                        hasDefended = true;
                        numDefense = i + 1;

                        cout << "Defense Order from territory " << source->getTerritoryName() << " to territory " << target->getTerritoryName() << endl;

                        break;
                    }
                }
            }
            
            cout << "No targets to defend. So we play a card and end turn" << endl;
            if (!this->getHand()->getHand().empty())
            {
                vector<Card*> cards = this->getHand()->getHand();
                cards[0]->play(this->getHand());
            }
            this->setTurn(true);
            finishedPlayers++;
            cout << "Player " << this->getName() << " has ended their turn" << endl;
        }
    }
}

// helper method to get a specific order which adds to the player's orderslist
void Player::cardOrder(int orderNumber)
{
    Order* newOrder{};
    switch (orderNumber)
    {
    case 1:
        newOrder = new Deploy();
        break;
    case 2:
        newOrder = new Advance();
        break;
    case 3:
        newOrder = new Bomb();
        break;
    case 4:
        newOrder = new Blockade();
        break;
    case 5:
        newOrder = new Airlift();
        break;
    case 6:
        newOrder = new Negotiate();
        break;
    default:
        cout << "Invalid card type" << endl;
        break;
    }
    if (newOrder != nullptr)
    {
        cout << (*newOrder) << endl;
        this->orderslist->addOrder(newOrder);
    }
}

/**
 * Check the number of continent owning bonus armies for the player
 */
int Player::getContinentsBonus()
{
    int bonus = 0;

    // for each continent pointer in the map
    for (auto& kv : worldMap->continents)
    {
        // get a vector of all territories
        vector<Territory*> c_territories = kv.second->getNodesPtr();

        // get the number of territories in the continent
        int count = c_territories.size();

        // for each territory in the continent, try to find it in the player's territory list
        // if found, move onto the next continent territory
        for (auto& c_t : c_territories)
        {
            for (auto& t : this->territories)
            {
                if (c_t == t)
                {
                    count--;
                    break;
                }
            }
        }

        // in the end if all continent territories are found, continent bonus is added
        if (count == 0)
        {
            bonus += kv.second->getBonusArmy();
        }
    }
    return bonus;
}

bool compareArmyNumber(Territory* t1, Territory* t2){
    return (t1->getArmyNumber() < t2->getArmyNumber());
}
// return a list of arbitrary territories to defend
vector<Territory*> Player::toDefend()
{
    vector<Territory*> d_territories;
    for (int i = 0; i < territories.size(); i++)
    {
        d_territories.push_back(territories.at(i));
    }

    sort(d_territories.begin(),d_territories.end(), compareArmyNumber);
    return d_territories;
}

// return a list of arbitrary territories to attack
vector<Territory*> Player::toAttack()
{
    vector<Territory*> a_territories;
    set<Territory*> a_set;
    
    for (int i = 0; i < territories.size(); i++)
    {
        vector<Territory*> temp = worldMap->getNeighboursPtr(*(territories.at(i)->getTerritoryName()));
        for(auto& neighbor : temp){
            if(neighbor->getOwner() != this){
                a_set.insert(neighbor);
            }
        }
    }

    for(auto& neighbor : a_set){
        a_territories.push_back(neighbor);
    }

    sort(a_territories.begin(),a_territories.end(), compareArmyNumber);

    return a_territories;
}

// stream operator that prints the player's owned countries
ostream& operator<<(ostream& outs, Player& player)
{
    outs << player.getName() << "'s owned territories: " << endl;

    for (int i = 0; i < player.territories.size(); i++)
    {
        outs << (*player.territories.at(i)->getTerritoryName()) << endl;
    }

    return outs;
}