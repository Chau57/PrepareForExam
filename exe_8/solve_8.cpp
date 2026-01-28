#include <stdio.h>

int cnt;
int chessBoardSize;
int diagonalSize;

void placeQueen(int r, int* Queens, bool* collums, bool* lDiagonals, bool* rDiagonals, bool io) {
    if (r == chessBoardSize) {
        if (!io) {
            ++cnt;
            return;
        }
        for (int i = 0; i < chessBoardSize; ++i) {
            for (int j = 0; j < chessBoardSize; ++j) {
                printf(Queens[i] == j ? "Q " : ". ");
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int c = 0; c < chessBoardSize; ++c) {
        int ld = (r - c + chessBoardSize - 1);
        int rd = (r + c);
        if (collums[c] || lDiagonals[ld] || rDiagonals[rd]) continue;
        
        
        Queens[r] = c;
        collums[c] = true;
        lDiagonals[ld] = true;
        rDiagonals[rd] = true;
        
        placeQueen(r + 1, Queens, collums, lDiagonals, rDiagonals, io);

        Queens[r] = -1;
        collums[c] = false;
        lDiagonals[ld] = false;
        rDiagonals[rd] = false;
    }
}

int main() {
    scanf("%d", &chessBoardSize);
    diagonalSize = (chessBoardSize << 1) - 1;
    int Queens[chessBoardSize];
    bool collums[chessBoardSize] = {false};
    bool lDiagonals[diagonalSize] = {false};
    bool rDiagonals[diagonalSize] = {false};

    cnt = 0;
    placeQueen(0, Queens, collums, lDiagonals, rDiagonals, false);
    printf("%d\n", cnt);
    placeQueen(0, Queens, collums, lDiagonals, rDiagonals, true);
    return 0;
}
