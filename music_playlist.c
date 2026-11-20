
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of a song (Node)
struct Song {
    char name[100];
    struct Song *next;
    struct Song *prev;
};

// Head and current song pointers
struct Song *head = NULL;
struct Song *current = NULL;

// Function to add a song
void addSong() {
    struct Song *newSong;
    newSong = (struct Song*)malloc(sizeof(struct Song));

    if (newSong == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter song name: ");
    scanf(" %99[^\n]", newSong->name);

    newSong->next = NULL;
    newSong->prev = NULL;

    if (head == NULL) {
        head = newSong;
        current = newSong;
    } else {
        struct Song *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newSong;
        newSong->prev = temp;
    }

    printf("Song added successfully!\n");
}

// Function to display playlist
void displayPlaylist() {
    struct Song *temp = head;

    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("\n----- YOUR MUSIC PLAYLIST -----\n");

    int i = 1;

    while (temp != NULL) {
        printf("%d. %s", i, temp->name);

        if (temp == current) {
            printf("  <-- Currently Playing");
        }

        printf("\n");
        temp = temp->next;
        i++;
    }
}

// Function to delete a song
void deleteSong() {
    char songName[100];
    struct Song *temp = head;

    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("Enter song name to delete: ");
    scanf(" %99[^\n]", songName);

    while (temp != NULL &&
           strcmp(temp->name, songName) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song not found!\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    if (current == temp) {
        current = (temp->next != NULL)
                  ? temp->next : temp->prev;
    }

    free(temp);

    printf("Song deleted successfully!\n");
}

// Function to search a song
void searchSong() {
    char songName[100];
    struct Song *temp = head;

    printf("Enter song name to search: ");
    scanf(" %99[^\n]", songName);

    while (temp != NULL) {
        if (strcmp(temp->name, songName) == 0) {
            printf("Song found: %s\n", temp->name);
            return;
        }

        temp = temp->next;
    }

    printf("Song not found!\n");
}

// Function to play current song
void playSong() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("Now Playing: %s\n", current->name);
}

// Function to play next song
void nextSong() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    if (current->next == NULL) {
        printf("This is the last song!\n");
        return;
    }

    current = current->next;
    playSong();
}

// Function to play previous song
void previousSong() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    if (current->prev == NULL) {
        printf("This is the first song!\n");
        return;
    }

    current = current->prev;
    playSong();
}

// Function to count songs
void countSongs() {
    struct Song *temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Total songs in playlist: %d\n", count);
}

// Function to free memory
void freePlaylist() {
    struct Song *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    current = NULL;
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n========== MUSIC PLAYLIST ==========\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Delete Song\n");
        printf("4. Search Song\n");
        printf("5. Play Current Song\n");
        printf("6. Next Song\n");
        printf("7. Previous Song\n");
        printf("8. Count Songs\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                addSong();
                break;

            case 2:
                displayPlaylist();
                break;

            case 3:
                deleteSong();
                break;

            case 4:
                searchSong();
                break;

            case 5:
                playSong();
                break;

            case 6:
                nextSong();
                break;

            case 7:
                previousSong();
                break;

            case 8:
                countSongs();
                break;

            case 9:
                freePlaylist();
                printf("Thank you for using Music Playlist!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    freePlaylist();
    return 0;
}
