#include "defs.h"
#include "entities.h"
#include "ui.h"
#include "events.h"

void searchArea() { // Find stuff

}

void loreTablet(string text) {
    cout << "╔══════════════╗" << endl;
    cout << "║              ║" << endl;
    cout << "║   ═ ══ ═══   ║" << endl;
    cout << "║   ═══ ════   ║" << endl;
    cout << "║   ═══  ═══   ║" << endl;
    cout << "║   ════════   ║" << endl;
    cout << "║   ═══  ═══   ║" << endl;
    cout << "║   ══ ═════   ║" << endl;
    cout << "║              ║" << endl;
    cout << "╠══════════════╣" << endl;
    cout << "╚══════════════╝" << endl << endl;
    cout << "You found a stone tablet!" << endl;
    cout << "Its words are thus..." << endl << endl;

    cout << "\"" << ITALIC << text << UNTALIC << "\"" << endl;
}

void genericLoreResponse() {
    string messages[5] = {
    "\nYou ponder it's meaning...\n",
    "\nThe words make you think...\n",
    "\nIt makes you question what came before...\n",
    "\nYou contemplate its significance...\n",
    "\nThe tablet sparks a quiet curiosity...\n"
    };

    int messagesIndex = rand() % 5;
    cout << messages[messagesIndex] << endl;
    pressEnter();
}

void shrineDecor() {
    cout << "        ╔═══════════════╗        " << endl;
    cout << " ══════ ║  ♦    ♦    ♦  ║ ══════ " << endl;
    cout << "╔══╦═╦══╩═══════════════╩══╦═╦══╗" << endl;
    cout << "│  ║ ║       ╔═════╗       ║ ║  │" << endl;
    cout << "║  ║ ║     ╔═╩═════╩═╗     ║ ║  ║" << endl;
    cout << "│  ║ ║     ║ ■  ■  ■ ║     ║ ║  │" << endl;
    cout << "╠══╩═╩═════╩═════════╩═════╩═╩══╣" << endl;
    cout << "╚═══════════════════════════════╝" << endl << endl;
}

void monestaryDecor() {
    cout << "                     ╔═══╗   ╔═══╗" << endl;
    cout << "   ╔═════╗           ║   ╚═══╝   ║" << endl;
    cout << "   ║     ║           ║ ■ ■ ■ ■ ■ ║" << endl;
    cout << "   ╚═════╝           ║           ║" << endl;
    cout << "                     ║           ║" << endl;
    cout << "╔═══╗  ╔═══╗  ╔═══╗  ║           ║" << endl;
    cout << "║   ╚══╝   ╚══╝   ╚══╝           ║" << endl;
    cout << "║            ■ ■ ■ ■             ║" << endl;
    cout << "║   ╔═══╗   ╒═══════╕    ╔═══╗   ║" << endl;
    cout << "║   ║   ║   │       │    ║   ║   ║" << endl;
    cout << "║   ╚═══╝   ┠───────┨    ╚═══╝   ║" << endl;
    cout << "╚═══ ═══════╛       ╘══════ ═════╝" << endl << endl;
}

void spellShrine() { // Learn spells here (based on intelligence)
    system("cls");

    int learnChance = min(100, (int)(player.intelligence + 50.0));

    cout << "You found a scroll shrine. Place a scroll on the tablet." << endl;
    cout << "With your intelligence, you have a " << learnChance << "% chance of learning each spell." << endl << endl;

    shrineDecor();

    Item scroll = inventory(player, 2);

    system("cls");
    shrineDecor();

    for (int i = 0; i < (int)scroll.spells.size(); i++) {
        Spell spell = scroll.spells.at(i);

        if (findSpell(spell) != -1) {
            cout << "You already know the " << spell.getColor() << spell.getName() << NORMAL << " spell." << endl;
        }
        else if (rand() % 100 < learnChance) {
            player.learnedSpells.push_back(spell);
            cout << "You learned the " << spell.getColor() << spell.getName() << NORMAL << " spell!" << endl;
        }
        else {
            cout << "You didn't learn the " << spell.getColor() << spell.getName() << NORMAL << " spell..." << endl;
        }
        Sleep(1000);
    }

    pressEnter();
}

void monestary() {
    system("cls");
    int learnChance = min(100, (int)(player.intelligence + 50.0));

    cout << "You found a Monestary. Enter inside to learn a skill from a Tome." << endl;
    cout << "With your intelligence, you have a " << learnChance << "% chance of learning the skill." << endl << endl;

    monestaryDecor();
    Item tome = inventory(player, 3);

    system("cls");
    monestaryDecor();

    if(findSkill(tome.ability) != -1) cout << "You already know the " << tome.ability.name << NORMAL << " skill." << endl;
    else if (rand() % 100 < learnChance) {
        player.learnedAbilities.push_back(tome.ability);
        cout << "You learned the " << tome.ability.name << NORMAL << " skill." << endl;}
    else cout << "You didn't learn the " << tome.ability.name << NORMAL << " skill." << endl;
    Sleep(1000);
    
    pressEnter();
}

void shop(string name, vector<Item> wares, string color){
    cout << "╔═════════════════════════<" << color << "o" NORMAL << ">═════════════════════════╗" << endl;
    cout << "[ # | " << name << endl;
    cout << "╚═════════════════════════<" << color << "o" NORMAL << ">═════════════════════════╝" << endl << endl;

    int counter = 0;
    for (int i = 0; i < wares.size(); i++){
        cout << "  [ " << right << setfill('0') << setw(2) << (i + 1) << left << setfill(' ') << " ] "
        << wares.at(i).getColor() << setw(20) << wares.at(i).getName() << NORMAL;
        counter++;
        if(counter >= 2) {
            counter = 0;
            cout << endl;
        }
    }
    
}

void chest(Item key, vector<Item> loot, string rarityColor) { // Get weapons from these
    cout << rarityColor;
    cout << "╔═══════════════════╗" << endl;
    cout << "╠═════╠═══════║═════╣" << endl;
    cout << "╠═    ║   ■   ║    ═╣" << endl;
    cout << "║     ║       ║     ║" << endl;
    cout << "╚═════╩═══════╩═════╝" << endl << endl << NORMAL;

    bool hasKey = false;

    if(findItem(key) != -1) hasKey = true;

    if(hasKey){
        cout << "You use your key to open the chest..." << endl << endl;
        for (int i = 0; i < loot.size(); i++){
            Item item = loot.at(i);
            addItem(item);
            cout << "You obtained a " << item.getColor() << item.getName() << NORMAL << " !" << endl;
            Sleep(1000);
        }
    }
    else {
        cout << "Find a " << key.getColor() << key.getName() << NORMAL << " to open the chest.\n\n";
    }

    pressEnter();
}

int dice(){
    int roll = rand() % 6 + 1;
    
    // I know it looks strange, but this is an array of dice
    string faces[6] = {
        "           ╔═════════╗\n           ║         ║\n           ║    ○    ║\n           ║         ║\n           ╚═════════╝",
        "           ╔═════════╗\n           ║       ● ║\n           ║         ║\n           ║ ●       ║\n           ╚═════════╝",
        "           ╔═════════╗\n           ║       ● ║\n           ║    ○    ║\n           ║ ●       ║\n           ╚═════════╝",
        "           ╔═════════╗\n           ║ ●     ● ║\n           ║         ║\n           ║ ●     ● ║\n           ╚═════════╝",
        "           ╔═════════╗\n           ║ ●     ● ║\n           ║    ○    ║\n           ║ ●     ● ║\n           ╚═════════╝",
        "           ╔═════════╗\n           ║ ●     ● ║\n           ║ ●     ● ║\n           ║ ●     ● ║\n           ╚═════════╝"
    };

    for (int i = 0; i < 11; i++)
    {
        cout << faces[(rand() % 6 + 1) - 1] << endl;
        Sleep(100);
        cout << RESETCURSOR;
    }
    system("cls");
    
    cout << faces[roll-1] << endl;

    return roll;
}
