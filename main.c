#include <gtk/gtk.h>

static void
activate (GtkApplication *app, gpointer) {
    GtkWidget *window;
    GtkWidget *label;

    // Erstellen Sie ein neues Fenster
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Memory Game");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    // Setzen Sie die Standardgröße des Fensters
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600); // 800x600 als Beispielauflösung

    // Erstellen Sie ein neues Label
    label = gtk_label_new ("Memory Game");
    gtk_window_set_child (GTK_WINDOW (window), label);

    // Zeigen Sie das Fenster an
    gtk_widget_show (window);
}

int
main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    // Erstellen Sie eine neue GTK-Anwendung
    app = gtk_application_new ("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    // Starten Sie die GTK-Anwendung
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
