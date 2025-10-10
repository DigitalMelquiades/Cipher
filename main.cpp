#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
// I am not using namespace std, because I am built different
class Cipher {
    char* text; char* encrypted; char* decrypted;
    int* shift; int* operation; int* len;
public:
    Cipher() { text = nullptr; shift = new int(0); encrypted = nullptr; decrypted = nullptr; len = nullptr; }
    ~Cipher() { delete[] text; delete[] encrypted; delete[] decrypted; delete shift; delete operation; delete len; }
    void setText(char* text) { this->text = text; }
    void setShift(int* shift) { this->shift = shift; }
    void encrypt() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        encrypted = new char[*len];
        int* it = new int(0);
        for((*it) = 0; (*it)<(*len); (*it)++){
            if (text[*it] >= 'A' && text[*it] <= 'Z') encrypted[*it] = ((*shift) + text[*it] - 'A')%26 + 'A';
            else if (text[*it] >= 'a' && text[*it] <= 'z') encrypted[*it] = ((*shift) + (text[*it] - 'a'))%26 + 'a'; // Dealing with both, lower and uppercase letters
            else encrypted[*it] = text[*it];
        }
        delete it;
    }
    void decrypt() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        decrypted = new char[*len];
        int* it = new int(0);
        for(*it = 0; (*it)<(*len); (*it)++){
            if (text[*it] >= 'A' && text[*it] <= 'Z') {
                decrypted[*it] = ((text[*it] - 'A' - *shift)%26+'A' < 'A') ?
                ((text[*it] - 'A' - *shift)%26+'A' + 26) : ((text[*it] - 'A' - *shift)%26 +'A');
            }
            else if (text[*it] >= 'a' && text[*it] <= 'z') {
                decrypted[*it] = ((text[*it] - 'a' - *shift)%26+'a' < 'a') ?
                ((text[*it] - 'a' - *shift)%26+'a' + 26) : ((text[*it] - 'a' - *shift)%26 +'a');
            }
            else decrypted[*it] = text[*it];
        }
        delete it;
    }
    void encryptBruteForce() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        int* shifts = new int(0);
        for (*shifts = 1; (*shifts) < 26; (*shifts)++) {
            encrypted = new char[*len];
            int* it = new int(0);
            for((*it) = 0; (*it)<(*len); (*it)++){
                if (text[*it] >= 'A' && text[*it] <= 'Z') encrypted[*it] = ((*shifts) + text[*it] - 'A')%26 + 'A';
                else if (text[*it] >= 'a' && text[*it] <= 'z') encrypted[*it] = ((*shifts) + (text[*it] - 'a'))%26 + 'a'; // Dealing with both, lower and uppercase letters
                else encrypted[*it] = text[*it];
            }
            std::cout<< (*shifts)<<". ";
            for (char* letter = encrypted; letter<encrypted+(*len); letter++) std::cout<<*letter; std::cout<<std::endl;
            delete it; delete[] encrypted;
        }
        delete shifts;
    }
    void decryptBruteForce() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        int* shifts = new int(0);
        for (*shifts = 1; (*shifts)<26; (*shifts)++) {
            decrypted = new char[*len];
            int* it = new int(0);
            for((*it) = 0; (*it)<(*len); (*it)++){
                if (text[*it] >= 'A' && text[*it] <= 'Z') {
                    decrypted[*it] = ((text[*it] - 'A' - (*shifts))%26+'A' < 'A') ?
                    ((text[*it] - 'A' - (*shifts))%26+'A' + 26) : ((text[*it] - 'A' - (*shifts))%26 +'A');
                }
                else if (text[*it] >= 'a' && text[*it] <= 'z') {
                    decrypted[*it] = ((text[*it] - 'a' - (*shifts))%26+'a' < 'a') ?
                    ((text[*it] - 'a' - (*shifts))%26+'a' + 26) : ((text[*it] - 'a' - (*shifts))%26 +'a');
                }
                else decrypted[*it] = text[*it];
            }
            std::cout<< (*shifts)<<". ";
            for (char* letter = decrypted; letter<decrypted+(*len); letter++) std::cout<<*letter; std::cout<<std::endl;
            delete it; delete[] decrypted;
        }
        delete shifts;
    }
    void displayEncrypted() { for (char* letter = encrypted; letter<encrypted+(*len); letter++) std::cout<<*letter; std::cout<<std::endl; }
    void displayDecrypted() { for (char* letter = decrypted; letter<decrypted+(*len); letter++) std::cout<<*letter; std::cout<<std::endl; }
    void setOperation(int* operation) { this->operation = operation; }
    int getOperation() const { return *this->operation; }
    void quit() {
        delete[] encrypted; delete[] decrypted; delete[] text;
        delete len; delete shift; delete operation;
    }
};

void menu(Cipher* c);
char* text();
int* shift();

int main() {
    Cipher* c = new Cipher();
    menu(c);
    delete c;
    return 0;
}
void menu(Cipher* c) {
    int* option = new int(0); int* operation = new int(0);
    do {
        std::cout<<"Welcome to Caesar Cipher!\nOptions:\n";
        std::cout<<"1.Operation Selection.\n";
        std::cout<<"2.Quit.\n";
        std::cout<<"Choose: ";
        while (!(std::cin >> *option) || (*option<1 || *option>5)) {
            /*By the way, I copied this input validation from the Google, but in my defence
             * 1. We never really did any input validation, hence never learned one
             * 2. Copying is normal thing, like it is programming, at least I am not using AI!!!
             */
            std::cout << "Invalid input. Please try again (input should be an integer between 1-5): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while (*option < 1 || *option > 2);
    switch (*option) {
    case 1: {
        std::cout<<"Choose which operation to execute:\n";
        std::cout<<"1.Encrypt.\n";
        std::cout<<"2.Decrypt.\n";
        std::cout<<"3.Brute Force Encryption.\n";
        std::cout<<"4.Brute Force Decryption.\n";
        std::cout<<"Enter the option: ";
        while (!(std::cin >> *operation) || (*operation < 1 || *operation > 4)) {
            std::cout << "Invalid input.\nPlease try again (Note: input should be an integer between 1-3): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        c->setOperation(operation);
        switch (*operation) {
        case 1: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->setShift(shift());
            c->encrypt();
            std::cout<<"The Encrypted Text is: ";
            c->displayEncrypted();
        } break;
        case 2: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->setShift(shift());
            c->decrypt();
            std::cout<<"The Decrypted Text is: ";
            c->displayDecrypted();
        } break;
        case 3: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->encryptBruteForce();
        } break;
        case 4: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->decryptBruteForce();
        } break;
        default: break;
        }
        menu(c);
    } break;
    case 2: {
        std::cout<<"Thanks for using Cipher.\nGoodbye!\n"; // No additional "e" in "goodbye", gotta keep it professional and answer like my previous crush
        c->quit(); break;
    }
    default: break;
    }
    delete option; delete operation;
}
char* text() {
    char* temp = new char[100000];
    std::cout<<"Input the text (Note: it has to be larger than 5 characters): ";
    std::cin.getline(temp,100000);
    int* length = new int(0);
    while (temp[*length] != '\0') (*length)++;
    while ((*length)<6) {
        std::cout<<"The input text has to be greater than 5 characters!\nTry again: ";
        std::cin.getline(temp,100000);
        std::cin.clear();
        (*length) = 0;
        while (temp[*length] != '\0') (*length)++;
    }
    char* input = new char[(*length)+1];
    input[*length] = '\0';
    int* it = new int(0);
    for ((*it) = 0; (*it)<(*length); (*it)++) input[*it]=temp[*it];
    delete[] temp; delete length; delete it;
    return input;
}
int* shift() {
    int* shift = new int(0);
    std::cout << "Enter the shift value: ";
    while (!(std::cin >> *shift)) {
        std::cout << "Invalid input.\nPlease try again (Note: input should be an integer between 1-25): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return shift;
}