#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
// I am not using namespace std, because I am built different
class Cipher {
    char* text; char* encrypted; char* decrypted;
    int* shift; int* operation; int* len;
public:
    Cipher() { text = nullptr; shift = new int(0); }
    ~Cipher() { delete[] text; delete[] encrypted; delete[] decrypted; delete shift; delete operation; }
    void setText(char* text) {
        this->text = text;
        /*delete[] this->text;
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        this->text = new char[*len+1];
        this->text[*len] = '\0';
        int* it = new int(0);
        for (*it = 0; (*it)<(*len); it++) this->text[*it] = text[*it];
        delete it;
        for (char* letter = this->text; letter<(this->text)+(*len);letter++) std::cout<<*letter;
        std::cout<<'\n'<<len;*/
    }
    void setShift(const int* shift) { *(this->shift)=*shift; std::cout<<this->shift << ' '<< shift;}
    void encrypt() {
        std::cout<<text;
        /*int* it = new int(0);
        for (const char* letter = text; letter < text; letter++) {
            if (*letter >= 'A' && *letter <= 'Z') encrypted[*it] = (*letter - 'A' + *shift)%26+'A';
            /* To clear things out, I used the following logic of Ceaser Cipher Encryption
            while building one few months ago (I also have Git Repository of that project on
            my private GitHub account, if there will be any concerns I will be glad to chare the code)
            logic is the following to make sure while encrypting we don't go out from the boundary
            (Because we are using ASCII table) we plug in mathematical formula, which ensures that when
            we want to shift last letters form the alphabet while shift is too high for example shift is 3 and letter is Z
            Z will turn into a C and etc.
            #1#
            else if (*letter >= 'a' && *letter <= 'z') encrypted[*it] = (*letter - 'a' + *shift)%26+'a'; // Dealing with both, lower and uppercase letters
            else encrypted[*it] = *letter;
            (*it)++;
        }
        delete it;*/
    }
    void decrypt() {
        int* it = new int(0);
        for (const char* letter = text; letter < text+(*len); letter++) {
            if (*letter >= 'A' && *letter <= 'Z') {
                decrypted[*it] = ((*letter - 'A' - *shift)%26+'A' < 'A') ?
                ((*letter - 'A' - *shift)%26+'A' + 26) : ((*letter - 'A' - *shift)%26 +'A');
            }
            else if (*letter >= 'a' && *letter <= 'z'){
                decrypted[*it] = ((*letter - 'a' - *shift)%26+'a' < 'a') ?
                ((*letter - 'a' - *shift)%26+'a' + 26) : ((*letter - 'a' - *shift)%26 +'a');
            }
            else decrypted[*it] = *letter;
            (*it)++;
        }
    }
    void decryptBruteForce() {
        int* i = new int(0);
        for (*i = 1; *i < 26; (*i)++) {
            int* it = new int(0);
            for (const char* letter = text; letter < text+(*len); letter++) {
                if (*letter >= 'A' && *letter <= 'Z') {
                    decrypted[*it] = ((*letter - 'A' - (*i))%26+'A' < 'A') ?
                    ((*letter - 'A' - (*i))%26+'A' + 26) : ((*letter - 'A' - (*i))%26 +'A');
                }
                else if (*letter >= 'a' && *letter <= 'z'){
                    decrypted[*it] = ((*letter - 'a' - *i)%26+'a' < 'a') ?
                    ((*letter - 'a' - (*i))%26+'a' + 26) : ((*letter - 'a' - (*i))%26 +'a');
                }
                else decrypted[*it] = *letter;
                (*it)++;
            }
            std::cout<<i<<". ";
            for (char* letter = decrypted; letter < decrypted+(*len); letter++) std::cout<<*letter;
            std::cout<<std::endl;
            delete[] decrypted;
            delete it;
        }
        delete i;
    }
    void displayEncrypted() {for (char* letter = encrypted; letter < encrypted+(*len); letter++) std::cout<<*letter;}
    void displayDecrypted() {for (char* letter = decrypted; letter < decrypted+(*len); letter++) std::cout<<*letter;}
    void setOperation(int* operation) { this->operation = operation; }
    int getOperation() const { return *this->operation; }
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
        std::cout<<"2.Run.\n";
        std::cout<<"3.Quit.\n";
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
    }while (*option<1 || *option>5);
    switch (*option) {
    case 1: {
        std::cout<<"Choose which operation to execute:\n";
        std::cout<<"1.Encrypt.\n";
        std::cout<<"2.Decrypt.\n";
        std::cout<<"3.Brute Force Decryption.\n";
        std::cout<<"Enter the option: ";
        while (!(std::cin >> *operation) || (*operation<1 || *operation>3)) {
            std::cout << "Invalid input.\nPlease try again (Note: input should be an integer between 1-3): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        c->setOperation(operation);
        switch (*operation) {
        case 1: {
            c->setText(text());
            c->setShift(shift());
            c->encrypt();
            c->displayEncrypted();
        } break;
        case 2: {
            c->setText(text());
            c->setShift(shift());
            c->decrypt();
        } break;
        case 3: {
            c->setText(text());
        } break;
        default: break;
        }
        menu(c);
    } break;
    case 2: {
        switch (c->getOperation()) {
        case 1: {
            std::cout<<"The Encrypted Text is: ";
            c->displayEncrypted();
        } break;
        case 2: {
            std::cout<<"The Decrypted Text is: ";
            c->displayDecrypted();
        } break;
        case 3: c->decryptBruteForce(); break;
        default: break;
        }
        menu(c);
    } break;
    case 3: {
        std::cout<<"Thanks for using Cipher.\nGoodbye!\n"; // No additional "e" in "goodbye", gotta keep it professional and answer like my previous crush
        break;}
    default: break;
    }
    delete option; delete operation;
}
char* text() {
    char* temp = new char[100000];
    std::cout<<"Input the text (Note: it has to be larger than 5 characters): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(temp,100000);
    int* length = new int(0);
    while (temp[*length] != '\0') (*length)++;
    while ((*length)<6) {
        std::cout<<"The input text has to be greater than 5 characters!\nTry again: ";
        std::cin.getline(temp,100000);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        (*length) = 0;
        while (temp[*length] != '\0') (*length)++;
    }
    char* input = new char[(*length)+1];
    input[*length] = '\0';
    int* it = new int(0);
    for ((*it) = 0; (*it)<(*length); (*it)++) input[*it]=temp[*it];
    /*for (char* letter = input; letter < input + (*length); letter++) std::cout<<*letter;
    std::cout<<*length;*/
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
    std::cout<<*shift;
    return shift;
}