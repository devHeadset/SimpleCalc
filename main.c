#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *entry;

void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    gchar *endptr;

    if (g_strcmp0(button_label, "=") == 0) {
        // Evaluate the expression
        gdouble result = g_ascii_strtod(current_text, &endptr);
        if (*endptr == '\0') {
            gchar *result_str = g_strdup_printf("%g", result);
            gtk_entry_set_text(GTK_ENTRY(entry), result_str);
            g_free(result_str);
        } else {
            gtk_entry_set_text(GTK_ENTRY(entry), "Error");
        }
    } else if (g_strcmp0(button_label, "C") == 0) {
        // Clear the entry
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        // Append the button label to the entry text
        gchar *new_text = g_strconcat(current_text, button_label, NULL);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
        g_free(new_text);
    }
}

GtkWidget* create_button(const gchar *label) {
    GtkWidget *button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    return button;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    gchar *labels[] = {"7", "8", "9", "/",
                       "4", "5", "6", "*",
                       "1", "2", "3", "-",
                       "0", ".", "=", "+",
                       "C"};
    
    int pos = 0;
    for (int row = 1; row <= 5; row++) {
        for (int col = 0; col < 4; col++) {
            if (pos >= 17) break;
            GtkWidget *button = create_button(labels[pos++]);
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
        }
    }

    gtk_container_add(GTK_CONTAINER(window), grid);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

