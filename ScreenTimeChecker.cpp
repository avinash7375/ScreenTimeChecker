#include <iostream>
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

int main() {
    const std::string uptime_file = "/proc/uptime";
    std::ifstream file(uptime_file);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open " << uptime_file << "\n";
        return 1;
    }

    double uptime_seconds = 0.0;
    file >> uptime_seconds; // Read the first value (uptime in seconds)
    file.close();

    std::cout << "System Uptime: " << formatUptime(uptime_seconds) << "\n";
    return 0;
}
