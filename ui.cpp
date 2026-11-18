#include "defs.h"
#include "entities.h"
#include "combat.h"
#include "ui.h"
#include "events.h"

/*
This script is used for display, and creates the UI elements 
so the player can know what is going on, and so it looks nice
*/

int loadDialogueLines(string tag, char lines[32][512]);
void stats();
void gearMenu();
void travel();

#define HOME "\033[2J\033[H"

// reates a progress bar for any purpose
// Parameters; currentVal maxVal -> current value that the progress bar is at right now (colored part), and depleted part (black)
//             color -> the color of filled part
void bar(int currentVal, int maxVal, string color) {
    cout << "[ ";
    for (int i = 0; i < maxVal; i++) {
        if (i < currentVal)
            cout << color << "■" << NORMAL;
        else
            cout << BLACK << "■" << NORMAL;
    }
    cout << " ]";
}

// Same as bar but it operates on a ration percentage based system instead, useful for large numbers
// Parameters: same as the last one, but also with the max number of bars taht the ratio works with
void percentBar(int currentNum, int maxNum, int maxBars, string color, string icon) {
    int filled = (currentNum * maxBars) / maxNum;
    if (currentNum > 0 && filled == 0) filled = 1;   // always at least one segment

    cout << "[ ";
    for (int i = 0; i < maxBars; i++) {
        if (i < filled)
            cout << color << icon << NORMAL;  
        else
            cout << BLACK << icon << NORMAL;
    }
    cout << " ]";
}

// Very simple function that returns text based on enum value
string statusText(StatusType status){
    switch(status){
        case POISON: 
            return LIME "POIS" NORMAL;
        case BURN: 
            return ORANGE "BURN" NORMAL;
        case FEAR: 
            return DARKBLUE "FEAR" NORMAL;
        case FROZEN:
            return ICEBLUE "FRZN" NORMAL;
        case BLEED: 
            return RED "BLED" NORMAL; 
        case ELECTRIC:
            return YELLOW "ELEC" NORMAL;
        case CONFUSE: 
            return LILAC "CONF" NORMAL;
        case REGEN:
            return PINK "REGN" NORMAL;
        case CURSED: 
            return BLACK "CURS" NORMAL;
        case DIVINE:
            return GOLD "DIVN" NORMAL;
        default:
            return "NONE";
    }
}

// looks more complex than it is, just prints out the battle UI based on the current enemy and player stats
// Parameters: enemy -> enemy we are fighting, isPlayerTurn -> self explanitory, used bevcause player turn needs a different ui (slightly)
void battleUI(Enemy enemy, bool isPlayerTurn) {

    cout << "╔═════════════════════════════▪" << RED "■" NORMAL << "▪═════════════════════════════╗" << endl << endl;
    cout << "  [ " << RED << enemy.name << NORMAL << " ]" << endl << "  Status: [ " << statusText(enemy.currentStatus) 
    << " ] ATK: [ " << enemy.currentAttack << " ]" << " Item Used: " << ((enemy.usedItem) ? GREEN "✓" : RED "X") << NORMAL << endl << endl;
    cout << "  HP:  " << "[ " << enemy.currentHealth << " / " << enemy.maxHealth << " ] "; 
    percentBar(enemy.currentHealth, enemy.maxHealth, 35, RED, "■"); cout << endl << endl;
    cout << "╚═════════════════════════════▪" << RED "■" NORMAL << "▪═════════════════════════════╝" << endl;

    cout << "╔═════════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════════╗" << endl << endl;
    cout << "  [ " << CYAN << player.name << NORMAL <<  " ]" << endl << "  Status: [ " 
    << statusText(player.currentStatus) << " ] ATK: [ " << player.currentAttack << " ] MATK: [ " << player.currentMattack << " ]" << endl << endl;
    cout << "  HP:   " << "[ " << player.currentHealth << " / " << player.maxHealth << " ] "; 
    bar(player.currentHealth, player.maxHealth, RED); cout << endl;
    cout << "  MANA: " << "[ " << player.currentMana << " / " << player.maxMana << " ] "; 
    bar(player.currentMana, player.maxMana, BLUE); cout << endl;
    cout << "  STA:  " << "[ " << player.currentStamina << " / " << player.maxStamina << " ] "; 
    bar(player.currentStamina, player.maxStamina, GREEN); cout << endl << endl;
    cout << "╚═════════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════════╝" << endl;
    
    if(isPlayerTurn) {
        cout << "         [ 1 | STRIKE ]  [ 2 | SPELL  ]  [ 3 | SKILL  ]      " << endl;
        cout << "         [ 4 | ITEM   ]  [ 5 | -----  ]  [ 6 | FLEE   ]      " << endl << endl;
    }

}

// in battle, this is used to select which spell you want to use
int selectSpellUI(Player& player) {
    system("cls");

    cout << "═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═" << endl << endl;

    for (int i = 0; i < 3; i++) {
        Spell s = player.spells.at(i);

        // No spell there (as in equipped at that slot)
        if (s.getName() == noneSpell.getName()) {
            cout << "  [" << i + 1 << "] ---" << endl << endl;
            continue;
        }

        // Spell is there
        string costColor = (player.currentMana < s.getManaCost()) ? RED : BLUE; 
        cout << "  [" << i + 1 << "] " << s.getColor() << left << setfill(' ') << setw(30) << s.getName() << NORMAL
             << costColor << right << setw(3) << s.getManaCost() << " MANA" << NORMAL << endl;
        cout << "      " << s.getDesc() << endl << endl;
    }

    cout << "═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═" << endl;
    cout << "  MANA  ";
    bar(player.currentMana, player.maxMana, BLUE);
    cout << "  " << player.currentMana << " / " << player.maxMana << endl << endl;

    int choice;
    cout << "Choose a spell (1-3) > ";
    cin >> choice;

    if (choice < 1 || choice > 3) return -1;

    Spell chosen = player.spells.at(choice - 1);
    if (chosen.getName() == noneSpell.getName()) {
        cout << "No spell is equipped in that slot." << endl;
        pressEnter();
        return -1;
    }
    if (player.currentMana < chosen.getManaCost()) {
        cout << "Not enough mana." << endl;
        pressEnter();
        return -1;
    }
    return choice - 1;
}

Item inventory(Player& player, int type) {

    int counter = 0;

    if (type == 0) { // Normal Inventory
        system("cls");
        cout << "╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "[ # ] | INVENTORY                                                                                   ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl << endl;
        for (int i = 0; i < player.inventory.size(); i++){
            cout << "  [ " << right << setfill('0') << setw(2) << (i + 1) << left << setfill(' ') << " ] "
            << player.inventory.at(i).getColor() << setw(20) << player.inventory.at(i).getName() << NORMAL
            << " x" << right << setfill('0') << setw(2) << player.inventory.at(i).quantity;
            counter++;
            if(counter >= 3) {
                counter = 0;
                cout << endl;
            }
        }
        cout << endl << "╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗";
        cout << endl << "║ Choose an Item to Inspect [ 0 | To Return ]                                                       ║";
        cout << endl << "╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;

        int choice;
        cout << "> ";
        cin >> choice;

        if(choice > 0) {
            viewItem(player.inventory.at(choice - 1));
            return player.inventory.at(choice - 1);
        }
        if(choice <= 0) return noneItem;
    }
    else if (type == 1) { // Battle Inventory
        system("cls");
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "[ # ] | ITEMS                                                   ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
        vector<Item> fakeInventory;
        int number = 1;
        for (int i = 0; i < player.inventory.size(); i++){
            if (player.inventory.at(i).getEnumCate() == POTION || player.inventory.at(i).getEnumCate() == ARTIFACT || player.inventory.at(i).getEnumCate() == CURE) {
                cout << "[ " << right << setfill('0') << setw(2) << (number) << left << setfill(' ') << " ] "
                << player.inventory.at(i).getColor() << setw(20) << player.inventory.at(i).getName() << NORMAL
                << " x" << right << setfill('0') << setw(2) << player.inventory.at(i).quantity << " ";
                counter++;
                if(counter >= 2) {
                    counter = 0;
                    cout << endl;
                }
                fakeInventory.push_back(player.inventory.at(i));
                number++;
            }
        }
        cout << endl;
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║ Choose an Item to Use                                         ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

        int choice;
        cout << "> ";
        cin >> choice;

        Item chosenItem = fakeInventory.at(choice - 1);
        return chosenItem;
    }
    else if(type == 2){ // Shrine Inventory
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "[ # ] | SCROLLS                                                 ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
        vector<Item> fakeInventory;
        int number = 1;
        for (int i = 0; i < player.inventory.size(); i++){
            if (player.inventory.at(i).getEnumCate() == SCROLL) {
                cout << "[ " << right << setfill('0') << setw(2) << (number) << left << setfill(' ') << " ] "
                << player.inventory.at(i).getColor() << setw(20) << player.inventory.at(i).getName() << NORMAL
                << " x" << right << setfill('0') << setw(2) << player.inventory.at(i).quantity << " ";
                counter++;
                if(counter >= 2) {
                    counter = 0;
                    cout << endl;
                }
                fakeInventory.push_back(player.inventory.at(i));
                number++;
            }
        }
        cout << endl;
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║ Choose a Scroll to Learn                                      ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

        int choice;
        cout << "> ";
        cin >> choice;

        Item chosenItem = fakeInventory.at(choice - 1);
        return chosenItem;
    } 
    else if(type == 3){ // Tome Inventory
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "[ # ] | SKILL TOMES                                             ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
        vector<Item> fakeInventory;
        int number = 1;
        for (int i = 0; i < player.inventory.size(); i++){
            if (player.inventory.at(i).getEnumCate() == TOME) {
                cout << "[ " << right << setfill('0') << setw(2) << (number) << left << setfill(' ') << " ] "
                << player.inventory.at(i).getColor() << setw(20) << player.inventory.at(i).getName() << NORMAL
                << " x" << right << setfill('0') << setw(2) << player.inventory.at(i).quantity << " ";
                counter++;
                if(counter >= 2) {
                    counter = 0;
                    cout << endl;
                }
                fakeInventory.push_back(player.inventory.at(i));
                number++;
            }
        }
        cout << endl;
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║ Choose a Tome to Read                                         ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

        int choice;
        cout << "> ";
        cin >> choice;

        Item chosenItem = fakeInventory.at(choice - 1);
        return chosenItem;
    } 

    return sealOfSonder;
}

void beastiary() {
    system("cls");
    int counter = 0;
    cout << "╔═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╗" << endl;
    cout << "[ # ] | BEASTIARY  [ 0 to Return ]" << endl;
    cout << "╚═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╝" << endl << endl;
    for (int i = 0; i < player.beastiary.size(); i++){
        cout << "  [ " << right << setfill('0') << setw(2) << (i + 1) << left << setfill(' ') << " ] "
        << RED << setw(20) << player.beastiary.at(i).getName() << NORMAL;
        counter++;
        if(counter >= 2) {
            counter = 0;
            cout << endl;
        }
    }
    cout << endl <<"╚═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╝" << endl << endl;
    int choice;
    cout << "> ";
    cin >> choice;

    if(choice > 0) {
        viewEnemy(player.beastiary.at(choice - 1));
    }
}

// Function searches for an item in the player's inventory (which is a vector of items)
// Paremeter: The item that we are looking for
// Returns the item's location it finds the object, -1 if the object isn't found
int findItem(Item itemToFind) {
    for (int i = 0; i < player.inventory.size(); i++){
        if(player.inventory.at(i).getName() == itemToFind.getName()) { // Apparently you can't compare class objects?
            return i;
        }
    }
    return -1;
}

int findSpell(Spell spellToFind) {
    for (int i = 0; i < player.learnedSpells.size(); i++){
        if(player.learnedSpells.at(i).getName() == spellToFind.getName()) { // Apparently you can't compare class objects?
            return i;
        }
    }
    return -1;
}

int findSkill(Ability abilityToFind) {
    for (int i = 0; i < player.learnedAbilities.size(); i++){
        if(player.learnedAbilities.at(i).name == abilityToFind.name) { // Apparently you can't compare class objects?
            return i;
        }
    }
    return -1;
}

// If we find the item already in the inventory, we increase the quanitiy, otherwise pushback the item into inventory
// Parameter: Item we are going to add
void addItem(Item itemToAdd) {
    if(findItem(itemToAdd) != -1) {
        player.inventory.at(findItem(itemToAdd)).quantity++;
    }
    else{
        player.inventory.push_back(itemToAdd);
        player.inventory.at(findItem(itemToAdd)).quantity++;
    }
}

// If we find the item already in the inventory, we decrease the quanitiy, otherwise erase the item in inventory
// Parameter: Item we are going to remove
void removeItem(Item itemToRemove) {
    if(findItem(itemToRemove) != -1 && itemToRemove.quantity != 1) {
        player.inventory.at(findItem(itemToRemove)).quantity--;
    }
    else if (itemToRemove.quantity == 1){
        player.inventory.erase(player.inventory.begin() + findItem(itemToRemove));
    }
}

// Lists every inventory item of one category and returns the one picked (noneItem if they back out), basically a mini inventory
Item pickItem(string title, ItemType category) {
    vector<Item> options;
    cout << "  " << title << endl << endl;
    for (int i = 0; i < (int)player.inventory.size(); i++) {
        if (player.inventory.at(i).getEnumCate() == category) {
            options.push_back(player.inventory.at(i));
            cout << "  [ " << right << setfill('0') << setw(2) << options.size() << left << setfill(' ') << " ] "
                 << options.back().getColor() << setw(20) << options.back().getName() << NORMAL << endl;
        }
    }
    if (options.empty()) {
        cout << "  Nothing here you can equip." << endl;
        pressEnter();
        return noneItem;
    }
    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl << endl;
    cout << "  [ 0 ] Back" << endl << "> ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > (int)options.size()) return noneItem;
    return options.at(choice - 1);
}

// Equipment and stuff ==========================================================================================================================================================================================================================

void equipWeaponUI() {
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped: " << player.weapon.getColor() << player.weapon.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl;
    Item chosen = pickItem("Weapons", WEAPON);
    
    if (chosen.getName() == noneItem.getName()) return;

    player.weapon = chosen;
    cout << endl << "You equipped the " << chosen.getColor() << chosen.getName() << NORMAL << "." << endl;
    pressEnter();
    gearMenu();
}

void equipCatalystUI() {
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped: " << player.catalyst.getColor() << player.catalyst.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl;
    Item chosen = pickItem("Catalysts", CATALYST);
    
    if (chosen.getName() == noneItem.getName()) return;

    player.catalyst = chosen;
    cout << endl << "You equipped the " << chosen.getColor() << chosen.getName() << NORMAL << "." << endl;
    pressEnter();
    gearMenu();
}

void equipArmorUI() {
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped: " << player.armor.getColor() << player.armor.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl;
    Item chosen = pickItem("Armor Sets", ARMOR);
    
    if (chosen.getName() == noneItem.getName()) return;

    player.armor = chosen;
    cout << endl << "You equipped the " << chosen.getColor() << chosen.getName() << NORMAL << "." << endl;
    pressEnter();
    gearMenu();
}

void gearMenu(){
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped Weapon: " << player.weapon.getColor() << player.weapon.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped Catalyst: " << player.catalyst.getColor() << player.catalyst.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped Armor Set: " << player.armor.getColor() << player.armor.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    int choice;
    cout << "What would you like to change?" << endl << "[ 1 | Weapon ] [ 2 | Catalyst ] [ 3 | Armor ] [ 0 | Return ]" << endl << endl;
    cout << "> ";

    cin >> choice;

    if(choice == 0) return;

    if(choice == 1) {
        equipWeaponUI();
    } else if (choice == 2){
        equipCatalystUI();
    } else{
        equipArmorUI();
    }

}

void equipAmuletUI() {
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << " Equipped" << endl;
    for (int i = 0; i < 3; i++) cout << "  Slot " << i + 1 << ": " << player.amulets.at(i).getColor() << player.amulets.at(i).getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;

    cout << endl;

    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl;
    Item chosen = pickItem("Amulets", AMULET);
    if (chosen.getName() == noneItem.getName()) return;

    // checks if you have the amult already
    for (int i = 0; i < 3; i++) {
        if (player.amulets.at(i).getName() == chosen.getName()) {
            cout << endl << "You are already wearing that amulet." << endl;
            pressEnter();
            equipAmuletUI();
        }
    }

    cout << endl << "Which slot? (1-3) > ";
    int slot;
    cin >> slot;
    if (slot < 1 || slot > 3) return;

    player.amulets.at(slot - 1) = chosen;
    cout << endl << "You equipped the " << chosen.getColor() << chosen.getName() << NORMAL << "." << endl;
    pressEnter();
    equipAmuletUI();
}

void equipSpellUI() {
    system("cls");

    cout << "╔══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╗" << endl;
    cout << "  Equipped Spells:" << endl << endl;
    for (int i = 0; i < 3; i++) cout << "  Slot " << i + 1 << ": " << player.spells.at(i).getColor() << player.spells.at(i).getName() << NORMAL << endl;
    cout << "╚══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╝" << endl << endl;

    cout << "╔══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╗" << endl;
    cout << "  Learned Spells" << endl << endl;

    for (int i = 0; i < (int)player.learnedSpells.size(); i++) {
        Spell spell = player.learnedSpells.at(i);
        cout << "  [ " << right << setfill('0') << setw(2) << i + 1 << left << setfill('.') << " ] "
            << spell.getColor() << setw(20) << spell.getName() << setfill('0') << setw(2) << right << NORMAL << spell.getManaCost() << " MP | " 
            << spell.getDesc() << endl << endl;
    }

    cout << "╚══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╝" << endl << endl;

    cout << "[ 0 ] Back" << endl << "> ";

    int choice;
    cin >> choice;
    
    if (choice < 1 || choice > (int)player.learnedSpells.size()) return;
    Spell chosen = player.learnedSpells.at(choice - 1);

    // checks if its in another slot already
    for (int i = 0; i < 3; i++) {
        if (player.spells.at(i).getName() == chosen.getName()) {
            cout << endl << "That spell is already equipped." << endl;
            equipSpellUI();
        }
    }

    cout << endl << "Which slot? (1-3) > ";
    int slot;
    cin >> slot;
    if (slot < 1 || slot > 3) return;

    player.spells.at(slot - 1) = chosen;
    cout << endl << "You equipped " << chosen.getColor() << chosen.getName() << NORMAL << "." << endl;
    pressEnter();
    equipSpellUI();
}

void equipSkillUI() {
    system("cls");
    cout << "╔══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╗" << endl;
    cout << "  Equipped Ability: " << player.skill.name << endl;
    cout << "╚══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╝" << endl << endl;

    cout << "╔══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╗" << endl;
    cout << "  Learned Abilities" << endl << endl;

    for (int i = 0; i < (int)player.learnedAbilities.size(); i++) {
        Ability ability = player.learnedAbilities.at(i);
        cout << "  [ " << right << setfill('0') << setw(2) << i + 1 << left << setfill('.') << " ] "
        << setw(24) << ability.name << setfill('0') << setw(2) << right << ability.staminaCost << " SP | " << ability.description << endl << endl;
    }
    cout << "╚══════════════════════════════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════════════════════════════╝" << endl << endl;

    cout <<"[ 0 ] Back" << endl << "> ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > (int)player.learnedAbilities.size()) return;

    player.skill = player.learnedAbilities.at(choice - 1);
    cout << endl << "You equipped " << player.skill.name << "." << endl;
    pressEnter();
}

//==========================================================================================================================================================================================================================

void levelUpScreen() {
    system("cls");
    bool hasChosen = false;

    while(!hasChosen){
        cout << "                     < Level Stats >" << endl << endl;
        cout << "─═════════════─ <" << BLUE "♦" NORMAL << "> ─═════════════─" << endl << endl;

        cout << "  [ 1 ]  Health............"       << player.maxHealth << endl;
        cout << "  [ 2 ]  Attack............"       << player.attack << endl;
        cout << "  [ 3 ]  Magic Attack......" << player.magicAttack << endl;
        cout << "  [ 4 ]  Intelligence......" << player.intelligence << endl;
        cout << "  [ 5 ]  Mana.............."         << player.maxMana << endl;
        cout << "  [ 6 ]  Stamina..........."      << player.maxStamina << endl << endl;

        cout << "─═════════════─ <" << BLUE "♦" NORMAL << "> ─═════════════─" << endl << endl;

        int choice;
        cout << "Level which stat: ";
        cin >> choice;

        switch (choice){
        case 1:
            player.maxHealth += 1;
            cout << "You chose to level up Health!" << endl; hasChosen = true; break;
        case 2:
            player.attack += 1;
            cout << "You chose to level up Attack!" << endl; hasChosen = true; break;
        case 3:
            player.magicAttack += 1;
            cout << "You chose to level up Magic Attack!" << endl; hasChosen = true; break;
        case 4:
            player.intelligence += 1;
            cout << "You chose to level up Intelligence!" << endl; hasChosen = true; break;
        case 5:
            player.maxMana += 1;
            cout << "You chose to level up Mana!" << endl; hasChosen = true; break;
        case 6:
            player.maxStamina += 1;
            cout << "You chose to level up Stamina!" << endl; hasChosen = true; break;
        default:
            cout << "Invalid choice!" << endl; hasChosen = true; break;
        }
    }
}

void stats() {
    system("cls");
    cout << "╒═══════════════════<" << BLUE "♦" NORMAL << ">═══════════════════╕" << endl;
    cout << " " << BLUE << player.name << NORMAL << "    Level: " << player.level << endl ;
    cout << "╘═══════════════════<" << BLUE "♦" NORMAL << ">═══════════════════╛" << endl << endl;
    
    cout << " Health........[" << player.maxHealth << "]" <<   
    "     Attack........[" << player.attack << "]" << endl;
    cout << " Mana..........[" << player.maxMana << "]" <<   
    "     Magic Attack..[" << player.magicAttack << "]" << endl;
    cout << " Stamina.......[" << player.maxStamina << "]" <<   
    "     Intelligence..[" << player.intelligence << "]" << endl << endl;

    cout << "════════════════════<" << BLUE "♦" NORMAL << ">════════════════════" << endl;
    cout << " Class: ( " << player.className << " )";
    cout << "   Silverbells: ( " << SILVER << player.coins << NORMAL " )" << endl;
    cout << "════════════════════<" << BLUE "♦" NORMAL << ">════════════════════" << endl << endl;

    pressEnter();

}

// Main options menu that the player will use to choose what to do next
// returns the coorespondig char that the player picked
char options() {
    system("cls");
    cout << " Location: [ " << areaNames[location - 1] << " ]   Progress: [ " << progress << " / 30 ]   Level: " << player.level << endl;
    cout << "╒═════════════════<" << BLUE "♦" NORMAL << ">═════════════════╕ ╒═════════════════<" << BLUE "♦" NORMAL << ">═════════════════╕" << endl;
    cout << "│   EXPLORE                           │ │   INSPECT                           │" << endl;
    cout << "│                                     │ │                                     │" << endl;
    cout << "│   [ 1 | ADVANCE ] [ 2 | SEARCH  ]   │ │   [ a | ITEMS   ] [ b | WEAPON  ]   │" << endl;
    cout << "│   [ 3 | BATTLE  ] [ 4 | TRAVEL  ]   │ │   [ c | AMULETS ] [ d | SPELLS  ]   │" << endl;
    cout << "│   [ 5 | CRAFT   ] [ 6 | ENEMIES ]   │ │   [ e | SKILLS  ] [ f | STATS   ]   │" << endl; 
    cout << "│                                     │ │                                     │" << endl;
    cout << "╘═════════════════<" << BLUE "♦" NORMAL << ">═════════════════╛ ╘═════════════════<" << BLUE "♦" NORMAL << ">═════════════════╛" << endl;
    cout << "EXP ";
    percentBar(player.experience, player.maxExperience, 71, BLUE, "■"); cout << endl << endl;

    cout << "> ";
    char choice;
    cin >> choice;

    switch (choice){ 
    /* EXPLORE -----------------------------------------------------*/
    case '1': // <-------------- ADVANCE ---------------->
    
        if(isTravelling == false) return '1'; 
        else {
            cout << "You don't find much... (Return to the Story to keep going)" << endl << endl; 
            Sleep(2000);
            return 'Z';
        }
        break;

    case '2': // <-------------- SEARCH ---------------->
        monestary();
        return '2'; 
        break;

    case '3': // <-------------- BATTLE ---------------->
        randomEncounter(); 
        return '3'; 
        break;

    case '4': // <-------------- TRAVEL ---------------->
        travel();
        return '4'; 
        break;

    case '5': // <-------------- CRAFT ---------------->

        return '5'; 
        break;

    case '6': // <-------------- BEASTIARY ---------------->
        beastiary();
        return '6'; 
        break;


    /* INSPECT -----------------------------------------------------*/
    case 'a': // <-------------- ITEMS ---------------->
        inventory(player, 0); return 'd'; 
        return 'a'; 
        break;

    case 'b': // <-------------- GEAR ---------------->
        gearMenu();
        return 'b'; 
        break;

    case 'c': // <-------------- AMULETS ---------------->
        equipAmuletUI();
        return 'c'; 
        break;

    case 'd': // <-------------- SPELLS ---------------->
        equipSpellUI();
        return 'd'; 
        break;

    case 'e': // <-------------- SKILLS ---------------->
        equipSkillUI();
        return 'e'; 
        break;

    case 'f': // <-------------- STATS ---------------->
        stats();
        return 'f'; 
        break;


        /* Debug -----------------------------------------------------*/
    case 's': // SKIP TO LATER QUEST

        return 's'; break;
    case 't': // INSTANT TEXT
        instantDialouge = true; return 't'; break;
    case 'u': // DEBUG STRENGTH
        cout << RED << "You were granted strength beyond this world." << NORMAL << endl << endl;
        Sleep(1000);
        player.maxHealth = 99;
        player.attack = 99;
        player.magicAttack = 99;
        player.maxStamina = 99;
        player.maxMana = 99;
        player.intelligence = 99;
        player.spells[0] = earlStar; 
        player.spells[1] = earlStar; 
        player.spells[2] = earlStar; 
        player.weapon = UltraBlade;
        player.catalyst = infiniteTome;
        
        return 'u'; break;
    case 'v': // ITEMS

        return 'v'; break;
    case 'w': // QUESTS

        return 'w'; break;
    case 'x': // HELP

        return 'x'; break;
    case 'y': // HELP

        return 'y'; break;
    case 'z': // HELP

        return 'z'; break;
    
    default:
       return '0'; break;
    }


    pressEnter();
}

// opens and reads dialouge.txt and extracts the lines under a given tag. Could have been part of the dialouge function but separated for readablity
// Parameters: "tag" (name of the dialouge blurb), lines of text
// Returns the count of lines found, fills 'lines' array
int loadDialogueLines(string tag, char lines[32][512]) {
    char fileName[] = "dialouge.txt";
    FILE *file = fopen(fileName, "r");

    if (!file) {
        cout << "Could not open " << fileName << endl;
        return -1;
    }

    char line[256];
    int count = 0;
    int found = 0;

    char target[64];
    sprintf(target, "[%s]", tag.c_str());

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        if (line[0] == '[') {
            if (strcmp(line, target) == 0) {
                found = 1;
                continue;
            } else if (found) {
                break;
            }
        }
        if (found) {
            strcpy(lines[count], line);
            count++;
        }
    }

    fclose(file);

    if (!found) {
        cout << "Dialogue tag [" << tag << "] not found.\n";
        return -1;
    }

    return count;
}

// Prints out a dialouge box for the player based on what loadDialougeLines collected
// Parameters: name -> name of the character, color -> color of the current line/nametag, tag -> the "tag" that we look for from dialouge.txt
//             isLast -> checks if it is the last reply so it wont clear (for replies to keep the last message up there)
void dialougeBox(string name, string color, string tag, bool isLast) {
    char lines[32][512];
    int count = loadDialogueLines(tag, lines);
    if (count < 0) return;

    int speed = (instantDialouge ? 0 : 17);


    system("cls");

    for (int i = 0; i < count; i++){
        cout << HOME;

        cout << "( " << color << name << NORMAL << " )" << endl;
        cout << "╭──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮" << endl << endl;

        // print all already-typed lines instantly
        for (int j = 0; j < i; j++) {
            cout << "  " << lines[j] << endl;
        }

        cout << endl << endl << "╰──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╯" << endl;

        // move the cursor back up 2 rows (the blank line + footer we just printed)
        // so the next line we write lands in the empty row ABOVE the footer

        // # Source - https://stackoverflow.com/a/10402513
        // # Posted by John Bode
        // # Retrieved 2026-10-27, License - CC BY-SA 3.0
        cout << "\033[3A";

        // now animate the current line into that empty row
        cout << "  ";
        specialPrint(lines[i], color, speed);
        cout << endl;   // finishing the line drops the cursor back down into the already-drawn footer area
    }

    cout << RESETCURSOR;
    cout << "( " << color << name << NORMAL << " )" << endl;
    cout << "╭──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮" << endl << endl;

    for (int i = 0; i < count; i++) {
        cout << "  " << lines[i] << "\n";
    }

    cout << endl << "╰──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╯" << endl;
    
    cout << endl;
    if (!isLast) pressEnter();
}

// Same as dialougeBox(), but with centering
void narrationBox(string color, string tag) {
    char lines[32][512];
    int count = loadDialogueLines(tag, lines);

    int speed = 20;

    if (count < 0) return;

    for (int i = 0; i < count; i++) {
        cout << HOME;
        cout << "────────────────────────────────────────────────═════════ ❖ ═════════─────────────────────────────────────────────────" << endl << endl;

        for (int j = 0; j < i; j++) {
            cout << string((118 - (int)strlen(lines[j])) / 2, ' ') << lines[j] << "\n";
        }

        cout << endl << endl << "────────────────────────────────────────────────═════════ ❖ ═════════─────────────────────────────────────────────────" << endl;
        cout << "\033[3A";

        cout << string((118 - (int)strlen(lines[i])) / 2, ' ');
        specialPrint(lines[i], color, speed);

        Sleep(instantDialouge ? 0 : 100);
    }

    cout << "\033[3E";
    pressEnter();
}

int reply(vector<string> replyChoices) {

    bool chosen = false;

    cout << "───" << player.name << "──────────────────────────────────────────────────────────" << endl << endl;

    for (int i = 0; i < replyChoices.size(); i++){
        cout << i+1 << " | " << "\""<< replyChoices.at(i) << "\"" << endl;
    }
    
    int choice;

    while(!chosen) {
        cout << "> ";
        cin >> choice;
        if(choice > 0 && choice <=replyChoices.size()){
            chosen = true;
        }else{
            cout << "Invalid Choice, Try Again." << endl;
        }
    }

    return choice;

}

void viewItem(Item item){
    system("cls");
    cout << "╔═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╗" << endl;
    cout << "  " << item.getColor() << item.getName() << NORMAL << endl;
    cout << "╚═════════════════════════<" << BLUE "♦" NORMAL << ">═════════════════════════╝" << endl << endl;
    cout << " Category    : " << left << setfill(' ') << setw(8) << item.getCategory() << "   Value       : " << item.getValue() << endl;
    cout << " Status      : " << statusText(item.status) << NORMAL << "       Damage Type : " << item.getDamageType() << endl << endl;
    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl;
    string desc = item.getDesc();
    cout << " ";
    // does a new line if theres a period
    for (size_t i = 0; i < desc.length(); i++) {
        if (desc[i] == ' ' && i > 0 && (desc[i - 1] == '.' || desc[i-1] == '-')) {   
            cout << endl << " ";
        } else {
            cout << desc[i];
        }
    }
    cout << endl;
    cout << "══════════════════════════<" << BLUE "♦" NORMAL << ">══════════════════════════" << endl << endl;

    pressEnter();
    inventory(player, 0);
}

void viewEnemy(Enemy enemy){
    system("cls");
    cout << "╔═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╗" << endl;
    cout << "  " << RED << enemy.name << NORMAL << endl;
    cout << "╚═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╝" << endl << endl;

    cout << " Health    : " << enemy.maxHealth << "  " << "     Attack     : " << enemy.attack << endl;
    cout << " Exp       : " << enemy.xpReward  << "  " << "     Silvers    : " << enemy.silverReward << endl << endl;

    cout << "══─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─══" << endl << endl;

    cout << " Inflicts  [ " << statusText(enemy.inflictStatus) << " ]";
    cout << "   Weakness   [ " << enemy.getWeakness() << " ]" << endl << endl;

    cout << " Drop      [ ";
    for (int i = 0; i < enemy.drops.size(); i++) cout << enemy.drops.at(i).getName() << ((i + 1 == enemy.drops.size()) ? " " : ", ");
    cout << "]" << endl;
    cout << " Held Item [ " << enemy.heldItem.getName() << " ]" << endl << endl;


    cout << "╚═─═─═─═─═─═─═─═─═─═─═─═─═▪■▪═─═─═─═─═─═─═─═─═─═─═─═─═╝" << endl << endl;

    pressEnter();
    beastiary();
}

string travelNum(int location){
    switch (location){
    case 1: if(unlockedAreas.size() >= location) return "[1]"; else return "   "; break;
    case 2: if(unlockedAreas.size() >= location) return "[2]"; else return "   "; break;
    case 3: if(unlockedAreas.size() >= location) return "[3]"; else return "   "; break;
    case 4: if(unlockedAreas.size() >= location) return "[4]"; else return "   "; break;
    case 5: if(unlockedAreas.size() >= location) return "[5]"; else return "   "; break;
    case 6: if(unlockedAreas.size() >= location) return "[6]"; else return "   "; break;
    case 7: if(unlockedAreas.size() >= location) return "[7]"; else return "   "; break;
    case 8: if(unlockedAreas.size() >= location) return "[8]"; else return "   "; break;
    case 9: if(unlockedAreas.size() >= location) return "[9]"; else return "   "; break;
    default: return "NULL"; break;}
}

int saveLocation = 1;

void travel() {
    system("cls");
    cout << "╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                                ║" << endl;
    cout << "║                                                       ......                   ║" << endl;
    cout << "║                                  ..         _.. .-.._/      \\                  ║" << endl;
    cout << "║                                 /  \\ . .-..                  \\                 ║" << endl;
    cout << "║                               ..                              ;                ║" << endl;
    cout << "║                    _....,    ./                              .                 ║" << endl;
    cout << "║               _....;     \\...)               " << travelNum(9) << "             `                 ║" << endl;
    cout << "║              /                           Castle Norn        ',                 ║" << endl;
    cout << "║              /                          ▲=--=-=-=-=--=▲      .,                ║" << endl;
    cout << "║             :               ◦  ◦             " << travelNum(8) << "              .,               ║" << endl;
    cout << "║           /          " << travelNum(7) << "  ◦      ◦   ◦   Castle Walls        .`                ║" << endl;
    cout << "║           ;       Def.Reigon            ◦   ◦            ./                    ║" << endl;
    cout << "║           ;            ◦    ◦  ◦   ◦                     ./                    ║" << endl;
    cout << "║            \\                          ◦  " << travelNum(6) << "             ..                    ║" << endl;
    cout << "║             .              " << travelNum(5) << "  ◦     Ver.Expanse         .\\                   ║" << endl;
    cout << "║             .     ◦  ◦  Blue Lake  ◦      ◦                 .                  ║" << endl;
    cout << "║            ;    ◦        .--..         ◦                    .                  ║" << endl;
    cout << "║          ..   " << travelNum(4) << "      /      .\\                           ..     ,....,       ║" << endl;
    cout << "║         .`  Filmont    .       .           " << travelNum(2) << "            ..    /       \\      ║" << endl;
    cout << "║        (           ◦   (     .)        ◦  Millmore      .)     :        |      ║" << endl;
    cout << "║         \\..--..,...,  ◦ `...--        ◦         ◦        .;     \\....._/       ║" << endl;
    cout << "║                     \\.  ◦           ◦              ◦       .\\                  ║" << endl;
    cout << "║         .-----..     .    ◦    " << travelNum(3) << "        .           " << travelNum(1) << "     .                ║" << endl;
    cout << "║       /         .\\   `,     So.Expanse   .--.    Outskirts  .                  ║" << endl;
    cout << "║       .          .\\    (.._._.           /     \\ .         ..                  ║" << endl;
    cout << "║       (...      ,./            \\..       .         . .-.-..)                   ║" << endl;
    cout << "║           \\....)                 .. .   .,                                     ║" << endl;
    cout << "║                                       \\..                                      ║" << endl;
    cout << "║                                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "     [ # | Area to Travel To ] [ 11 | Return to Story ] [ 0 | Return to Menu ]     " << endl << endl;

    int newLocation = 0;

    cout << "> ";
    cin >> newLocation;


    if(newLocation == 0) return;
    if(newLocation == 11){
        isTravelling = false;
        location = saveLocation;
        cout << "You return to " << areaNames.at(location - 1);
        Sleep(2000);
        return;
    }

    if (newLocation <= unlockedAreas.size()) {
        saveLocation = location;
        location = newLocation;
        isTravelling = true;
        cout << "You travel to " << areaNames.at(newLocation - 1);
        Sleep(2000);
    }
    else {
        cout << endl << "You haven't unlocked that area yet.";
        Sleep(1000);
        travel();
    }

}

