#include <stdio.h>
#include <stdlib.h>

int Move(int fig, int y, int x) {
    switch(fig) {
        case 1: // Rook
            if (y == 0 || x == 0) return 1; 
            break;
        case 2: // Knight
            if ((y == 2 && x == 1) || (y == 1 && x == 2)) return 1;
            break;
        case 3: // Bishop
            if (y == x) return 1; 
            break;
        case 4: // Queen
            if (y == 0 || x == 0 || y == x) return 1; 
            break;
        case 5: // King
            if (y <= 1 && x <= 1) return 1; 
            break;
    }
    return 0;

}

int main() {
    char k1, k2;
    int k1_int, k2_int, fig;
    int x, y;

    printf("Enter the starting position (e.g., a1): ");
    scanf(" %c%d", &k1, &k1_int);
    printf("Enter the ending position (e.g., b2): ");
    scanf(" %c%d", &k2, &k2_int);

    if (k1 < 'a' || k1 > 'h' || k2 < 'a' || k2 > 'h' || k1_int < 1 || k1_int > 8 || k2_int < 1 || k2_int > 8) {
        printf("Invalid input. Please enter valid chess positions.\n");
        return 1;
    }

    printf("Enter the figure (1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen, 5 - King): ");
    scanf("%d", &fig);

    if (fig < 1 || fig > 5) {
        printf("Invalid figure. Please enter a number between 1 and 5.\n");
        return 1;
    }
    
    x = abs(k2 - k1);
    y = abs(k2_int - k1_int);

    if (Move(fig, y, x)) {
        printf("The move is valid.\n");
    } else {
        printf("The move is invalid.\n");

        printf("Other figures can move in the following ways:\n");
        int found = 0;

        for (int i = 1; i <= 5; i++) {
            if (i != fig && Move(i, y, x)) {
                found = 1;
                switch(i) {
                    case 1: printf("Rook can move.\n"); break;
                    case 2: printf("Knight can move.\n"); break;
                    case 3: printf("Bishop can move.\n"); break;
                    case 4: printf("Queen can move.\n"); break;
                    case 5: printf("King can move.\n"); break;
                }
            }
        }
        if (!found) {
            printf("No other figures can move to that position.\n");
        }
    }

    return 0;
}