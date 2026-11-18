#include "defs.h"
#include "entities.h"
#include "ui.h"
#include "combat.h"

void useStrike(Enemy& enemy);
void useSpell(Enemy& enemy);
void useItem(Enemy& enemy);
void useSkill(Player& player, Enemy& enemy, Ability& ability);
bool flee(Enemy& enemy);

void applyStatus(StatusType* status, StatusType newStatus);
void processStatus(StatusType status, auto &target);
bool canAct(StatusType status, auto &target, Enemy enemy);
bool knownEnemy(Enemy enemyToFind);

void randomEncounter() {
    switch(location){
        case 1: encounter(outskirts,       false, false, 0); break;
        case 2: encounter(millmore,        false, false, 0); break;
        case 3: encounter(southernExpanse, false, false, 0); break;
        case 4: encounter(filmont,         false, false, 0); break;
        case 5: encounter(blueLake,        false, false, 0); break;
        case 6: encounter(verdentExpanse,  false, false, 0); break;
        case 7: encounter(defiledReigon,   false, false, 0); break;
        case 8: encounter(capitalWalls,    false, false, 0); break;
        case 9: encounter(castleNorn,      false, false, 0); break;
        case 10: encounter(throneRoom,      false, false, 0); break;
        default: cout << "No monsters here.\n";
    }
}

// Sets up the variables of the battle and handles the results.
// Parameters: area -> reference to a vector of enemies, isSpecific -> if enemy is random or specific,
//             isTutorial -> if encounter will have a tutorial or not, index -> index of enemy if its specific
int encounter(const vector<Enemy>& area, bool isSpecific, bool isTutorial, int index) {
    system("cls");
    resetPlayer(player);
    int count = area.size();
    Enemy enemy;
    if (isTutorial) {
        enemy = area[index];  // Select the tutorial enemy
        cout << "You encounter a(n) " << enemy.name << endl;
    }
    else if (isSpecific) {
        enemy = area[index];
        cout << "An elite enemy stands before you..." << endl;
    }
    else {
        enemy = area[rand() % count];
        cout << "You encounter a(n) " << enemy.name << endl;
    }
    pressEnter();

    int result;

    if (!isTutorial){
        result = battle(enemy);
        resetPlayer(player);
    }
    else {
        result = tutorialBattle(enemy);
        resetPlayer(player);
    }

    system("cls");
    bool didWin = false;

    cout << "[ BATTLE RESULTS ]" << endl;
    cout << "════════════════════════════════════════════════════════════════════" << endl << endl;
    switch (result){
    case 0:
        cout << "You ran away from the fight." << endl; 
        break;
    case 1:
        cout << "You fell in battle..." << endl; 
        player.changeCoins(enemy.silverReward, false);
        break;
    case 2:
        cout << "You defeated the [ " << enemy.name << " ]!"<< endl; 
        cout << "- Obtained -" << endl << endl;
        player.changeCoins(enemy.silverReward, true);
        cout << "You earned " << enemy.xpReward << BLUE << " Experience!" << NORMAL << endl;

        for (int i = 0; i < enemy.drops.size(); i++){
            Item drop = enemy.drops.at(i);
            addItem(drop);
            cout << "You obtained " << drop.getColor() << drop.getName() << NORMAL << "!" << endl;
        }
        
        didWin = true;
        
        if(!knownEnemy(enemy)){
            cout << endl;
            cout << "You learned about " << enemy.name << "..." << endl;
            cout << "You write about it in your enemy log..." << endl;
            player.beastiary.push_back(enemy);
        }

        break;
    default:
        break;
    }
    player.gainXP(enemy.xpReward);
    
    cout << endl << endl;

    pressEnter();

    return result;
}

int gauntlet(const vector<Enemy>& enemies, string groupName, string groupTitle){
    cout << "Defend your seal." << endl;
    cout << "Defeat every " << groupName << " in the " << groupTitle << "." << endl;

    Sleep(3000);
    int result = 0;
    int exp = 0;
    bool didWin = false;

    for(int i = 0; i < enemies.size(); i++){
        Enemy enemy = enemies[i];
        
        cout << "A " << enemy.name <<  "appears before you!" << endl;

        result = battle(enemy);

        cout << "[ BATTLE RESULTS ]\n";
        cout << "════════════════════════════════════════════════════════════════════" << endl << endl;

        cout << "Enemy " << i+1 << "/" << enemies.size() << endl << endl;

        switch (result){
        case 0:
            cout << "You ran away from the fight." << endl; 
            break;
        case 1:
            cout << "You were overrun..." << endl; 
            player.changeCoins(enemy.silverReward, false);
            break;
        case 2:
            cout << "You defeated the [ " << enemy.name << " ]!"<< endl; 
            cout << "- Obtained -" << endl << endl;
            player.changeCoins(enemy.silverReward, true);
            cout << "You earned " << enemy.xpReward << BLUE << " Experience!" << NORMAL << endl;
            exp += enemy.xpReward;
            didWin = true;
            
            if(!knownEnemy(enemy)){
                cout << endl;
                cout << "You learned about " << enemy.name << "..." << endl;
                cout << "You write about it in your enemy log..." << endl;
                player.beastiary.push_back(enemy);
            }

            break;
        default:
            break;
        }
        cout << "Prepare for the next enemy..." << endl << endl;
        pressEnter();
        system("cls");
    }
    
    player.gainXP(exp);
    pressEnter();
    cout << "You cleared the entire gauntlet!" << endl << endl;
    return result;
}

// Runs the actual battle set up from encounter().
// Parameters: the enemy chosen from encounter
// Returns: result (0 if ran away, 1 if lost, 2 if won)
int battle(Enemy enemy){
    bool playerTurn = true; 
    bool hasRun = false;


    // battle loop =================================================

    while(player.isAlive() && enemy.isAlive() && hasRun == false) {
        if (playerTurn == true && canAct(player.currentStatus, player, enemy)) { // PLAYER TURN
            system("cls");
            processStatus(player.currentStatus, player);

            if (player.isAlive() == false){break;}
            
            cout << BOLD << "                         < Your Turn >" << UNBOLD << endl;
            battleUI(enemy, true);
            cout << "What will you do? > ";
            int choice;
            cin >> choice;
            switch (choice){
            case 1:  useStrike(enemy); break;
            case 2:  useSpell(enemy);  break;
            case 3:  useSkill(player, enemy, player.skill); break;
            case 4:  useItem(enemy);   break;
            case 5:  /* code */   break;
            case 6:  
            
            if(flee(enemy)) {
                hasRun = true;
            } else {
                cout << "The enemy caught up to you!" << endl; Sleep(1000);
            }
                break;
            default:
                break;
            }
            playerTurn = false;
        }
        else if (canAct(enemy.currentStatus, enemy, enemy) && hasRun == false){ // ENEMY TURN
            system("cls");
            processStatus(enemy.currentStatus, enemy);

            if (enemy.isAlive() == false){break;}

            cout << BOLD << "                        < Enemy Turn >" << UNBOLD << endl;
            battleUI(enemy, false);
            Sleep(2000);
            int damage = enemyTurn(player, enemy, enemy.currentStamina, enemy.skillLevel);
            // Enemy used an attack
            if(damage > -1){
                player.takeDamage(damage);
                cout << "The enemy dealt " << damage << " Damage!" << endl;
                if (damage > 0 && enemy.currentStatus == CURSED) {
                    cout << BOLD << BLACK << enemy.name << "'s Curse has activated, this damage returns to them." << NORMAL << UNBOLD << endl;
                    enemy.takeDamage(damage * 2);
                }
            } // Enemy used an item
            else {
                enemyUseItem(enemy);
            }

            pressEnter();
            playerTurn = true;
        }

        // End of Turn stuff

        // Equ Exchange Skill proc
        if (player.equCounter > 0) {
            player.equCounter--;
            if (player.equCounter == 0) {
                player.currentHealth = 0;
                cout << "The pact comes due. Your strength consumes you." << endl;
                pressEnter();
            }
        }
          
    }

    // What happened that ended the loop? =================================================

    if(hasRun == true) {
        return 0;
    }
    else if(player.isAlive() == false) {
        return 1;
    }
    else if(enemy.isAlive() == false) {
        return 2;
    }
    
    return -1;

}

int tutorialBattle(Enemy enemy) {
    bool playerTurn = true;
    bool hasRun = false;
    bool firstTurn = true;

    system("cls");
    cout << BOLD << "Tutorial Battle" << UNBOLD << endl << endl;
    cout << "You're pretty rattled, you need to warm up before venturing forth." << endl;
    cout << "This monster is a great oppurtunity to prime yourself for the battles ahead." << endl << endl;
    pressEnter();

    // Battle loop =================================================

    while (player.isAlive() && enemy.isAlive() && !hasRun) {

        if (playerTurn && canAct(player.currentStatus, player, enemy)) {

            system("cls");
            processStatus(player.currentStatus, player);

            if (!player.isAlive()) {
                break;
            }

            cout << BOLD << "                         < Your Turn >" << UNBOLD << endl;


            if (firstTurn) {
                cout << "This is the main battle screen." << endl;
                cout << "It tells you everything you need to know" << endl;
                cout << "about what is currently happening in the battle." << endl << endl;
                
                cout << "You have a health bar, stamina bar, and mana bar." << endl;
                cout << "Keep track of them. The enemy has a health bar too." << endl;
                cout << "Make sure that becomes 0 before yours does!" << endl << endl;
            }

            battleUI(enemy, true);

            if (firstTurn) {
                cout << endl;
                cout << "Choose an action from the menu." << endl;
                cout << "Strike is a basic attack, it takes no stamina or mana to use." << endl;
                cout << "Spells are magic attacks and apply status's, but come at a cost." << endl;
                cout << "Skills are useful special abilities, but deplete stamina." << endl;
                cout << "Items can help you survive or assist you in combat." << endl << endl;
                cout << "You can also attempt to flee if things get dangerous."<< endl;
                pressEnter();

                firstTurn = false;
                system("cls");
                battleUI(enemy, true);
            }

            cout << "What will you do? > ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                useStrike(enemy);
                break;

            case 2:
                useSpell(enemy);
                break;

            case 3:
                useSkill(player, enemy, player.skill);
                break;

            case 4:
                useItem(enemy);
                break;

            case 5:
                // Reserved for another battle action
                break;

            case 6:

                if (flee(enemy)) {
                    cout << "You escaped successfully!" << endl;
                    hasRun = true;
                }
                else {
                    cout << "The enemy caught up to you!" << endl;
                    Sleep(1000);
                }
                break;

            default:
                cout << "Invalid choice!" << endl;
                pressEnter();
                playerTurn = true;
                continue;
            }

            playerTurn = false;
        }

        else if (canAct(enemy.currentStatus, enemy, enemy)
                 && !hasRun) {

            system("cls");
            processStatus(enemy.currentStatus, enemy);

            if (!enemy.isAlive()) {
                break;
            }

            cout << BOLD << "            < Enemy Turn >" << UNBOLD << endl;
            battleUI(enemy, false);

            cout << enemy.name << " is preparing to attack!" << endl;
            cout << "Get ready, the enemy will swing at you in a pattern." << endl;
            cout << "The patten will appear to you in a string of letters..." << endl;
            cout << "Memorize the letters and then type it in again to parry the attack!" << endl;
            cout << "Are you prepared? When you're ready, hit enter." << endl;
            pressEnter();

            int damage = enemyTurn( player, enemy, enemy.currentStamina, enemy.skillLevel);

            player.takeDamage(damage);

            cout << "The enemy dealt " << damage << " damage!" << endl;

            if (damage > 0 && enemy.currentStatus == CURSED) {
                cout << BOLD << BLACK << enemy.name << "'s Curse returns the damage to them." << NORMAL << UNBOLD << endl;

                enemy.takeDamage(damage * 2);
            }

            pressEnter();
            playerTurn = true;
        }

        // End of Turn =============================================

        if (player.equCounter > 0) {
            player.equCounter--;

            if (player.equCounter == 0) {
                player.currentHealth = 0;
                cout << "The pact comes due. Your strength consumes you." << endl;
                pressEnter();
            }
        }
    }

    // Battle Results ==============================================

    system("cls");

    if (hasRun) {
        cout << "You escaped the tutorial battle." << endl;
        return 0;
    }
    else if (!player.isAlive()) {
        cout << "You were defeated..." << endl;
        cout << "Don't give up. Try using items or different actions."
             << endl;
        pressEnter();
        return 1;
    }
    else if (!enemy.isAlive()) {
        cout << BOLD << "Tutorial Complete!" << UNBOLD << endl << endl;
        cout << "You defeated the enemy!" << endl;
        cout << "You're ready to take on the battles ahead." << endl;
        pressEnter();
        return 2;
    }

    return -1;
}

void resetPlayer(Player &player) {
    // STATS
    player.currentAttack = player.attack;
    player.currentMattack = player.magicAttack;
    player.currentMana = player.maxMana;
    player.currentHealth = player.maxHealth;
    player.currentStamina = player.maxStamina;

    // FLAGS
    player.parryCounterActive = false;
    player.equCounter = 0;
}

// STATUS EFFECT STUFF ===================================================================================================

// Changes the "target status" to the new status, unless it cannot be changed
// Parameters: Target status (tied to enemy or player), Status to change into (taken from enum StatusType)
void applyStatus(StatusType* status, StatusType newStatus){
    if (*status != DIVINE) {
        *status = newStatus;
    }
    else if (newStatus != DIVINE){
        cout << BOLD << GOLD;
        cout << (*status == player.currentStatus ? "Your" : "The enemy's") << " Divinity is unassailable...\n\n";
        cout << UNBOLD << NORMAL;
    } 
}

void processStatus(StatusType status, auto &target){
    
    if (target.currentHealth <= 0){
        return;
    }
    if (target.currentStatus == NONE) {
        return;
    }

    int damage = 0;
    int heal = 0;
    switch (status){
        case POISON:
            damage = (int)(target.maxHealth * 0.15);
            if (damage < 1) damage = 1;

            if(target.currentHealth - damage <= 0) {
                cout << BOLD << LIME;
                cout << "The Poison isn't effective... " << target.name << " survives.\n\n";
                cout << UNBOLD << NORMAL;
            }
            else {
                cout << BOLD << LIME;
                cout << "The Poison eats away at " << target.name << "... (-" << damage << " HP)\n\n";
                target.currentHealth -= damage;
                cout << UNBOLD << NORMAL;
            }
            break;

        case BURN:
            damage = (int)(target.maxHealth * 0.05);
            cout << BOLD << ORANGE;
            cout << "The flames Burn " << target.name << "... (-" << damage << " HP)\n\n";
            cout << UNBOLD << NORMAL;
            target.currentHealth -= damage;
            if(target.currentAttack - damage > 0) target.currentAttack -= damage;
            break;

        case BLEED:
            damage = (int)(target.maxHealth * 0.15);
            if (damage < 1) damage = 1;
            cout << BOLD << RED;
            cout << target.name << " continues to Bleed out... (-" << damage << " HP)\n\n";
            cout << UNBOLD << NORMAL;
            target.currentHealth -= damage;
            break;

        case REGEN:
            heal = (int)(target.maxHealth * 0.15);
            cout << BOLD << PINK;
            cout << target.name << " Regenerates a bit of health... (+" << heal << " HP)\n\n";
            cout << UNBOLD << NORMAL;
            target.currentHealth += heal;
            break;
        
        case ELECTRIC:
            damage = 3;
            cout << BOLD << YELLOW;
            cout << target.name << " is Electricuted... (-" << damage << " HP)\n\n";
            cout << UNBOLD << NORMAL;
            target.currentHealth -= damage;
            break;

        case FEAR:

            break;

        case NONE:
        default:
            break;
    }

    // clamp HP
    if (target.currentHealth < 0) target.currentHealth = 0;
}

bool canAct(StatusType status, auto &target, Enemy enemy) {
    if (status == FROZEN){
        int random = (rand() % 100) + 1;
        if (random <= 75){
            cout << BOLD << ICEBLUE;
            cout << target.name << " is Frozen... ( Turn Skipped )\n\n";
            cout << UNBOLD << NORMAL;
            battleUI(enemy, false);
            pressEnter();
            system("cls");
            return false;
        }
    }else if (status == ELECTRIC){
        int random = (rand() % 100) + 1;
        if (random <= 40){
            cout << BOLD << YELLOW;
            cout << target.name << " is Paralized... ( Turn Skipped )\n\n";
            cout << UNBOLD << NORMAL;
            battleUI(enemy, false);
            pressEnter();
            system("cls");
            return false;
        }
    }
    return true;
}

// AMULETS ===================================================================================================

// Collects all the buffs found in your amulet slots
// Parameters: isSpell -> function acts differently if a spell is the subject, spellIndex -> self explanitory
// Returns: the value of damageIncreases after tracking everything
int amulet(bool isSpell, Spell spell) {
    int damageIncreases = 0;

    for (int i = 0; i < (int)player.amulets.size(); i++) {
        Item amulet = player.amulets.at(i);
        if (amulet.getName() == noneItem.getName()) continue;       // empty amulet slot

        if (isSpell) {
            if (amulet.damage != NADA && amulet.damage == spell.getDamage()) damageIncreases += amulet.getValue();
            if (amulet.spellType != NOPE && amulet.spellType == spell.getSpellType()) damageIncreases += amulet.getValue();
        }
        else if (amulet.damage != NADA && amulet.damage == player.weapon.damage) {
            damageIncreases += amulet.getValue();
        }
    }
    return damageIncreases;
}

// PLAYER INPUTS ===================================================================================================
// (Parameter for all of these is the instance of the enemy the player is fighting currently)

void useStrike(Enemy& enemy){

    if(player.currentStatus == CONFUSE){
        int chance = rand() % 100;
        if(chance >= 50) {
            cout << "You are Confused, and missed the attack!" << "\n\n";
            pressEnter();
            system("cls");
            return;
        }
    }

    cout << "You strike the enemy with your " << BOLD << player.weapon.getColor() << player.weapon.getName() << UNBOLD << NORMAL << "!" << endl;

    int damage = (player.currentAttack + (player.weapon.getValue())) / 2;
    if (player.weapon.damage == enemy.weakness){
        damage += (int)(damage/3);
        cout << "The enemy is weak to your weapon..." << RED << "Critical Hit!" << NORMAL << endl;
    }

    damage+= amulet(false, noneSpell);
    

    if(player.currentStatus == FEAR) {
        cout << BOLD << DARKBLUE;
        cout << "Fear grips your heart.. ( ATK / 2 )" << "\n\n";
        cout << UNBOLD << NORMAL;  
    }

    // chance of inflicting status gets better with higher intelligence
    int chance = min(100, player.intelligence * 3);
    if ((rand() % 100) < chance && player.weapon.status != NONE) applyStatus(&enemy.currentStatus, player.weapon.status);
    
    enemy.takeDamage(damage); cout << BOLD;
    cout << "You dealt " << BLUE << damage << NORMAL << " damage!" << UNBOLD << endl; 

    if(player.currentStatus == CURSED) {
        cout << BOLD << BLACK << "Your Curse has activated, this damage returns to you." << NORMAL << UNBOLD << endl;
        player.takeDamage(damage / 2);
    }

    pressEnter();
    system("cls");
}

void useSpell(Enemy& enemy){
    Spell spell;
    int choice = 0; bool chosen = false;

    while (chosen == false){
        choice = selectSpellUI(player);
        if (choice >= 0 && choice <= 2){
            chosen = true;
        } else {
            system("cls");
            cout << "Invalid Spell";
        }
    }
    
    system("cls");
    battleUI(enemy, true);

    spell = player.spells.at(choice);

    if (player.currentMana < spell.getManaCost()) {
        cout << "Not enough Mana!" << endl;
        pressEnter();
        return;
    }
    if (player.currentStamina < 1) {
        cout << "Not enough stamina!" << endl;
        pressEnter();
        return;
    }

    player.currentMana -= spell.getManaCost();
    player.currentStamina -= 1;

    cout << "You cast " << BOLD << spell.getColor() << spell.getName() << NORMAL << UNBOLD << " with your " 
    << BOLD << player.catalyst.getColor() << player.catalyst.getName() << NORMAL << UNBOLD << "!" << endl;

    int damage = player.currentMattack + (int)((player.catalyst.damage + spell.getValue()) / 2);
    if (spell.getDamage() == enemy.weakness){
        damage += (int)(damage/4);
        cout << "The enemy is weak to your spell... " << RED << "Critical Hit!" << NORMAL << endl;
    }

    damage+= amulet(true, spell);

    // chance of inflicting status gets better with higher intelligence
    int chance = min(100, player.intelligence * 3);
    if ((rand() % 100) < chance && spell.getStatus() != NONE) applyStatus(&enemy.currentStatus, spell.getStatus());

    enemy.takeDamage(damage); cout << BOLD;
    cout << "You dealt " << BLUE << damage << NORMAL << " damage!" << UNBOLD << endl; 
    pressEnter();
    system("cls");
}

// Allows player to choose an item from inventory,
void useItem(Enemy& enemy) {
    cout << "You chose to use an item!" << endl << endl;
    Item chosenItem = inventory(player, 1);

    // < Alleviate >
    if (chosenItem.getEnumCate() == POTION){
        cout << "You drank a " << chosenItem.getName() << " !" << endl;
    }
    
    if(chosenItem.getEnumCate() == CURE){
        if(player.currentStatus == chosenItem.status) {
            applyStatus(&player.currentStatus, NONE);
            cout << "You cure your " << statusText(chosenItem.status) << " ." << endl;
        }
    }

    // < Heal >
    if (chosenItem.getName() == healingPotion.getName()){
        player.heal(chosenItem.getValue());
    }
    if(chosenItem.getName() == healingElixer.getName()){
        player.heal(chosenItem.getValue());
    }
    if(chosenItem.getName() == lifeElixer.getName()){
        applyStatus(&player.currentStatus, REGEN);
    }
    if(chosenItem.getName() == pheonixTears.getName()){
        player.heal(chosenItem.getValue());
        applyStatus(&player.currentStatus, BURN);
    }

    // < Up Stats >
    if (chosenItem.getName() == focusTrinket.getName()){
        player.focus(chosenItem.getValue());
    }
    if(chosenItem.getName() == focusCharm.getName()){
        player.focus(chosenItem.getValue());
    }
    if(chosenItem.getName() == injection.getName()){
        player.staminaUp(chosenItem.getValue());
    }
    if(chosenItem.getName() == pheonixTears.getName()){
        player.heal(chosenItem.getValue());
        applyStatus(&player.currentStatus, BURN);
    }
    if(chosenItem.getName() == strongPotion.getName()){
        player.currentAttack += chosenItem.getValue();
    }
    if(chosenItem.getName() == boilPotion.getName()){
        player.currentAttack += chosenItem.getValue();
        applyStatus(&player.currentStatus, BLEED);
    }
    
    // < Weaken Enemy >

    if (chosenItem.getName() == oilPot.getName()){
        enemy.weakness = FIRE;
    }
    if(chosenItem.getName() == rosaries.getName()){
        enemy.weakness = HOLY;
    }

    removeItem(chosenItem);

    pressEnter();

}

void useSkill(Player& player, Enemy& enemy, Ability& ability) {
    if (ability.name == noneAbility.name) {
        cout << "You don't have a skill equipped." << endl;
        pressEnter();
        return;
    }

    if (player.currentStamina < ability.staminaCost) {
        cout << "Not enough stamina!" << endl;
        pressEnter();
        return;
    }

    player.currentStamina -= ability.staminaCost;
    cout << ability.name << ": " << ability.activationMessage << endl;

    int state = 0;
    ability.effect(player, enemy, state);
    pressEnter();
    system("cls");
}

bool flee(Enemy& enemy) {
    int baseChance = 50;  // 50% base chance to flee
    int staminaDiff = player.currentStamina - enemy.currentStamina;   // or whatever enemy stat makes sense
    int chance = baseChance + staminaDiff;

    chance = max(5, min(95, chance));   // clamp between 5% and 95% so it's never guaranteed or impossible

    if(enemy.currentStatus == FEAR) chance = 101; // if enemy is in FEAR then it will always let you run away

    int roll = rand() % 100;
    return roll < chance;
}


// ENEMY INPUTS ===================================================================================================

// This function handles the enemies attack, and give the player a pattern to memorize and retype to "dodge" the attack
// Parameters: Player instance, enemy insatace, length of the pattern, amount of letters the pattern will contain
int enemyTurn(Player& player, Enemy& enemy, int patternLength, int difficultyLevel){

    bool use = false; // by default, enemy wont use an item

    if(enemy.usedItem == false && enemy.heldItem.getName() != noneItem.getName()) {
        // if the enemy has a healing item and is low on health it will use the item.
        if(enemy.heldItem.getName() == healingElixer.getName() || enemy.heldItem.getName() == healingPotion.getName() || enemy.heldItem.getName() == pheonixTears.getName()) {
            if((float)enemy.currentHealth/(float)enemy.maxHealth < 0.2) {
                use = true;
            }
        }
        // if the enemy has a cure item that can work it will use the item.
        if(enemy.heldItem.status == enemy.currentStatus && enemy.currentStatus != NONE) {
            use = true;
        }
    }

    if(use == false) {
        string pattern(enemy.attack + 1, '\0'); // Enemy's attack pattern
        string user_pat(enemy.currentHealth + 1, '\0'); // Player input
        string letters = {'X','O','A','B','C','D','E','F','G','H', 'I', 'W', 'Y', 'Z'}; // Possible letters for patterns

        int enemyDamagePerLetter = enemy.currentAttack / enemy.currentHealth;

        if(enemy.currentStatus == FEAR){
            cout << BOLD << DARKBLUE;
            cout << "Fear lingers in " << "the heart of your enemy" << "...\n\n";
            cout << UNBOLD << NORMAL;
            enemyDamagePerLetter /= 2;
        }
        

        for (int i = 0; i < patternLength; i++) {
            pattern[i] = letters[(rand() % (difficultyLevel * 2))];
        }
        pattern[patternLength]='\0';

        cout << endl << "Enemy prepares an attack!" << endl;
        cout << "Counter this pattern: [ " << BOLD << RED;

        for(int i=0;i<patternLength;i++) {
            cout << pattern[i] << " ";
        }  
        cout << NORMAL << "]" << UNBOLD;

        Sleep(200); cout << endl << "3, "; Sleep(900); cout << "2, "; Sleep(900); cout << "1"; Sleep(100);
        system("cls");
        battleUI(enemy, false);
        
        cout << "Enter counter sequence: " << BOLD << BLUE;
        cin >> user_pat;
        int correct = 0;

        for(int i = 0; i < patternLength; i++) {
            if (i < (int)user_pat.size()) {
                user_pat[i] = toupper(user_pat[i]);
            }
        }
        for(int i = 0; i < patternLength; i++) {
            if (i < (int)user_pat.size() && user_pat[i] == pattern[i]) correct++;
        }
        int damageToPlayer = ((patternLength - correct) * enemy.attack) / patternLength; 
        cout << "You counter the attack with your " << player.weapon.getColor() << BOLD << player.weapon.getName() << UNBOLD << NORMAL << "..." << endl;
        Sleep(1500);

        bool missed = false;

        if (correct == patternLength){
            cout << BLUE << "Perfect Counter!" << NORMAL << endl;    
            if(player.parryCounterActive) {
                cout << WHITE << "You follow the counter with an attack!" << NORMAL << endl; 
                Sleep(1000);
                enemy.takeDamage(player.weapon.getValue());   
                cout << "You dealt " << BLUE << player.weapon.damage << NORMAL << " damage!" << UNBOLD << endl; 
                Sleep(2700);
            }   
        }
        else {
            cout << RED << "Imperfect Counter..." << NORMAL << endl;   
            if(enemy.currentStatus == FEAR) {
                cout << BOLD << DARKBLUE;
                cout << "Fear grips" << enemy.name << "'s heart.. ( ATK / 2 )" << "\n\n";
                cout << UNBOLD << NORMAL;  
                damageToPlayer/=2;
            }
            if(enemy.currentStatus == CONFUSE){
                int chance = rand() % 100;
                if(chance >= 50) cout << enemy.name << "is Confused, and missed the attack!" << "\n\n";
                missed = true;
                damageToPlayer = 0;
            }
        }
        if (correct != patternLength && damageToPlayer > 0 && missed == false) {
            // I THINk this works. Calculation should increase chance of status applying the more letters you got wrong
            int amountWrong = (patternLength - correct);
            if (amountWrong > 0 && enemy.inflictStatus != NONE && player.currentStatus == NONE && player.isAlive() == true) {
                float chance = (float)amountWrong / patternLength;
                int random = rand() % 100;

                if (random < (chance * 100) || correct == 0) {
                    if (enemy.currentStatus != NONE){
                        applyStatus(&player.currentStatus, enemy.inflictStatus);
                        if (player.currentStatus != DIVINE) {
                            cout << "\nThe " << enemy.name << " has afflicted you with " << statusText(enemy.inflictStatus) << "!\n";
                        }
                    }
                }
            }
        }
        damageToPlayer = (int)(damageToPlayer * (1.0f - ((float)player.armor.getValue() / (player.armor.getValue() + 35.0f))));
        return damageToPlayer;
    }
    return -1; // use an item
}

void enemyUseItem(Enemy& enemy){
    Item item = enemy.heldItem;
    enemy.usedItem = true;

    // < Alleviate >
    if (item.getEnumCate() == POTION){
        cout << "The enemy drank a " << item.getName() << " !" << endl;
    }
    
    if(item.getEnumCate() == CURE){
        if(enemy.currentStatus == item.status) {
            applyStatus(&enemy.currentStatus, NONE);
            cout << "The enemy cures their " << statusText(item.status) << " ." << endl;
        }
    }

    // < Heal >
    if(item.getName() == healingPotion.getName()) {
        enemy.heal(item.getValue());
    }

    if(item.getName() == healingElixer.getName()){
        enemy.heal(item.getValue());
    }
    if(item.getName() == lifeElixer.getName()){
        applyStatus(&enemy.currentStatus, REGEN);
    }
    if(item.getName() == pheonixTears.getName()){
        enemy.heal(item.getValue());
        applyStatus(&enemy.currentStatus, BURN);
    }
}

bool knownEnemy(Enemy enemyToFind) {
    for (int i = 0; i < player.beastiary.size(); i++){
        if(player.beastiary.at(i).getName() == enemyToFind.getName()) {
            return true;
        }
    }
    return false;
}
