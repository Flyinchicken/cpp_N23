#include "PlayerStrategies.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "Orders.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::isdigit;
using std::stoi;

///
/// PLAYER STRATEGY
///

/**
 * Free function to compare army numbers between two territories, decreasing order
*/
bool compareArmyNumberDecrease(Territory* t1, Territory* t2) {
	return (t1->getArmyNumber() < t2->getArmyNumber());
}

/**
 * Free function to compare army numbers between two territories, increasing order
*/
bool compareArmyNumberIncrease(Territory* t1, Territory* t2) {
	return (t1->getArmyNumber() > t2->getArmyNumber());
}

/**
 * Uses polymorphism to display the type of Strategy this is
*/
ostream& operator << (ostream& out, const PlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}

/**
 * Constructor that takes a Player and sets the player pointer this Strategy is associated with
 *
 * No default constructor since Player is needed for toAttack and toDefend.
 *
 * @param p The player this strategy is assocuated with
*/
PlayerStrategy::PlayerStrategy(Player* p) {
	this->player = p;
}

/**
 * Basic destructor
*/
PlayerStrategy::~PlayerStrategy() {
	delete this->player;
}

/**
 * Getter used for testing purposes
 *
 * @returns Player attached to this strategy
*/
Player* PlayerStrategy::getPlayer() {
	return this->player;
}

/**
 * Determines if a string is an int/number.
 *
 * From: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
 *
 * @returns bool indicating if string is a number
*/
bool PlayerStrategy::isStringNumber(string input) {
	std::string::const_iterator iterator = input.begin();

	while (iterator != input.end() && isdigit(*iterator)) {
		++iterator;
	}

	return !input.empty() && iterator == input.end();
}

///
/// HUMAN PLAYER
///

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {
	commandProcessor = new CommandProcessor();
	showCommandList = true;
}

/**
 * Copy constructor
*/
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& strat) : PlayerStrategy(strat.player) {
	commandProcessor = new CommandProcessor();
	showCommandList = strat.showCommandList;
}

HumanPlayerStrategy::~HumanPlayerStrategy() {
	delete commandProcessor;
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
HumanPlayerStrategy& HumanPlayerStrategy::operator = (const HumanPlayerStrategy& toAssign) {
	if (this != &toAssign) {
		player = toAssign.player;
		showCommandList = toAssign.showCommandList;

		delete commandProcessor;
		commandProcessor = toAssign.commandProcessor;
	}

	return *this;
}

/**
 * Checks if user input indicates they've ended their turn.
 *
 * @param commandString User input
 * @returns If player has ended turn
*/
bool HumanPlayerStrategy::hasPlayerEndedTurn(string commandString) {
	if (commandString == CommandStrings::issueOrdersEnd) {
		player->setTurnCompleted(true);
		return true;
	}

	return false;
}

/**
 * Checks that the user has input a command with "issueorder" at the front, and that they have input at
 * least an Order type (airlift, deploy, blockade, etc.)
 *
 * @param commandKeyword First word user input. Should be "issueorder"
 * @param inputSize Size of input user input (size of whitespace-split array of input command)
 * @return True if commandKeyword isn't "issueorder" and not Order was given.
*/
bool HumanPlayerStrategy::areKeywordAndSizeInvalid(string commandKeyword, int inputSize) {
	if (commandKeyword != CommandStrings::issueOrder) {
		cout << "Issue orders using the \"issueorder\" keyword. \""
			<< commandKeyword << "\" is not valid"
			<< endl;

		return true;
	}

	if (inputSize < 2) {
		cout << "Please specify an order type!" << endl;

		return true;
	}

	return false;
}

/**
 * Adds a Deploy Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processDeployInput(vector<string> splitCommand) {
	if (splitCommand.size() != 4) {
		cout << "Deploy order must be formatted as: issueorder deploy <num_armyunits> <target_territory>" << endl;
		nextCommand->saveEffect("Command not properly formatted");
		return true;
	}

	string armyString = splitCommand.at(2);
	string territoryString = splitCommand.at(3);

	if (!isStringNumber(armyString)) {
		cout << armyString << " is not a valid number!" << endl;
		nextCommand->saveEffect("Army size not a number");
		return true;
	}
	int numArmyToDeploy = stoi(armyString);

	Territory* targetTerritory = worldMap->getNode(territoryString);
	if (targetTerritory == NULL) {
		cout << "Could not find territory with name " << territoryString << " in world map" << endl;
		nextCommand->saveEffect("Target territory not found");
		return true;
	}

	player->addOrderToList(new Deploy(player, numArmyToDeploy, targetTerritory));
	nextCommand->saveEffect("Created new Deploy order");

	return false;
}

/**
 * Adds an Advance Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processAdvanceInput(vector<string> splitCommand) {
	if (splitCommand.size() != 5) {
		cout << "Advance order must be formatted as: issueorder advance <source_territory> <target_territory> <num_armyunits>" << endl;
		nextCommand->saveEffect("Command not properly formatted");
		return true;
	}

	Territory* sourceTerritory = worldMap->getNode(splitCommand.at(2));
	if (sourceTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(2) << " in world map" << endl;
		nextCommand->saveEffect("Source territory not found");
		return true;
	}

	Territory* targetTerritory = worldMap->getNode(splitCommand.at(3));
	if (targetTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(3) << " in world map" << endl;
		nextCommand->saveEffect("Target territory not found");
		return true;
	}

	if (!isStringNumber(splitCommand.at(4))) {
		cout << splitCommand.at(4) << " is not a valid number!" << endl;
		nextCommand->saveEffect("Army size not a number");
		return true;
	}
	int numArmyToDeploy = stoi(splitCommand.at(4));

	player->addOrderToList(new Advance(player, sourceTerritory, targetTerritory, numArmyToDeploy));
	nextCommand->saveEffect("Created new Advance order");

	return false;
}

/**
 * Adds a Bomb Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processBombInput(vector<string> splitCommand) {
	if (splitCommand.size() != 3) {
		cout << "Bomb order must be formatted as: issueorder bomb <target_territory>" << endl;
		nextCommand->saveEffect("Comman not properly formatted");
		return true;
	}

	Card* toPlay = player->getCardFromHandIfExists("bomb");
	if (toPlay == NULL) {
		cout << "No card of type 'bomb' found in current hand!" << endl;
		nextCommand->saveEffect(player->getName() + " has not bomb card");
		return true;
	}

	Territory* targetTerritory = worldMap->getNode(splitCommand.at(2));
	if (targetTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(2) << " in world map" << endl;
		nextCommand->saveEffect("Could not find target territory");
		return true;
	}

	CardParameters params(targetTerritory);
	toPlay->play(player->getHand(), params);
	nextCommand->saveEffect("Played Bomb card");

	return false;
}

/**
 * Adds a Blockade Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processBlockadeInput(vector<string> splitCommand) {
	if (splitCommand.size() != 3) {
		cout << "Blockade order must be formatted as: issueorder blockade <target_territory>" << endl;
		nextCommand->saveEffect("Command not properly formatted");
		return true;
	}

	Card* toPlay = player->getCardFromHandIfExists("blockade");
	if (toPlay == NULL) {
		cout << "No card of type 'blockade' found in current hand!" << endl;
		nextCommand->saveEffect(player->getName() + " has no bloackde card");
		return true;
	}

	Territory* targetTerritory = worldMap->getNode(splitCommand.at(2));
	if (targetTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(2) << " in world map" << endl;
		nextCommand->saveEffect("Target territory not found");
		return true;
	}

	CardParameters params(targetTerritory);
	toPlay->play(player->getHand(), params);
	nextCommand->saveEffect("Played blockade card");

	return false;
}

/**
 * Adds an Airlift Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processAirliftInput(vector<string> splitCommand) {
	if (splitCommand.size() != 5) {
		cout << "Airlift order must be formatted as: issueorder airlift <source_territory> <target_territory> <armyunits>" << endl;
		nextCommand->saveEffect("Command not properly formatted");
		return true;
	}

	Card* toPlay = player->getCardFromHandIfExists("airlift");
	if (toPlay == NULL) {
		cout << "No card of type 'airlift' found in current hand!" << endl;
		nextCommand->saveEffect(player->getName() + " has no airlift card");
		return true;
	}

	Territory* sourceTerritory = worldMap->getNode(splitCommand.at(2));
	if (sourceTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(2) << " in world map" << endl;
		nextCommand->saveEffect("Source territory not found");
		return true;
	}

	Territory* targetTerritory = worldMap->getNode(splitCommand.at(3));
	if (targetTerritory == NULL) {
		cout << "Could not find territory with name " << splitCommand.at(3) << " in world map" << endl;
		nextCommand->saveEffect("Target territory not found");
		return true;
	}

	if (!isStringNumber(splitCommand.at(4))) {
		cout << splitCommand.at(4) << " is not a valid number!" << endl;
		nextCommand->saveEffect("Army size not a number");
		return true;
	}
	int numArmyToDeploy = stoi(splitCommand.at(4));

	CardParameters params(sourceTerritory, targetTerritory, numArmyToDeploy);
	toPlay->play(player->getHand(), params);
	nextCommand->saveEffect("Played airlift card");

	return false;
}

/**
 * Adds a Negotiate Order to the player's order list assuming all command parameters are valid.
 *
 * @param splitCommand Vector containing each keyword the user input as a command (i.e. input split by whitespace)
 * @returns If no Order was issued (i.e. true = no order issued, incorrect input)
*/
bool HumanPlayerStrategy::processNegotiateInput(vector<string> splitCommand) {
	if (splitCommand.size() != 3) {
		cout << "Negotiate order must be formatted as: issueorder negotiate <target_player>" << endl;
		nextCommand->saveEffect("Command not formatted correctly");
		return true;
	}

	Card* toPlay = player->getCardFromHandIfExists("diplomacy");
	if (toPlay == NULL) {
		cout << "No card of type 'diplomacy' found in current hand!" << endl;
		nextCommand->saveEffect(player->getName() + " has no diplomacy card");
		return true;
	}

	string targetPlayerName = splitCommand.at(2);
	Player* targetPlayer = ge->getPlayerIfExists(targetPlayerName);
	if (targetPlayer == nullptr) {
		cout << "No player with name " << targetPlayerName << " found in the current game instance!" << endl;
		nextCommand->saveEffect("Target player not found");
		return true;
	}

	CardParameters params(targetPlayer);
	toPlay->play(player->getHand(), params);
	nextCommand->saveEffect("Played diplomacy card");

	return false;
}

/**
 * Prints a list of Territories
 *
 * @param list The list to print
*/
void HumanPlayerStrategy::printTerritoryList(vector<Territory*> list) {
	for (int i = 0; i < list.size(); i++) {
		cout << (i + 1) << ": " << *(list.at(i)) << endl;
	}
}

/**
 * Lists all accepted commands
*/
void HumanPlayerStrategy::showValidCommandList() {
	cout << "List of valid commands: " << endl
		<< "1: toattack = show list of Territories to attack" << endl
		<< "2: todefend = show list of Territories to defend" << endl
		<< "3: info = show your player info, including your Territories, Hand, and reinforcement pool" << endl
		<< "4: help = show this list again" << endl
		<< "5: issueorder = issue an order. The following are valid order formats:" << endl
		<< "\t I: issueorder deploy <armyunits> <territory>" << endl
		<< "\t II: issueorder advance <source_territory> <target_territory> <armyunits>" << endl
		<< "\t III: issueorder bomb <target_territory>" << endl
		<< "\t IV: issueorder blockade <target_territory>" << endl
		<< "\t V: issueorder airlift <source_territory> <target_territory> <armyunits>" << endl
		<< "\t VI: issueorder negotiate <target_player>" << endl
		<< "6: issueordersend = indicate you've finished issueing orders" << endl;
}

/**
 * Console interface that allows a human player to issue an Order of any variety. Includes other additional commands
 * to aid in the process.
*/
void HumanPlayerStrategy::issueOrder() {
	if (showCommandList) {
		showValidCommandList();
	}

	bool noOrderIssued = true;
	while (noOrderIssued) {
		nextCommand = commandProcessor->getCommand();
		vector<string> splitCommand = commandProcessor->splitStringByDelim(nextCommand->getCommand(), ' ');
		string commandKeyword = splitCommand.front();

		cout << endl;

		if (commandKeyword == "toattack") {
			cout << "You can attack the following territories: " << endl;
			printTerritoryList(this->toAttack());
			nextCommand->saveEffect("Displayed list of toAttack Territories");
		}
		else if (commandKeyword == "todefend") {
			cout << "The following are the territories you must defend: " << endl;
			printTerritoryList(this->toDefend());
			nextCommand->saveEffect("Displayed list of toDefend Territories");
		}
		else if (commandKeyword == "info") {
			cout << *player << endl;
			nextCommand->saveEffect("Displayed player info for " + player->getName());
		}
		else if (commandKeyword == "help") {
			showValidCommandList();
			nextCommand->saveEffect("Displayed list of commands for a Human player");
		}
		else if (hasPlayerEndedTurn(commandKeyword)) {
			noOrderIssued = false;
			nextCommand->saveEffect(player->getName() + " indicated they have no more orders to issue");
			continue;
		}
		else if (areKeywordAndSizeInvalid(commandKeyword, splitCommand.size())) {
			nextCommand->saveEffect("Not a valid command for a Human player");
			continue;
		}
		else {
			string commandType = splitCommand.at(1);

			if (commandType == "deploy") {
				noOrderIssued = processDeployInput(splitCommand);
			}
			else if (commandType == "advance") {
				noOrderIssued = processAdvanceInput(splitCommand);
			}
			else if (commandType == "bomb") {
				noOrderIssued = processBombInput(splitCommand);
			}
			else if (commandType == "blockade") {
				noOrderIssued = processBlockadeInput(splitCommand);
			}
			else if (commandType == "airlift") {
				noOrderIssued = processAirliftInput(splitCommand);
			}
			else if (commandType == "negotiate") {
				noOrderIssued = processNegotiateInput(splitCommand);
			}
			else {
				cout << commandType << " is not a valid command type!" << endl;
				nextCommand->saveEffect("Not a valid command type");
			}
		}
	}

	showCommandList = false;
}

/**
 * @returns All territories the player can attack, ordered by biggest army number first.
*/
vector<Territory*> HumanPlayerStrategy::toAttack() {
	vector<Territory*> a_territories;
	set<Territory*> a_set;

	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		vector<Territory*> temp = worldMap->getNeighboursPtr(*(player->getTerritories().at(i)->getTerritoryName()));
		for (auto& neighbor : temp) {
			if (neighbor->getOwner() != player) {
				a_set.insert(neighbor);
			}
		}
	}

	for (auto& neighbor : a_set) {
		a_territories.push_back(neighbor);
	}

	sort(a_territories.begin(), a_territories.end(), compareArmyNumberIncrease);

	return a_territories;
}

/**
 * @returns All player owned territories, ordered by lowest army number first.
*/
vector<Territory*> HumanPlayerStrategy::toDefend() {
	vector<Territory*> d_territories;
	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		d_territories.push_back(player->getTerritories().at(i));
	}

	sort(d_territories.begin(), d_territories.end(), compareArmyNumberDecrease);
	return d_territories;
}

/**
 * @returns The type of strategy as a string
*/
string HumanPlayerStrategy::getStrategyAsString() const {
	return "Human Player";
}

/**
 * Outputs the type of strategy this instance is.
*/
ostream& operator << (ostream& out, const HumanPlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}

void deploy(Player* player, vector<Territory*> d_territories) {
	Territory* target = d_territories.at(0);
	player->addOrderToList(new Deploy(player, player->getReinforcementPool(), target));
	player->setReinforcementPool(0);
}
bool advanceAttack(Player* player, vector<Territory*> d_territories, vector<Territory*> potentialAttacks) {
	vector<Territory*> reinforcers = d_territories;

	cout << "Player has targets to attack. Player has attacked " << player->numAttacks << " territories this turn" << endl;

	Territory* target = potentialAttacks.at(player->numAttacks);

	for (Territory* p : reinforcers)
	{
		vector<Territory*> adj = worldMap->getNeighboursPtr(*p->getTerritoryName());

		vector<Territory*>::iterator it = find(adj.begin(), adj.end(), target); // Tries to find which territory should be the source

		if (it != adj.end())
		{
			Territory* source = p; // Source territory
			player->getOrdersList()->addOrder(new Advance(player, source, target, source->getArmyNumber() - 1));
			player->numAttacks++;

			cout << "Attack Order from territory " << *source->getTerritoryName() << " to territory " << *target->getTerritoryName() << endl;
			return true;
		}
	}
}
bool advanceDefend(Player* player, vector<Territory*> d_territories) {
	vector<Territory*> reinforcers = d_territories;

	cout << "No new targets to attack. So we try to defend " << player->numDefense << endl;
	bool hasDefended = false;

	for (int i = player->numDefense; i < d_territories.size(); i++)
	{
		/*if (hasDefended)
		{
			return;
		}*/

		Territory* target = d_territories.at(i);

		for (Territory* tempRe : reinforcers)
		{
			vector<Territory*> adj = worldMap->getNeighboursPtr(*tempRe->getTerritoryName()); //VERIFY WORLD
			vector<Territory*>::iterator it = find(adj.begin(), adj.end(), target); // Tries to find where it can take troops from to defend from the territory with the most troops
			if (it != adj.end())
			{
				Territory* source = tempRe;
				if (source->getArmyNumber() > target->getArmyNumber()) {
					player->getOrdersList()->addOrder(new Advance(player, source, target, source->getArmyNumber() / 2)); // VERIFY ORDER
					hasDefended = true;
					player->numDefense = i + 1;

					cout << "Defense Order from territory " << *source->getTerritoryName() << " to territory " << *target->getTerritoryName() << endl;
					return true;
				}
				else {
					continue;
				}
			}
		}
	}
}

void playCard(Player* player, vector<Territory*> d_territories, vector<Territory*> potentialAttacks) {
	cout << "Nothing left to do. So we play a card and end turn" << endl;
	if (!player->getHand()->getHand().empty())
	{
		vector<Card*> cards = player->getHand()->getHand();
		CardParameters params(nullptr, nullptr, 0);
		cards[0]->play(player->getHand(), params);
	}
}
/// 
/// AGGRESSIVE PLAYER
///

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& strat) : PlayerStrategy(strat.player) {
	cout << "Copy" << endl;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
AggressivePlayerStrategy& AggressivePlayerStrategy::operator = (const AggressivePlayerStrategy& toAssign) {
	if (this == &toAssign) {
		return *this;
	}

	player = toAssign.player;

	return *this;
}

void AggressivePlayerStrategy::issueOrder() {
	vector<Territory*> d_territories = this->toDefend();
	vector<Territory*> potentialAttacks = this->toAttack();

	bool completed = false;
	if (player->getReinforcementPool() > 0) {
		//deploy to strongest country
		deploy(player, d_territories);
	}
	else
	{
		if (potentialAttacks.size() - 1 > player->numAttacks)
		{
			//advance to ennemy territories
			completed = advanceAttack(player, d_territories, potentialAttacks);
		}
		else {
			//defend strongest country (advance to own strongest country)
			completed = advanceDefend(player, d_territories);
		}
		if (!completed) {
			playCard(player, d_territories, potentialAttacks);
			player->setTurnCompleted(true);
			finishedPlayers++;
			cout << "Player " << player->getName() << " has ended their turn" << endl;
		}
	}
	
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> a_territories;
	set<Territory*> a_set;

	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		vector<Territory*> temp = worldMap->getNeighboursPtr(*(player->getTerritories().at(i)->getTerritoryName()));
		for (auto& neighbor : temp) {
			if (neighbor->getOwner() != player) {
				a_set.insert(neighbor);
			}
		}
	}

	for (auto& neighbor : a_set) {
		a_territories.push_back(neighbor);
	}

	sort(a_territories.begin(), a_territories.end(), compareArmyNumberIncrease);

	return a_territories;
}

// Return vector of territories belong to the player in decreasing order, the first territory in the vector will be the strongest
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	vector<Territory*> d_territories;
	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		d_territories.push_back(player->getTerritories().at(i));
	}

	sort(d_territories.begin(), d_territories.end(), compareArmyNumberDecrease);
	return d_territories;
}

string AggressivePlayerStrategy::getStrategyAsString() const {
	return "Aggressive Player (bot)";
}

ostream& operator << (ostream& out, const AggressivePlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}

///
/// BENEVOLENT PLAYER
///

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strat) : PlayerStrategy(strat.player) {
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator = (const BenevolentPlayerStrategy& toAssign) {
	if (this == &toAssign) {
		return *this;
	}

	player = toAssign.player;

	return *this;
}

void BenevolentPlayerStrategy::issueOrder() {
	vector<Territory*> d_territories = this->toDefend();

	bool completed = false;
	if (player->getReinforcementPool() > 0) {
		//deploy to weakest country
		deploy(player, d_territories);
	}
	else
	{
		//defend weakest country (advance to own weakest country)
		completed = advanceDefend(player, d_territories);
		if (!completed) {
			playCard(player, d_territories, {});
			player->setTurnCompleted(true);
			finishedPlayers++;
			cout << "Player " << player->getName() << " has ended their turn" << endl;
		}
	}
}


vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	return {};
}

//return weakest to strongest territory
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> d_territories;
	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		d_territories.push_back(player->getTerritories().at(i));
	}

	sort(d_territories.begin(), d_territories.end(), compareArmyNumberIncrease);
	return d_territories;
}

//return strongest to weakest territory
vector<Territory*> BenevolentPlayerStrategy::getStrongestTerritories() {
	vector<Territory*> d_territories;
	for (int i = 0; i < player->getTerritories().size(); i++)
	{
		d_territories.push_back(player->getTerritories().at(i));
	}

	sort(d_territories.begin(), d_territories.end(), compareArmyNumberDecrease);
	return d_territories;
}

string BenevolentPlayerStrategy::getStrategyAsString() const {
	return "Benevolent Player (bot)";
}

ostream& operator << (ostream& out, const BenevolentPlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}

///
/// NEUTRAL PLAYER
///

/**
 * Constructor takes Player and passes to PlayerStrategy()
*/
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& strat) : PlayerStrategy(strat.player) {
}

/**
 * Empty destructor
*/
NeutralPlayerStrategy::~NeutralPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
NeutralPlayerStrategy& NeutralPlayerStrategy::operator = (const NeutralPlayerStrategy& toAssign) {
	if (this == &toAssign) {
		return *this;
	}

	player = toAssign.player;

	return *this;
}

/**
 * Doesn't issue any orders so just ends turn
*/
void NeutralPlayerStrategy::issueOrder() {
	// I'll have an uh...uhhhhhhhhhhhhhhhh...
	player->setTurnCompleted(true);
	finishedPlayers++;
	cout << "Player " << player->getName() << " has ended their turn" << endl;
}

/**
 * @returns Empty vector since will not attack anything
*/
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	return {};
}

/**
 * @returns Empty vector since will not attack anything
*/
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	return {};
}

string NeutralPlayerStrategy::getStrategyAsString() const {
	return "Neutral Player (bot)";
}

ostream& operator << (ostream& out, const NeutralPlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}

///
/// CHEATER PLAYER
///

/**
 * Constructor takes Player and passes to PlayerStrategy()
*/
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& strat) : PlayerStrategy(strat.player) {
	cout << "Copy" << endl;
}

/**
 * Empty destructor
*/
CheaterPlayerStrategy::~CheaterPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
CheaterPlayerStrategy& CheaterPlayerStrategy::operator = (const CheaterPlayerStrategy& toAssign) {
	if (this != &toAssign) {
		player = toAssign.player;
	}

	return *this;
}

/**
 * Changes ownership for all neighbouring territories and ends turn. Does not issue orders according to prof.
*/
void CheaterPlayerStrategy::issueOrder() {
	vector<Territory*> territoriesToConquer = this->toAttack();

	for (Territory* t : territoriesToConquer) {
		t->setOwner(player);
	}
	
	player->setTurnCompleted(true);
	finishedPlayers++;
	cout << "Player " << player->getName() << " has ended their turn" << endl;
}

/**
 * @returns List of territories the player can attack
*/
vector<Territory*> CheaterPlayerStrategy::toAttack() {
	return getAdjacentEnemyTerritories();
}

/**
 * Gets all enemy territoties adjacent to the player's own territories.
 * Results are not ordered since a Cheater player will conquer all these anyway, regardless
 * of army (a true hero).
 *
 * @returns Vector of all adjacent enemy territories
*/
vector<Territory*> CheaterPlayerStrategy::getAdjacentEnemyTerritories() {
	vector<Territory*> playerTerritories = this->player->getTerritories();
	vector<Territory*> a_territories;
	set<Territory*> a_set;

	for (int i = 0; i < playerTerritories.size(); i++)
	{
		vector<Territory*> temp = worldMap->getNeighboursPtr(*(playerTerritories.at(i)->getTerritoryName()));
		for (auto& neighbor : temp) {
			if (neighbor->getOwner() != this->player) {
				a_set.insert(neighbor);
			}
		}
	}

	for (auto& neighbor : a_set) {
		a_territories.push_back(neighbor);
	}

	return a_territories;
}

/**
 * Cheater player does nothing but absorb other territories
 *
 * @returns Empty vector
*/
vector<Territory*> CheaterPlayerStrategy::toDefend() {
	return {};
}

/**
 * @returns The type of strategy as a string
*/
string CheaterPlayerStrategy::getStrategyAsString() const {
	return "Cheater Player (bot)";
}

/**
 * Outputs relevant information of the Player strategy.
 *
 * @returns The strategy as a string
*/
ostream& operator << (ostream& out, const CheaterPlayerStrategy& strategy) {
	out << strategy.getStrategyAsString();

	return out;
}