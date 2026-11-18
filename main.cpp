#include "defs.h"
#include "entities.h"
#include "ui.h"
#include "combat.h"

/*
This script has all the setup, main menu, and runs the story functions
*/

int location = 1; // 1-10
bool isTravelling = false;

vector<string> areaNames = {GREEN "Outskirts" NORMAL, GRAY "Millmore" NORMAL, SANDY "Southern Expanse" NORMAL, 
    YELLOW "Filmont" NORMAL, BLUE "Blue Lake" NORMAL, GREEN "Verdent Expanse" NORMAL,
    DEEPRED "Defiled Reigon" NORMAL, SANDY "Capital Walls" NORMAL, GOLD "Castle Norn" NORMAL, RED "Throne Room" NORMAL};

vector<int> unlockedAreas = {1};

// 0 -> Outskirts
// 1 -> Millmore
// 2 -> Southern Expanse
// 3 -> Filmont
// 4 -> Blue Lake
// 5 -> Verdent Expanse
// 6 -> Defiled Reigon
// 7 -> Capital Walls
// 8 -> Castle Norn
// 9 -> Throne Room


// Outskirts


// 1-HP,    2-ATK,    3-MATK,    4-INTEL,    5-MANA,   6-STA (107 stat totals at start)

// Classes (in the game)
CharClass knight    ("Knight",    25, 18, 15, 17, 17, 15, knightSet     ,straightSword, spellBook,   starDust,   counterAttack);
CharClass penitant  ("Penitant",  17, 24, 14, 21, 17, 14, prisonerSet   ,flintLock,     spellBook,   starDust,   prayer);
CharClass traveller ("Traveller", 18, 18, 18, 21, 15, 17, wildernessSet ,basicSpear,    spellBook,   starDust,   resonance);
CharClass vanguard  ("Vanguard",  16, 27, 23, 14, 13, 14, knightSet     ,claymore,      spellBook,   flameSwirl, intimidate);
CharClass alchemist ("Alchemist", 17, 10, 25, 25, 20, 10, scholarSet    ,flameFlask,    alchemyTome, tincture,   equivalentExchange);
CharClass archanist ("Archanist", 13, 11, 30, 18, 25, 10, scholarSet    ,walkingStaff,  magicWand,   levin,      manaBurst);

/* =========== Important Variables =========== */

// Player
CharClass playerClass;
Player player;

int progress = -1;

/* ========== Unimportant Variables ========== */

bool instantDialouge = true;

/*
system("cls");
    cout << "════════════════════════════════════════════════════\n";
    cout << " " << item.getColor() << item.getName() << NORMAL << "\n";
    cout << "════════════════════════════════════════════════════\n";
    cout << " Category : " << item.getCategory() << "\n";
    cout << " Type     : " << item.getType()     << "\n";
    cout << " Value    : " << item.getValue()    << "\n";
    if (item.getStatus() != NONE) {
        cout << " Status   : " << changeColor(item.getStatus())
             << left << setw(17) << statusText(item.getStatus()) << NORMAL << "║\n";
    }
    cout << "════════════════════════════════════════════════════\n";
    cout << item.getDesc() << "\n";
    cout << "════════════════════════════════════════════════════\n\n";
*/

/* ============== General Fn's ============== */

// asks the player to hit any key actually, this was changed
void pressEnter() {
    // int enter;
    // fflush(stdout);
    // while ((enter = getchar()) != '\n' && enter != EOF);
    // getchar();

    // system("pause");
    specialPrint("\n> Press a Key to Continue", NORMAL, 3);
    // cin.ignore(1).get();
    _getwch();
    system("cls");
}

// Prints a string letter by letter
// Parameters: text -> the text we print, color -> color of the text, speed -> how long program sleeps before next letter
void specialPrint(string text, string color, int speed) {
    cout << color;
    for (int i = 0; text[i] != '\0'; i++) {
        // cout << text[i];
        cout << color << text[i] << NORMAL;
        fflush(stdout);

        if (text[i] != ' ') {
            int actualSpeed = speed;
            if (text[i] == ',' || text[i] == '-') {
                actualSpeed = speed * 9;
            } else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
                actualSpeed = speed * 15;
            }

            if (instantDialouge == false) {
                Sleep(actualSpeed);
            } else {
                Sleep(0);
            }
        }
    }
    fflush(stdout);
    cout << NORMAL;
}

// a function for quick yes or no questions, theres gonna be a ot of them
// paremeter: text that prompts the player
// returns: 0 if no, 1 if yes, -1 if invalid
int confirm(string text) {
    char confirmChoice;
    cout << text; cout << " [ y/n ] \n> ";
    cin >> confirmChoice;
    
    if (confirmChoice == 'n' || confirmChoice == 'N') {
        return 0;
    }
    else if (confirmChoice == 'y' || confirmChoice == 'Y')
    {
        return 1;
    }
    else {
        return -1;
    }
}

/* =============== Class Menu =============== */

// Where the player goes to choose their class and their name
// returns the name of the class the player chose;
string chooseClass(){
    system("cls");

    cout << "         - Choose the class you want to play as -         \n" << endl;
    cout << "     [ 1 | Knight    ] [ 2 | Penitant  ] [ 3 | Traveller ]\n" << endl;
    cout << "     [ 4 | Vanguard  ] [ 5 | Alchemist ] [ 6 | Archanist ]\n" << endl;
    cout << "                       [ 0 | Return    ]\n" << endl;

    int choice;
    cout << "> ";
    cin >> choice;

    if (choice < 0 || choice > 6){ // verefiy valid number 
        return "NULL";
    }

    int confirmation = confirm("Are you sure? This choice cannot be changed."); 

    if ( confirmation == 0 || confirmation == -1)
    {
        return "NULL";
    }
    string chosenName = "Seeker";
    // cout << "Enter your name: ";
    // cin >> chosenName;

    
    switch (choice){ 
    case 0: return "NULL"; break;
    case 1: playerClass = knight; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Knight"; break;
    case 2: playerClass = penitant; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Penitant"; break;
    case 3: playerClass = traveller; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Traveller"; break;
    case 4: playerClass = vanguard; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Vanguard"; break;
    case 5: playerClass = alchemist; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Alchemist"; break;
    case 6: playerClass = archanist; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Archanist"; break;
    default: cout << "Invalid choice\n"; 
            return "NULL"; break;
    }
}

// Prints a description of each class. No logic here, just for fun
void descriptions(){
    system("cls");
    specialPrint("Knight       >   A noble warrior with high health and strength", BLUE, 10);
    cout << " | Best Stats: (HP, ATK)" << endl << endl;
    specialPrint("Penitant     >   A regretful prisoner who studied and trained inside", DARKBLUE, 10);
    cout << " | Best Stats: (INTEL, ATK)" << endl << endl;
    specialPrint("Traveller    >   A wanderer from lands beyond, with great experience and endurance.", GREEN, 10);
    cout << " | Best Stats: (INTEL, STA)" << endl << endl;
    specialPrint("Vanguard     >   A powerful soldier with unrivaled strength in weaponry and magic.", GRAY, 10);
    cout << " | Best Stats: (ATK, MATK)" << endl << endl;
    specialPrint("Archanist    >   An old magician with powerful magic and a large pool of mana.", LIGHTBLUE, 10);
    cout << " | Best Stats: (MATK, MANA)" << endl << endl;
    specialPrint("Alchemist    >   A genius magical scholar with natural magic of science.", RED, 10);
    cout << " | Best Stats: (INTEL, MANA)" << endl << endl;

    pressEnter();
    
}

// Prints the full name of each stat in case it's confusing. No logic here, just for fun
void explainAbb() {
    system("cls");
    specialPrint("HP      >   Health Points: The amount of health you have at the start of each battle.\n\n", RED, 10);
    specialPrint("ATK     >   Attack: The default, base amount of physical damage before calculations.\n\n", DEEPRED, 10);
    specialPrint("MATK    >   Magic Attack: The default, base amount of magic damage before calculations.\n\n", DARKBLUE, 10);
    specialPrint("INTEL   >   Intelligence: Determines the chance of learning a spell, the effeciency of status effects, and experience gain.\n\n", BLUE, 10);
    specialPrint("MANA    >   Mana: Determines the amount of times you can cast a spell.\n\n", LIGHTBLUE, 10);
    specialPrint("STA     >   Stamina: Determines the amount of spells and skills you can use in a battle.\n\n", GREEN, 10);

    pressEnter();
}

// The same as choose class except it's random
string randomClass() {
    int num = (rand() % 6) + 1;

    string chosenName = "Seeker";
    // cout << "Enter your name: ";
    // cin >> chosenName;

        switch (num){ 
    case 0: return "NULL"; break;
    case 1: playerClass = knight; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Knight"; break;
    case 2: playerClass = penitant; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Penitant"; break;
    case 3: playerClass = traveller; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Traveller"; break;
    case 4: playerClass = vanguard; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Vanguard"; break;
    case 5: playerClass = alchemist; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Alchemist"; break;
    case 6: playerClass = archanist; chosenName = playerClass.getName();
            player.chosenFromClass(playerClass, chosenName); 
            addItem(playerClass.getWeap()); 
            addItem(playerClass.getCat());
            return "Archanist"; break;
    default: cout << "Invalid choice\n"; 
            return "NULL"; break;
    }
}


// Prints ONE line of ONE class card (no newline), so three cards can sit side by side.
// line 0 = top border, lines 1-6 = the six stats, line 7 = bottom border
// Parametes:
void printCardLine(const CharClass& c, int line) {
    string labels[6] = {"HP", "ATK", "MATK", "INTEL", "MANA", "STA"};
    string colors[6] = {RED, RED, DARKBLUE, DARKBLUE, LIGHTBLUE, GREEN};
    int values[6] = {c.getHealth(), c.getAttack(), c.getMagicAttack(), c.getIntel(), c.getMana(), c.getStamina()};

    if (line == 0) {
        string name = c.getName();
        if (name == "Knight")         cout << "╭── Knight ─────────────────╮";
        else if (name == "Penitant")  cout << "╭── Penitant ───────────────╮";
        else if (name == "Traveller") cout << "╭── Traveller ──────────────╮";
        else if (name == "Vanguard")  cout << "╭── Vanguard ───────────────╮";
        else if (name == "Alchemist") cout << "╭── Alchemist ──────────────╮";
        else if (name == "Archanist") cout << "╭── Archanist ──────────────╮";
    }
    else if (line == 7) {
        cout << "╰───────────────────────────╯";
    }
    else {
        int k = line - 1;
        cout << "│ " << left << setw(5) << labels[k] << " " << right << setw(2) << values[k] << " ";
        percentBar(values[k], 30, 10, colors[k], "■");
        cout << "   │";
    }
}

void drawClassCards() {
    for (int line = 0; line < 8; line++) {
        printCardLine(knight, line);    cout << " ";
        printCardLine(penitant, line);  cout << " ";
        printCardLine(traveller, line); cout << endl;
    }
    for (int line = 0; line < 8; line++) {
        printCardLine(vanguard, line);  cout << " ";
        printCardLine(alchemist, line); cout << " ";
        printCardLine(archanist, line); cout << endl;
    }
}

// The main screen for choosing the class. Handles the interface to choose each of the 4 options.
void classScreen() {
    drawClassCards();
    cout << "  [ 1 | Choose ] [ 2 | Description ] [ 3 | Explain Abbreviations ] [ 4 | Random Class ]  \n" << endl;

    int choice;
    cout << "> ";
    cin >> choice;

    switch (choice){
    case 1:
        if (chooseClass() != "NULL"){
            cout << "You have chosen the " << playerClass.getName() << " class." << endl << endl;
            pressEnter();
        } break;
    case 2: descriptions(); break;
    case 3: explainAbb(); break;
    case 4: if (randomClass() != "NULL"){
            cout << "You were given the " << playerClass.getName() << " class." << endl << endl;
            pressEnter();
        } break;
    default: cout << "Invalid choice\n"; break;
    }
}

/* ================= Debug ================= */

// gives total stats if we add new class
void findTotals(CharClass c) {
    cout << c.getName() << " " << 
    (c.getAttack() + c.getHealth() + c.getMana() + c.getMagicAttack() + c.getIntel() + c.getStamina()) << endl;
}

void statTotals() { 
    findTotals(knight); findTotals(penitant); findTotals(traveller);
    findTotals(vanguard); findTotals(archanist); findTotals(alchemist);
}

// finds ansi escape codes for colors
void codeLookup() {
    for (int i = 0; i < 250; i++)
    {   
        printf("\x1b[38;5;%dm", i);
        printf("[ %d ] Hello World [■■■■■]\n", i);
        printf(NORMAL);
    }
}

void giveEverything(){
    addItem(ironKnuckle);
    addItem(emberBead);
    addItem(snowflakeCharm);
    addItem(lightningBottle);
    addItem(unwiltingRose);
    addItem(goldenEmblem);
    addItem(obsidianEye);
    addItem(etchedVial);
    addItem(glyphStone);
    addItem(apprenticePin);
    addItem(elenoranLumen);
    addItem(elenoranLumen);
    addItem(elenoranLumen);
    addItem(elenoranLumen);
    addItem(oilPot);
    addItem(rosaries);
    addItem(scrollOfTheElements);
    addItem(scrollOfTheAlchemist);

    addItem(knightTome);
    addItem(alchemyTeach);
    addItem(bloodTome);
    addItem(prayerTome);
    addItem(guideToFear);
    addItem(resonantTome);
    addItem(demonicText);
    addItem(arcaneTome);
    addItem(transferLaw);
}

/* ================= Main ================= */

void mainMenu() {
    cout << NORMAL;

    cout << "══════════════════════════════════════════════════════════════════════════════════" << endl << endl;

    cout << BOLD;
    cout << GOLD;

    cout << "                               " << WHITE << "." << GOLD << "       |         " << WHITE << "." << GOLD << "    " << WHITE << "." << GOLD << "" << endl;
    cout << "                         " << WHITE << "." << GOLD << "  " << WHITE << "*" << GOLD << "         -" << WHITE << "*" << GOLD << "-          " << WHITE << "*" << GOLD << "" << endl;
    cout << "                              \\        |         /   " << WHITE << "." << GOLD << "" << endl;
    cout << "             " << WHITE << "." << GOLD << "    " << WHITE << "." << GOLD << "            " << WHITE << "." << GOLD << "      /^\\     " << WHITE << "." << GOLD << "              " << WHITE << "." << GOLD << "    " << WHITE << "." << GOLD << "" << endl;
    cout << "                " << WHITE << "*" << GOLD << "    |\\   /\\    /\\  / / \\ \\  /\\    /\\   /|    " << WHITE << "*" << GOLD << "" << endl;
    cout << "              " << WHITE << "." << GOLD << "   " << WHITE << "." << GOLD << "  |  \\ \\/ /\\ \\ / /     \\ \\ / /\\ \\/ /  | " << WHITE << "." << GOLD << "     " << WHITE << "." << GOLD << "" << endl;
    cout << "                      \\ | _ _\\/_ _ \\_\\_ _ /_/_ _\\/_ _ \\_/" << endl;
    cout << "                        \\  " << WHITE << "*" << GOLD << "  " << WHITE << "*" << GOLD << "  " << WHITE << "*" << GOLD << "   \\ \\/ /  " << WHITE << "*" << GOLD << "  " << WHITE << "*" << GOLD << "  " << WHITE << "*" << GOLD << "  /" << endl;
    cout << "                         ` ~ ~ ~ ~ ~  ~\\/~ ~ ~ ~ ~ ~ '" << endl;

    cout << WHITE;
    cout << "   ___________                __       _________                                       " << endl;
    cout << "   \\_   _____/_____  _______ |  |      \\_   ___ \\_______   ____ __  _  __ ____          " << endl;
    cout << "    |    __)_ \\__  \\ \\_  __ \\|  |      /    \\  \\/\\_  __ \\ /  _ \\\\ \\/ \\/ //    \\        " << endl;
    cout << "    |        \\ / __ \\_|  | \\/|  |__    \\     \\____|  | \\/(  <_> )\\     /|   |  \\       " << endl;
    cout << "   /_______  /(____  /|__|   |____/     \\______  /|__|    \\____/  \\/\\_/ |___|  /        " << endl;
    cout << "           \\/      \\/                          \\/                            \\/         " << endl << endl;
    cout << UNBOLD;

    cout << "══════════════════════════════════════════════════════════════════════════════════" << NORMAL << endl;
    cout << endl;
    
    cout << WHITE << "                           [ Press any key to begin ]" << NORMAL;
    _getwch();

    // PlaySound(TEXT("theme.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

int main() {

    addItem(sealOfSonder);

    system("chcp 65001 > nul"); // For special ASCII characters
    system("cls");
    srand(time(NULL));
    giveEverything();

    while (progress == -1) {
        system("cls");
        mainMenu();
        narrationBox(GOLD, "NAR_INTRO");
        progress++;
    }

    while (progress == 0) {
        system("cls");
        while(player.className == "None") {classScreen();}
        progress++;
    }
    while(1) {
        switch(progress) {
            case 1: quest1_EnterMillmore(); break;
            case 2: quest2_MeetCorvin(); break;
        }
    }

    return 0;
}

