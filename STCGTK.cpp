#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

// Function to format uptime into days, hours, minutes, and seconds
std::string formatUptime(double uptime_seconds) {
    int days = static_cast<int>(uptime_seconds / 86400);
    uptime_seconds = static_cast<int>(uptime_seconds) % 86400;

    int hours = static_cast<int>(uptime_seconds / 3600);
    uptime_seconds = static_cast<int>(uptime_seconds) % 3600;

    int minutes = static_cast<int>(uptime_seconds / 60);
    int seconds = static_cast<int>(uptime_seconds) % 60;

    std::ostringstream formatted_time;
    formatted_time << days << " days, "
                   << std::setfill('0') << std::setw(2) << hours << " hours, "
                   << std::setw(2) << minutes << " minutes, "
                   << std::setw(2) << seconds << " seconds";
    return formatted_time.str();
}

std::string getUptime() {
    const std::string uptime_file = "/proc/uptime";
    std::ifstream file(uptime_file);

    if (!file.is_open()) {
        return "Error: Unable to open uptime file.";
    }

    double uptime_seconds = 0.0;
    file >> uptime_seconds; // Read the first value (uptime in seconds)
    file.close();

    return formatUptime(uptime_seconds);
}

class UptimeWindow : public Gtk::Window {
public:
    UptimeWindow() {
        set_title("System Uptime Checker");
        set_default_size(300, 100);

        // Set up the label
        label.set_text(getUptime());
        label.set_margin(10);
        label.set_justify(Gtk::JUSTIFY_CENTER);

        // Set up the refresh button
        button.set_label("Refresh");
        button.signal_clicked().connect(sigc::mem_fun(*this, &UptimeWindow::on_button_clicked));

        // Add components to the box
        box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        box.set_spacing(10);
        box.set_margin(10);
        box.append(label);
        box.append(button);

        // Add box to the window
        set_child(box);
    }

protected:
    void on_button_clicked() {
        label.set_text(getUptime());
    }

private:
    Gtk::Box box;
    Gtk::Label label;
    Gtk::Button button;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.example.uptimechecker");

    UptimeWindow window;

    return app->run(window);
}
