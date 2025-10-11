#include <iostream>
#include <limits>
// I am not using namespace std, because I am built different
class Cipher {
    char* text; char* ciphertext;
    int* shift; int* len;
public:
    Cipher() { text = nullptr; shift = new int(0); ciphertext = nullptr; len = nullptr; }
    ~Cipher() { delete[] text; delete[] ciphertext; delete shift; delete len; } // I delete those variables here, so I avoid "double free" error in runtime
    void setText(char* text) { this->text = text; }
    void setShift(int* shift) { this->shift = shift; }
    void encrypt() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        ciphertext = new char[*len];
        int* it = new int(0);
        for((*it) = 0; (*it)<(*len); (*it)++){
            if (text[*it] >= 'A' && text[*it] <= 'Z') ciphertext[*it] = ((*shift) + text[*it] - 'A' + 26) % 26 + 'A';
            else if (text[*it] >= 'a' && text[*it] <= 'z') ciphertext[*it] = ((*shift) + text[*it] - 'a' + 26) % 26 + 'a'; // Dealing with both, lower and uppercase letters
            else ciphertext[*it] = text[*it];
            /* To clear things out, I used the following logic of Ceaser Cipher Encryption
            while building one few months ago (I also have GitHub Repository of that project on
            my private GitHub account, if there will be any concerns I will be glad to share the code)
            logic is the following: to make sure while encrypting we don't exceed the boundary
            (Because we are using ASCII table) we plug in mathematical formula, which ensures that when
            we want to shift last letters form the alphabet while shift is too high for example shift is 3 and letter is Z
            Z will turn into a C and etc. Same for Decryption but lower boundary, hence using minus*/
        }
        delete it;
    }
    void decrypt() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        ciphertext = new char[*len];
        int* it = new int(0);
        for(*it = 0; (*it)<(*len); (*it)++){
            if (text[*it] >= 'A' && text[*it] <= 'Z') ciphertext[*it] = (((text[*it] - 'A' - (*shift)) % 26 + 26) % 26) + 'A';
            else if (text[*it] >= 'a' && text[*it] <= 'z') ciphertext[*it] = (((text[*it] - 'a' - (*shift)) % 26 + 26) % 26) + 'a';
            else ciphertext[*it] = text[*it];
        }
        delete it;
    }
    void encryptBruteForce() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        int* shifts = new int(0);
        for (*shifts = 1; (*shifts) < 26; (*shifts)++) {
            ciphertext = new char[*len];
            int* it = new int(0);
            for((*it) = 0; (*it)<(*len); (*it)++){
                if (text[*it] >= 'A' && text[*it] <= 'Z') ciphertext[*it] = ((*shifts) + text[*it] - 'A' + 26) % 26 + 'A';
                else if (text[*it] >= 'a' && text[*it] <= 'z') ciphertext[*it] = ((*shifts) + (text[*it] - 'a' + 26)) % 26 + 'a'; // Dealing with both, lower and uppercase letters
                else ciphertext[*it] = text[*it];
            }
            std::cout<< (*shifts)<<". ";
            for (char* letter = ciphertext; letter<ciphertext+(*len); letter++) std::cout<<*letter; std::cout<<std::endl;
            delete it;
        }
        delete shifts;
    } // Does all 25 possible permutations of encryption of Caesar Cipher
    void decryptBruteForce() {
        len = new int(0);
        while (text[*len] != '\0') (*len)++;
        int* shifts = new int(0);
        for (*shifts = 1; (*shifts)<26; (*shifts)++) {
            ciphertext = new char[*len];
            int* it = new int(0);
            for((*it) = 0; (*it)<(*len); (*it)++){
                if (text[*it] >= 'A' && text[*it] <= 'Z') ciphertext[*it] = (((text[*it] - 'A' - (*shifts)) % 26 + 26) % 26) + 'A';
                else if (text[*it] >= 'a' && text[*it] <= 'z') ciphertext[*it] = (((text[*it] - 'a' - (*shifts)) % 26 + 26) % 26) + 'a';
                else ciphertext[*it] = text[*it];
            }
            std::cout<< (*shifts)<<". ";
            for (char* letter = ciphertext; letter<ciphertext+(*len); letter++) std::cout<<*letter; std::cout<<std::endl;
            delete it;
        }
        delete shifts;
    } // Same for decoding, trying all possible 25 keys, but to be honest I only wrote this for I wouldn't have to try all 25 versions all by myself, I am too lazy, better automate things than to plug in numbers and do manual work, definitely not me
    void display() { for (char* letter = ciphertext; letter<ciphertext+(*len); letter++) std::cout<<*letter; std::cout<<std::endl; }
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
        std::cout<<"=========================\n";
        std::cout<<"Welcome to Caesar Cipher!\n";
        std::cout<<"=========================\n";
        std::cout<<"1.Operation Selection.\n";
        std::cout<<"2.Quit.\n";
        std::cout<<"Choose an option: ";
        while (!(std::cin >> *option) || (*option < 1 || *option > 5)) {
            /*By the way, I copied this input validation from the Google, but in my defence
             * 1. We never really did any input validation, hence never learned one
             * 2. Copying is normal thing, like it is programming, at least I am not using AI!!!
             */
            std::cout << "[Error] Invalid input. Please try again (input should be an integer between 1-5): ";
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
            std::cout << "Invalid input.(Note: input should be an integer between 1-3)\nPlease, try again : ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (*operation) {
        case 1: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->setShift(shift());
            c->encrypt();
            std::cout<<"====Encrypted Text====\n"; c->display(); std::cout<< "======================\n" << std::endl;
        } break;
        case 2: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->setShift(shift());
            c->decrypt();
            std::cout<<"====Decrypted Text===="; c->display(); std::cout<< "======================\n" << std::endl;
        } break;
        case 3: {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c->setText(text());
            c->encryptBruteForce();
            std::cout<<std::endl;
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
    } break;
    default: break;
    }
    delete option; delete operation;
}
char* text() {
    char* temp = new char[100000]; // Would use const int SIZE variable but no named variables, so no const size :)
    std::cout<<"Input the text: ";
    std::cin.getline(temp,100000);
    int* length = new int(0);
    while (temp[*length] != '\0') (*length)++;
    while ((*length)<6) {
        std::cout<<"[Error] The input text has to be greater than 5 characters!\nTry again: ";
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
        std::cout << "[Error] Invalid input.\nPlease try again (Note: input should be an integer between 1-25): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return shift;
}
// I've also made a GitHub Repository of the following project,
// there are two versions, one with variables and the other without variables
// master branch is with variables, "test" branch is pointers-only version
// -> https://github.com/DigitalMelquiades/Cipher
// Want to test the code decryption? ->
// L vdgob frxogq'w xvh pb idyrulwh Whuqdub Rshudwru... eb wkh zdb, zkdw'v wkh qhaw wdvn? D Iuhqfk Flskhu? Iru lw zrxog kdyh ehhq ixq wr ghfubsw wklv: "Up uvll Xhrl Bahbwascnz"