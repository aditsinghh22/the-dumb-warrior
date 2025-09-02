#include <stdio.h>
#include <stdlib.h> // For exit()
#include <ctype.h>  // For tolower()

// --- Global State ---
// 0 = Nothing, 1 = Fire Rune, 2 = Scrap Metal
int player_inventory = 0;

// --- Helper Functions for Dialogue and Flow ---

// A utility to pause the game and wait for the user
void press_enter_to_continue() {
    printf("\n(Press Enter to continue...)");
    while (getchar() != '\n'); // Clear the input buffer
    // Wait for Enter key
}


// Safely gets a character choice from the user

char get_choice(char a, char b, char c) {
    char choice;
    while (1) {
        printf("> ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        // Clear the input buffer to prevent issues with the next input
        while (getchar() != '\n'); 

        if (choice == a || choice == b || (c != 0 && choice == c)) {
            return choice;
        } else {
            if (c == 0) {
                 printf("Invalid choice. Please enter '%c' or '%c'.\n", a, b);
            } else {
                 printf("Invalid choice. Please enter '%c', '%c', or '%c'.\n", a, b, c);
            }
        }
    }
}

// --- Story Scene Functions ---

void scene_dragon_lair(); // Forward declaration

void ending_coward() {
    printf("\n--- ENDING 1: A COWARD'S END ---\n");
    printf("Narrator: He lay there, paralyzed, as a herd of fluffy sheep trotted over and began to nibble on his hair. A truly pathetic sight.\n");
    printf("(You died from a botanical blunder. Maybe the scary path was safer.)\n");
    printf("\n========= GAME OVER =========\n");
    exit(0);
}

void ending_skill_issue() {
    printf("\n--- ENDING 2: SKILL ISSUE ---\n");
    printf("Narrator: The adventurers didn't even stand up. Their leader, a woman with a scar over one eye, flicked a pebble at Leo's forehead. He crumpled to the ground, unconscious. They took his pan.\n");
    printf("(You were defeated by a pebble. A PEBBLE. Let that sink in.)\n");
    printf("\n========= GAME OVER =========\n");
    exit(0);
}

void ending_cremation() {
    printf("\n--- ENDING 3: UNSCHEDULED CREMATION ---\n");
    printf("Leo: Wait, maybe this wasn't such a good—\n");
    printf("Narrator: It was not, in fact, a good idea. A torrent of fire erupted from the dragon's maw, engulfing our hero. He was simply... gone. A puff of smoke and a faint, lingering smell of burnt toast.\n");
    printf("(You tried to fight a dragon head-on. The results were predictable.)\n");
    printf("\n========= GAME OVER =========\n");
    exit(0);
}

void ending_accidental_hero() {
     printf("\n--- ENDING 4: THE ACCIDENTAL HERO ---\n");
    if (player_inventory == 1) { // Has Fire Rune
        printf("Narrator: Leo slapped the fire rune onto his pan. It immediately began to glow cherry-red. He hurled it at a far wall, causing a massive, deafening BOOM! The startled dragon fled out a back exit in a panic. The treasure was all his.\n");
    } else { // Has Scrap Metal
        printf("Narrator: Leo hurled the scrap metal. It ricocheted and embedded itself in the dragon's nostril. The dragon awoke with a titanic sneeze that blew Leo—and half the treasure—out of the cave. It then flew away, trying to dislodge the metal from its nose.\n");
    }
    printf("Narrator: And so, Leo won. He stumbled back to town, bruised but rich. The most incompetent hero the kingdom had ever seen, but a hero nonetheless.\n");
    printf("(You somehow succeeded. You're rich! Now you can finally afford a real weapon.)\n");
    printf("\n========= YOU WIN! =========\n");
    exit(0);
}


void scene_adventurers() {
    printf("\n--- In a Clearing ---\n");
    printf("Narrator: Leo, filled with a courage he definitely didn't feel, plunged into the darkness. After an hour of fumbling, he stumbled into a clearing with a warm campfire. Three grizzled adventurers sharpening actual swords looked at Leo, then at his frying pan, and sighed.\n");
    printf("Adventurer: ...You lost, kid?\n");
    printf("Narrator: Here we go. What will our hero do?\n");
    printf("\nChoices:\n");
    printf("  (A) Fight them! Their gear looks expensive.\n");
    printf("  (B) Leave them alone. They look scary.\n");
    printf("  (C) Ask to join their team.\n");

    char choice = get_choice('a', 'b', 'c');

    if (choice == 'a') {
        ending_skill_issue();
    } else if (choice == 'b') {
        printf("\nLeo: Uh, nope! Not lost! Just... admiring the local moss. Carry on!\n");
        printf("Narrator: Leo wisely decided not to antagonize the people holding pointy objects. As he backed away, the leader chuckled.\n");
        printf("Adventurer: Wait, kid. It's dangerous out here. Take this.\n");
        printf("Narrator: She tossed him a small, red stone that pulsed with a warm light.\n");
        printf("** You got a FIRE RUNE! **\n");
        player_inventory = 1;
    } else { // choice == 'c'
        printf("\nLeo: Can I... can I join you guys? I'm on a quest!\n");
        printf("Narrator: The adventurers looked at his pan. Then at each other. Then they burst out laughing.\n");
        printf("Adventurer: Hah! No. We don't have a \"culinary division.\" But hey, for trying, you can have this.\n");
        printf("Narrator: One of them tossed him a bent piece of metal.\n");
        printf("** You got some SCRAP METAL! **\n");
        player_inventory = 2;
    }
    
    press_enter_to_continue();
    scene_dragon_lair();
}

void scene_dragon_lair() {
    printf("\n--- The Dragon's Lair ---\n");
    printf("Narrator: Whether he was equipped with a magical rune or a piece of junk, Leo pressed on. Finally, he reached the entrance to the dragon's lair. Inside, sleeping atop a mountain of gold, was a colossal red dragon.\n");
    printf("Leo: (Whispering) Okay, Narrator. No more tricks. What's the plan?\n");
    printf("Narrator: The plan? You're the hero! Do you charge in, or try something creative?\n");
    printf("\nChoices:\n");
    printf("  (A) Charge! For glory and gold!\n");
    printf("  (B) Try to create a diversion.\n");

    char choice = get_choice('a', 'b', 0);
    if (choice == 'a') {
        ending_cremation();
    } else {
        ending_accidental_hero();
    }
}

void start_game() {
    printf("--- The Adventure Begins ---\n");
    printf("Narrator: In a kingdom where dental insurance was a distant dream, a hero was needed. Behold, Leo! He stood mesmerized before a bounty poster. 'SLAY THE DRAGON, GET 10,000 GOLD,' it read.\n");
    press_enter_to_continue();
    printf("Leo: Hey, Narrator! Just so we're clear, this pan isn't just for cooking. It's a... dragon-bonking instrument.\n");
    printf("Narrator: Whatever helps you sleep at night, kid. Before you, the path splits. To the left, a path shrouded in shadow. To his right, a path bathed in cheerful sunlight.\n");
    printf("\nChoices:\n");
    printf("  (A) Take the dark, horror path.\n");
    printf("  (B) Take the path with full daylight.\n");

    char choice = get_choice('a', 'b', 0);

    if (choice == 'a') {
        scene_adventurers();
    } else { // choice == 'b'
        printf("\nNarrator: Leo, deciding that skulls were bad for his complexion, wisely chose the sunny path. He frolicked through a meadow of beautiful, yellow Buttercups.\n");
        printf("Leo: See? This is much better! What could possibly go wrong?\n");
        printf("Narrator: What could go wrong, indeed. It turns out that Buttercups, while cheerful, are also incredibly poisonous to ingest. And in his frolicking, Leo had tripped and face-planted...\n");
        press_enter_to_continue();
        ending_coward();
    }
}

int main() {
    printf("============================================\n");
    printf("  Leo the Unlikely vs. The Lucrative Lizard \n");
    printf("============================================\n\n");
    
    start_game();
    
    return 0;
}