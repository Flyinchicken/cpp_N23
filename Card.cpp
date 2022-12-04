#include "Card.h" //Below is the implementation of all the members of the class Card, Deck and Hand

/*****************************************************************************************
Below are the definitions for the Card class
*/

int Card::numCards = 0; //Initializes numCards

/*
Default Constructor
Incriments numCards and sets up default types for the Card members
Assisgns a random type to the Cards
*/
Card::Card() {
    numCards++;
    _description = "default";
    _name = "Card " + to_string(numCards);
    _type = generateType((rand() % 5) + 1); //Calls generate type to get a string version of the type generated by the random number
};

Card::Card(string description, int type, string name) : _name(name), _description(description) {
    _type = generateType(type); //Generates string version of type
    numCards++;
};

//Copy Constructor
Card::Card(const Card& e) {
    this->_description = e._description;
    this->_type = e._type;
    this->_name = e._name;
};

//Assignment Operator
Card& Card::operator =(const Card& e) {
    this->_description = e._description;
    this->_type = e._type;
    this->_name = e._name;
    return *this;
};

//Stream operator
ostream& operator<<(std::ostream& stream, Card& e) {
    stream << "This is Card " << e.getName() << " of type " << e.getType() << ".\n Description: " << e.getDescription() << endl;
    return stream;
};

//Destructor
Card::~Card() {

};

//Plays a card, issues and order, removes it from the hand and puts it in the deck
void Card::play(Hand* hand, CardParameters params) {
    cout << "Playing card " << _name << " from hand " << hand->getName() << endl;
    bool isRemoved;
    isRemoved = hand->removeCardFromHand(this); //Attemps to remove the Card from the Hand
    if (isRemoved) { //If the Card was removed
        x->addCardToDeck(this); //Adds to the deck
        hand->getPlayer()->cardOrder(generateOrderNumber(_type), params); //Calls member of the Player class which issues an order based on the type of the card and adds it to its list
    }
    else { //If the card wasn't succesfully removed the card is not played. Most likely the card is not in the hand
        cout << "Card could not be played" << endl;
    }
};

//Returns name of the card
string Card::getName() {
    return _name;
};

//Returns description of the card
string Card::getDescription() {
    return _description;
};

//Returns the type of the card
string Card::getType() {
    return _type;
};


/****************************************************************************************
Below are the definitions for the Deck class
*/

//Default constructor
Deck::Deck() {

};

//Constructor that accepts a card collection
Deck::Deck(vector<Card*> input) : _cardDeck(input) {

};

//Copy Constructor
Deck::Deck(const Deck& e) {
    this->_cardDeck = e._cardDeck;
};

//Assignment operator
Deck& Deck::operator =(const Deck& e) {
    this->_cardDeck = e._cardDeck;
    return *this;
};

//Manually adds a Card to the Deck
void Deck::addCardToDeck(Card* e) {
    _cardDeck.push_back(e);
};

//Stream operator
ostream& operator<<(std::ostream& stream, Deck& e) {
    stream << "This is the Deck and it has " << e._cardDeck.size() << endl;
    return stream;
};

//Destructor
Deck::~Deck() {

};

//Returns the collection of Cards in the deck
vector<Card*> Deck::getDeck() {
    return _cardDeck;
}

//Draws a random card into the hand and removes it from the Deck
void Deck::draw(Hand* hand) {
    int max = _cardDeck.size();
    if (_cardDeck.size() > 0) { //If deck is not empty
        int index = rand() % _cardDeck.size();
        hand->addCardToHand(_cardDeck.at(index)); //Adds the random card to the hand
        _cardDeck.erase(_cardDeck.begin() + index); //Removes it from the deck
    }
    else {
        cout << "The Deck is empty, you can't draw from it" << endl;
    }
};

/****************************************************************************************
Below are the definitions for the Deck class
*/

//Initializes numHands
int Hand::numHands = 0;

/*
Default Constructor
Incriments numHands and sets up default types for the Hand members
Creates a default player and assigns it as owner of the hand
*/
Hand::Hand() {
    numHands++;
    _name = to_string(numHands);
    _player = new Player("Default");
};

//Accepts a Card* collection, Creates a default player for the Hand
Hand::Hand(vector<Card*> input) : _cardHand(input) {
    _player = new Player("Default");
    numHands++;
    _name = to_string(numHands);
};

//Accepts a Player* and assigns it as the Hand owner
Hand::Hand(Player* e) {
    numHands++;
    _name = to_string(numHands);
    _player = e;
};

//Does the job of the last two constructors combined
Hand::Hand(Player* e, vector<Card*> input) : _cardHand(input) {
    _player = e;
    numHands++;
    _name = to_string(numHands);
};

//Returns the collection of Cards in the deck
vector<Card*> Hand::getHand() {
    return _cardHand;
}

//Returns the name of the Hand
string Hand::getName() {
    return _name;
}

//Returns a pointer to the owner of the hand
Player* Hand::getPlayer() {
    return _player;
}

//Copy Constructor
Hand::Hand(const Hand& e) {
    this->_name = e._name;
    this->_cardHand = e._cardHand;
    this->_player = new Player(e._player->getName());
};

//Asignment Operator
Hand& Hand::operator =(const Hand& e) {
    this->_cardHand = e._cardHand;
    this->_name = e._name;
    this->_player = new Player(e._player->getName());
    return *this;
};

//Stream Operator
ostream& operator<<(std::ostream& stream, Hand& e) {
    stream << "This is the Hand " << e._name << " and it has " << e._cardHand.size() << " and belongs to " << e._player->getName() << endl;
    return stream;
};

//Sets the owner of the Hand
void Hand::setPlayer(Player* e) {
    delete _player;
    _player = e;
};

//Adds a Card manually to the Hand
void Hand::addCardToHand(Card* e) {
    _cardHand.push_back(e);
};

//Removes a Card from the Hand, returns true if successful
bool Hand::removeCardFromHand(Card* e) {
    vector<Card*>::iterator it = find(_cardHand.begin(), _cardHand.end(), e); //Tries to find the Card inside the card by assigning an itetator to the index
    if (it != _cardHand.end()) { //If the card is found
        _cardHand.erase(it);
        return true;
    }
    else { //If the Card is not found, the iterator returns one after the end of the vector
        cout << "Incorrect instruction, this Card is not in this Hand";
        return false;
    }
}

/*
Destructor of Hand
Cards shouldn't be deleted, they are instead added to the deck
The Pointer to the Player owner of the hand is assigned to null, but the Player shouldn't be deleted either if a hand is deleted
*/
Hand::~Hand() {
    for (int i = 0; i < _cardHand.size(); i++) {
        x->addCardToDeck(_cardHand.at(i));
    }
    _player = NULL;
};

/****************************************************************************************
Below are the definitions for the free functions of Card.h
*/

//Returns string equivalent of number type
string generateType(int type) {
    string cardType = "";
    switch (type) {
    case 1:
        cardType = "bomb";
        break;
    case 2:
        cardType = "reinforcement";
        break;
    case 3:
        cardType = "blockade";
        break;
    case 4:
        cardType = "airlift";
        break;
    case 5:
        cardType = "diplomacy";
        break;
    default:
        cardType = "default";
    }

    return cardType;
}

//Returns number equivalent of string type
int generateOrderNumber(string type) {
    if (type == "bomb") {
        return 3;
    }
    else if (type == "reinforcement") {
        return 1;
    }
    else if (type == "blockade") {
        return 4;
    }
    else if (type == "airlift") {
        return 5;
    }
    else if (type == "diplomacy") {
        return 6;
    }
    else {
        return 7;
    }
}

///
/// CARD PARAMETERS
///

/**
 * Default constructor
*/
CardParameters::CardParameters() {
    targetTerritory = nullptr;
    sourceTerritory = nullptr;
    armyUnits = 0;
}

/**
 * Constructor that sets target territory based on input (bomb & blockade cards)
*/
CardParameters::CardParameters(Territory* target) {
    targetTerritory = target;
    sourceTerritory = nullptr;
    armyUnits = 0;
    targetPlayer = nullptr;
}

/**
 * Constructor for all parameters save targetPlayer (airlift card)
*/
CardParameters::CardParameters(Territory* source, Territory* target, int army) {
    targetTerritory = target;
    sourceTerritory = source;
    armyUnits = army;
    targetPlayer = nullptr;
}

/**
 * Constructor that sets the targetPlayer (diplomacy card)
*/
CardParameters::CardParameters(Player* target) {
    targetTerritory = nullptr;
    sourceTerritory = nullptr;
    armyUnits = 0;
    targetPlayer = target;
}

/**
 * Copy Constructor
*/
CardParameters::CardParameters(const CardParameters& cp) {
    targetTerritory = cp.targetTerritory;
    sourceTerritory = cp.sourceTerritory;
    armyUnits = cp.armyUnits;
    targetPlayer = cp.targetPlayer;
}

/**
 * Assignment operator
*/
CardParameters& CardParameters::operator=(const CardParameters& cp) {
    if (&cp != this) {
        targetTerritory = cp.targetTerritory;
        sourceTerritory = cp.sourceTerritory;
        armyUnits = cp.armyUnits;
        targetPlayer = cp.targetPlayer;
    }

    return *this;
}

/**
 * Destructor. CardParameters' pointers point to sensitive Map data that should be managed
 * elsewhere.
*/
CardParameters::~CardParameters() {
}

/**
 * Stream insertion operator
*/
ostream& operator << (ostream& out, CardParameters& cp) {
    if (cp.targetTerritory != nullptr) {
        out << "Target territory: " << endl << "\t" << *(cp.targetTerritory);
    }
    if (cp.sourceTerritory != nullptr) {
        out << "Source territory: " << endl << "\t" << *(cp.sourceTerritory);
    }  
    out << "Army units: " << cp.armyUnits;
    
    if (cp.targetPlayer != nullptr) {
        out << "Target Player: " << endl << "\t" << *(cp.targetPlayer);
    }  

    return out;
}