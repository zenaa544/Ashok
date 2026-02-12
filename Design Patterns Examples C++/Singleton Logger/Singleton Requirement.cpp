Singleton Design Pattern Requires
Only one object to be created.
To Restrict Any other program to create another instance.
  - Make constructor private.
  - Make copy constructor private.
  - Make =operator overloading private.
  - Have a seprate interface for clients to create instance which should return pointer to the ONLY object created.
  - The interface should be a static member ,so that objects of class Need Not be created for using the interface.
  
#include <iostream>

// Singleton class definition
class Singleton {
private:
    // Private constructor prevents external instantiation
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }

    // Deleted copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Public static method to access the instance
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed thread-safe in C++11 and later
        return instance;
    }

    // Example member function
    void showMessage() {
        std::cout << "Hello from Singleton!" << std::endl;
    }
};

int main() {
    // Access and use the singleton instance
    Singleton& s1 = Singleton::getInstance();
    s1.showMessage();

    // Show that both variables point to the same instance
    Singleton& s2 = Singleton::getInstance();
    if (&s1 == &s2) {
        std::cout << "s1 and s2 are the same instance." << std::endl;
    } else {
        std::cout << "s1 and s2 are different instances." << std::endl;
    }

    return 0;
}


#include <iostream>

class Complex {
private:
    double real, imag;
public:
    // Default constructor
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Copy constructor
    Complex(const Complex& other) {
        real = other.real;
        imag = other.imag;
        std::cout << "Copy constructor called!" << std::endl;
    }

    // Copy assignment operator
    Complex& operator=(const Complex& other) {
        std::cout << "Copy assignment operator called!" << std::endl;
        // Check for self-assignment
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    void display() const {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main() {
    Complex c1(2, 3);       // Calls parameterized constructor
    Complex c2 = c1;        // Calls copy constructor
    c2.display();

    Complex c3;             // Default constructor
    c3 = c1;                // Calls copy assignment operator
    c3.display();

    return 0;
}
