#pragma once

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::ostream;
using std::string;

extern int finishedPlayers;

class Territory;
class Player;
class CommandProcessor;
class Command;

// Abstract strategy class
class PlayerStrategy {
    friend ostream& operator << (ostream&, const PlayerStrategy&);
public:
    virtual ~PlayerStrategy();
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual string getStrategyAsString() const = 0;
    Player* getPlayer();                             // For testing purposes
    bool isStringNumber(string input);
    Territory* getTerritoryByName(string name);
protected:
    PlayerStrategy(Player*);
    Player* player;
};

// Concrete strategy classes
class HumanPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const HumanPlayerStrategy&);
public:
    HumanPlayerStrategy(Player*);
    HumanPlayerStrategy(const HumanPlayerStrategy&);
    ~HumanPlayerStrategy();
    HumanPlayerStrategy& operator = (const HumanPlayerStrategy&);

    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    string getStrategyAsString() const;
private:
    CommandProcessor* commandProcessor;
    Command* nextCommand;
    bool showCommandList;       // Bool so command list is only shown first time Human issues order

    void printTerritoryList(vector<Territory*>);
    void showValidCommandList();
    bool hasPlayerEndedTurn(string);
    bool areKeywordAndSizeInvalid(string, int);

    bool processDeployInput(vector<string>);
    bool processAdvanceInput(vector<string>);
    bool processBombInput(vector<string>);
    bool processBlockadeInput(vector<string>);
    bool processAirliftInput(vector<string>);
    bool processNegotiateInput(vector<string>);
};

class AggressivePlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const AggressivePlayerStrategy&);
public:
    AggressivePlayerStrategy(Player*);
    AggressivePlayerStrategy(const AggressivePlayerStrategy&);
    ~AggressivePlayerStrategy();
    AggressivePlayerStrategy& operator = (const AggressivePlayerStrategy&);

    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    string getStrategyAsString()const;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const BenevolentPlayerStrategy&);
public:
    BenevolentPlayerStrategy(Player*);
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy&);
    ~BenevolentPlayerStrategy();
    BenevolentPlayerStrategy& operator = (const BenevolentPlayerStrategy&);

    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    string getStrategyAsString() const;
    vector<Territory*> getStrongestTerritories();
};

class NeutralPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const NeutralPlayerStrategy&);
public:
    NeutralPlayerStrategy(Player*);
    NeutralPlayerStrategy(const NeutralPlayerStrategy&);
    ~NeutralPlayerStrategy();
    NeutralPlayerStrategy& operator = (const NeutralPlayerStrategy&);

    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    string getStrategyAsString() const;
};

class CheaterPlayerStrategy : public PlayerStrategy {
    friend ostream& operator << (ostream&, const CheaterPlayerStrategy&);
public:
    CheaterPlayerStrategy(Player*);
    CheaterPlayerStrategy(const CheaterPlayerStrategy&);
    ~CheaterPlayerStrategy();
    CheaterPlayerStrategy& operator = (const CheaterPlayerStrategy&);

    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    string getStrategyAsString() const;
private:
    vector<Territory*> getAdjacentEnemyTerritories();
};