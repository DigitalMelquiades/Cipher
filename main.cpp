#include <iostream>
#include <limits>
#include <string>
// I am not using namespace std, because I am built different
class Cipher {
    std::string text, encrypted, decrypted;
    int shift, operation;
public:
    Cipher(const std::string& text = "", const int& shift = 0) : text(text), shift(shift) {};
    void setText(const std::string& text) { this->text=text; }
    void setShift(const int& shift) { this->shift=shift;}
    void encrypt() {
        for (const char& letter:text) {
            if (letter >= 'A' && letter <= 'Z') encrypted += (letter - 'A' + shift)%26+'A';
            /* To clear things out, I used the following logic of Ceaser Cipher Encryption
            while building one few months ago (I also have Git Repository of that project on
            my private GitHub account, if there will be any concerns I will be glad to chare the code)
            logic is the following to make sure while encrypting we don't go out from the boundary
            (Because we are using ASCII table) we plug in mathematical formula, which ensures that when
            we want to shift last letters form the alphabet while shift is too high for example shift is 3 and letter is Z
            Z will turn into a C and etc.
            */
            else if (letter >= 'a' && letter <= 'z') encrypted += (letter - 'a' + shift)%26+'a'; // Dealing with both, lower and uppercase letters
            else encrypted += letter;
        }
    }
    void decrypt() {
        for (const char& letter:text) {
            if (letter >= 'A' && letter <= 'Z') {
                decrypted += ((letter - 'A' - shift)%26+'A' < 'A') ?
                ((letter - 'A' - shift)%26+'A' + 26) : ((letter - 'A' - shift)%26 +'A');
            }
            else if (letter >= 'a' && letter <= 'z'){
                decrypted += ((letter - 'a' - shift)%26+'a' < 'a') ?
                ((letter - 'a' - shift)%26+'a' + 26) : ((letter - 'a' - shift)%26 +'a');
            }
            else decrypted += letter;
        }
    }
    void decryptBruteForce() {
        for (int i = 1; i < 26; i++) {
            for (const char& letter:text) {
                if (letter >= 'A' && letter <= 'Z') {
                    decrypted += ((letter - 'A' - i)%26+'A' < 'A') ?
                    ((letter - 'A' - i)%26+'A' + 26) : ((letter - 'A' - i)%26 +'A');
                }
                else if (letter >= 'a' && letter <= 'z'){
                    decrypted += ((letter - 'a' - i)%26+'a' < 'a') ?
                    ((letter - 'a' - i)%26+'a' + 26) : ((letter - 'a' - i)%26 +'a');
                }
                else decrypted += letter;
            }
            std::cout<<i<<". "<<decrypted<<std::endl;
            decrypted = "";
        }
    }
    void displayEncrypted() {std::cout<<encrypted<<std::endl;}
    void displayDecrypted() {std::cout<<decrypted<<std::endl;}
    void setOperation(const int& operation) { this->operation = operation; }
    int getOperation() const { return this->operation; }
};

void menu(Cipher& c);
std::string text();
int shift();

int main() {
    Cipher c;
    menu(c);
    return 0;
}
void menu(Cipher& c) {
    int option = 0, operation = 0;
    do {
        std::cout<<"Welcome to Caesar Cipher!\nOptions:\n";
        std::cout<<"1.Operation Selection.\n";
        std::cout<<"2.Run.\n";
        std::cout<<"3.Quit.\n";
        std::cout<<"Choose: ";
        while (!(std::cin >> option) || (option<1 || option>5)) {
            /*By the way, I copied this input validation from the Google, but in my defence
             * 1. We never really did any input validation, hence never learned one
             * 2. Copying is normal thing, like it is programming, at least I am not using AI!!!
             */
            std::cout << "Invalid input. Please try again (input should be an integer between 1-5): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while (option<1 || option>5);
    switch (option) {
    case 1: {
        std::cout<<"Choose which operation to execute:\n";
        std::cout<<"1.Encrypt.\n";
        std::cout<<"2.Decrypt.\n";
        std::cout<<"3.Brute Force Decryption.\n";
        while (!(std::cin >> operation) || (operation<1 || operation>3)) {
            std::cout << "Invalid input. Please try again (Note: input should be an integer between 1-3): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        c.setOperation(operation);
        switch (operation) {
        case 1: {
            c.setText(text());
            c.setShift(shift());
            c.encrypt();
        } break;
        case 2: {
            c.setText(text());
            c.setShift(shift());
            c.decrypt();
        } break;
        case 3: {
            c.setText(text());
        } break;
        default: break;
        }
        menu(c);
    } break;
    case 2: {
        switch (c.getOperation()) {
        case 1: {
            std::cout<<"The Encrypted Text is: ";
            c.displayEncrypted();
        } break;
        case 2: {
            std::cout<<"The Decrypted Text is: ";
            c.displayDecrypted();
        } break;
        case 3: c.decryptBruteForce(); break;
        default: break;
        }
        menu(c);
    } break;
    case 3: {
        std::cout<<"Thanks for using Cipher.\nGoodbye!\n"; // No additional "e" in "goodbye", gotta keep it professional and answer like my previous crush
        break;} return;
    default: break;
    }
}
std::string text() {
    std::string input;
    std::cout<<"Input the text (Note: it has to be larger than 5 characters): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,input);
    while (input.length()<6) {
        std::cout<<"The input text has to be greater than 5 characters!\nTry again: ";
        std::getline(std::cin,input);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}
int shift() {
    int shift;
    std::cout<<"Enter the shift value: ";
    while (!(std::cin >> shift)) {
        std::cout << "Invalid input. Please try again (Note: input should be an integer between 1-3): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return shift;
}