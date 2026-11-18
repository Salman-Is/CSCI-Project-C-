CSCI C++ Project - Earlcrown

   ___________                __       _________                                       
   \_   _____/_____  _______ |  |      \_   ___ \_______   ____ __  _  __ ____          
    |    __)_ \__  \ \_  __ \|  |      /    \  \/\_  __ \ /  _ \\ \/ \/ //    \        
    |        \ / __ \_|  | \/|  |__    \     \____|  | \/(  <_> )\     /|   |  \       
   /_______  /(____  /|__|   |____/     \______  /|__|    \____/  \/\_/ |___|  /        
           \/      \/                          \/                            \/   

Overview ===============================================================================================================================

This program is a video game where the player makes decisions basically every second.

The program is devided up into several files, each with their own set of functions, classes, or other definitions
I started the project much much earlier than was assigned, which is why it's likely much bigger than expected.
I am just very passionate about programming haha. 

Below this first section is the planning I did before and during my ime with the project. 
It's not really supposed to be in a README file, but I didn't want to clutter my files up with ANOTHER text file.

╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║                                                                                                                                          ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


Basic Idea ===============================================================================================================================

Fantasy game where you explore a post apocalyptic fantasy world, fight monsters, and try to save the world. Pretty simple.

g++ .\main.cpp .\ui.cpp .\combat.cpp .\events.cpp .\story.cpp -std=c++20
g++ .\main.cpp .\ui.cpp .\combat.cpp .\events.cpp .\story.cpp .\events.h .\defs.h .\ui.h .\entities.h .\combat.h -std=c++20

Story ====================================================================================================================================

  The Sondering Bell tolls over Linaura. Ten Earls have risen and fallen, 
mortal deities who proved their strength in the Crownseeker Wars. 
Now the eleventh Earl, Elenora the Elder, is dead, and the bell calls all who would claim the Earlcrown. 
Only the strong may wear it, and the war to prove that strength has begun again. 
With no Earl to hold the borders, monsters from the underworld and invaders from the Lands Beyond pour into the land. 
The people you fought beside are gone, lost in the first days of this war. 
Take the Earlcrown, and decide whether the cycle ends with you.

PARTS =============================================================================

Part 0 - Outlands; The starting area and the uninhabited land on the outskirts of Linaura. After news of the war reached you, 
you return to the kingdom after years of being away, and have come for the Earlcrown.

Part I - Millmore; The outermost settlement in the country. It is an old milling town who supply the kingdom with flour.

Part II - Southern Expanse; A mostly uninhabited reigon of the country that is a large artificial desert.
It was once a forest, until a great battle in the previous war took place.

BOSS: Desert Dweller Torne, a Crownseeker.

Part III - Filmont; A trading town that serves as one of the only areas the knights protect from battle. One of the richest
towns in the kingdom. Crownseekers are not allowed to fight here.

OPTIONAL BOSS: Knights of Linaura.

Part IV - Blue Lake; The largest lake in the country. Once serving as a beautiful destination, it has been taken over 
and transformed into an outpost for invading warriors from outside the country.

BOSS: Drewkal the Scoundrel, a vicious warlord from outside Linaura

Part V - Verdent Expanse; A large forest known to be the deadliest for weaker Crownseekers. It is rife with
stealthy Crownseekers and dragons, and is ruled by a vicious dragon.

BOSS: Remel the Marred, an elite Crownseeker
BOSS: Marik the Ancient, king of all dragons

Part VI - Defiled Reigon; At the center of the lies a gaping portal from which hundereds of underworld 
creatures emerge.

BOSS: Asag the Reviled, a vile demon who tried taking the crown and use it to steal every human's soul

Part VII - Capital Walls; The most dangerous area during a Crownseeker War. Hundereds of battles take place here every
day. You must fight your way past the battles and have the gate open for you.

Part VIII - Castle Norn; The Capitol of the kingdom, and the location of the Earlcrown.

BOSS: Elenora the Empty, the ghost of the 10th Earl

Part Final - Throne Room; The final area where the end of the game takes place.


Gameplay =================================================================================================================================

You have 4 different moves: Attack, Spell, Item, Skill

- Attack deals damage corresponding to your weapon. Some weapons have skills.
  Only uses up 1 stamina. Attack damage is halved when staimina depletes to 0. 

- Spells deal damage based on the type of spell and wand. 
  They use up mana AND stamina.

- Items can buff you, heal you, or give status effects. They dont use stamina.

- Skills are rare abilties that deplete your stamina quickly.
  They basically just do random stuff idk. Your skill is tied to your weapon.

Leveling up lets you increase 1 stat. 

There are 6 classes at the start of the game. 
You can use a playstyle outside of the class type but it will make the game harder. 
Like you can use spells as a Vanguard, even though you should be using physical attacks.

There are a few status effects. 3 for physical, 3 for potions, and 4 for spells. 
- Physical status effects are bleed, poison, and fear. 

    - Bleed: -5 flat damage over time, -25% attack. (RED)
    - Fear: -50% attack, can always flee from enemy. (DARKBLUE)
    - Poison: -10% hp every turn. (LIME)

- Magic status effects are electrified, frozen, cursed, and burned. 

    - Electrified: 40% chance to skip turn, 3 flat damage every turn. (YELLOW)
    - Frozen: 75% chance to skip turn. (LIGHTBLUE)
    - Cursed: All damage delt is delt to the cursed dealer as well. (BLACK)
    - Burned: -5% hp every turn, instant death after 4 turns while burned. (ORANGE)

- Potions have regeneration, overload, and vitality. 

   - Regeneration: +10% hp every turn. (PINK)
   - Overload: +25% damage, -10% health when taken. (PURPLE)
   - Vitality: +3 Stamina every turn. (GREEN)



Programming ==============================================================================================================================

main.cpp -> Controls the setup at the start of the game and contains the main() function

battle.cpp -> The core of all the battle elements, controls calculations and battle starts and outcomes

              encounter() -> Sets up the variables of the battle and handles the results.
              battle() -> Runs the actual battle logic and gameplay.
              onTurn() -> Runs every turn, this function will handle the effects of status's.
              dealPlayerDamage() -> calculations for the damage player recives
              dealEnemyDamage() -> calculations for the damage enemy recives

entities.cpp -> Controls and tracks everything about the player. Their stats, inventory, and abilities, and defines enemies

              addItem() -> Adds item to player inventory
              removeItem() -> Removes item from player inventory

              struct Enemy{} -> Defines enemy stats and other elements

              class Item{} -> Defines Item values and other elements

              class CharClass{} -> Values for all the starting character classes
              class Abilities{} -> Base class to define characteristics of weapon abilities
              class Spells{} -> Base class to define characteristics of weapon abilities
              class xSpell{} and class xAbility{} -> derived classes for each spell and ability

story.cpp -> 90% print statements and dialouge function calls. Each section of the story will have it's own function

              storyOne() -> part 1 of story
              storyTwo() -> part 2 of story etc.

dialouge.txt -> Text file that contains all the dialouge from characters and such

              [NAMETAG_1] <---- Nametag that identifies what paragraph of dialouge is being references
              Lorem ipsum dolor sit amet consectetur adipiscing elit et
              Ex sit possimus deserunt iusto aliqua
              

ui.cpp -> This script is used for display, and creates the UI elements so the game looks nice. 

              battleUI() -> UI for combat
              bar() -> Creates a progress bar that fills or decreases based on flat number
              percentBar() -> Creates a progress bar that fills or decreases based on percentage
              inventoryUI() -> UI for the inventory

events.cpp -> Controls any cool random events we could add

defs.h -> Contains variables and definitions of classes and structs that all scripts will use 

filename.h -> Every file will have a .h file so the other scripts can use their functions

Concept Art? =============================================================================================================================


BOSSES ===============================================================

╔════════════════════════════☾〇☽═════════════════════════════╗

                   [ Everghast the Forgotten ]                  
  
  [ ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ ]
  [ 200 / 200 ]                               Status: [ DIVN ]

╚════════════════════════════☾〇☽═════════════════════════════╝
╚═════════════════════════════▪■▪═════════════════════════════╝

DIALOUGE ===============================================================

[ Character Name ]
╔══════════════════════════════════════════════════════════════╗
║   Here are some random lines of dialouge                     ║
║   lorem ipsum dolor sit amet                                 ║
╚══════════════════════════════════════════════════════════════╝

[ 1 ] > choice one
[ 2 ] > another choice
[ 3 ] > a choice you can pick

Characters =============================================================================================================================

Desert Dweller Torne (Part II, Crownseeker)
Role: Early boss, first named Crownseeker the player meets
Look: Lean, sun-leathered, wrapped in layers of sand-colored cloth. Carries a long curved blade and a waterskin he never lets out of reach.
Personality: Patient, dry-humored, respectful of anyone who survives the walk to his territory.
Motive: He wants the crown to regrow the forest the previous war burned away. His ancestors were the cheiftans of that forested land.
Weakness: Blunt.
Drop: Dwellers Seal. 
Sample line: 

Drewkal the Scoundrel (Part IV, Invader Warlord)
Role: Mid-game boss, holds Blue Lake
Look: Broad, scarred, dressed in stolen finery layered over salt-stained leather. Wears a different noble’s ring on each finger.
Personality: Loud, charming, cruel when it’s convenient. Treats war as a business and the lake as his shop.
Motive: His homeland Kigura heard the ringing of Linaura's bell, and set forth to try to take the reigon in it's time of war.
Weakness: Pierce.
Drop: Kiguran Mace
Sample line: 

Remel the Marred (Part V, Elite Crownseeker)
Role: Forest boss, ambush specialist
Look: Hooded, face covered in burn-scarred patches, wears bark-dyed leathers and a mask carved from a dragon’s tooth.
Personality: Quiet, suspicious, speaks in short sentences. Hates being seen.
Motive: He lost his whole squad to a trap he set himself, and he has distrusted every plan since. The crown is the only thing he thinks can undo what happened.
Weakness: Lightning.
Drop: Marred Seal.
Sample line: 

Marik the Ancient (Part V, Optional Apex)
Role: Optional boss, lore keeper
Look: Massive, dull sandy scales, one cloudy eye, old harpoons and broken spears still lodged in his hide.
Personality: Unhurried, curious about short-lived things, quietly amused by Crownseekers. He addresses the player as “little flame.”
Motive: Wants to stop all Crownseekers so the cycle of war will be forgotten.
Weakness: Pierce
Drop: Dragonbone Club
Sample line: 

Asag the Reviled (Part VI, Demon Crownseeker)
Role: Boss, ties the portal to the plot
Look: Tall, charred red skin, ram-like horns bound in iron chains, eyes that glow yellow.
Personality: Articulate, bitter, smug
Motive: 
Weakness: Holy
Drop: Demonic Axe
Sample line: 

Elenora the Empty (Part VIII, Ghost of the 10th Earl)
Role: Final boss before the Throne Room, truth-teller
Look: Pale, translucent, wearing a gown that looks half-finished, as if parts of her faded before the rest. On her head sits the crown.
Personality: Gentle, tired, sometimes loses the thread mid-sentence. Remembers everything about others and little about herself.
Motive: She wants to rest, and her ghost is still holding the crown’s weight, which is why the bell keeps ringing. She tests whether the player understands what the crown costs.
Weakness: Dark
Drop: Earlcrown
Sample line: 

The Knights of Linaura (Part III, Optional Boss)
Role: Faction, peacekeepers of Filmont
Look: Matching silver plate with weathered blue tabards, helms that hide expressions.
Personality: Formal, courteous, tired. They enforce the old accord by habit now.
Motive: Keep Filmont standing. Their order has watched ten cycles and has stopped believing the war can end.
Leader: Captain Isolde Varn. Fights with sword and shield, speaks politely mid-duel, apologizes before landing hits.
Combat: Strong Guard and counters. Fights as a group of three. The player breaks the line or wins one-on-one.
Phases: 100-60% formation fighting. Below 60%, Isolde fights alone.
Peaceful route (respected_knights): The Knights stand aside at the Walls or send a letter that speeds the gate.
Defeated: Filmont turns hostile and shops raise prices.
Sample line: “Draw steel in this market and I will end you gently. Please don’t make me.”


Hesk, the Millmore Miller (Part I, quest giver): Old, flour-dusted, remembers the Tenth War. 
He gives the player the first lead on their company and sets the tone. Short dialogue tree, three entry points based on class.

Wren, the Bellkeeper’s Apprentice (Part I and recurring): A young girl who reports how the bell sounds each time the player returns. 
No combat. Her updates are your bell-tone exposition and an emotional anchor.

Sera Tolliver, Surviving Company Member (Part IV or V): Someone from the player’s old company, held at Blue Lake or hired by a Crownseeker. 
Rescuing her ties the motive to a concrete choice and she reacts to your mercy flags.

The Merchant of Filmont, Dulcet Marrow: A cheerful vendor who sells gear and rumors. She quietly sells to every faction, including the invaders. 
Good for a rumors system and for a recurring shop with changing stock.

The False Earl, Brannock the Gilded (Part V, optional boss): A Crownseeker wearing a forged crown. His fight is theatrical, with a gaudy arena and lines about destiny. 
Dropping the fake crown reveals what makes the real one different.

The Pilgrim Elder, Maelis (Part VI): Leads a group of villagers toward the portal to find lost family. 
The player can guide, block, or fight them. Her outcome feeds mercy and cruelty flags and hints at what lies beyond.

The Gatewarden, Oswin Reeve (Part VII): A weary captain commanding one section of the Capital Walls. 
He opens the gate for players who bring enough sigils or favors, giving the Walls a human face and a non-combat solution.



cout << "              [ MAP OF Aureveil ]" << endl;
cout << "╔═══════════════════════════════════════════════════════════╗" << endl;
cout << "║                    __.--._        .---,                   ║" << endl;
cout << "║                 _.'       \\:.,   ;     ;                 ║" << endl;
cout << "║               ,-'             \\_/       \\               ║" << endl;
cout << "║      _.''' `--'        ▲▲     ▲       ▲▲  ;.              ║" << endl;
cout << "║     :                     ▲▲    5           ;             ║" << endl;
cout << "║     ,'    4            ▲   Mountains ▲▲▲    ;             ║" << endl;
cout << "║    :    Caves         ▲▲      ▲▲           ,              ║" << endl;
cout << "║    :                                      ;               ║" << endl;
cout << "║    :       ....                           :               ║" << endl;
cout << "║    ;      /  3  \\                          :             ║" << endl;
cout << "║    (     : Lake :        2                  ;             ║" << endl;
cout << "║    `-.    \\..../      Plains      1       ,'             ║" << endl;
cout << "║      ;                         Forest   :                 ║" << endl;
cout << "║    .'                             .-._,'                  ║" << endl;
cout << "║    `.                       ---._;                        ║" << endl;
cout << "║      `-.__          __.--._)                              ║" << endl;
cout << "║           `.--.____;                                      ║" << endl;
cout << "║                                                           ║" << endl;
cout << "║                                                           ║" << endl;
cout << "║                                                           ║" << endl;
cout << "╚═══════════════════════════════════════════════════════════╝" << endl;

cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
cout << "║                                                                              ║" << endl;
cout << "║                                                      ......                  ║" << endl;
cout << "║                                 ..       .. .. .-.._/      \                 ║" << endl;
cout << "║                                /  \ . .-..                  \                ║" << endl;
cout << "║                              ..                              ;               ║" << endl;
cout << "║                   _....,    ./                              .                ║" << endl;
cout << "║              _....;     \...)               [9]             `                ║" << endl;
cout << "║             /                           Castle Norn        ',                ║" << endl;
cout << "║             /                          ▲=--=-=-=-=--=▲      .,               ║" << endl;
cout << "║            :               ◦  ◦             [8]              .,              ║" << endl;
cout << "║          /          [7]  ◦      ◦   ◦   Castle Walls        .`               ║" << endl;
cout << "║          ;       Def.Reigon            ◦   ◦            ./                   ║" << endl;
cout << "║          ;            ◦    ◦  ◦   ◦                     ./                   ║" << endl;
cout << "║           \                          ◦  [6]             ..                   ║" << endl;
cout << "║            .              [5]  ◦     Ver.Expanse         .\                  ║" << endl;
cout << "║            .     ◦  ◦  Blue Lake  ◦      ◦                 .                 ║" << endl;
cout << "║           ;    ◦        .--..         ◦                    .                 ║" << endl;
cout << "║         ..   [4]      /      .\                           ..     ,....,      ║" << endl;
cout << "║        .`  Filmont    .       .           [2]            ..    /       \     ║" << endl;
cout << "║       (           ◦   (     .)        ◦  Millmore      .)     :        |     ║" << endl;
cout << "║        \..--..,...,  ◦ `...--        ◦         ◦        .;     \....._/      ║" << endl;
cout << "║                    \.  ◦           ◦              ◦       .\                 ║" << endl;
cout << "║        .-----..     .    ◦    [3]        .           [1]     .               ║" << endl;
cout << "║      /         .\   `,     So.Expanse   .--.    Outskirts  .                 ║" << endl;
cout << "║      .          .\    (.._._.           /     \ .         ..                 ║" << endl;
cout << "║      (...      ,./            \..       .         . .-.-..)                  ║" << endl;
cout << "║          \....)                 .. .   .,                                    ║" << endl;
cout << "║                                      \..                                     ║" << endl;
cout << "║                                                                              ║" << endl;
cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;