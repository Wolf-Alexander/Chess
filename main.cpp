#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

void zeige_brett(char brett[8][8]) {
    std::cout << "\n  a b c d e f g h\n";
    
    for (int reihe = 0; reihe < 8; reihe++) {
        std::cout << 8 - reihe << " "; 
        
        for (int spalte = 0; spalte < 8; spalte++) {
            std::cout << brett[reihe][spalte] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n\n";
}

bool bauer_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte, int ep_reihe, int ep_spalte) {
    if (figur == 'B') { // Weißer Bauer
        if (start_spalte == ziel_spalte) {
            if (start_reihe == 6 && ziel_reihe == 4 && brett[5][start_spalte] == '.' && brett[4][start_spalte] == '.') {
                return true; // Erster Zug: zwei Felder nach vorne
            }
            if (ziel_reihe == start_reihe - 1 && brett[ziel_reihe][ziel_spalte] == '.') {
                return true; // Normales Vorwärtsziehen
            }
        } else if (abs(start_spalte - ziel_spalte) == 1 && ziel_reihe == start_reihe - 1) {
            // Normaler Schlag
            if (brett[ziel_reihe][ziel_spalte] != '.' && islower(brett[ziel_reihe][ziel_spalte])) {
                return true; // Schlagen einer schwarzen Figur
            }
            // En Passant Schlag: Zielfeld ist leer, aber es ist das markierte En-Passant-Feld
            if (brett[ziel_reihe][ziel_spalte] == '.' && ziel_reihe == ep_reihe && ziel_spalte == ep_spalte) {
                return true; 
            }
        }
    }
    else if (figur == 'b') { // Schwarzer Bauer
        if (start_spalte == ziel_spalte) {
            if (start_reihe == 1 && ziel_reihe == 3 && brett[2][start_spalte] == '.' && brett[3][start_spalte] == '.') {
                return true; // Erster Zug: zwei Felder nach vorne
            }
            if (ziel_reihe == start_reihe + 1 && brett[ziel_reihe][ziel_spalte] == '.') {
                return true; // Normales Vorwärtsziehen
            }
        } else if (abs(start_spalte - ziel_spalte) == 1 && ziel_reihe == start_reihe + 1) {
            // Normaler Schlag
            if (brett[ziel_reihe][ziel_spalte] != '.' && isupper(brett[ziel_reihe][ziel_spalte])) {
                return true; // Schlagen einer weißen Figur
            }
            // En Passant Schlag
            if (brett[ziel_reihe][ziel_spalte] == '.' && ziel_reihe == ep_reihe && ziel_spalte == ep_spalte) {
                return true; 
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

bool koenig_gueltig(char brett[8][8], char figur, int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte) {
    char gegnerfigur = brett[ziel_reihe][ziel_spalte];

    if (figur != '.' && gegnerfigur != '.' && ((isupper(figur) && isupper(gegnerfigur)) || (islower(figur) && islower(gegnerfigur)))) {
        return false; // Ungültiger Zug: König kann nicht auf eine eigene Figur ziehen
    }

    int reihen_diff = std::abs(start_reihe - ziel_reihe);
    int spalten_diff = std::abs(start_spalte - ziel_spalte);

    return (reihen_diff <= 1 && spalten_diff <= 1 && (reihen_diff + spalten_diff > 0));
}

// Prüft, ob ein bestimmtes Feld von der gegnerischen Farbe bedroht wird
bool ist_feld_angegriffen(char brett[8][8], int reihe, int spalte, bool ist_weiss) {
    char gegner_springer = ist_weiss ? 's' : 'S';
    int springer_zuege[8][2] = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};
    for (int i = 0; i < 8; i++) {
        int r = reihe + springer_zuege[i][0];
        int s = spalte + springer_zuege[i][1];
        if (r >= 0 && r < 8 && s >= 0 && s < 8 && brett[r][s] == gegner_springer) return true;
    }

    char gegner_koenig = ist_weiss ? 'k' : 'K';
    for (int dr = -1; dr <= 1; dr++) {
        for (int ds = -1; ds <= 1; ds++) {
            if (dr == 0 && ds == 0) continue;
            int r = reihe + dr;
            int s = spalte + ds;
            if (r >= 0 && r < 8 && s >= 0 && s < 8 && brett[r][s] == gegner_koenig) return true;
        }
    }

    if (ist_weiss) {
        int angreifer_r = reihe - 1;
        if (angreifer_r >= 0) {
            if (spalte - 1 >= 0 && brett[angreifer_r][spalte - 1] == 'b') return true;
            if (spalte + 1 < 8 && brett[angreifer_r][spalte + 1] == 'b') return true;
        }
    } else {
        int angreifer_r = reihe + 1;
        if (angreifer_r < 8) {
            if (spalte - 1 >= 0 && brett[angreifer_r][spalte - 1] == 'B') return true;
            if (spalte + 1 < 8 && brett[angreifer_r][spalte + 1] == 'B') return true;
        }
    }

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
    return false;
}

bool ist_grundsaetzlich_gueltig(char brett[8][8], char figur, int sr, int ss, int zr, int zs, int ep_reihe, int ep_spalte) {
    char f = std::tolower(figur);
    if (f == 'b') return bauer_gueltig(brett, figur, sr, ss, zr, zs, ep_reihe, ep_spalte);
    if (f == 't') return turm_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 's') return springer_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 'l') return laufer_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 'd') return dame_gueltig(brett, figur, sr, ss, zr, zs);
    if (f == 'k') return koenig_gueltig(brett, figur, sr, ss, zr, zs);
    return false;
}

bool ist_rochade_gueltig(char brett[8][8], bool ist_weiss, bool ist_kurz, bool king_moved, bool rook_moved) {
    if (king_moved || rook_moved) return false;

    int koenig_reihe = ist_weiss ? 7 : 0;
    if (ist_schach(brett, ist_weiss)) return false;

    if (ist_kurz) {
        if (brett[koenig_reihe][5] != '.' || brett[koenig_reihe][6] != '.') return false;
        
        if (ist_feld_angegriffen(brett, koenig_reihe, 5, ist_weiss)) return false;
        if (ist_feld_angegriffen(brett, koenig_reihe, 6, ist_weiss)) return false;
        
        return true;
    } else {
        if (brett[koenig_reihe][1] != '.' || brett[koenig_reihe][2] != '.' || brett[koenig_reihe][3] != '.') return false;
        
        if (ist_feld_angegriffen(brett, koenig_reihe, 3, ist_weiss)) return false;
        if (ist_feld_angegriffen(brett, koenig_reihe, 2, ist_weiss)) return false;
        
        return true;
    }
}

// Prüft, ob der aktuelle Spieler noch irgendeinen gültigen Zug hat (für Schachmatt/Patt)
bool hat_gueltige_zuege(char brett[8][8], bool ist_weiss, int ep_reihe, int ep_spalte,
                        bool wking_moved, bool bking_moved, 
                        bool w_rook_a_moved, bool w_rook_h_moved, 
                        bool b_rook_a_moved, bool b_rook_h_moved) {
    
    for (int sr = 0; sr < 8; sr++) {
        for (int ss = 0; ss < 8; ss++) {
            char figur = brett[sr][ss];
            
            if (figur == '.') continue;
            if (ist_weiss && std::islower(figur)) continue;
            if (!ist_weiss && std::isupper(figur)) continue;

            for (int zr = 0; zr < 8; zr++) {
                for (int zs = 0; zs < 8; zs++) {
                    
                    if (ist_grundsaetzlich_gueltig(brett, figur, sr, ss, zr, zs, ep_reihe, ep_spalte)) {
                        
                        // Sonderfall: Rochade als möglicher Ausweg aus dem Schach
                        if (std::tolower(figur) == 'k' && std::abs(ss - zs) == 2) {
                            bool ist_kurz = (zs > ss);
                            bool king_moved = ist_weiss ? wking_moved : bking_moved;
                            bool rook_moved = ist_weiss ? (ist_kurz ? w_rook_h_moved : w_rook_a_moved) 
                                                        : (ist_kurz ? b_rook_h_moved : b_rook_a_moved);
                            
                            if (ist_rochade_gueltig(brett, ist_weiss, ist_kurz, king_moved, rook_moved)) {
                                return true;
                            }
                        } 
                        else {
                            char gemerkte_ziel_figur = brett[zr][zs];
                            char gemerkte_ep_bauer = '.';
                            bool ist_en_passant = (std::tolower(figur) == 'b' && ss != zs && brett[zr][zs] == '.');

                            // Zug temporär ausführen (Simulieren)
                            brett[zr][zs] = figur;
                            brett[sr][ss] = '.';
                            if (ist_en_passant) {
                                gemerkte_ep_bauer = brett[sr][zs];
                                brett[sr][zs] = '.';
                            }

                            // König noch in Schach?
                            if (!ist_schach(brett, ist_weiss)) {
                                // Zug war erfolgreich und sicher -> Rückgängig machen und true zurückgeben
                                brett[sr][ss] = figur;
                                brett[zr][zs] = gemerkte_ziel_figur;
                                if (ist_en_passant) brett[sr][zs] = gemerkte_ep_bauer;
                                return true; 
                            }

                            // Zug war ungültig (führt zu Schach) -> Rückgängig machen und weiterprobieren
                            brett[sr][ss] = figur;
                            brett[zr][zs] = gemerkte_ziel_figur;
                            if (ist_en_passant) brett[sr][zs] = gemerkte_ep_bauer;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void zug_machen(char brett[8][8], int start_reihe, int start_spalte, int ziel_reihe, int ziel_spalte, 
                bool &ist_weiss_am_zug, int &ep_reihe, int &ep_spalte, 
                bool &wking_moved, bool &bking_moved, 
                bool &w_rook_a_moved, bool &w_rook_h_moved, 
                bool &b_rook_a_moved, bool &b_rook_h_moved) {
    
    char figur = brett[start_reihe][start_spalte];
    if (figur == '.') {
        std::cout << "Dort steht keine Figur!\n";
        return;
    }

    if (std::isupper(figur) && !ist_weiss_am_zug) {
        std::cout << "Es ist Schwarz am Zug, aber du versuchst eine weiße Figur zu bewegen!\n";
        return;
    }
    if (std::islower(figur) && ist_weiss_am_zug) {
        std::cout << "Es ist Weiß am Zug, aber du versuchst eine schwarze Figur zu bewegen!\n";
        return;
    }

    bool ist_weiss = isupper(figur);

    if (std::tolower(figur) == 'k' && std::abs(start_spalte - ziel_spalte) == 2) {
        bool ist_kurz = (ziel_spalte > start_spalte);
        
        bool king_moved = ist_weiss ? wking_moved : bking_moved;
        bool rook_moved = ist_weiss ? (ist_kurz ? w_rook_h_moved : w_rook_a_moved) 
                                    : (ist_kurz ? b_rook_h_moved : b_rook_a_moved);

        if (!ist_rochade_gueltig(brett, ist_weiss, ist_kurz, king_moved, rook_moved)) {
            std::cout << "Rochade ist hier ungültig!\n";
            return; // Kein Zugwechsel bei ungültiger Rochade
        }

        // Rochade ausführen (König bewegen)
        brett[ziel_reihe][ziel_spalte] = figur;
        brett[start_reihe][start_spalte] = '.';

        // Rochade ausführen (Turm bewegen)
        int turm_start_spalte = ist_kurz ? 7 : 0;
        int turm_ziel_spalte = ist_kurz ? 5 : 3;
        char turm = brett[start_reihe][turm_start_spalte];
        
        brett[start_reihe][turm_ziel_spalte] = turm;
        brett[start_reihe][turm_start_spalte] = '.';

        std::cout << "Rochade erfolgreich ausgeführt!\n";

        // Flags dauerhaft aktualisieren
        if (ist_weiss) {
            wking_moved = true;
            if (ist_kurz) w_rook_h_moved = true; else w_rook_a_moved = true;
        } else {
            bking_moved = true;
            if (ist_kurz) b_rook_h_moved = true; else b_rook_a_moved = true;
        }

        ist_weiss_am_zug = !ist_weiss_am_zug;
        return; 
    }

    if (!ist_grundsaetzlich_gueltig(brett, figur, start_reihe, start_spalte, ziel_reihe, ziel_spalte, ep_reihe, ep_spalte)) {
        std::cout << "Zug ist nach Grundregeln ungültig.\n";
        return;
    }

    // Prüfen, ob es sich um einen En Passant-Schlag handelt
    bool ist_en_passant = false;
    if (std::tolower(figur) == 'b' && start_spalte != ziel_spalte && brett[ziel_reihe][ziel_spalte] == '.') {
        ist_en_passant = true;
    }

    char gemerkte_ziel_figur = brett[ziel_reihe][ziel_spalte];
    char gemerkter_ep_bauer = '.';
    
    brett[ziel_reihe][ziel_spalte] = figur;
    brett[start_reihe][start_spalte] = '.';
    
    if (ist_en_passant) {
        gemerkter_ep_bauer = brett[start_reihe][ziel_spalte];
        brett[start_reihe][ziel_spalte] = '.';
    }

    if (ist_schach(brett, ist_weiss)) {
        std::cout << "Zug ist ungültig: Dein König stünde im Schach!\n";
        brett[start_reihe][start_spalte] = figur;
        brett[ziel_reihe][ziel_spalte] = gemerkte_ziel_figur;
        if (ist_en_passant) {
            brett[start_reihe][ziel_spalte] = gemerkter_ep_bauer;
        }
        return;
    }

    std::cout << "Zug ist gültig.\n";
    
    // En Passant-Status für den NÄCHSTEN Spieler setzen
    int naechste_ep_reihe = -1;
    int naechste_ep_spalte = -1;
    if (std::tolower(figur) == 'b' && std::abs(start_reihe - ziel_reihe) == 2) {
        naechste_ep_reihe = start_reihe + (ziel_reihe - start_reihe) / 2; // Das Feld, das übersprungen wurde
        naechste_ep_spalte = start_spalte;
    }
    ep_reihe = naechste_ep_reihe;
    ep_spalte = naechste_ep_spalte;

     // Bauern-Umwandlung
    if (std::tolower(figur) == 'b' && (ziel_reihe == 0 || ziel_reihe == 7)) {
        char umwandlung;
        
        if (ist_weiss) { 
            // Weißer Bauer erreicht die 8. Reihe (Index 0)
            std::cout << "Bauer erreicht die letzte Reihe! Bitte wähle eine Figur (D, T, L, S): ";
            std::cin >> umwandlung;
            
            // Mache die Eingabe sicherheitshalber groß, falls der Nutzer 'd' statt 'D' tippt
            umwandlung = std::toupper(umwandlung); 
            
            if (umwandlung == 'D' || umwandlung == 'T' || umwandlung == 'L' || umwandlung == 'S') {
                brett[ziel_reihe][ziel_spalte] = umwandlung;
            } else {
                std::cout << "Ungültige Wahl. Standardmäßig wird zur Dame (D) umgewandelt.\n";
                brett[ziel_reihe][ziel_spalte] = 'D';
            }
        } else { 
            // Schwarzer Bauer erreicht die 1. Reihe (Index 7)
            std::cout << "Bauer erreicht die letzte Reihe! Bitte wähle eine Figur (d, t, l, s): ";
            std::cin >> umwandlung;
            
            // Mache die Eingabe sicherheitshalber klein, falls der Nutzer 'D' statt 'd' tippt
            umwandlung = std::tolower(umwandlung); 
            
            if (umwandlung == 'd' || umwandlung == 't' || umwandlung == 'l' || umwandlung == 's') {
                brett[ziel_reihe][ziel_spalte] = umwandlung;
            } else {
                std::cout << "Ungültige Wahl. Standardmäßig wird zur Dame (d) umgewandelt.\n";
                brett[ziel_reihe][ziel_spalte] = 'd';
            }
        }
        std::cout << "Bauer wurde befördert!\n";
    }

    
    if (gemerkte_ziel_figur == 'T') {
        if (ziel_spalte == 0) w_rook_a_moved = true;
        if (ziel_spalte == 7) w_rook_h_moved = true;
    }
    if (gemerkte_ziel_figur == 't') {
        if (ziel_spalte == 0) b_rook_a_moved = true;
        if (ziel_spalte == 7) b_rook_h_moved = true;
    }

    if (figur == 'K') wking_moved = true;
    if (figur == 'k') bking_moved = true;
    
    if (figur == 'T') {
        if (start_spalte == 0) w_rook_a_moved = true;
        if (start_spalte == 7) w_rook_h_moved = true;
    }
    if (figur == 't') {
        if (start_spalte == 0) b_rook_a_moved = true;
        if (start_spalte == 7) b_rook_h_moved = true;
    }

    ist_weiss_am_zug = !ist_weiss_am_zug;
}

bool input_zug(char brett[8][8], std::string start_zug, std::string ziel_zug, 
               int &ep_reihe, int &ep_spalte, bool &ist_weiss_am_zug, 
               bool &wking_moved, bool &bking_moved, 
               bool &w_rook_a_moved, bool &w_rook_h_moved, 
               bool &b_rook_a_moved, bool &b_rook_h_moved) {
    int start_reihe = '8' - start_zug[1];
    int start_spalte = start_zug[0] - 'a';
    int ziel_reihe = '8' - ziel_zug[1];
    int ziel_spalte = ziel_zug[0] - 'a';

    std::cout << "Versuche Zug von " << start_zug << " nach " << ziel_zug << "\n";

    bool alter_zug_weiss = ist_weiss_am_zug;
    
    zug_machen(brett, start_reihe, start_spalte, ziel_reihe, ziel_spalte, 
               ist_weiss_am_zug, ep_reihe, ep_spalte, 
               wking_moved, bking_moved, 
               w_rook_a_moved, w_rook_h_moved, 
               b_rook_a_moved, b_rook_h_moved);
    
    // Wenn sich ist_weiss_am_zug geändert hat, war der Zug gültig
    return (ist_weiss_am_zug != alter_zug_weiss);
}

int main() {
    char brett[8][8];

    for (int reihe = 0; reihe < 8; reihe++) {
        for (int spalte = 0; spalte < 8; spalte++) {
            brett[reihe][spalte] = '.';
        }
    }

    brett[7][0] = 'T'; brett[7][1] = 'S'; brett[7][2] = 'L'; brett[7][3] = 'D';
    brett[7][4] = 'K'; brett[7][5] = 'L'; brett[7][6] = 'S'; brett[7][7] = 'T';
    for (int i = 0; i < 8; i++) brett[6][i] = 'B'; // Weiße Bauern

    brett[0][0] = 't'; brett[0][1] = 's'; brett[0][2] = 'l'; brett[0][3] = 'd';
    brett[0][4] = 'k'; brett[0][5] = 'l'; brett[0][6] = 's'; brett[0][7] = 't';
    for (int i = 0; i < 8; i++) brett[1][i] = 'b'; // Schwarze Bauern

    // 4. Brett ausgeben
    std::cout << "--- Startposition ---";
    zeige_brett(brett);
    
    // Status-Variablen für das Spiel initialisieren
    int ep_reihe = -1;
    int ep_spalte = -1;
    bool ist_weiss_am_zug = true; // Weiß beginnt immer
    bool spiel_beendet = false;

    // Rochade-Flags initialisieren
    bool wking_moved = false, bking_moved = false;
    bool w_rook_a_moved = false, w_rook_h_moved = false;
    bool b_rook_a_moved = false, b_rook_h_moved = false;

    while (!spiel_beendet) {
        if (ist_weiss_am_zug) {
            std::cout << "\n>>> WEISS ist am Zug <<<\n";
        } else {
            std::cout << "\n>>> SCHWARZ ist am Zug <<<\n";
        }

        std::string z1, z2;
        std::cout << "Was willst du bewegen? (z.B. e2): ";
        std::cin >> z1;
        std::cout << "Wohin willst du es bewegen? (z.B. e4): ";
        std::cin >> z2;
        
        // Prüfe, ob der Zug gültig war
        bool zug_war_gueltig = input_zug(brett, z1, z2, ep_reihe, ep_spalte, 
                      ist_weiss_am_zug, wking_moved, bking_moved, 
                      w_rook_a_moved, w_rook_h_moved, 
                      b_rook_a_moved, b_rook_h_moved);

        std::cout << "--- Aktuelles Brett ---";
        zeige_brett(brett);

        // NUR bei gültigen Zügen auf Schachmatt/Patt prüfen!
        if (zug_war_gueltig) {
            // ist_weiss_am_zug wurde bereits gewechselt, also ist der NÄCHSTE Spieler am Zug
            bool naechster_spieler_ist_weiss = ist_weiss_am_zug;

            if (ist_schach(brett, naechster_spieler_ist_weiss)) {
                // König steht im Schach
                if (!hat_gueltige_zuege(brett, naechster_spieler_ist_weiss, ep_reihe, ep_spalte,
                                        wking_moved, bking_moved, 
                                        w_rook_a_moved, w_rook_h_moved, 
                                        b_rook_a_moved, b_rook_h_moved)) {
                    std::cout << "\n========================================\n";
                    std::cout << "   SCHACHMATT! " << (naechster_spieler_ist_weiss ? "SCHWARZ" : "WEISS") << " GEWINNT!\n";
                    std::cout << "========================================\n";
                    spiel_beendet = true;
                } else {
                    std::cout << "\n>>> ACHTUNG: SCHACH! <<<\n";
                }
            } else {
                // König steht NICHT im Schach (Patt)
                if (!hat_gueltige_zuege(brett, naechster_spieler_ist_weiss, ep_reihe, ep_spalte,
                                        wking_moved, bking_moved, 
                                        w_rook_a_moved, w_rook_h_moved, 
                                        b_rook_a_moved, b_rook_h_moved)) {
                    std::cout << "\n========================================\n";
                    std::cout << "   PATT! Das Spiel endet unentschieden.\n";
                    std::cout << "========================================\n";
                    spiel_beendet = true;
                }
            }
        }
    }
    
    return 0;
}