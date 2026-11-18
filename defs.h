#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <format>
#include <iomanip>
#include <print>
#include <vector>
#include <time.h>
#include <windows.h>
#include <limits>
#include <conio.h>
#include <functional>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define RED "\x1b[31m"
#define BLACK "\x1b[30m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define NORMAL "\x1b[m"

// extended pallete
// https://jakob-bagterp.github.io/colorist-for-python/ansi-escape-codes/extended-256-colors/#examples_2
#define LIME "\x1b[38;5;40m"
#define ORANGE "\x1b[38;5;215m"
#define DARKBLUE "\x1b[38;5;17m"
#define LILAC "\x1b[38;5;225m"
#define GRAY "\x1b[38;5;235m"
#define GOLD "\x1b[38;5;220m"
#define PURPLE "\x1b[38;5;141m"
#define DEEPRED "\x1b[38;5;9m"
#define PALEYELL "\x1b[38;5;181m"
#define PINK "\x1b[38;5;211m"
#define LIGHTBLUE "\x1b[38;5;45m"
#define ICEBLUE "\x1b[38;5;152m"
#define SANDY "\x1b[38;5;223m"

#define SILVER "\033[38;2;218;238;240m"

// formatting
#define BOLD "\x1b[1m"
#define UNBOLD "\x1b[22m"
#define ITALIC "\033[3m"
#define UNTALIC "\033[23m"
#define RESETCURSOR "\033[H"

void quest1_EnterMillmore();
void quest2_MeetCorvin();

enum StatusType{
    NONE,     /* does nothing (WHITE) */
    POISON,   /* damaged every turn (-15% hp) but can't be killed from it (LIME) */
    BURN,     /* -5% hp every turn, -5% attack every turn. (ORANGE) */
    FEAR,     /* -50% attack, can always flee from enemy when they have it. (DARKBLUE) */
    FROZEN,   /* 75% chance to skip turn. (ICEBLUE) */
    BLEED,    /* -10% hp every turn. (RED) */
    REGEN,    /* +10% hp every turn. (PINK) */
    DIVINE,   /* this status cannot be overwitten (immune to all status effects) (GOLD) */
    CURSED,   /* All damage delt is delt to the cursed dealer as well. (BLACK) */
    ELECTRIC, /* 40% chance to skip turn, 3 flat damage every turn. (YELLOW) */
    CONFUSE,  /* 50% chance to miss attack*/
};

enum DamageType{
    NADA,      /* For non weapon items and enemies with no weakness */
    ARCANE,    /* Standard magic damage */
    SLASH,     /* Standard sword damage ()*/
    STAB,      /* Standard spear damage ()*/
    BLUNT,     /* Standard blugeon damage ()*/
    CAUSTIC,   /* Strong against slime enemies */
    ICE,       /* Strong against fire and water enemies ()*/
    FIRE,      /* Strong against ice enemies ()*/
    LIGHTNING, /* Strong against human enemies ()*/
    FLORA,     /* Strong against stone enemies ()*/
    HOLY,      /* Strong against demonic enemies ()*/
    DARK,      /* Strong against ghost enemies ()*/
};

enum ItemType{ DROP, WEAPON, CATALYST, ARMOR, AMULET, POTION, ARTIFACT, CURE, SCROLL, TOME, KEYITEM, };

enum SpellType{ 
    NOPE,       /* For no type of spell */
    MAGICAL,    /* Regular, basic category of spells with no origin. Basic english names */
    ALCHEMICAL, /* Alchemy related spells, associated with toxins and psuedo science vibe. Named for alchemical terms */
    INCENDIARY, /* Fire type spells associated with a fire cult. Basic english names but like, advanced english */
    CELESTIAL,  /* Space spells. Studied by Old Archanists. Names should sound grandiose */
    LINAURAN,   /* Spells invented in Linaura. These should be real latin names */
    DEMONIC,    /* Evil spells. Associated with blood, fire, and darkness. Should sound like FAKE latin */
    ELENORAN,   /* Spells created by Elenora. Associated with lightning and holy. Should sound like Linauran spells */
    ARBOREAL,   /* Ancient forest spells. Should sound very natural */
};

//main
void pressEnter();
void specialPrint(string text, string color, int speed);

extern int location;
extern vector<int> unlockedAreas;
extern vector<string> areaNames;
extern int progress;
extern bool isTravelling;

extern bool instantDialouge;

#endif 