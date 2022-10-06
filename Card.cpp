#pragma once
#include<iostream>
#include "Card.h"
#include<string>
using namespace std;

//Card definitions

Card::Card(){
    cout << "card Created" <<endl;
};

Card::Card(string* description, string* type, string* name): _name(name), _description(description), _type(type){
    cout <<"card created" <<endl;
};

Card::Card(const Card& e){
    this->_description = new string(*(e._description)); 
    this->_type = new string(*(e._type)); 
    this->_name = new string(*(e._name)); 
};

Card& Card::operator =(const Card& e){
    this->_description = new string(*(e._description)); 
    this->_type = new string(*(e._type)); 
    this->_name = new string(*(e._name)); 
    return *this;
};

ostream& operator<<(std::ostream& stream, Card& e){
    stream << "This is Card " << e.getName() << " of type " << e.getType() << ".\n Description: " << e.getDescription() << endl;
    return stream;
};

Card::~Card(){
    
};

void Card::play() {
    cout << "Playing" << endl;
};

string Card::getName() {
    return *_name;
};

string Card::getDescription() {
    return *_description;
};

string Card::getType(){
    return *_type;
};

//Deck Definitions
Deck::Deck() {
    cout << "Deck Created" << endl;
};

Deck::Deck(vector<Card*> input) : _cardDeck(input){
    cout << "Deck created" << endl;
};

Deck::Deck(const Deck& e) {
    this->_cardDeck = e._cardDeck;
};

Deck& Deck::operator =(const Deck& e) {
    this->_cardDeck = e._cardDeck;
    return *this;
};

ostream& operator<<(std::ostream& stream, Deck& e) {
    stream << "This is the Deck and it has "<<e._cardDeck.size() << endl;
    return stream;
};

Deck::~Deck() {

};

void Deck::draw() {
    cout << "I draw" << endl ;
};

//Hand Definitions
Hand::Hand() {
    cout << "Hand Created" << endl;
};

Hand::Hand(vector<Card*> input) : _cardHand(input) {
    cout << "Hand created" << endl;
};

Hand::Hand(const Hand& e) {
    this->_cardHand = e._cardHand;
};

Hand& Hand::operator =(const Hand& e) {
    this->_cardHand = e._cardHand;
    return *this;
};

ostream& operator<<(std::ostream& stream, const Hand& e) {
    stream << "This is the Hand and it has " << e._cardHand.size() << endl;
    return stream;
};

Hand::~Hand() {

};