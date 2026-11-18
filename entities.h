#ifndef ENTITIES_H
#define ENTITIES_H

#include "defs.h"

class Player;
class Enemy;
class Spell;

// STRUCTS AND STUFF  ==================================================================================================================
struct Ability{
    string name;
    string description;
    string activationMessage;
    int staminaCost;
    //Ref to Player, Ref to Enemy, random number in case it's needed
    function<void(Player&, Enemy&, int&)> effect;
};
inline Ability noneAbility = {"", "", "", 0, [](Player& p, Enemy& e, int& i) {}};
void levelUpScreen();

// SPELLS ==============================================================================================================================

// Spell(name, desc, color, value, manaCost, status, damage, spellType)

class Spell{
private:
    string name;
    string description;
    string color;

    int manaCost;
    StatusType status;
    DamageType damage;
    SpellType spellType;

    int value; //( amount it increases damage, amount of damage it deals etc. )
public:

    string getName() const { return name; }
    string getDesc() const { return description; }
    string getColor() const { return color; }
    int getValue() const { return value; }
    int getManaCost() const { return manaCost; }
    StatusType getStatus() const { return status; }
    DamageType getDamage() const { return damage; }
    SpellType getSpellType() const { return spellType; }

    Spell() : name(""), description(""), color(GRAY), value(0), manaCost(1), status(NONE), damage(NADA), spellType(MAGICAL) {}

    Spell(string newName, string newDesc, string newColor, int newVal, int newCost, StatusType newStatus = NONE, DamageType newDamage = NADA, SpellType newType = MAGICAL) {
        name = newName; description = newDesc; color = newColor; value = newVal; manaCost = newCost; status = newStatus, damage = newDamage, spellType = newType;}
};

inline Spell noneSpell     ("---", "No spell equipped.", GRAY, 0, 0, NONE, NADA, MAGICAL);
inline Spell earlStar      ("Earl Star", "A cosmic particle of infinte energy.", RED, 9999, 0, DIVINE, ARCANE, CELESTIAL);

// Basic Spells
inline Spell starDust      ("Stardust", "A basic spell that summons trace residue from starlight.", GRAY, 7, 7, NONE, ARCANE, CELESTIAL);
inline Spell flameSwirl    ("Flame Swirl", "A torrent of fire called upon by magic.", GRAY, 10, 7, BURN, FIRE, INCENDIARY);
inline Spell icicleDrop    ("Icicle Drop", "A shard of ice summoned to strike from above.", GRAY, 10, 7, FROZEN, ICE, MAGICAL);
inline Spell levin         ("Levin", "Charged lighting surging from the body.", GRAY, 10, 7, ELECTRIC, LIGHTNING, LINAURAN);
inline Spell thorns        ("Thorns", "A tangle of thorned vines grown to strike the enemy.", GRAY, 10, 7, NONE, FLORA, ARBOREAL);
inline Spell tincture      ("Tincture","A volatile mixture that corrodes and poisons on contact.", GRAY, 10, 7, POISON, CAUSTIC, ALCHEMICAL);
inline Spell citrinitas    ("Citrinitas","A summoned stone that draws in the light of the sun.", GRAY, 10, 7, BURN, HOLY, ALCHEMICAL);

// Intermediate Spells

inline Spell cometFall     ("Comet Fall", "A fragment of falling star, called down to crash with force.", GREEN, 18, 10, BURN, BLUNT, CELESTIAL);
inline Spell glacialSpike  ("Glacial Spike", "A thick spear of ice driven through the target.", GREEN, 18, 10, FROZEN, ICE, MAGICAL);
inline Spell temptus       ("Temptus", "A localized storm summoned to strike repeatedly.", GREEN, 18, 5, ELECTRIC, LIGHTNING, LINAURAN);
inline Spell calcination   ("Calcination", "A lingering mist that burns anything caught inside it.", GREEN, 18, 10, BURN, CAUSTIC, ALCHEMICAL);
inline Spell rootbind      ("Rootbind", "Thick roots that burst from the ground to crush and restrain.", GREEN, 18, 10, BLEED, FLORA, ARBOREAL);
inline Spell voidLash      ("Void Lash", "A tether of raw magic that lashes out and unravels its target.", GREEN, 18, 10, CURSED, ARCANE, DEMONIC);

// Advanced Spells

inline Spell arcaneBurst   ("Arcane Detonation", "A concentrated eruption of raw magic torn loose at the target.", CYAN, 30, 8, NONE, ARCANE, MAGICAL);
inline Spell conflagration ("Conflagration", "A wall of fire that consumes everything caught within it.", CYAN, 30, 8, BURN, FIRE, INCENDIARY);
inline Spell novaFrost     ("Nova Frost", "A collapsing field of cosmic ice that entombs the target where it stands.", CYAN, 30, 8, FROZEN, ICE, CELESTIAL);
inline Spell tonitrus      ("Tonitrus", "A thunderclap given form, striking with the full weight of a storm.", CYAN, 30, 9, ELECTRIC, LIGHTNING, LINAURAN);
inline Spell triaPrima     ("Tria Prima", "Three divine flashes of blinding and burning light.", CYAN, 42, 8, BURN, ARCANE, ALCHEMICAL);
inline Spell wildrootSurge ("Wildroot Surge", "The earth itself convulses, driving ancient roots through the target.", CYAN, 30, 7, BLEED, FLORA, ARBOREAL);
inline Spell ignisExanimus ("Ignis Exanimus", "An unholy flame drawn from the void, cold and hungry beneath its heat.", CYAN, 30, 9, CURSED, DARK, DEMONIC);
inline Spell sanctusFulgur ("Sanctus Fulgur", "A bolt of consecrated lightning that judges before it strikes.", CYAN, 30, 8, ELECTRIC, HOLY, ELENORAN);

// ITEMS ===============================================================================================================================

class Item {
private:
    string name;
    string description;
    ItemType itemCategory; // Armor, Weapon, Spellbook, Artifact, Potion, Drop
    string color; // Item color in inventory
    int value; // Damage of weapon, hp of armor, price when selling etc.

public:
    int quantity;
    StatusType status;
    DamageType damage;
    SpellType spellType;
    vector<Spell> spells;
    Ability ability;

    string getName() const {return name;};
    string getDesc() const {return description;};
    string getCategory() const {
        switch (itemCategory){
        case DROP:     return "Drop"; break;
        case WEAPON:   return "Weapon"; break;
        case AMULET:   return "Amulet"; break;
        case POTION:   return "Potion"; break;
        case ARTIFACT: return "Artifact"; break;
        case ARMOR:    return "Armor"; break;
        case KEYITEM:  return "Key Item"; break;
        case SCROLL:   return "Scroll"; break;
        case TOME:     return "Tome"; break;
        default:
            break;
        }
        return "Null";
    };

    string getDamageType() const {
        switch (damage){
        case NADA:      return "None"; break;
        case ARCANE:    return "Arcane"; break;
        case SLASH:     return "Slash"; break;
        case STAB:      return "Stab"; break;
        case BLUNT:     return "Blunt"; break;
        case CAUSTIC:   return "Caustic"; break;
        case ICE:       return "Ice"; break;
        case FIRE:      return "Fire"; break;
        case LIGHTNING: return "Lightning"; break;
        case FLORA:     return "Flora"; break;
        case HOLY:      return "Holy"; break;
        case DARK:      return "Dark"; break;
        default:
            break;
        }
        return "Null";
    };
    ItemType getEnumCate() const {return itemCategory;};
    string getColor() const {return color;};
    int getValue() const {return value;};

    Item() : name(""), description(""), itemCategory(DROP), color(GRAY), value(0), status(NONE), damage(NADA), spellType(NOPE), spells({noneSpell}), ability(noneAbility), quantity(0){}

    Item(string newName, string newDesc, ItemType newCat, string newColor, int newVal,
    StatusType newStatus = NONE, DamageType newDamage = NADA, SpellType newSType = NOPE, vector<Spell> newSpells = {}, Ability newSkill = noneAbility, int newQuan = 0) {
        name = newName; description = newDesc; itemCategory = newCat; color = newColor;
        value = newVal; status = newStatus; damage = newDamage; spellType = newSType; spells = newSpells; ability = newSkill; quantity = newQuan;
    }
};

inline Item noneItem       ("Nothing", "???", DROP, WHITE, 0, NONE, NADA);

// Drops ------------------------------------------------------------------------------------------------------------------
// General / Common
inline Item cloth          ("Cloth",          "A piece of ripped fabric.", DROP, GRAY, 10);
inline Item tooth          ("Tooth",          "A crooked tooth pried from a beast's jaw.", DROP, GRAY, 8);
inline Item ooz            ("Ooz",            "A jar of viscous slime that never quite stops moving.", DROP, GRAY, 10);
inline Item leather        ("Leather",        "A worn piece of leather, dry and sewed.", DROP, GRAY, 15);
inline Item pelt           ("Pelt",           "A coarse pelt, still furred.", DROP, GRAY, 12);
inline Item fang           ("Fang",           "A sharpened fang from a predator's jaw.", DROP, GRAY, 18);
inline Item scrapMetal     ("Scrap Metal",    "A twisted piece of metal, worn down but still useful.", DROP, GRAY, 8);
// Unique / Rare
inline Item banditEmblem   ("Bandit Emblem",  "The badge held by elite members of the bandits.", DROP, GREEN, 30);
inline Item moonBearClaw   ("Moon Bear Claw", "A heavy claw, cold to the touch no matter how long it's held.", DROP, GREEN, 22);
inline Item wraithEssence  ("Wraith Essence", "A wisp of captured spirit, swirling faintly within a glass vial.", DROP, GREEN, 35);

// Weapons ------------------------------------------------------------------------------------------------------------------

// Basic Weapons

inline Item straightSword  ("Straight Sword", "A standard steel sword.", WEAPON, GRAY, 10, NONE, SLASH);
inline Item basicDagger    ("Dagger", "A standard steel dagger.", WEAPON, GRAY, 10, NONE, SLASH);
inline Item flintLock      ("Flintlock", "A basic firearm, worn but useable.", WEAPON, GREEN, 13, BLEED, STAB);
inline Item basicSpear     ("Spear", "A standard iron pointed spear.", WEAPON, GRAY, 10, NONE, STAB);
inline Item claymore       ("Claymore", "An imposing sword, very heavy.", WEAPON, GRAY, 15, NONE, SLASH);
inline Item flameFlask     ("Flame Flask", "A mix of chemicals that erupt in flame in air.", WEAPON, GRAY, 10, BURN, FIRE);
inline Item walkingStaff   ("Walking Staff", "A wooden stick used for walking.", WEAPON, GRAY, 7, CONFUSE, BLUNT);

inline Item spellBook      ("Spell Book", "A basic tome anyone can use for magic.", CATALYST, GRAY, 10); 
inline Item alchemyTome    ("Alchemy Tome", "An advanced tome written by Alchemists.", CATALYST, GRAY, 10);
inline Item magicWand      ("Magic Wand", "A basic, yet straightforward spell catalyst.", CATALYST, GRAY, 10, NONE, BLUNT);

// Intermidiate Weapons 

// Debug Weapons

inline Item UltraBlade     ("Ultra Blade", "A blade that cuts through every form of resistance at once.", WEAPON, RED, 9999, DIVINE, ARCANE);
inline Item infiniteTome   ("The Infinite Tome", "Every spell ever written, bound into one impossible volume.", CATALYST, RED, 9999, DIVINE, ARCANE);

// Armor -----------------------------------------------------------------------------------------------------------------------

inline Item knightSet      ("Knight Set", "Chain and plate armor built from steel.", ARMOR, GREEN, 10, NONE); // Knight, Vangaurd
inline Item prisonerSet    ("Prisoner Set", "Darkened pants and shirt, with steel cuffs for defense.", ARMOR, GRAY, 7, NONE); // Penitant
inline Item wildernessSet  ("Wilderness Set", "Flowing cotton robes, thick and comfortable.", ARMOR, GRAY, 5, NONE); // Traveller
inline Item scholarSet     ("Scholar Set", "Intricate robes, given to graduates of the Universitas.", ARMOR, GRAY, 6, NONE); // Alchemist, Archanist

inline Item banditSet      ("Bandit Set", "A black steel set of armor worn by Corvin Ash. His sacrifice will never be forgotten.", ARMOR, CYAN, 16, NONE);
inline Item ashenSet       ("Ashen Set", "A black steel set of armor worn by Corvin Ash. His sacrifice will never be forgotten.", ARMOR, CYAN, 16, NONE);
inline Item desertSet      ("Desert Dweller Set", "A light set of tobes and chainmail, airy and defensive.", ARMOR, GREEN, 17, NONE);

// Potions & Artifacts ----------------------------------------------------------------------------------------------------------

// < Healing >
inline Item healingPotion  ("Healing Potion", "A drink that heals small wounds.", POTION, GRAY, 5);
inline Item healingElixer  ("Healing Elixer", "An elixer that heals deeper wounds.", POTION, GREEN, 10);
inline Item pheonixTears   ("Pheonix Tears", "Tears from a pheonix, it heals you to full and BURNS to drink.", POTION, GREEN, 100, BURN);
inline Item lifeElixer     ("Life Elixer", "An elixer that grants you REGENERATION.", POTION, GREEN, 0, REGEN);

// < Aleviate >
inline Item bezoar         ("Bezoar", "A medicine that cure's POISON.", CURE, GREEN, 10, POISON);
inline Item bandages       ("Bandages", "Stop's BLEED.", CURE, GREEN, 10, BLEED);
inline Item chamomile      ("Chamomile", "A sweet tea that treats FEAR.", CURE, GREEN, 10, FEAR);
inline Item warmingStone   ("Warming Stone", "Crystalized fire that will stop FROZEN.", CURE, CYAN, 10, FROZEN);
inline Item bellFragment   ("Bell Fragment", "A shard from the Sonder Bell itself, it staves off CURSED.", CURE, CYAN, 10, CURSED);
inline Item medicinalHerbs ("Medicinal Herbs", "A special blend of herbs that makes you less CONFUSED.", CURE, CYAN, 10, CONFUSE);
inline Item nail           ("Grounding Nail", "A special metal that will hold your residual ELECTRIC.", CURE, CYAN, 10, ELECTRIC);

// < Up Stats >
inline Item focusTrinket   ("Focus Trinket", "Break this artifact open to gain MANA.", ARTIFACT, GRAY, 5);
inline Item focusCharm     ("Focus Charm", "Break this mystic artifact open to gain MANA.", ARTIFACT, GREEN, 10);
inline Item injection      ("Injection", "A strange syringe that ups your STAMINA but POISONs you.", ARTIFACT, GREEN, 10, POISON);
inline Item strongPotion   ("Strengthening Potion", "A drink that ups your attack.", POTION, GRAY, 10);
inline Item boilPotion     ("Bloodboil Potion", "A drink that strengthens you, but makes you BLEED.", POTION, GREEN, 15, BLEED);

// < Weaken Enemy >
inline Item oilPot         ("Oil Pot", "Turns the weakness of the enemy to fire damage.", ARTIFACT, GREEN, 10, NONE, FIRE);
inline Item rosaries       ("Prayer Rosaries", "Changes the weakness of the enemy to holy damage.", ARTIFACT, GREEN, 10, NONE, HOLY);


// Scrolls ------------------------------------------------------------------------------------------------------------------

inline Item scrollOfTheElements  ("Elemental Scroll", "Contains the spells of the 4 elements", SCROLL, RED, 0, NONE, NADA, NOPE, {flameSwirl, icicleDrop, levin, thorns});
inline Item scrollOfTheAlchemist ("Alchemist's Scroll", "Contains the spells for a beginner alchemist", SCROLL, RED, 0, NONE, NADA, NOPE, {tincture, citrinitas});

// Amulets ------------------------------------------------------------------------------------------------------------------

inline Item ironKnuckle       ("Iron Knuckle",       "A finger cover from the armor of a great warrior.", AMULET, GRAY, 5, NONE, BLUNT, NOPE);
inline Item emberBead         ("Ember Bead",         "Fire, captured in a glass bead.", AMULET, GRAY, 5, NONE, FIRE, NOPE);
inline Item snowflakeCharm    ("Snowflake Charm",    "Once, a snowflake fell from the sky. Unlike its peers, it never melted.", AMULET, GRAY, 5, NONE, ICE, NOPE);
inline Item lightningBottle   ("Lightning Bottle",   "They said lightning could never be captured.", AMULET, GREEN, 6, NONE, LIGHTNING, NOPE);
inline Item unwiltingRose     ("Unwilting Rose",     "An immortal rose, with an unknown origin.", AMULET, GREEN, 6, NONE, FLORA, NOPE);
inline Item goldenEmblem      ("Golden Emblem",      "A golden symbol, blessed by a devout.", AMULET, CYAN, 7, NONE, HOLY, NOPE);
inline Item obsidianEye       ("Obsidian Eye",       "A pitch dark glass eye, it stares at you...", AMULET, CYAN, 7, NONE, DARK, NOPE);
inline Item etchedVial        ("Etched Vial",        "A bottle that absorbed countless alchemical compunds.", AMULET, PURPLE, 9, NONE, CAUSTIC, NOPE);
inline Item glyphStone        ("Glyph Stone",        "An ancient stone. It has a strange symbol scratched into it...", AMULET, PURPLE, 9, NONE, ARCANE, NOPE); 

inline Item apprenticePin     ("Apprentice Pin",     "Created by the Old Masters at the Universitas, to help it's students with their study.", AMULET, GRAY, 5, NONE, NADA, MAGICAL);
inline Item athanorCharm      ("Athanor Charm",      "Forged by the great Alchemist Anathor.", AMULET, GRAY, 5, NONE, NADA, ALCHEMICAL);
inline Item cinderBrand       ("Cinder Brand",       "The branding iron used by the Fire Cult. Its always warm to the touch.", AMULET, GRAY, 5, NONE, NADA, INCENDIARY);
inline Item heartwoodCharm    ("Heartwood Charm",    "The seed of an ancient tree. It's age has long past, and it's unable to grow.", AMULET, GRAY, 5, NONE, NADA, ARBOREAL); 
inline Item lunarStone        ("Lunar Stone",        "A piece of an asteriod from a planet beyond the galaxy.", AMULET, CYAN, 6, NONE, NADA, CELESTIAL);
inline Item linauranSigillum  ("Linauran Sigillum",  "The symbol of Linaura, granted to it's knights.", AMULET, CYAN, 6, NONE, NADA, LINAURAN);
inline Item maledicSigil      ("Maledic Sigil",      "Created by the vile demon Asag in his youth. It was left here during the sixth Crownseeker war.", AMULET, PURPLE, 7, NONE, NADA, DEMONIC);
inline Item elenoranLumen     ("Elenoran Sigillum",  "Elenoras Linauran Sigillum during her youth as a Knight.", AMULET, GOLD, 9, NONE, NADA, ELENORAN);

inline Item pyreHeart         ("Pyre Heart",         "The strongest Amulet of the Fire Cult.", AMULET, GREEN, 6, NONE, FIRE, INCENDIARY);
inline Item moonfrostPendant  ("Moonfrost Pendant",  "A necklace carved from Moonfrost. It will never melt.", AMULET, GREEN, 6, NONE, ICE, CELESTIAL);
inline Item asagsEmblem       ("Asag's Emblem",      "An amulet depicting the vile demon Asag.", AMULET, GREEN, 7, NONE, DARK, DEMONIC);
inline Item elderRoot         ("Elder Root",         "The root of an Elder tree. It's as rare as it is powerful.", AMULET, CYAN, 5, NONE, FLORA, ARBOREAL);
inline Item philosopherStone  ("Philosphers Stone",  "The ultimate substance that can be created through Alchemy. Its power is second to none.", AMULET, PURPLE, 8, NONE, CAUSTIC, ALCHEMICAL);
inline Item stormSigillum     ("Storm Sigillum",     "The Linauran Sigillum of storm king Moraai, fifth Earl.", AMULET, GOLD, 9, NONE, LIGHTNING, LINAURAN);
inline Item elenorasBell      ("Elanora's Bell",     "A golden bell, forged by Elenora years ago. It was the last one she made before claiming the crown.", AMULET, GOLD, 10, NONE, HOLY, ELENORAN);

// Other ------------------------------------------------------------------------------------------------------------------

inline Item sealOfSonder      ("Seal of Sonder", "The very essence of your being. Granted to those who have the will to seek the crown.", KEYITEM, GOLD, 0);

// ENEMIES =============================================================================================================================

class Enemy {
public:
    string name;
    int maxHealth, currentHealth;
    int attack, currentAttack;
    int maxStamina, currentStamina;
    int xpReward, silverReward;

    StatusType inflictStatus;
    int skillLevel;
    DamageType weakness;
    StatusType currentStatus = NONE;

    vector<Item> drops;

    Item heldItem;
    bool usedItem = false;

    string getName() const {return name;};
    // string getDesc() const {return description;};
    string getWeakness() const {
        switch (weakness){
        case NADA:      return "None"; break;
        case ARCANE:    return "Arcane"; break;
        case SLASH:     return "Slash"; break;
        case STAB:      return "Stab"; break;
        case BLUNT:     return "Blunt"; break;
        case CAUSTIC:   return "Caustic"; break;
        case ICE:       return "Ice"; break;
        case FIRE:      return "Fire"; break;
        case LIGHTNING: return "Lightning"; break;
        case FLORA:     return "Flora"; break;
        case HOLY:      return "Holy"; break;
        case DARK:      return "Dark"; break;
        default:
            break;
        }
        return "Null";
    };
    string getStatus() const {
        switch (inflictStatus){
        case NONE:     return "None (NONE)"; break;
        case POISON:   return "Poison (POIS)"; break;
        case BURN:     return "Burn (BURN)"; break;
        case FEAR:     return "Fear (FEAR)"; break;
        case FROZEN:   return "Frozen (FRZN)"; break;
        case BLEED:    return "Bleed (BLED)"; break;
        case REGEN:    return "Regeneration (REGN)"; break;
        case DIVINE:   return "Divine (DIVN)"; break;
        case CURSED:   return "Cursed (CURS)"; break;
        case ELECTRIC: return "Electric (ELEC)"; break;
        default:
            break;
        }
        return "Null";
    };

    vector<Item> getDrops() const {
        vector<Item> toReturn;
        for (int i = 0; i < drops.size(); i++){
            toReturn.push_back(drops.at(i));
        }
        return toReturn;
    }

    Enemy() {}
    Enemy(string n, int hp, int atk, int stamina, int xp, int silver, StatusType infStatus, int skill, DamageType weakness, vector<Item> drops, Item held = noneItem)
        : name(n), maxHealth(hp), currentHealth(hp), attack(atk), currentAttack(atk), maxStamina(stamina), currentStamina(stamina),
          xpReward(xp), silverReward(silver),
          inflictStatus(infStatus), skillLevel(skill), weakness(weakness), drops(drops), heldItem(held){}

    void takeDamage(int dmg) { currentHealth = max(0, currentHealth - dmg); }
    void heal(int amount) { currentHealth = min(maxHealth, currentHealth + amount); }
    bool isAlive() const { return currentHealth > 0; }
};

// Enemy("Name",  hp, atk, stanima, xp, silver, status to inflict, skill (amount of letters), weakness, drop, spellToLearnFrom)

inline Enemy grimling      ("Grimling",  45, 10, 5, 15, 10, POISON, 1, STAB,      {cloth, tooth}, bezoar);
inline Enemy oozer         ("Oozer",     40, 10, 3, 15, 10, POISON, 1, CAUSTIC,   {ooz});
inline Enemy bandit        ("Bandit",    45, 12, 5, 25, 20, BLEED,  1, LIGHTNING, {cloth, leather}, healingPotion);
inline Enemy fangwolf      ("Fangwolf",  50, 10, 5, 30, 15, FEAR,   1, NADA,      {pelt, fang});
inline Enemy duskhound     ("Duskhound", 50, 14, 5, 40, 25, CURSED, 1, STAB,      {pelt, fang});
inline Enemy moonBear      ("Moon Bear", 60, 20, 7, 60, 25, FROZEN, 3, STAB,      {pelt, moonBearClaw});

inline Enemy banditEnforcer("Bandit",    50, 12, 5, 25, 20, BLEED,  1, LIGHTNING, {cloth, leather}, healingPotion);

inline Enemy wraith        ("Wraith",    70, 14, 7, 40, 25, CURSED, 2, DARK,      {cloth, wraithEssence});

inline vector<Enemy> outskirts = { grimling, bandit, fangwolf, duskhound, oozer, moonBear};

inline vector<Enemy> millmore = {};

inline vector<Enemy> southernExpanse = {};

inline vector<Enemy> filmont = {};

inline vector<Enemy> blueLake = {};

inline vector<Enemy> verdentExpanse = {};

inline vector<Enemy> defiledReigon = {};

inline vector<Enemy> capitalWalls = {};

inline vector<Enemy> castleNorn = {};

inline vector<Enemy> throneRoom = {};

// PLAYER ============================================================================================================================== 

class CharClass{
private: // stats and stuff
    string name; // 1-Knight, 1-Penitant, 3-Traveller, 4-Vanguard, 5-Archanist, 6-Alchemist
    int health; 
    int attack; // Normal damage from weapon
    int magicAttack; // Magical damage from spellbook
    int intelligence; // Increases chance of learning enemy spells
    int mana; // Amount of times you can cast a spell in a battle
    int stamina; // Amount of special moves you can do

    Item startArmor;
    Item startWeapon;
    Item startCatalyst;

    Spell startSpell;

    Ability startAbility;
    
public: // methods and constructor
    string getName() const {return name;};
    int getHealth() const {return health;};
    int getAttack() const {return attack;};
    int getMagicAttack() const {return magicAttack;};
    int getIntel() const {return intelligence;};
    int getMana() const {return mana;};
    int getStamina() const {return stamina;};

    Item getArmor() const {return startArmor;};
    Item getWeap() const {return startWeapon;};
    Item getCat() const {return startCatalyst;};
    Spell getSpell() const {return startSpell;};
    Ability getAbility() const {return startAbility;};

    // void setHealth(int i) {health = i;}; // increased by armor
    // void setAttack(int i) {attack = i;}; // increased by weapon
    // void setMagicAttack(int i) {magicAttack = i;}; // increased by wand
    // void setIntel(int i) {intelligence = i;}; // increased by reading lore
    // void setMana(int i) {mana = i;}; // increased by learning spells
    // void setStamina(int i) {stamina = i;}; // increased by battling more


    CharClass() : name(""), health(0), attack(0), magicAttack(0), intelligence(0), mana(0), stamina(0), startArmor(knightSet),
    startWeapon(straightSword), startCatalyst(spellBook), startSpell(noneSpell), startAbility() {}

    CharClass(string newName, int newHealth, int newAttack, int newMagicAttack, int newIntelligence, int newMana, int newStamina, 
        Item newArmor, Item newWeap, Item newCat, Spell newSpell, Ability newAbility) {
        
        name = newName; health = newHealth; attack = newAttack; stamina = newStamina; 
        magicAttack = newMagicAttack; intelligence = newIntelligence; mana = newMana; startArmor = newArmor;
        startWeapon = newWeap; startCatalyst = newCat; startSpell = newSpell; startAbility = newAbility;}
};

class Player{ // all public since theres only one player instance anyway
public:
    string name;
    string className = "None";
    
    // Stats
    int maxHealth, currentHealth;
    int attack, currentAttack;
    int magicAttack, currentMattack;
    int intelligence;
    int maxMana, currentMana;
    int maxStamina, currentStamina;

    StatusType currentStatus = NONE;

    vector<Spell> learnedSpells;
    vector<Ability> learnedAbilities;
    vector<Enemy> beastiary;

    Item armor;
    Item weapon;
    Item catalyst;
    vector<Spell> spells = {noneSpell, noneSpell, noneSpell};

    Ability skill;
    vector<Item> amulets = {noneItem, noneItem, noneItem};

    // Ability flags
    bool parryCounterActive = false;
    int equCounter = 0;
    

    // Other
    int level = 1;
    int experience = 0;
    int maxExperience = 40 - (intelligence / 2);
    int coins = 0;

    vector<Item> inventory = {};

    // Set the players stats and items to reflect the chosen class
    // Parameters: c -> Class the player chose, chosenName -> Name the player chose
    void chosenFromClass(const CharClass& c, const string& chosenName) {
        name = chosenName;
        className = c.getName();
        currentHealth = maxHealth = c.getHealth();
        attack = currentAttack = c.getAttack();
        magicAttack = currentMattack = c.getMagicAttack();
        intelligence = c.getIntel();
        currentMana = maxMana = c.getMana();
        currentStamina = maxStamina = c.getStamina();

        learnedSpells.push_back(c.getSpell());
        learnedAbilities.push_back(c.getAbility());

        armor = c.getArmor();
        weapon = c.getWeap(); catalyst = c.getCat();
        spells.at(0) = c.getSpell();
        skill = c.getAbility();
    }

    void takeDamage(int damage) { currentHealth = max(0, currentHealth - damage); }
    void heal(int amount) { currentHealth = min(maxHealth, currentHealth + amount); }
    void focus(int amount) { currentMana = min(maxMana, currentMana + amount); }
    void staminaUp(int amount) { currentStamina= min(maxStamina, currentStamina + amount); }

    void changeCoins(int amount, bool add) {
        if (add){
            coins += amount;
            cout << "You earned " << amount << SILVER << " Silverbells!" << NORMAL << endl;
        }else{
            coins -= amount;
            if (coins < 0) {
                coins = 0;
                cout << "You had no " << SILVER << "Silverbells" << NORMAL << " to lose." << endl;
            }
            else {
                cout << "You lost " << amount << SILVER << " Silverbells." << NORMAL << endl;
            }
        }
        
    }

    bool gainXP(int amount) {
        experience += amount;
        while (experience >= maxExperience) { levelUp(); return true;}
        return false;
    }
    void levelUp() {
        experience -= maxExperience;
        level++;
        maxExperience = (int)(maxExperience * 1.25);
        cout << "You Leveled Up!" << endl;
        cout << endl << "════════════════════════════════════════════════════════════════════" << endl << endl;
        pressEnter();
        levelUpScreen();
    }

    bool isAlive() const { return currentHealth > 0; }
};


extern CharClass knight;
extern CharClass penitant;
extern CharClass traveller;
extern CharClass vanguard;
extern CharClass archanist;
extern CharClass alchemist;

extern Player player;
extern CharClass playerClass;

// ABILITIES ===========================================================================================================================

// LF = Lambda Function in the explanations. 
// Parameters for all of them: p to reference player, e to reference the current enemy, i to work with a number in case it's needed



// LF sets a player class flag to true. Parameters don't really matter here lol
inline Ability counterAttack = {"Counterattack", "Perfect counters will deal damage to your opponent.",
    "You will follow up your perfect counters with an attack...", 7, 
    [](Player& p, Enemy& e, int& i) {p.parryCounterActive = true;}};

// LF starts a countdown that will kill the player in i turns, and multiplies player magic attack by 1.5 (int)
inline Ability equivalentExchange = {"Equivalent Exchange", "Strengthens your magic, but you will die in 3 turns.",
    "The countdown starts... destroy the enemy quickly with your newfound power.",10,
    [](Player& p, Enemy& e, int& i) { p.equCounter = 6;p.currentMattack = (int)(p.currentMattack * 1.5);}};

// LF inflicts the StatusTyupe BLEED on player, and multiplies player attack by 1.5 (int)
inline Ability bloodPact = {"Blood Pact", "Strengthens your attacks, but will make you bleed.",
    "Your blood sacrifice grants you strength.", 12, 
    [](Player& p, Enemy& e, int& i) {p.attack *= (int)(p.currentAttack * 1.5); p.currentStatus = BLEED;}};

// LF inflicts the StatusType DIVINITY on player. Parameters don't really matter here lol
inline Ability prayer = {"Prayer", "Grants you DIVINITY, you are immune to status'",
    "Your prayer has been answered.", 14, 
    [](Player& p, Enemy& e, int& i) {p.currentStatus = DIVINE;}};

// LF changes the enemy weaknes to the player's weapon damage type. 
inline Ability resonance = {"Resonance", "Changes the enemy's weakness to your weapon type.",
    "The weakness of the enemy has changed.", 17, 
    [](Player& p, Enemy& e, int& i) {e.weakness = p.weapon.damage;}};

// LF lowers enemy attack by inflicting FEAR
inline Ability intimidate = {"Intimidate", "Makes your enemy FEAR you.",
    "You stare them down, unshaken.", 8, 
    [](Player& p, Enemy& e, int& i) {e.currentStatus = FEAR;}};

// LF deals damage equal to the player's current mana -- big if full, weak if drained
inline Ability manaBurst = {"Mana Burst", "Deplete your MANA for damage equal to it's value.",
    "You discharge raw magic in a single burst.", 0, 
    [](Player& p, Enemy& e, int& i) {e.takeDamage(p.currentMana); p.currentMana = 0;}};

// LF inflicts the player's OWN current status onto the enemy, then heals the player by removing it
inline Ability transference = {"Transference", "Cures your status and give it to the enemy.",
    "You force your burden onto the enemy.", 12, 
    [](Player& p, Enemy& e, int& i) {
        if (p.currentStatus != NONE) {
            e.currentStatus = p.currentStatus;
            cout << "Your affliction leaps to the enemy!" << endl;
            p.currentStatus = NONE;
        } else { cout << "You have nothing to pass on." << endl;}}};

// LF inflicts the StatusType CURSED on enemy 
inline Ability invocation = {"Invocation", "CURSE's the enemy.",
    "Your invocation has been answered...", 15, 
    [](Player& p, Enemy& e, int& i) {e.currentStatus = CURSED;}};

// Tomes ------------------------------------------------------------------------------------------------------------------

inline Item knightTome   ("Knighthood Tome", "Directions to learn the Counterattck skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, counterAttack);
inline Item alchemyTeach ("Alchemist Teachings", "Directions to learn the Equivalent Exhange skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, equivalentExchange);
inline Item bloodTome    ("Bloodied Tome", "Directions to learn the Blood Pact skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, bloodPact);
inline Item prayerTome   ("Holy Text", "Directions to learn the Prayer skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, prayer);
inline Item guideToFear  ("Guide to Fear", "Directions to learn the Intimidate skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, intimidate);
inline Item resonantTome ("Resonant Tome", "Directions to learn the Resonance skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, resonance);
inline Item demonicText  ("Demonic Text", "Directions to learn the Inovation skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, invocation);
inline Item arcaneTome   ("Archanist Teachings", "Directions to learn the Mana Burst skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, manaBurst);
inline Item transferLaw  ("Law of Transference", "Directions to learn the Transference skill", TOME, RED, 0, NONE, NADA, NOPE, {noneSpell}, prayer);


#endif