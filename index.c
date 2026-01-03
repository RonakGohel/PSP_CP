#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Game State Structure
typedef struct {
    char player_name[50];
    int current_location;
    int health;
    int has_sword;
    int has_key;
    int has_torch;
    int game_ended;
} GameState;

// Function Prototypes
void initialize_game(GameState *game);
void display_header();
void display_stats(GameState *game);
void location_entrance(GameState *game);
void location_hallway(GameState *game);
void location_armory(GameState *game);
void location_treasure_room(GameState *game);
void location_dark_tunnel(GameState *game);
void location_guardian_chamber(GameState *game);
void save_game(GameState *game);
int load_game(GameState *game);
void game_over(GameState *game, int won);

int main() {
    GameState game;
    int choice;
    
    srand(time(NULL)); // For random events
    
    display_header();
    
    printf("\n=== MAIN MENU ===\n");
    printf("[1] New Game\n");
    printf("[2] Load Game\n");
    printf("[3] Exit\n");
    printf("\nYour choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline
    
    if (choice == 1) {
        initialize_game(&game);
    } else if (choice == 2) {
        if (!load_game(&game)) {
            printf("\nNo save file found. Starting new game...\n");
            initialize_game(&game);
        } else {
            printf("\nGame loaded successfully!\n");
        }
    } else {
        printf("\nThanks for playing!\n");
        return 0;
    }
    
    // Main Game Loop
    while (!game.game_ended && game.health > 0) {
        display_stats(&game);
        
        switch (game.current_location) {
            case 1:
                location_entrance(&game);
                break;
            case 2:
                location_hallway(&game);
                break;
            case 3:
                location_armory(&game);
                break;
            case 4:
                location_treasure_room(&game);
                break;
            case 5:
                location_dark_tunnel(&game);
                break;
            case 6:
                location_guardian_chamber(&game);
                break;
            default:
                printf("\nError: Invalid location!\n");
                game.game_ended = 1;
        }
    }
    
    if (game.health <= 0) {
        game_over(&game, 0); // Lost
    }
    
    return 0;
}

void initialize_game(GameState *game) {
    printf("\nEnter your adventurer's name: ");
    fgets(game->player_name, 50, stdin);
    game->player_name[strcspn(game->player_name, "\n")] = 0; // Remove newline
    
    game->current_location = 1;
    game->health = 100;
    game->has_sword = 0;
    game->has_key = 0;
    game->has_torch = 0;
    game->game_ended = 0;
    
    printf("\nWelcome, %s! Your adventure begins...\n", game->player_name);
    printf("\nPress Enter to continue...");
    getchar();
}

void display_header() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     THE LOST TEMPLE ADVENTURE         ║\n");
    printf("║        Find the Ancient Treasure      ║\n");
    printf("╚════════════════════════════════════════╝\n");
}

void display_stats(GameState *game) {
    printf("\n═══════════════════════════════════════\n");
    printf("Player: %s | Health: %d | Location: %d\n", 
           game->player_name, game->health, game->current_location);
    printf("Inventory: ");
    if (game->has_sword) printf("[Sword] ");
    if (game->has_key) printf("[Golden Key] ");
    if (game->has_torch) printf("[Torch] ");
    if (!game->has_sword && !game->has_key && !game->has_torch) printf("Empty");
    printf("\n═══════════════════════════════════════\n\n");
}

void location_entrance(GameState *game) {
    printf("🏛️  TEMPLE ENTRANCE\n");
    printf("─────────────────────────────────────\n");
    printf("You stand at the entrance of an ancient temple.\n");
    printf("Vines cover the stone walls. A dark hallway leads inside.\n");
    printf("To your left, you notice a small armory room.\n\n");
    
    printf("[1] Enter the dark hallway\n");
    printf("[2] Check the armory room\n");
    printf("[3] Save game\n");
    printf("[4] Quit game\n");
    printf("\nYour choice: ");
    
    int choice;
    scanf("%d", &choice);
    getchar();
    
    switch (choice) {
        case 1:
            game->current_location = 2;
            break;
        case 2:
            game->current_location = 3;
            break;
        case 3:
            save_game(game);
            break;
        case 4:
            printf("\nAre you sure? (1=Yes, 2=No): ");
            int confirm;
            scanf("%d", &confirm);
            getchar();
            if (confirm == 1) game->game_ended = 1;
            break;
        default:
            printf("\nInvalid choice! Try again.\n");
    }
}

void location_hallway(GameState *game) {
    printf("🕯️  DARK HALLWAY\n");
    printf("─────────────────────────────────────\n");
    printf("The hallway is pitch black. You can barely see.\n");
    
    if (game->has_torch) {
        printf("Your torch illuminates two passages ahead:\n");
        printf("One leads to what looks like a treasure room.\n");
        printf("The other descends into a dark tunnel.\n\n");
        
        printf("[1] Go to treasure room\n");
        printf("[2] Descend into dark tunnel\n");
        printf("[3] Go back to entrance\n");
        printf("\nYour choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                game->current_location = 4;
                break;
            case 2:
                game->current_location = 5;
                break;
            case 3:
                game->current_location = 1;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    } else {
        printf("It's too dark to continue! You need a light source.\n");
        printf("You return to the entrance.\n");
        printf("\nPress Enter to continue...");
        getchar();
        game->current_location = 1;
    }
}

void location_armory(GameState *game) {
    printf("⚔️  ARMORY ROOM\n");
    printf("─────────────────────────────────────\n");
    printf("Old weapons and armor line the walls.\n");
    
    if (!game->has_sword) {
        printf("You find a sturdy iron sword!\n");
        printf("You also find a torch on the wall.\n");
        game->has_sword = 1;
        game->has_torch = 1;
        printf("\n[Sword added to inventory]\n");
        printf("[Torch added to inventory]\n");
    } else {
        printf("You've already taken everything useful here.\n");
    }
    
    printf("\nPress Enter to return to entrance...");
    getchar();
    game->current_location = 1;
}

void location_treasure_room(GameState *game) {
    printf("💎  TREASURE ROOM\n");
    printf("─────────────────────────────────────\n");
    printf("Gold coins and jewels are scattered everywhere!\n");
    printf("In the center, there's a locked golden chest.\n\n");
    
    if (game->has_key) {
        printf("You use the Golden Key to open the chest...\n");
        printf("\n✨ TREASURE FOUND! ✨\n");
        printf("The chest contains the legendary Crown of Eternity!\n");
        game_over(game, 1); // Won!
    } else {
        printf("The chest is locked. You need a key.\n");
        printf("\n[1] Go back to hallway\n");
        printf("[2] Enter the dark tunnel to search for key\n");
        printf("\nYour choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1) {
            game->current_location = 2;
        } else {
            game->current_location = 5;
        }
    }
}

void location_dark_tunnel(GameState *game) {
    printf("🌑  DARK TUNNEL\n");
    printf("─────────────────────────────────────\n");
    printf("The tunnel leads deeper underground.\n");
    printf("You hear strange noises echoing...\n");
    printf("Suddenly, you see a chamber ahead with a glowing pedestal.\n\n");
    
    printf("[1] Enter the chamber\n");
    printf("[2] Go back to hallway\n");
    printf("\nYour choice: ");
    
    int choice;
    scanf("%d", &choice);
    getchar();
    
    if (choice == 1) {
        game->current_location = 6;
    } else {
        game->current_location = 2;
    }
}

void location_guardian_chamber(GameState *game) {
    printf("👹  GUARDIAN'S CHAMBER\n");
    printf("─────────────────────────────────────\n");
    printf("A stone guardian blocks your path!\n");
    printf("On the pedestal behind it sits a Golden Key.\n\n");
    
    if (game->has_sword) {
        printf("The guardian awakens and attacks!\n\n");
        printf("[1] Fight the guardian\n");
        printf("[2] Try to run back\n");
        printf("\nYour choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1) {
            int random = rand() % 100;
            if (random < 70) { // 70% chance to win
                printf("\n⚔️  You fight bravely with your sword!\n");
                printf("After a fierce battle, the guardian crumbles to dust!\n");
                printf("You take the Golden Key from the pedestal.\n");
                game->has_key = 1;
                game->health -= 30;
                printf("\n[You lost 30 health in the battle]\n");
                printf("[Golden Key added to inventory]\n");
                printf("\nPress Enter to continue...");
                getchar();
                game->current_location = 2;
            } else {
                printf("\nThe guardian is too powerful!\n");
                game->health -= 60;
                if (game->health > 0) {
                    printf("You barely escape with your life!\n");
                    printf("[You lost 60 health!]\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    game->current_location = 5;
                }
            }
        } else {
            printf("\nYou flee back to the tunnel!\n");
            printf("\nPress Enter to continue...");
            getchar();
            game->current_location = 5;
        }
    } else {
        printf("You don't have a weapon! The guardian looks too dangerous.\n");
        printf("You decide to retreat.\n");
        printf("\nPress Enter to continue...");
        getchar();
        game->current_location = 5;
    }
}

void save_game(GameState *game) {
    FILE *fp = fopen("savegame.dat", "wb");
    if (fp == NULL) {
        printf("\nError: Could not save game!\n");
        return;
    }
    
    fwrite(game, sizeof(GameState), 1, fp);
    fclose(fp);
    
    printf("\n💾 Game saved successfully!\n");
    printf("\nPress Enter to continue...");
    getchar();
}

int load_game(GameState *game) {
    FILE *fp = fopen("savegame.dat", "rb");
    if (fp == NULL) {
        return 0; // No save file
    }
    
    fread(game, sizeof(GameState), 1, fp);
    fclose(fp);
    
    return 1; // Success
}

void game_over(GameState *game, int won) {
    printf("\n");
    printf("═══════════════════════════════════════\n");
    if (won) {
        printf("       🎉 VICTORY! 🎉\n");
        printf("═══════════════════════════════════════\n");
        printf("\nCongratulations, %s!\n", game->player_name);
        printf("You have found the legendary treasure!\n");
        printf("Your name will be remembered forever!\n");
        printf("\nFinal Health: %d\n", game->health);
    } else {
        printf("       💀 GAME OVER 💀\n");
        printf("═══════════════════════════════════════\n");
        printf("\n%s has fallen...\n", game->player_name);
        printf("Your adventure ends here.\n");
        printf("Better luck next time!\n");
    }
    printf("═══════════════════════════════════════\n\n");
    
    game->game_ended = 1;
}