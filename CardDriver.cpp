#include <iostream>
#include "Card.h"
#include<string>
#include "Player.h"
#include "CardDriver.h"
using namespace std;

void testCards() {

    cout << "Creating cards and placing them in the Deck: " << endl << endl;
    for (int i = 0; i < 50; i++) {
        x->addCardToDeck(new Card());
        vector<Card*> v = x->getDeck();
        cout << *v.at(i) << endl;
    }

    Hand* myHand = new Hand();

    cout << "\n Drawing Random Cards from the Deck \n it will also try to draw one last card from the empty Deck for error testing" << endl;
    for (int i = 0; i < 51; i++) {
        x->draw(myHand);
    }

    cout << "Printing the Hand and the Deck to see where the Cards are" << endl;
    cout << *x << endl;
    cout << *myHand << endl;

    cout << "\n Playing every Card from the Hand" << endl;
    for (int i = 0; i < 50; i++) {
        vector<Card*> t = myHand->getHand();
        if (t.size() == 0) { //if the hand is empty
            break;
        }
        CardParameters params;
        t.at(0)->play(myHand, params);
    }

    cout << "Printing the Hand and the Deck to see where the Cards are" << endl;
    cout << *x << endl;
    cout << *myHand << endl;
   
    cout << "Testing delete hand feature by creating a Card, adding it to a hand and deleting it" << endl;
    Card* testCard = new Card();
    Hand* testHand = new Hand();
    testHand->addCardToHand(testCard);
    cout << *testHand << endl;
    cout << *x << endl;
    
    cout << "Printing Deck after deletion" << endl;
    delete testHand;
    cout << *x << endl;
}