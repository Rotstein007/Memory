#ifndef MEMORY_SPIEL_H
#define MEMORY_SPIEL_H

#include <gtk/gtk.h>
#include <vector>
#include <memory>
#include <random>
#include "MemorySpiel.h"

class MemorySpiel {
public:
    static int spielAusfuehren(int argc, char** argv);
    static inline std::mt19937 generator{std::random_device{}()};

    int currentScore;      // Aktueller Punktestand
    int highScore;         // Höchster Punktestand

    MemorySpiel();         // Konstruktor
    void showHighScore();  // Methode zur Anzeige des Highscores

private:
    static void onButtonKlick(GtkWidget* widget, gpointer daten);
    static void feldHinzufuegen();
    static void zeigeSequenz();
    static void spielZuruecksetzen(GtkWidget* widget, gpointer daten);
    static void spielStarten(GtkApplication* app, gpointer benutzerDaten);

    static inline std::vector<int> sequenz;
    static inline int aktuellerIndex = 0;
    static inline GtkWidget* buttons[9];
    static inline GtkWidget* gameOverLabel;
    static inline GtkWidget* playAgainButton;
    static inline bool spielAktiv = true;
};

#endif