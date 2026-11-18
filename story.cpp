#include "defs.h"
#include "entities.h"
#include "ui.h"
#include "combat.h"

// Enemy Groups for the story
inline vector<Enemy> fangwolfPack = { fangwolf, fangwolf, fangwolf };
bool questTakeItems(Item itemToTake, int amount);

void quest_Template() {
    while(progress == 1){
        static int part = 1;
        char option = options();
        if (option == '1'){
            switch (part){
            case 1: { 
                
            break;}

            case 2:{

            break;}

            default: break;
            }
        }
    }
    location++;
}

void quest1_EnterMillmore() {
    while(progress == 1){
        static int part = 1;
        char option = options();
        if (option == '1'){
            switch (part){
            case 1: { // Meet the doctor then fight the monster
                narrationBox(SANDY, "NAR_1");
                dialougeBox("Mysterious Man", ICEBLUE, "DOCTOR_1", true);
                int reply1 = reply({"Who are you?", "Where am I?"});

                if (reply1 == 1) dialougeBox("War Surgeon Haney", ICEBLUE, "DOCTOR_2a");
                if (reply1 == 2) dialougeBox("War Surgeon Haney", ICEBLUE, "DOCTOR_2b");

                dialougeBox("War Surgeon Haney", ICEBLUE, "DOCTOR_3");
                if (encounter(outskirts, true, true, 0) == 2 ) part++;
            break;}

            case 2: // Speak with the doctor after the fight
                dialougeBox("War Surgeon Haney", ICEBLUE, "DOCTOR_4");
                dialougeBox("War Surgeon Haney", ICEBLUE, "DOCTOR_5");
                addItem(healingPotion);
                progress++;
            break;

            default:
                break;
            }
        }
    }
    location++;
    unlockedAreas.push_back(2);
}

void quest2_MeetCorvin() {
    while(progress == 2){
        static int part = 1;
        char option = options();
        if (option == '1'){
            switch (part){
            case 1:{ // before meeting Corvin
                narrationBox(GOLD, "NAR_2");
                dialougeBox("Civilain", GRAY, "CIVILIAN_1", true);
                int reply1 = reply({"I'm looking for a man named Corvin Ash."});
                dialougeBox("Civilain", GRAY, "CIVILIAN_2");
                dialougeBox("Civilain", GRAY, "CIVILIAN_3a", true);
                int reply2 = reply({"Alright, ill do it.", ITALIC "Threaten him." UNTALIC});
                if (reply2 == 1) part++; // comply
                else if (reply2 == 2) { // threaten
                    dialougeBox("Civilain", GRAY, "CIVILIAN_3b");
                    part = 4;}
            break;}

            case 2:{ // fight the fangwolves
                if (gauntlet(fangwolfPack, "Fangwolf", "pack") == 2 ) part++;
            break;}

            case 3:{ // finish fangwolf quest
                dialougeBox("Civilain", GRAY, "CIVILIAN_4", true);
            break;}

            case 4:{ // Meet Corvin
                dialougeBox("Corvin Ash?", GRAY, "CORVIN_1", true);
                int reply3 = reply({"Haney sent me, said you could help me avenge my party."});
                dialougeBox("Corvin Ash", DEEPRED, "CORVIN_2");
                dialougeBox("Corvin Ash", DEEPRED, "CORVIN_3");
                dialougeBox("Corvin Ash", DEEPRED, "CORVIN_4", true);
                int reply4 = reply({"You're a real piece of work huh?", "Aren't I your last hope?"});
                dialougeBox("Corvin Ash", DEEPRED, "CORVIN_5", true);
                int reply5 = reply({"I'm in.", "I don't need you.", "What's in it for me?"});

                switch (reply5){
                case 1: dialougeBox("Corvin Ash", DEEPRED, "CORVIN_6a"); progress++; break;
                case 2: dialougeBox("Corvin Ash", DEEPRED, "CORVIN_6b"); progress++; break;
                case 3: dialougeBox("Corvin Ash", DEEPRED, "CORVIN_6c"); progress++; break;
                default: break;}

            break;}

            default: break;
            }
        }
    }
}

void quest3_FightBandits() {
    while(progress == 1){
        static int part = 1;
        char option = options();
        if (option == '1'){
            switch (part){
            case 1: { 
                
            break;}

            case 2:{

            break;}

            default: break;
            }
        }
    }
}

// Helper functions for streamlining the code above --------------------------

bool questTakeItems(Item itemToTake, int amount){
    for (int i = 0; i < amount; i++){
        if(findItem) removeItem(itemToTake);
        else return false;
    }
    return true;
}

