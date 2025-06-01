✅ IPv4 Address Format Rules
A valid IPv4 address:

Has 4 octets separated by 3 dots (.).

Each octet must:

Be a number from 0 to 255.

Contain only digits (0–9).

Have no leading zeros unless the number is 0.


#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

bool isValidIPv4(const std::string& ip) {
    std::istringstream iss(ip);
    std::string part;
    std::vector<std::string> parts;

    // Split by '.'
    while (std::getline(iss, part, '.')) {
        parts.push_back(part);
    }

    // Step 1: Check there are exactly 4 parts
    if (parts.size() != 4) {
        return false;
    }

    for (const std::string& segment : parts) {
        // Step 2: Not empty
        if (segment.empty()) {
            return false;
        }

        // Step 3: Only digits
        for (char c : segment) {
            if (!std::isdigit(c)) {
                return false;
            }
        }

        // Step 4: No leading zeros unless the segment is "0"
        if (segment.size() > 1 && segment[0] == '0') {
            return false;
        }

        // Step 5: Check numeric range 0–255
        try {
            int value = std::stoi(segment);
            if (value < 0 || value > 255) {
                return false;
            }
        } catch (...) {
            return false; // e.g. overflow or non-integer string
        }
    }

    return true;
}

int main() {
    std::vector<std::string> testCases = {
        "192.168.0.1",    // valid
        "0.0.0.0",        // valid
        "255.255.255.255",// valid
        "256.100.1.1",    // invalid
        "192.168.01.1",   // invalid (leading zero)
        "192.168.1",      // invalid
        "abc.def.ghi.jkl",// invalid
        "192..168.1.1",   // invalid
        "1.2.3.4.5",      // invalid
        "123.456.78.90",  // invalid
        "172.16.254.1 "   // invalid (trailing space)
    };

    for (const std::string& ip : testCases) {
        std::cout << "[" << ip << "] -> " << (isValidIPv4(ip) ? "Valid" : "Invalid") << '\n';
    }

    return 0;
}
