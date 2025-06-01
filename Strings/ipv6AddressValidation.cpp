🛠️ Validation Plan
Handle the :: (compressed zeros) only once.

Split the address into parts using : and check:

Each group has 1–4 valid hex digits.

Count of groups is 8 (or fewer if :: is used).

Disallow invalid characters or lengths.



#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

bool isHexDigit(char c) {
    return std::isxdigit(c); // 0–9, a–f, A–F
}

bool isValidIPv6Group(const std::string& group) {
    if (group.empty() || group.length() > 4) return false;
    for (char c : group) {
        if (!isHexDigit(c)) return false;
    }
    return true;
}

bool isValidIPv6(const std::string& ip) {
    if (ip.empty()) return false;

    // Check for "::" (compressed zero blocks)
    size_t doubleColon = ip.find("::");
    bool hasDoubleColon = doubleColon != std::string::npos;

    // If "::" appears more than once → invalid
    if (hasDoubleColon && ip.find("::", doubleColon + 1) != std::string::npos) {
        return false;
    }

    std::vector<std::string> groups;

    if (hasDoubleColon) {
        std::string left = ip.substr(0, doubleColon);
        std::string right = ip.substr(doubleColon + 2);

        // Split both sides by ':'
        std::istringstream issLeft(left), issRight(right);
        std::string part;

        while (std::getline(issLeft, part, ':')) {
            if (!part.empty()) groups.push_back(part);
        }

        // Use placeholder for "::"
        groups.push_back(""); // mark position of "::"

        while (std::getline(issRight, part, ':')) {
            if (!part.empty()) groups.push_back(part);
        }

        // Count actual groups (excluding placeholder)
        int totalGroups = groups.size();
        int numRealGroups = std::count_if(groups.begin(), groups.end(),
                                          [](const std::string& g) { return !g.empty(); });

        // Total groups after expansion must be ≤ 8
        if (numRealGroups >= 8) return false;
    } else {
        // No "::", just split directly
        std::istringstream iss(ip);
        std::string part;
        while (std::getline(iss, part, ':')) {
            groups.push_back(part);
        }

        if (groups.size() != 8) return false;
    }

    // Now validate each real group
    for (const std::string& group : groups) {
        if (group.empty()) continue; // skip "::" marker
        if (!isValidIPv6Group(group)) return false;
    }

    return true;
}

=============================
How this regex works (briefly):
It matches either full 8 groups (each 1–4 hex digits separated by :),

Or compressed versions with :: replacing one or more groups of zeros,

Supports the optional IPv4-mapped part at the end (e.g. ::ffff:192.168.0.1),

Allows optional zone index for link-local addresses (fe80::7:8%eth0).

  
#include <iostream>
#include <regex>
#include <string>

bool isValidIPv6Regex(const std::string& ip) {
    // Regex for standard and compressed IPv6 addresses
    static const std::regex ipv6_regex(R"(^(
        (?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}|                                    # 1:2:3:4:5:6:7:8
        (?:[0-9a-fA-F]{1,4}:){1,7}:|                                                # 1::                              1:2:3:4:5:6:7::
        (?:[0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|                                # 1::8             1:2:3:4:5:6::8
        (?:[0-9a-fA-F]{1,4}:){1,5}(?::[0-9a-fA-F]{1,4}){1,2}|                       # 1::7:8           1:2:3:4:5::7:8
        (?:[0-9a-fA-F]{1,4}:){1,4}(?::[0-9a-fA-F]{1,4}){1,3}|                       # 1::6:7:8         1:2:3:4::6:7:8
        (?:[0-9a-fA-F]{1,4}:){1,3}(?::[0-9a-fA-F]{1,4}){1,4}|                       # 1::5:6:7:8       1:2:3::5:6:7:8
        (?:[0-9a-fA-F]{1,4}:){1,2}(?::[0-9a-fA-F]{1,4}){1,5}|                       # 1::4:5:6:7:8     1:2::4:5:6:7:8
        [0-9a-fA-F]{1,4}:(?:(?::[0-9a-fA-F]{1,4}){1,6})|                            # 1::3:4:5:6:7:8   1::3:4:5:6:7:8
        :(?:(?::[0-9a-fA-F]{1,4}){1,7}|:)|                                          # ::2:3:4:5:6:7:8  ::8             ::
        fe80:(?::[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|                            # fe80::7:8%eth0   fe80::7:8%1
        ::ffff:(?:0{1,4}:){0,1}
        ((25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])\.){3}
        (25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])|                                       # ::ffff:192.168.1.1 IPv4 mapped IPv6
        (?:[0-9a-fA-F]{1,4}:){1,4}:
        ((25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])\.){3}
        (25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])                                        # 1:2:3:4:192.168.1.1
    )$)", std::regex::extended | std::regex::icase | std::regex::optimize);

    return std::regex_match(ip, ipv6_regex);
}

int main() {
    std::string ip1 = "2001:0db8:85a3::8a2e:0370:7334";
    std::string ip2 = "2001:db8::85a3::7334";  // invalid, multiple ::

    std::cout << ip1 << " is " << (isValidIPv6Regex(ip1) ? "valid" : "invalid") << "\n";
    std::cout << ip2 << " is " << (isValidIPv6Regex(ip2) ? "valid" : "invalid") << "\n";
}
