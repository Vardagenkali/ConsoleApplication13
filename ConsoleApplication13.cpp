#include <iostream>
#include <cstring>

class String {
private:
    static int count;
    char* str;
    int size;

public:
    String() : String(80) {}

    explicit String(size_t size) : size(static_cast<int>(size)), str(new char[size + 1]) {
        ++count;
    }

    String(const char* inputString) : String(strlen(inputString)) {
        strcpy_s(str, size + 1, inputString);
    }

    String(String&& other) noexcept : str(other.str), size(other.size) {
        ++count;
        other.str = nullptr;
        other.size = 0;
    }

    ~String() {
        delete[] str;
        --count;
    }

    static int getCount() {
        return count;
    }

    void inputString() {
        std::cout << "Enter a string: ";
        std::cin.getline(str, size + 1);
    }

    void printString() const {
        std::cout << "String: " << str << std::endl;
    }

    char operator[](int index) const {
        if (index >= 0 && index < size) {
            return str[index];
        }
        else {
            return '\0';
        }
    }

    int operator()(char ch) const {
        for (int i = 0; i < size; ++i) {
            if (str[i] == ch) {
                return i;
            }
        }
        return -1;
    }

    operator int() const {
        return size;
    }
};

int String::count = 0;

int main() {
    String defaultString;
    defaultString.printString();

    String customSizeString(50);
    customSizeString.inputString();
    customSizeString.printString();

    String userInputString;
    userInputString.inputString();
    userInputString.printString();

    std::cout << "Character at index 2: " << userInputString[2] << std::endl;

    std::cout << "Index of 'e': " << userInputString('e') << std::endl;

    std::cout << "Length of the string: " << int(userInputString) << std::endl;

    String movedString = std::move(userInputString);
    std::cout << "After move constructor, userInputString: ";
    userInputString.printString();
    std::cout << "Moved string: ";
    movedString.printString();

    std::cout << "Number of String objects created: " << String::getCount() << std::endl;

    return 0;
}
