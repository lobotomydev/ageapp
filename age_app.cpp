#include <gtk/gtk.h>
#include <string>
#include <iostream>

class AgeApp {
private:
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *age_entry;

public:
    AgeApp() {
        create_main_window();
    }

    void create_main_window() {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Age Input App");
        gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        main_box = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window), main_box);

        // Центр
        GtkWidget *center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_halign(center_box, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(center_box, GTK_ALIGN_CENTER);
        gtk_fixed_put(GTK_FIXED(main_box), center_box, 125, 100);

        GtkWidget *age_label = gtk_label_new("Enter your age:");
        gtk_box_pack_start(GTK_BOX(center_box), age_label, FALSE, FALSE, 0);

        age_entry = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(age_entry), 15);
        gtk_entry_set_alignment(GTK_ENTRY(age_entry), 0.5);
        gtk_box_pack_start(GTK_BOX(center_box), age_entry, FALSE, FALSE, 0);
        g_signal_connect(age_entry, "activate", G_CALLBACK(on_submit_clicked), this);

        GtkWidget *submit_button = gtk_button_new_with_label("Submit");
        gtk_widget_set_size_request(submit_button, 100, 30);
        gtk_box_pack_start(GTK_BOX(center_box), submit_button, FALSE, FALSE, 0);
        g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_clicked), this);

        gtk_widget_grab_focus(age_entry);
    }

    void show_age_result(int age) {
        GtkWidget *dialog = gtk_dialog_new_with_buttons(
            "Age Result",
            GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            "Close",
            GTK_RESPONSE_CLOSE,
            NULL
        );

        gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 150);

        std::string result_text = "Your age: " + std::to_string(age);
        GtkWidget *result_label = gtk_label_new(result_text.c_str());

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        gtk_container_add(GTK_CONTAINER(content_area), result_label);

        gtk_widget_show_all(dialog);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    void run() {
        gtk_widget_show_all(window);
        gtk_main();
    }

    static void on_submit_clicked(GtkWidget *widget, gpointer data) {
        AgeApp *app = static_cast<AgeApp*>(data);

        const char *age_text = gtk_entry_get_text(GTK_ENTRY(app->age_entry));
        std::string age_str(age_text);

        if (age_str.empty()) {
            GtkWidget *dialog = gtk_message_dialog_new(
                GTK_WINDOW(app->window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_WARNING,
                GTK_BUTTONS_OK,
                "Please enter your age!"
            );
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        try {
            int age = std::stoi(age_str);
            if (age < 0) {
                GtkWidget *dialog = gtk_message_dialog_new(
                    GTK_WINDOW(app->window),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_ERROR,
                    GTK_BUTTONS_OK,
                    "Age cannot be negative!"
                );
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                return;
            }

            app->show_age_result(age);
        } catch (const std::exception &e) {
            GtkWidget *dialog = gtk_message_dialog_new(
                GTK_WINDOW(app->window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Please enter a valid number!"
            );
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
};

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    AgeApp app;
    app.run();
    return 0;
}
