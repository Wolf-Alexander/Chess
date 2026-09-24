#include <iostream>

// Funktion, um das Brett hübsch auf dem Bildschirm auszugeben
void zeige_brett(char brett[8][8]) {
    std::cout << "\n  a b c d e f g h\n";
    
    // Wir gehen die 8 Reihen durch (von 0 bis 7)
    for (int reihe = 0; reihe < 8; reihe++) {
        // Wir geben die Zahlen 8 bis 1 aus (Reihe 0 ist die 8. Reihe)
        std::cout << 8 - reihe << " "; 
        
        // Nun gehen wir die 8 Spalten durch
        for (int spalte = 0; spalte < 8; spalte++) {
            std::cout << brett[reihe][spalte] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n\n";
}

void zug_machen(char brett[8][8], int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char figur = brett[start_reihe][start_spalte];
    brett[start_reihe][start_spalte] = '.';
    brett[ziel_reihe][ziel_spalte] = figur;
}


bool bauer_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    if (figur == 'B') {
        if()
    }

    return false;
}

int main() {
    // 1. Wir erschaffen ein leeres 8x8 Schachbrett
    char brett[8][8];

    // 2. Wir füllen es komplett mit '.' (Punkt = leeres Feld)
    for (int reihe = 0; reihe < 8; reihe++) {
        for (int spalte = 0; spalte < 8; spalte++) {
            brett[reihe][spalte] = '.';
        }
    }

    // 3. Wir stellen die Figuren auf (Startposition)
    // Weiße Figuren (Reihe 7 ist die 1. Reihe auf dem Brett)
    brett[7][0] = 'T'; brett[7][1] = 'S'; brett[7][2] = 'L'; brett[7][3] = 'D';
    brett[7][4] = 'K'; brett[7][5] = 'L'; brett[7][6] = 'S'; brett[7][7] = 'T';
    
    for (int i = 0; i < 8; i++) brett[6][i] = 'B'; // Weiße Bauern

    // Schwarze Figuren (Reihe 0 ist die 8. Reihe auf dem Brett)
    brett[0][0] = 't'; brett[0][1] = 's'; brett[0][2] = 'l'; brett[0][3] = 'd';
    brett[0][4] = 'k'; brett[0][5] = 'l'; brett[0][6] = 's'; brett[0][7] = 't';
    
    for (int i = 0; i < 8; i++) brett[1][i] = 'b'; // Schwarze Bauern

    // 4. Brett ausgeben
    std::cout << "--- Startposition ---";
    zeige_brett(brett);
    
    zug_machen(brett, 6, 4, 4, 4);
    zug_machen(brett, 0, 0, 3, 4);
    /*char figur = brett[6][4];      // Figur auf e2 "aufheben"
    brett[6][4] = '.';             // e2 wird leer
    brett[4][4] = figur;           // Figur auf e4 "abstellen"

    std::cout << "--- Nach 1. e2-e4 ---";
    zeige_brett(brett);
    */

    std::cout << "--- Nach 1. e2-e4 ---";
    zeige_brett(brett);

    return 0;
}