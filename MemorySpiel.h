#include <random>
#include <vector>
#include <gtk/gtk.h>
#include <fstream>

class MemorySpiel {
public:
    static int spielAusfuehren(int argc, char** argv);
    static inline std::mt19937 generator{std::random_device{}()};

    static int currentScore;      // Aktueller Punktestand
    static int highScore;         // Höchster Punktestand

    MemorySpiel();         // Konstruktor
    void showHighScore();  // Methode zur Anzeige des Highscores

private:
    static void onButtonKlick(GtkWidget* widget, gpointer daten);
    static void feldHinzufuegen();
    static void zeigeSequenz();
    static void spielZuruecksetzen(GtkWidget* widget, gpointer daten);
    static void spielStarten(GtkApplication* app, gpointer benutzerDaten);
    static void loadHighScore();
    static void saveHighScore();
    static void onInfoButtonClicked(GtkWidget* widget, gpointer data);

    static inline std::vector<int> sequenz;
    static inline int aktuellerIndex = 0;
    static inline GtkWidget* buttons[9];
    static inline GtkWidget* gameOverLabel;
    static inline GtkWidget* playAgainButton;
    static inline GtkWidget* scoreLabel;  // Combined score label
    static inline GtkWidget* spielfeld;   // Field with buttons
    static inline GtkWidget* startLabel;  // Start label
    static inline bool spielAktiv = true;
    static inline bool zeigeSequenzAktiv = false;  // New flag to indicate if sequence is being shown
};