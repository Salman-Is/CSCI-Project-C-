#ifndef UI_H
#define UI_H

#include "defs.h"
#include "entities.h"

void bar(int currentVal, int maxVal, string color);
void percentBar(int currentNum, int maxNum, int maxBars, string color, string icon);
void battleUI(Enemy enemy, bool isPlayerTurn);
char options();
string statusText(StatusType status);
int selectSpellUI(Player& player);

int findItem(Item itemToFind);
int findSpell(Spell spellToFind);
int findSkill(Ability abilityToFind);

Item inventory(Player& player, int type);
void addItem(Item itemToAdd);
void removeItem(Item itemToRemove);

void dialougeBox(string name, string color, string tag, bool isLast = false);
void narrationBox(string color, string tag);
int reply(vector<string> replyChoices);

void viewItem(Item item);
void viewEnemy(Enemy enemy);

#endif