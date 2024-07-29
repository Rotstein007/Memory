#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct linked_list_elem {
    int data;
    struct linked_list_elem * next;
};
struct linked_list {
    struct linked_list_elem * first;
    struct linked_list_elem * last;
};

static gboolean button_clicked_async(gpointer data) {
    int button_index = GPOINTER_TO_INT(data);
    printf("Button %d clicked\n", button_index);
    return G_SOURCE_CONTINUE;  // oder G_SOURCE_REMOVE, je nachdem, ob der Idle-Handler entfernt werden soll
}

static void button_clicked(GtkWidget *widget, gpointer data) {
    int button_index = GPOINTER_TO_INT(data);
    g_print("Button %d clicked\n", button_index);  // Verwenden Sie g_print für GTK-Anwendungen
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *buttons[3][3];

    // Erstellen Sie ein neues Fenster
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Memory Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400); // Festgelegte Fenstergröße

    // Erstellen Sie ein GtkGrid
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // Setzen Sie den Abstand im Grid
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    // Fügen Sie Buttons zum Grid hinzu
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = gtk_button_new();
            gtk_widget_set_size_request(buttons[i][j], 100, 100);  // Festgelegte Button-Größe
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(i * 3 + j));
        }
    }

    // Zentrieren Sie das Grid im Fenster
    gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);

    // Zeigen Sie das Fenster an
    gtk_widget_set_visible(window, TRUE);
}

int main(int argc, char **argv) {
    // Initialisieren Sie den Zufallszahlengenerator
    srand(time(NULL));

    // Erstellen Sie eine neue GTK-Anwendung
    GtkApplication * app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Starten Sie die GTK-Anwendung
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
