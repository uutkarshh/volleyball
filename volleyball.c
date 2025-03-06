#include <stdio.h>
#include <string.h>

struct Match {
    int matchNumber;
    char team1[50];
    char team2[50];
    int scoreTeam1;
    int scoreTeam2;
};

void createMatch();
void displayMatches();
void updateMatch();
void deleteMatch();

int main() {
    int choice;

    do {
        printf("\nVolleyball Scorecard System\n");
        printf("1. Create Match\n");
        printf("2. Display Matches\n");
        printf("3. Update Match\n");
        printf("4. Delete Match\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createMatch();
                break;
            case 2:
                displayMatches();
                break;
            case 3:
                updateMatch();
                break;
            case 4:
                deleteMatch();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void createMatch() {
    struct Match match;

    printf("Enter match number: ");
    scanf("%d", &match.matchNumber);
    printf("Enter team 1: ");
    scanf("%49s", match.team1);
    printf("Enter team 2: ");
    scanf("%49s", match.team2);
    printf("Enter score for team 1: ");
    scanf("%d", &match.scoreTeam1);
    printf("Enter score for team 2: ");
    scanf("%d", &match.scoreTeam2);

    FILE *file = fopen("matches.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d %s %s %d %d\n", match.matchNumber, match.team1, match.team2, match.scoreTeam1, match.scoreTeam2);

    fclose(file);

    printf("Match created successfully.\n");
}

void displayMatches() {
    FILE *file = fopen("matches.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Match match;
    printf("\nVolleyball Matches:\n");
    
    while (fscanf(file, "%d %s %s %d %d", &match.matchNumber, match.team1, match.team2, &match.scoreTeam1, &match.scoreTeam2) != EOF) {
        printf("Match Number: %d, Team 1: %s, Team 2: %s, Score: %d - %d\n", match.matchNumber, match.team1, match.team2, match.scoreTeam1, match.scoreTeam2);
    }

    fclose(file);
}

void updateMatch() {
    int matchNumber;

    printf("Enter match number to update: ");
    scanf("%d", &matchNumber);

    FILE *file = fopen("matches.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int matchExists = 0;
    struct Match match;

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %s %s %d %d", &match.matchNumber, match.team1, match.team2, &match.scoreTeam1, &match.scoreTeam2) != EOF) {
        if (match.matchNumber == matchNumber) {
            matchExists = 1;
            printf("Enter new score for team 1: ");
            scanf("%d", &match.scoreTeam1);
            printf("Enter new score for team 2: ");
            scanf("%d", &match.scoreTeam2);
            fprintf(tempFile, "%d %s %s %d %d\n", match.matchNumber, match.team1, match.team2, match.scoreTeam1, match.scoreTeam2);
        } else {
            fprintf(tempFile, "%d %s %s %d %d\n", match.matchNumber, match.team1, match.team2, match.scoreTeam1, match.scoreTeam2);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("matches.txt");
    rename("temp.txt", "matches.txt");

    if (!matchExists) {
        printf("Error: Match with match number %d not found.\n", matchNumber);
    } else {
        printf("Match updated successfully.\n");
    }
}

void deleteMatch() {
    int matchNumber;

    printf("Enter match number to delete: ");
    scanf("%d", &matchNumber);

    FILE *file = fopen("matches.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int matchExists = 0;
    struct Match match;

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %s %s %d %d", &match.matchNumber, match.team1, match.team2, &match.scoreTeam1, &match.scoreTeam2) != EOF) {
        if (match.matchNumber != matchNumber) {
            fprintf(tempFile, "%d %s %s %d %d\n", match.matchNumber, match.team1, match.team2, match.scoreTeam1, match.scoreTeam2);
        } else {
            matchExists = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("matches.txt");
    rename("temp.txt", "matches.txt");

    if (!matchExists) {
        printf("Error: Match with match number %d not found.\n", matchNumber);
    } else {
        printf("Match deleted successfully.\n");
    }
}
