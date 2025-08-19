#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const std::string FILENAME = "users.txt";


bool usernameExists(const std::string& username) {
    std::ifstream file(FILENAME);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        getline(ss, storedUsername, ','); 
        if (storedUsername == username) {
            return true;
        }
    }
    return false;
}


void registerUser() {
    std::string username, password;
    std::cout << "\n--- Registration ---" << std::endl;
    std::cout << "Enter a new username: ";
    std::cin >> username;

    if (usernameExists(username)) {
        std::cout << "Username already exists. Please try a different one." << std::endl;
        return;
    }

    std::cout << "Enter a password: ";
    std::cin >> password;

    
    std::ofstream file(FILENAME, std::ios::app);
    if (file.is_open()) {
        file << username << "," << password << "\n";
        file.close();
        std::cout << "Registration successful!" << std::endl;
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}


void loginUser() {
    std::string username, password;
    std::cout << "\n--- Login ---" << std::endl;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::ifstream file(FILENAME);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open user database. No users registered yet?" << std::endl;
        return;
    }

    std::string line;
    bool loggedIn = false;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');

        if (storedUsername == username && storedPassword == password) {
            loggedIn = true;
            break;
        }
    }

    if (loggedIn) {
        std::cout << "Login successful! Welcome, " << username << "." << std::endl;
    } else {
        std::cout << "Invalid username or password." << std::endl;
    }
}

int main() {
    int choice;
    while (true) {
        std::cout << "\n--- Main Menu ---" << std::endl;
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}