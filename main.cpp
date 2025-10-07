#include <iostream>
// I am not using namespace std, because I am built different
class Cipher {
    std::string text, encrypted, decrypted;
    int shift;
public:
    Cipher(const std::string& text = "", const int& shift = 0) : text(text), shift(shift) {};
    void setText(const std::string& text) { this->text=text; }
    void setShift(const int& shift) { this->shift=shift; }
    void encrypt() {
        for (const char& letter:text) {
            if (letter>='A' && letter<='Z') encrypted += (letter - 'A' + shift)%26+'A';
            /* To clear things out, I used the following logic of Ceaser Cipher Encryption
            while building one few months ago (I also have Git Repository of that project on
            my private GitHub account, if there will be any concerns I will be glad to chare the code)
            logic is the following to make sure while encrypting we don't go out from the boundary
            (Because we are using ASCII table) we plug in mathematical formula, which ensures that when
            we want to shift last letters form the alphabet while shift is too high for example shift is 3 and letter is Z
            Z will turn into a C and etc.
            */
            else if (letter>='a' && letter<='z') encrypted += (letter - 'a' + shift)%26+'a'; // Dealig with both, lower and uppercase letters
            else encrypted += letter;
        }
    }
    void displayEncrypted() {std::cout<<encrypted<<std::endl;}
};

int main() {
    Cipher c;
    c.setText("Hello World!");
    c.setShift(3);
    c.encrypt();
    c.displayEncrypted();
    return 0;
}