#include <iostream>
#include <map>
#include <stdexcept>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class MorseCodeTranslator {
protected:
    map<char, string> charToMorse;
    map<string, char> morseToChar;

public:
    MorseCodeTranslator() {
        charToMorse['A'] = ".-";
        charToMorse['B'] = "-...";
        charToMorse['C'] = "-.-.";
        charToMorse['D'] = "-..";
        charToMorse['E'] = ".";
        charToMorse['F'] = "..-.";
        charToMorse['G'] = "--.";
        charToMorse['H'] = "....";
        charToMorse['I'] = "..";
        charToMorse['J'] = ".---";
        charToMorse['K'] = "-.-";
        charToMorse['L'] = ".-..";
        charToMorse['M'] = "--";
        charToMorse['N'] = "-.";
        charToMorse['O'] = "---";
        charToMorse['P'] = ".--.";
        charToMorse['Q'] = "--.-";
        charToMorse['R'] = ".-.";
        charToMorse['S'] = "...";
        charToMorse['T'] = "-";
        charToMorse['U'] = "..-";
        charToMorse['V'] = "...-";
        charToMorse['W'] = ".--";
        charToMorse['X'] = "-..-";
        charToMorse['Y'] = "-.--";
        charToMorse['Z'] = "--..";
        charToMorse[' '] = "/"; // For Space
        charToMorse['1'] = ".----";
        charToMorse['2'] = "..---";
        charToMorse['3'] = "...--";
        charToMorse['4'] = "....-";
        charToMorse['5'] = ".....";
        charToMorse['6'] = "-....";
        charToMorse['7'] = "--...";
        charToMorse['8'] = "---..";
        charToMorse['9'] = "----.";
        charToMorse['0'] = "-----";
        charToMorse['.'] = ".-.-.-";
        charToMorse[','] = "--..--";
        charToMorse['?'] = "..--..";
        charToMorse['!'] = "-.-.--";

        for (const auto& pair : charToMorse) {
            morseToChar[pair.second] = pair.first;
        }
    }

    string translateChar(char ch) const {
        // Convert the character to uppercase
        ch = toupper(ch);
        if (charToMorse.find(ch) != charToMorse.end()) {
            return charToMorse.at(ch);
        } else {
            throw invalid_argument("Invalid character: " + string(1, ch));
        }
    }

    string translateString(const string& text) const {
        string result;
        for (char ch : text) {
            if (ch != ' ') {
                result += translateChar(ch) + " ";
            } else {
                result += "/";
            }
        }
        return result;
    }

    string translateMorseToText(const std::string& morse) const {
        string result;
        string currentMorse;
        for (char ch : morse) {
            if (ch == ' ' || ch == '/') {
                if (!currentMorse.empty()) {
                    if (morseToChar.find(currentMorse) != morseToChar.end()) {
                        result += morseToChar.at(currentMorse);
                    } else {
                        result += '?';
                    }
                    currentMorse.clear();
                }
                if (ch == '/') {
                    result += ' ';
                }
            } else {
                currentMorse += ch;
            }
        }
        return result;
    }

    void displayMorseCodeTable() const {
        cout << "Morse Code Table:\n";
        for (const auto& pair : charToMorse) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

};

class UserAccount {
private:
    string username;
    string password;
    string securityQuestion;
    string securityAnswer;
    vector<std::string> translations;

public:
    UserAccount(const string& username, const string& password, const string& securityQuestion, const string& securityAnswer)
        : username(username), password(password), securityQuestion(securityQuestion), securityAnswer(securityAnswer) {}

    string getUsername() const {
        return username;
    }

    bool checkPassword(const string& passwordToCheck) const {
        return password == passwordToCheck;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    void setSecurityQuestion(const string& newSecurityQuestion) {
        securityQuestion = newSecurityQuestion;
    }

    string getSecurityQuestion() const {
        return securityQuestion;
    }

    void setSecurityAnswer(const string& newSecurityAnswer) {
        securityAnswer = newSecurityAnswer;
    }

    string getSecurityAnswer() const {
        return securityAnswer;
    }

    void addTranslation(const std::string& translation) {
        translations.push_back(translation);
    }

    const vector<std::string>& getTranslations() const {
        return translations;
    }

    void displayTranslations() const {
        if (translations.empty()) {
            cout << "No translations found for this user.\n\n";
        } else {
            cout << "Translations for user \"" << username << "\":\n";
            for (const auto& translation : translations) {
                cout << translation << "\n";
            }
            cout << "\n";
        }
    }
};

int main() {
    cout << "Welcome to the Morse Code Translator with User Accounts\n\n";

    MorseCodeTranslator morseTranslator;
    vector<UserAccount> userAccounts;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Log In\n";
        cout << "3. Reset Password\n";
        cout << "4. View Translations\n";
        cout << "5. Display the Morse code table\n";
        cout << "6. Exit\n";

        cout << "Choose an option: ";
        int option;
        cin >> option;
        cin.ignore();

        if (option == 1) {
            cout << "\nCreating Account\n";
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            // Check if username already exists
            auto it = find_if(userAccounts.begin(), userAccounts.end(), [&username](const UserAccount& user) {
                return user.getUsername() == username;
            });
            if (it != userAccounts.end()) {
                cout << "Username already exists. Please choose another.\n\n";
                continue;
            }

            cout << "Enter password: ";
            string password;
            getline(cin, password);

            cout << "Enter security question: ";
            string securityQuestion;
            getline(cin, securityQuestion);

            cout << "Enter security answer: ";
            string securityAnswer;
            getline(cin, securityAnswer);

            // Create the account
            userAccounts.emplace_back(username, password, securityQuestion, securityAnswer);
            cout << "Account created successfully!\n\n";
        } else if (option == 2) {
            cout << "\nLogging In\n";
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            auto it = find_if(userAccounts.begin(), userAccounts.end(), [&username](const UserAccount& user) {
                return user.getUsername() == username;
            });
            if (it == userAccounts.end()) {
                cout << "Username not found.\n\n";
                continue;
            }

            cout << "Enter password: ";
            string password;
            getline(cin, password);

            if (!it->checkPassword(password)) {
                cout << "Incorrect password.\n\n";
                continue;
            }

            cout << "Login successful!\n";
            cout << "Enter '1' to translate text: \nEnter'2' to translate Morse to text: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1) {

                cout << "Enter text to translate to Morse code: ";
                string inputText;
                getline(cin, inputText);

                string morseText = morseTranslator.translateString(inputText);
                cout << "Morse code for \"" << inputText << "\": " << morseText << "\n\n";

                it->addTranslation(morseText);

            } else if (choice == 2) {
                // Take input Morse code from the user
                cout << "Enter Morse code to translate to text: ";
                string morseInput;
                getline(cin, morseInput);

                // Translate Morse code to text
                string text = morseTranslator.translateMorseToText(morseInput);
                cout << "Text for Morse code \"" << morseInput << "\": " << text << "\n\n";

                // Add translation to user account
                it->addTranslation(text);
            } else {
                cout << "Invalid choice.\n\n";
            }
        } else if (option == 3) {
            cout << "\nResetting Password\n";
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            // Find the user account
            auto it = find_if(userAccounts.begin(), userAccounts.end(), [&username](const UserAccount& user) {
                return user.getUsername() == username;
            });
            if (it == userAccounts.end()) {
                cout << "Username not found.\n\n";
                continue;
            }

            // Ask security question
            cout << "Security Question: " << it->getSecurityQuestion() << "\n";
            cout << "Enter security answer: ";
            string securityAnswer;
            getline(cin, securityAnswer);

            if (securityAnswer == it->getSecurityAnswer()) {
                // Security answer is correct, allow password reset
                cout << "Security answer is correct. Enter new password: ";
                string newPassword;
                getline(cin, newPassword);

                it->setPassword(newPassword);
                cout << "Password reset successful!\n\n";
            } else {
                cout << "Incorrect security answer. Password reset failed.\n\n";
            }
        } else if (option == 4) {
            cout << "\nDisplaying User Translations\n";
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            auto it = find_if(userAccounts.begin(), userAccounts.end(), [&username](const UserAccount& user) {
                return user.getUsername() == username;
            });
            if (it == userAccounts.end()) {
                cout << "Username not found.\n\n";
                continue;
            }

            it->displayTranslations();
        } else if (option == 5) {
            cout << "The Morse Code Table\n";
            morseTranslator.displayMorseCodeTable();
        } else if (option == 6) {
            cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Please choose again.\n\n";
        }
    }

    return 0;
}
