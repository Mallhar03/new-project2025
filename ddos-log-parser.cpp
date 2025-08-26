#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Trim helper → remove leading and trailing spaces/tabs/newlines
std::string trim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end   = str.find_last_not_of(" \t\n\r");
    if (start == std::string::npos || end == std::string::npos) {
        return "";  // string was all spaces
    }
    return str.substr(start, end - start + 1);
}

int main() {
    std::ifstream logfile("ddos_log.txt");  // open our generated logs
    if (!logfile.is_open()) {
        std::cerr << "Error opening log file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(logfile, line)) {   // read line by line
        std::stringstream ss(line);
        std::string part;
        std::vector<std::string> tokens;

        // split using '|' as delimiter
        while (std::getline(ss, part, '|')) {
            tokens.push_back(trim(part));
        }

        // display parsed tokens
        if (tokens.size() == 3) {
            std::cout << "Timestamp: " << tokens[0] << "\n";
            std::cout << "IP: " << tokens[1] << "\n";
            std::cout << "Attack Type: " << tokens[2] << "\n";
            std::cout << "-----------------------------\n";
        }
    }

    logfile.close();
    return 0;
}
