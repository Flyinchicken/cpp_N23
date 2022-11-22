#pragma once

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::ostream;
using std::string;

class Territory;
class Player;

// Abstract strategy class
class PlayerStrategy {
    friend ostream& operator << (ostream&, const PlayerStrategy&);
    public:
        virtual ~PlayerStrategy();
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        virtual string getStrategyAsString() const = 0;
    protected:
        PlayerStrategy(Player*);
        Player *player;
};

// Concrete strategy classes
class HumanPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const HumanPlayerStrategy&);
    public:
        HumanPlayerStrategy(Player*);
        ~HumanPlayerStrategy();
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

class AggressivePlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const AggressivePlayerStrategy&);
    public:
        AggressivePlayerStrategy(Player*);
        ~AggressivePlayerStrategy();
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString()const;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const BenevolentPlayerStrategy&);
    public:
        BenevolentPlayerStrategy(Player*);
        ~BenevolentPlayerStrategy();
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

class NeutralPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const NeutralPlayerStrategy&);
    public:
        NeutralPlayerStrategy(Player*);
        ~NeutralPlayerStrategy();
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

// ??Not in instructions??
class CheaterPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const CheaterPlayerStrategy&);
    public:
        CheaterPlayerStrategy(Player*);
        ~CheaterPlayerStrategy();
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
    private:
        vector<Territory*> getAdjacentEnemyTerritories();
};