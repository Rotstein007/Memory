#include <gtk/gtk.h>
#include <iostream>
#include <memory>

class Listenelement {
public:
    int wert;
    std::unique_ptr<Listenelement> naechstes;

    explicit Listenelement(int wert) : wert(wert), naechstes(nullptr) {}
};

class VerknuepfteListe {
public:
    std::unique_ptr<Listenelement> erstesElement;
    Listenelement* letztesElement;

    VerknuepfteListe() : erstesElement(nullptr), letztesElement(nullptr) {}

    void hinzufuegen(int wert) {
        auto neuesElement = std::make_unique<Listenelement>(wert);
        if (!erstesElement) {
            erstesElement = std::move(neuesElement);
            letztesElement = erstesElement.get();
        } else {
            letztesElement->naechstes = std::move(neuesElement);
            letztesElement = letztesElement->naechstes.get();
        }
    }
};

class MemorySpiel {
public:
    static void onButtonKlick(GtkWidget* widget, gpointer daten) {
        int buttonIndex = GPOINTER_TO_INT(daten);
        std::cout << "Button " << buttonIndex << " geklickt" << std::endl;
    }

    static void spielStarten(GtkApplication* app, gpointer benutzerDaten) {
        GtkWidget* fenster = gtk_application_window_new(app);
        gtk_window_set_title(GTK_WINDOW(fenster), "Memory Spiel");
        gtk_window_set_default_size(GTK_WINDOW(fenster), 400, 400);

        GtkWidget* hauptBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
        gtk_window_set_child(GTK_WINDOW(fenster), hauptBox);

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

                g_signal_connect(feld, "clicked", G_CALLBACK(MemorySpiel::onButtonKlick), GINT_TO_POINTER(index));
                gtk_grid_attach(GTK_GRID(spielfeld), feld, spalte, zeile, 1, 1);
            }
        }

        gtk_window_present(GTK_WINDOW(fenster));
    }

    int spielAusfuehren(int argc, char** argv) {
        GtkApplication* app = gtk_application_new("org.gtk.memoryspiel", G_APPLICATION_DEFAULT_FLAGS);
        g_signal_connect(app, "activate", G_CALLBACK(spielStarten), nullptr);
        int status = g_application_run(G_APPLICATION(app), argc, argv);
        g_object_unref(app);
        return status;
    }
};

int main(int argc, char** argv) {
    MemorySpiel spiel;
    return spiel.spielAusfuehren(argc, argv);
}