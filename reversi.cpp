/**
 * Praktikum Informatik 1 MMXXIII
 *
 * @file main.cpp
 *
 * Die Funktionen fuer das Spiel Reversi
 */

/**
* @mainpage Reversi
*
* Dokumentation des Spiels Reversi im Rahmen des Praktikums Informatik 1.
*
*/

#include <iostream>
#include <string>
#include "config.h"
#include "test.h"
#include "reversiKI.h"


/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
    for (int j = 0; j < GROESSE_Y; j++)
        {
            for(int i = 0; i < GROESSE_X; i++)
            {
                spielfeld[j][i] = 0;
            }
        }
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
* @brief Ausgabe des Spielfelds auf der Konsole
*
* Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
* Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
*
*  @param spielfeld  Spielfeld, das ausgeben wird
*/
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    std::cout << "   | ";

    //Start bei ASCII 65 = A
    for (int i = 65; i < 65 + GROESSE_X; ++i)
        std::cout << ((char) i) << " | " ;

    std::cout << std::endl;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for(int i = 0; i < GROESSE_X; ++i)
        {
            std::cout << "---+";
        }
        std::cout << "---+" << std::endl;

        std::cout << " " << j + 1 << " |";
        for (int i = 0; i < GROESSE_X; ++i)
        {
            switch (spielfeld[j][i])
            {
                case 0:
                    std::cout << "   " ;
                    break;
                case 1:
                    std::cout << " X ";
                    break;
                case 2:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
                    std::cout << "Abbruch .... " << std::endl;
                    exit(0);
                    break;
            }
            std::cout << "|";
        };  //for i
        std::cout <<  std::endl;
    }  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    int zaehlerSpieler1 = 0;
    int zaehlerSpieler2 = 0;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for (int i = 0; i < GROESSE_X; ++i)
        {
            if (spielfeld[j][i] == 1)
            {
                ++zaehlerSpieler1;
            }
            if (spielfeld[j][i] == 2)
            {
                ++zaehlerSpieler2;
            }

        }
    }

    if (zaehlerSpieler1 == zaehlerSpieler2)
    {
        return 0;
    }
    if (zaehlerSpieler1 < zaehlerSpieler2)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/**
* @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
*
* @param posX Index fuer die Spalte
* @param posY Index fuer die Zeile
* @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
*/
bool aufSpielfeld(const int posX, const int posY)
{
    if((posX < GROESSE_X && posY < GROESSE_Y) && (posX >= 0 && posY >= 0)) return true; 
    // Prueft ob die Position innerhalb des Spielfelds ist.
    return false;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
                                       //               if aktuellerSpieler == 2 -> gegner = 1

    bool obereSeite = false; //
    bool untereSeite = false; //

    if (spielfeld[posY][posX] != 0) // ist das Feld leer? Wenn nein, dann kann man nicht spielen!
    {
        return false;
    }

    // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // Hier erfolgt jetzt Ihre Implementierung ...
            if(spielfeld[posX + j][posY + i] == gegner) // das Feld ist nicht leer und es gibt an der Stelle einen gegnerischen Stein.
            {
                while((posX + j < GROESSE_X && posY + i < GROESSE_Y) && (posX + j >= 0 && posY + i >= 0)) // bleib im Spielfeld
                {
                    if(j < 0 && i < 0) // Richtung links unten
                    {
                        j--; 
                        i--;
                        if(spielfeld[posX + j][posY + i] == aktuellerSpieler)
                            untereSeite = true;
                    }
                    if(j > 0 && i < 0) // Richtung links oben
                    {
                        j++; 
                        i--;
                        if(spielfeld[posX + j][posY + i] == aktuellerSpieler)
                            obereSeite = true;
                    }                    
                    if(j < 0 && i > 0) // Richtung rechts unten
                    {
                        j--; 
                        i++;
                        if(spielfeld[posX + j][posY + i] == aktuellerSpieler)
                            untereSeite = true;
                    }
                    if(j > 0 && i > 0) // Richtung rechts oben
                    {
                        j++; 
                        i++;
                        if(spielfeld[posX + j][posY + i] == aktuellerSpieler)
                            obereSeite = true;
                    }
                }
            }
        }
    }
    return obereSeite || untereSeite; // es muss eine von den Seiten 'true' sein. also einen eigenen Stein in der Seite gefunden werden m 
}


/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler;

    //Alle Richtungen bearbeiten
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // aehnlich wie die Funktion zugGueltig(), aber stellen Sie sicher, das alle gegnerischen Steine in
            // allen Richtungen in Ihre eigenen Steine umgewandelt werden
            if(spielfeld[posX + j][posY + i] == gegner) // das Feld ist nicht leer und es gibt an der Stelle einen gegnerischen Stein.
            {
                while((posX + j < GROESSE_X && posY + i < GROESSE_Y) && (posX + j >= 0 && posY + i >= 0)) // bleib im Spielfeld
                {
                    if(j < 0 && i < 0) // Richtung links unten
                    {
                        j--; 
                        i--;
                        if(spielfeld[posX + j][posY + i] == gegner) // solange es einen gegnerischen Stein gibt, der Stein wird umgewandelt
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                        else if(spielfeld[posX + j][posY + i] == 0) // falls es danach eine leere Position gefunden wird, ist die Position, wo unserer Stein hinkommt.
                        {
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                            break; // jetzt ist es fertig mit dem Zug und Break Schleife
                        }
                    }
                    if(j > 0 && i < 0) // Richtung links oben
                    {
                        j++; 
                        i--;
                        if(spielfeld[posX + j][posY + i] == gegner)
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                        else if(spielfeld[posX + j][posY + i] == 0)
                        {
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                            break;
                        }
                    }                    
                    if(j < 0 && i > 0) // Richtung rechts unten
                    {
                        j--; 
                        i++;
                        if(spielfeld[posX + j][posY + i] == gegner)
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                        else if(spielfeld[posX + j][posY + i] == 0)
                        {
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                            break;
                        }
                    }
                    if(j > 0 && i > 0) // Richtung rechts oben
                    {
                        j++; 
                        i++;
                        if(spielfeld[posX + j][posY + i] == gegner)
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                        else if(spielfeld[posX + j][posY + i] == 0)
                        {
                            spielfeld[posX + j][posY + i] == aktuellerSpieler;
                            break;
                        }
                    }
                }
            }
        }
    }

}

int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    int zuegeZahl = 0;
    for(int posX = 0; posX < GROESSE_X; posX++)
    {
        for(int posY = 0; posY < GROESSE_Y; posY++)
        {
            if(zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
                zuegeZahl++;
        }
    }
    return zuegeZahl;
}


bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }

    int posX;
    int posY;
    std::string symbolSpieler;
    if (aktuellerSpieler == 1)
    {
        symbolSpieler = "X";
    }
    else
    {
        symbolSpieler = "O";
    }

    while (true)
    {
        std::string eingabe;
        std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): " ;
        std::cin >> eingabe;
        posX = (int) eingabe[0] % 32 -1;
        posY = (int) eingabe[1] - 49;

        if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
        {
            // Accept turn
            break;
        }
        else
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
        }
    }

    zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char) (posX + 65) << (posY + 1) << std::endl;

    return true;
}


void spielen(const int spielerTyp[2])
{
    int spielfeld[GROESSE_Y][GROESSE_X];

    //Erzeuge Startaufstellung
    initialisiereSpielfeld(spielfeld);

    int aktuellerSpieler = 1;
    int gegner = 2;
    zeigeSpielfeld(spielfeld);

    // solange noch Zuege bei einem der beiden Spieler moeglich sind
    //
    while(moeglicheZuege(spielfeld, aktuellerSpieler) || moeglicheZuege(spielfeld, gegner)) // spiel weiter solange es einen möglichen Zug gibt.
    {
        if(menschlicherZug(spielfeld, aktuellerSpieler) && computerZug(spielfeld, gegner)) // es muessen beiden Spielern spielen
        {
            continue;
        }
        else
            break;
    }

    switch (gewinner(spielfeld))
    {
        case 0: //
            std::cout << "Unentschieden" << std::endl;
            break;
        case 1: //
            std::cout << spielerTyp[1] << " hat gewonnen!" << std::endl;
            break;
        case 2: //
            std::cout << spielerTyp[2] << " hat gewonnen!" << std::endl;
            break;
        default: //
            std::cout << "Error in gewinner(spielfeld) " << std::endl;
            break;
    }
}

int main()
{
    if (TEST == 1)
    {
        bool gesamtErgebnis = ganzenTestAusfuehren();
        if (gesamtErgebnis == true)
        {
            std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
        }
        else
        {
            std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
            exit(1);
        }
        std::cout << std::endl << std::endl;
    }
    
    // Die folgenden drei Zeilen werden auskommentiert oder geloescht, nachdem Sie die Funktion spielen()
    // implementiert haben (waeren sonst doppelt)
    // int spielfeld[GROESSE_Y][GROESSE_X];

    // initialisiereSpielfeld(spielfeld);

    // zeigeSpielfeld(spielfeld);

    int spielerTyp[2] = { COMPUTER, MENSCH };  // Feld, das Informationen ueber den Typ des Spielers enthaelt. MENSCH(=1) oder COPMUTER(=2)
    spielen(spielerTyp);
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
    
    return 0;
}
