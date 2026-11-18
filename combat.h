#ifndef COMBAT_H
#define COMBAT_H

#include "defs.h"
#include "entities.h"

int encounter(const vector<Enemy>& area, bool isSpecific, bool isTutorial, int index = 0);
int gauntlet(const vector<Enemy>& enemies, string groupName, string groupTitle);
int battle(Enemy enemy);
int tutorialBattle(Enemy enemy);

int enemyTurn(Player& player, Enemy& enemy, int patternLength, int difficultyLevel);
void enemyUseItem(Enemy& enemy);
void randomEncounter();
void resetPlayer(Player &player);

#endif