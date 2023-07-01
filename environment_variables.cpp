#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    std::ifstream file(".env");
    std::unordered_map<std::string, std::string> envVars;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Skip empty lines or lines starting with '#'
            if (line.empty() || line[0] == '#') {
                continue;
            }

            // Find the position of the '=' character
            size_t equalsPos = line.find('=');
            if (equalsPos != std::string::npos) {
                std::string key = line.substr(0, equalsPos);
                std::string value = line.substr(equalsPos + 1);

                // Store the key-value pair in the map
                envVars[key] = value;
            }
        }

        file.close();

        // Print the extracted environment variables
        for (const auto& pair : envVars) {
            std::cout << pair.second << std::endl;
        }
    } else {
        std::cerr << "Failed to open .env file." << std::endl;
    }

    return 0;
}