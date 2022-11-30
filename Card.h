#pragma once
#include<string> //The Hand and Card classes declare members of type string
#include<iostream> //Operator<< uses ostream
#include<vector> //The Hand and Deck classes declare members of type vector
#include<cstdlib> //Uses the find() member for vectors
#include<algorithm>
#include "Player.h"
using namespace std;

class Hand; //Card uses Hand and deck objects before they are declared so these needed to be added
class Deck;
class Player; //Hand uses Player*, but it only needs a declaration

extern Deck* x; //Since the game is in practice only supposed to have 1 deck, some members use the global variable (externally defined)
                // x of type Deck*


/**
 * Struct defining all possible parameters a Card may need to be properly execute.
 * 
 * For instance, a Bomb card requires a target Territory to be executed correctly given a player
 * order.
 * 
 * When it comes to creating an Order via Player's cardOrder, all properties that are not needed for
 * an Order are assumed to be NULL/not defined.
 * 
 * For instance, when create an Order of type Bomb, sourceTerritory and armyUnits are not used, so they 
 * be left as default.
*/
struct CardParameters {
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int armyUnits;

    CardParameters();
    CardParameters(Territory*);
};

/*
Class for the Cards used in the warzone game
*/
class Card

{
private:
    static int numCards; //Keeps track of the number of Cards existing during program runtime, used to assign default names to cards
    string _description; //Brief Description of Cards
    string _type; //Stores the type of a Card. They are: diplomacy, airlift, blockade, reinforcement, bomb
    string _name; //Name of the Card. Usually a number based on numCards

    // friend stream insertion operator to the class to access private member
    friend ostream& operator<<(std::ostream& stream, Card& e);
public:
    Card(); //Default Constructor
    Card(string description, int type, string name);
    Card(const Card& e); //Copy Constructor
    Card& operator =(const Card& e); //Asignment Operator
    ~Card(); //Destructor

    string getDescription(); //Returns the description the Card
    string getType(); //Returns the type of the Card
    string getName(); //Returns the name of the Card

    void play(Hand* hand, CardParameters); //Plays a Card from a hand, removing it and placing it back in the deck. Issues an order to the order list of the owner of the Hand
};

//Stream Operator for Card
ostream& operator<<(std::ostream& stream, Card& e);

/*
Class for the Deck, which is a collection of Cards of the warzone game. Only one instance of it should exist
*/
class Deck
{
private:
    vector<Card*> _cardDeck; //Collection of pointers to Cards that uses the vector object

    // friend stream insertion operator to the class to access private member
    friend ostream& operator<<(std::ostream& stream, Deck& e);
public:
    Deck(); //Default constructor
    Deck(vector<Card*> e); //Accepts a vector of pointers to Cards
    Deck(const Deck& e); //Copy constructor
    Deck& operator =(const Deck& e); //Assignment operator
    ~Deck(); //Destructor
    vector<Card*> getDeck(); //Returns the Card collection
    void addCardToDeck(Card* e); //Adds a card to the Deck collection of Cards
    void draw(Hand* hand); //Draws a card from the Deck, removes it and places it on the given Hand

};

//Stream insertion operator for Deck
ostream& operator<<(std::ostream& stream, Deck& e);

/*
Class for the Hand, which is a collection of Cards of the warzone game that belongs to a player
*/
class Hand
{
private:
    Player* _player; //Pointer to the Player that owns the Hand
    string _name; //Name of the Hand, usually based on numHands
    static int numHands; //Keeps track of the number of Hands existing during program runtime, used to assign default names to Hands
    vector<Card*> _cardHand; //Collection of pointers to Cards that uses the vector object

    // friend stream insertion operator to the class to access private member
    friend ostream& operator<<(std::ostream& stream, Hand& e);
public:
    Hand(); //Default constructor
    Hand(vector<Card*> e); //Accepts a vector of pointers to Cards
    Hand(Player* e); //Accepts a player
    Hand(Player* e, vector<Card*> v);
    Hand(const Hand& e); //Copy constructor
    Hand& operator =(const Hand& e); //Assignment operator
    ~Hand(); //Destructor

    Player* getPlayer(); //Returns a pointer to the player that owns the hand
    vector<Card*> getHand(); //Returns the collection of Cards in the hand
    string getName(); //Returns the name of the Hand

    void setPlayer(Player* e); //Sets the own of the Hand

    void addCardToHand(Card* e); //Adds a Card to the Hand
    bool removeCardFromHand(Card* e); //Removes a Card to the hand. Returns true if succesful
};

//Stream insertion operator for Hand
ostream& operator<<(std::ostream& stream, Hand& e);


//Free Functions
int generateOrderNumber(string type); //Transform string type into a number from 1-6
string generateType(int type); //Transform number type into a string





