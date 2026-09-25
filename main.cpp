#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

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

bool bauer_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    if (figur == 'B') {
        if (start_spalte == ziel_spalte) {
            if (start_reihe == 6 && ziel_reihe == 4 && brett[5][start_spalte] == '.' && brett[4][start_spalte] == '.') {
                return true; // Erster Zug: zwei Felder nach vorne
            }
            if (ziel_reihe == start_reihe - 1 && brett[ziel_reihe][ziel_spalte] == '.') {
                return true; // Normales Vorwärtsziehen
            }
        } else if (abs(start_spalte - ziel_spalte) == 1 && ziel_reihe == start_reihe - 1) {
            if (brett[ziel_reihe][ziel_spalte] != '.' && islower(brett[ziel_reihe][ziel_spalte])) {
                return true; // Schlagen einer schwarzen Figur
            }
        }
    }

    else if (figur == 'b') {
        if (start_spalte == ziel_spalte) {
            if (start_reihe == 1 && ziel_reihe == 3 && brett[2][start_spalte] == '.' && brett[3][start_spalte] == '.') {
                return true; // Erster Zug: zwei Felder nach vorne
            }
            if (ziel_reihe == start_reihe + 1 && brett[ziel_reihe][ziel_spalte] == '.') {
                return true; // Normales Vporwärtsziehen
            }
        } else if (abs(start_spalte - ziel_spalte) == 1 && ziel_reihe == start_reihe + 1) {
            if (brett[ziel_reihe][ziel_spalte] != '.' && isupper(brett[ziel_reihe][ziel_spalte])) {
                return true; // Schlagen einer weißen Figur
            }
        }
    }

    return false;
}

bool turm_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char gegnerfigur = brett[ziel_reihe][ziel_spalte];

    if (figur != '.' && gegnerfigur != '.' && ((isupper(figur) && isupper(gegnerfigur)) || (islower(figur) && islower(gegnerfigur)))) {
        return false; // Ungültiger Zug: Turm kann nicht auf eine eigene Figur ziehen
    }

    if (start_reihe == ziel_reihe) {
        // Horizontaler Zug
        int min_spalte = std::min(start_spalte, ziel_spalte);
        int max_spalte = std::max(start_spalte, ziel_spalte);
        for (int spalte = min_spalte + 1; spalte < max_spalte; spalte++) {
            if (brett[start_reihe][spalte] != '.') {
                return false; // Ein Hindernis auf dem Weg
            }
        }
        return true;
    } else if (start_spalte == ziel_spalte) {
        // Vertikaler Zug
        int min_reihe = std::min(start_reihe, ziel_reihe);
        int max_reihe = std::max(start_reihe, ziel_reihe);
        for (int reihe = min_reihe + 1; reihe < max_reihe; reihe++) {
            if (brett[reihe][start_spalte] != '.') {
                return false; // Ein Hindernis auf dem Weg
            }
        }
        return true;
    }
    return false; // Ungültiger Turmzug
}

bool springer_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char gegnerfigur = brett[ziel_reihe][ziel_spalte];

    if (figur != '.' && gegnerfigur != '.' && ((isupper(figur) && isupper(gegnerfigur)) || (islower(figur) && islower(gegnerfigur)))) {
        return false; // Ungültiger Zug: Springer kann nicht auf eine eigene Figur ziehen
    }

    int reihen_diff = std::abs(start_reihe - ziel_reihe);
    int spalten_diff = std::abs(start_spalte - ziel_spalte);

    return (reihen_diff == 2 && spalten_diff == 1) || (reihen_diff == 1 && spalten_diff == 2);
}

bool laufer_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char gegnerfigur = brett[ziel_reihe][ziel_spalte];

    if (figur != '.' && gegnerfigur != '.' && ((isupper(figur) && isupper(gegnerfigur)) || (islower(figur) && islower(gegnerfigur)))) {
        return false; // Ungültiger Zug: Läufer kann nicht auf eine eigene Figur ziehen
    }

    int reihen_diff = std::abs(start_reihe - ziel_reihe);
    int spalten_diff = std::abs(start_spalte - ziel_spalte);

    if (reihen_diff != spalten_diff) {
        return false; // Ungültiger Zug: Läufer muss diagonal ziehen
    }

    int reihen_schritt = (ziel_reihe - start_reihe) / reihen_diff;
    int spalten_schritt = (ziel_spalte - start_spalte) / spalten_diff;

    for (int i = 1; i < reihen_diff; i++) {
        int zwischen_reihe = start_reihe + i * reihen_schritt;
        int zwischen_spalte = start_spalte + i * spalten_schritt;
        if (brett[zwischen_reihe][zwischen_spalte] != '.') {
            return false; // Ein Hindernis auf dem Weg
        }
    }
    return true;
}

bool dame_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    return turm_gueltig(brett, figur, start_reihe, start_spalte, ziel_reihe, ziel_spalte) ||
           laufer_gueltig(brett, figur, start_reihe, start_spalte, ziel_reihe, ziel_spalte);
}

// Prüft, ob ein bestimmtes Feld von der gegnerischen Farbe bedroht wird
bool ist_feld_angegriffen(char brett[8][8], int reihe, int spalte, bool ist_weiss) {
    // 1. Prüfe auf Springer (L-Sprung)
    char gegner_springer = ist_weiss ? 's' : 'S';
    int springer_zuege[8][2] = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};
    for (int i = 0; i < 8; i++) {
        int r = reihe + springer_zuege[i][0];
        int s = spalte + springer_zuege[i][1];
        if (r >= 0 && r < 8 && s >= 0 && s < 8 && brett[r][s] == gegner_springer) return true;
    }

    // 2. Prüfe auf König (1 Feld Radius)
    char gegner_koenig = ist_weiss ? 'k' : 'K';
    for (int dr = -1; dr <= 1; dr++) {
        for (int ds = -1; ds <= 1; ds++) {
            if (dr == 0 && ds == 0) continue;
            int r = reihe + dr;
            int s = spalte + ds;
            if (r >= 0 && r < 8 && s >= 0 && s < 8 && brett[r][s] == gegner_koenig) return true;
        }
    }

    // 3. Prüfe auf Bauern (diagonal von vorne)
    if (ist_weiss) { // Wir sind Weiß, Angreifer ist Schwarz ('b')
        int angreifer_r = reihe - 1; // Schwarze Bauern kommen von oben (kleinerer Index)
        if (angreifer_r >= 0) {
            if (spalte - 1 >= 0 && brett[angreifer_r][spalte - 1] == 'b') return true;
            if (spalte + 1 < 8 && brett[angreifer_r][spalte + 1] == 'b') return true;
        }
    } else { // Wir sind Schwarz, Angreifer ist Weiß ('B')
        int angreifer_r = reihe + 1; // Weiße Bauern kommen von unten (größerer Index)
        if (angreifer_r < 8) {
            if (spalte - 1 >= 0 && brett[angreifer_r][spalte - 1] == 'B') return true;
            if (spalte + 1 < 8 && brett[angreifer_r][spalte + 1] == 'B') return true;
        }
    }

    // 4. Prüfe auf gerade Linien (Turm / Dame)
    char gegner_turm = ist_weiss ? 't' : 'T';
    char gegner_dame = ist_weiss ? 'd' : 'D';
    int gerade_richtungen[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    for (int i = 0; i < 4; i++) {
        int r = reihe + gerade_richtungen[i][0];
        int s = spalte + gerade_richtungen[i][1];
        while (r >= 0 && r < 8 && s >= 0 && s < 8) {
            if (brett[r][s] != '.') {
                if (brett[r][s] == gegner_turm || brett[r][s] == gegner_dame) return true;
                break; // Durch eigene oder andere gegnerische Figur blockiert
            }
            r += gerade_richtungen[i][0];
            s += gerade_richtungen[i][1];
        }
    }

    // 5. Prüfe auf diagonale Linien (Läufer / Dame)
    char gegner_laeufer = ist_weiss ? 'l' : 'L';
    int diagonal_richtungen[4][2] = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
    for (int i = 0; i < 4; i++) {
        int r = reihe + diagonal_richtungen[i][0];
        int s = spalte + diagonal_richtungen[i][1];
        while (r >= 0 && r < 8 && s >= 0 && s < 8) {
            if (brett[r][s] != '.') {
                if (brett[r][s] == gegner_laeufer || brett[r][s] == gegner_dame) return true;
                break;
            }
            r += diagonal_richtungen[i][0];
            s += diagonal_richtungen[i][1];
        }
    }

    return false;
}

// Prüft, ob der König der aktuellen Farbe im Schach steht
bool ist_schach(char brett[8][8], bool ist_weiss) {
    char koenig = ist_weiss ? 'K' : 'k';
    for (int r = 0; r < 8; r++) {
        for (int s = 0; s < 8; s++) {
            if (brett[r][s] == koenig) {
                return ist_feld_angegriffen(brett, r, s, ist_weiss);
            }
        }
    }
    return false; // Sicherheitshalber, falls König nicht gefunden wird
}

// Hilfsfunktion: Prüft die grundlegende Bewegung (ohne Schach-Prüfung)
bool ist_grundsaetzlich_gueltig(char brett[8][8], char figur, int sr, int ss, int zr, int zs) {
    char f = std::tolower(figur);
    if (f == 'b') return bauer_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 't') return turm_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 's') return springer_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 'l') return laufer_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 'd') return dame_gueltig(brett, figur, sr, ss, zr, zs);
    
    // König-Logik: Darf sich genau 1 Feld in jede Richtung bewegen
    if (f == 'k') {
        int reihen_diff = std::abs(sr - zr);
        int spalten_diff = std::abs(ss - zs);
        return (reihen_diff <= 1 && spalten_diff <= 1 && (reihen_diff + spalten_diff > 0));
    }
    return false;
}

void zug_machen(char brett[8][8], int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char figur = brett[start_reihe][start_spalte];
    if (figur == '.') {
        std::cout << "Dort steht keine Figur!\n";
        return;
    }

    bool ist_weiss = isupper(figur);

    // 1. Grundlegende Zugregeln prüfen
    if (!ist_grundsaetzlich_gueltig(brett, figur, start_reihe, start_spalte, ziel_reihe, ziel_spalte)) {
        std::cout << "Zug ist nach Grundregeln ungültig.\n";
        return;
    }

    // 2. Zug simulieren (auf dem echten Brett, wir machen es gleich rückgängig)
    char gemerkte_ziel_figur = brett[ziel_reihe][ziel_spalte];
    brett[ziel_reihe][ziel_spalte] = figur;
    brett[start_reihe][start_spalte] = '.';

    // 3. Prüfen, ob der eigene König jetzt im Schach steht
    if (ist_schach(brett, ist_weiss)) {
        std::cout << "Zug ist ungültig: Dein König stünde im Schach!\n";
        // 4. Zug rückgängig machen (Undo)
        brett[start_reihe][start_spalte] = figur;
        brett[ziel_reihe][ziel_spalte] = gemerkte_ziel_figur;
        return;
    }

    // 5. Wenn alles okay ist, ist der Zug gültig und bleibt bestehen!
    std::cout << "Zug ist gültig.\n";
    
    // Optional: Bauern-Umwandlung hier später einfügen
    if (std::tolower(figur) == 'b' && (ziel_reihe == 0 || ziel_reihe == 7)) {
        brett[ziel_reihe][ziel_spalte] = ist_weiss ? 'D' : 'd'; // Automatisch zur Dame
        std::cout << "Bauer wurde zur Dame befördert!\n";
    }
}



void input_zug(char brett[8][8], std::string start_zug, std::string ziel_zug) {
    int start_reihe = '8' - start_zug[1];
    int start_spalte = start_zug[0] - 'a';
    int ziel_reihe = '8' - ziel_zug[1];
    int ziel_spalte = ziel_zug[0] - 'a';

    std::cout << "Versuche Zug von " << start_zug << " nach " << ziel_zug << " (Array: [" 
              << start_reihe << "][" << start_spalte << "] -> [" << ziel_reihe << "][" << ziel_spalte << "])\n";

    zug_machen(brett, start_reihe, start_spalte, ziel_reihe, ziel_spalte);
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
    
    //zug_machen(brett, 6, 4, 4, 4);
    //zug_machen(brett, 1, 3, 3, 3);
    //zug_machen(brett, 4, 4, 3, 3);
    while (true) {
        std::string z1,z2;
        std::cout << "Was willst du bewegen?: ";
        std::cin >> z1;
        std::cout << "Wohin willst du es bewegen?: ";
        std::cin >> z2;
        input_zug(brett, z1, z2);

        std::cout << "--- Nach 1. e2-e4 ---";
        zeige_brett(brett);
    }
    
    //input_zug(brett, "e7", "e5");

    /*char figur = brett[6][4];      // Figur auf e2 "aufheben"
    brett[6][4] = '.';             // e2 wird leer
    brett[4][4] = figur;           // Figur auf e4 "abstellen"

    std::cout << "--- Nach 1. e2-e4 ---";
    zeige_brett(brett);
    */

    

    return 0;
}