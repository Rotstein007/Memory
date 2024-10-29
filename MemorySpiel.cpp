#include "MemorySpiel.h"
#include <iostream>
#include <random>

MemorySpiel::MemorySpiel() : currentScore(0), highScore(0) {}

void MemorySpiel::showHighScore() {
    std::string message = "Your High Score: " + std::to_string(highScore);
}

void MemorySpiel::onButtonKlick(GtkWidget* widget, gpointer daten) {
    if (!spielAktiv) return;

    int buttonIndex = GPOINTER_TO_INT(daten);
    if (buttonIndex == sequenz[aktuellerIndex]) {
        aktuellerIndex++;
        if (aktuellerIndex >= sequenz.size()) {
            aktuellerIndex = 0;
            feldHinzufuegen();
            zeigeSequenz();
        }
    } else {
        spielAktiv = false;
        gtk_label_set_text(GTK_LABEL(gameOverLabel), "Game Over!");
        gtk_widget_set_visible(playAgainButton, true);
    }
}

void MemorySpiel::feldHinzufuegen() {
    std::uniform_int_distribution<int> distribution(0, 8);
    int neuesFeld = distribution(generator);
    sequenz.push_back(neuesFeld);
}

void MemorySpiel::zeigeSequenz() {
    for (size_t i = 0; i < sequenz.size(); ++i) {
        int index = sequenz[i];
        g_timeout_add(500 * (i + 1), [](gpointer data) -> gboolean {
            auto [feld, sequenzPosition] = *static_cast<std::pair<GtkWidget*, size_t>*>(data);
            gtk_widget_add_css_class(feld, "highlight");
            g_timeout_add(300, [](gpointer data) -> gboolean {
                gtk_widget_remove_css_class(static_cast<GtkWidget*>(data), "highlight");
                return G_SOURCE_REMOVE;
            }, feld);
            delete static_cast<std::pair<GtkWidget*, size_t>*>(data);
            return G_SOURCE_REMOVE;
        }, new std::pair<GtkWidget*, size_t>(buttons[index], i));
    }
}

void MemorySpiel::spielZuruecksetzen(GtkWidget* /*widget*/, gpointer /*data*/) {
    sequenz.clear();
    aktuellerIndex = 0;
    spielAktiv = true;

    gtk_label_set_text(GTK_LABEL(gameOverLabel), "");
    gtk_widget_set_visible(playAgainButton, false);

    feldHinzufuegen();
    zeigeSequenz();
}

void MemorySpiel::spielStarten(GtkApplication* app, gpointer benutzerDaten) {
    GtkWidget* fenster = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(fenster), "Memory Spiel");
    gtk_window_set_default_size(GTK_WINDOW(fenster), 400, 500);

    GtkWidget* hauptBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_window_set_child(GTK_WINDOW(fenster), hauptBox);

    gtk_widget_set_margin_top(hauptBox, 20);
    gtk_widget_set_margin_bottom(hauptBox, 20);
    gtk_widget_set_margin_start(hauptBox, 20);
    gtk_widget_set_margin_end(hauptBox, 20);

    GtkWidget* spielfeld = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(spielfeld), 10);
    gtk_grid_set_column_spacing(GTK_GRID(spielfeld), 10);

    gtk_widget_set_halign(spielfeld, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(spielfeld, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(hauptBox), spielfeld);

    for (int zeile = 0; zeile < 3; ++zeile) {
        for (int spalte = 0; spalte < 3; ++spalte) {
            int index = zeile * 3 + spalte;
            GtkWidget* feld = gtk_button_new();
            gtk_widget_set_size_request(feld, 100, 100);
            buttons[index] = feld;

            g_signal_connect(feld, "clicked", G_CALLBACK(MemorySpiel::onButtonKlick), GINT_TO_POINTER(index));
            gtk_grid_attach(GTK_GRID(spielfeld), feld, spalte, zeile, 1, 1);
        }
    }

    gameOverLabel = gtk_label_new("");
    gtk_widget_set_halign(gameOverLabel, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(hauptBox), gameOverLabel);

    playAgainButton = gtk_button_new_with_label("Play Again");
    gtk_widget_set_halign(playAgainButton, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(playAgainButton, false);
    gtk_box_append(GTK_BOX(hauptBox), playAgainButton);

    g_signal_connect(playAgainButton, "clicked", G_CALLBACK(spielZuruecksetzen), nullptr);

    GtkCssProvider* cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(cssProvider, ".highlight { background-color: lightblue; }");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
        GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(cssProvider);

    feldHinzufuegen();
    zeigeSequenz();

    gtk_window_present(GTK_WINDOW(fenster));
}

int MemorySpiel::spielAusfuehren(int argc, char** argv) {
    GtkApplication* app = gtk_application_new("org.gtk.memoryspiel", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(spielStarten), nullptr);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}