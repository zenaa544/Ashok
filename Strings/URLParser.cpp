How it works:
Regex match splits URL into components.

parse() extracts parts from regex capture groups.

parseQueryParams() splits query string by &, then by = into a map.

Public getters give access to URL parts and query parameters.

setURL() allows replacing the URL, re-validating, and re-parsing.

Why hybrid?
Regex ensures only valid URL formats are accepted.

Manual parsing lets you work with parts easily.

Query params extracted cleanly into a map for quick lookup.


#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iterator>

class URL {
private:
    std::string url;
    std::string scheme, host, path, query, fragment;
    int port = -1; // -1 means no port specified
    std::map<std::string, std::string> query_params;

    // Regex to validate URL and capture components
    static const std::regex url_regex;

    bool isValid(const std::string& url_str) const {
        return std::regex_match(url_str, url_regex);
    }

    void parse() {
        std::smatch match;
        if (!std::regex_match(url, match, url_regex)) {
            throw std::invalid_argument("Invalid URL format");
        }

        // match groups:
        // 1: scheme
        // 2: host (domain or IP)
        // 3: port (optional)
        // 4: path (optional)
        // 5: query (optional, includes '?')
        // 6: fragment (optional, includes '#')

        scheme = match[1];
        host = match[2];

        std::string port_str = match[3];
        if (!port_str.empty()) {
            port = std::stoi(port_str.substr(1)); // skip ':'
        } else {
            port = -1;
        }

        path = match[4];
        query = match[5];
        if (!query.empty() && query[0] == '?')
            query.erase(query.begin()); // remove '?'

        fragment = match[6];
        if (!fragment.empty() && fragment[0] == '#')
            fragment.erase(fragment.begin()); // remove '#'

        parseQueryParams();
    }

    void parseQueryParams() {
        query_params.clear();
        std::istringstream qstream(query);
        std::string kv;
        while (std::getline(qstream, kv, '&')) {
            if (kv.empty()) continue;
            auto pos = kv.find('=');
            if (pos == std::string::npos) {
                query_params[kv] = ""; // key with no value
            } else {
                std::string key = kv.substr(0, pos);
                std::string value = kv.substr(pos + 1);
                query_params[key] = value;
            }
        }
    }

public:
    URL(const std::string& url_str) : url(url_str) {
        if (!isValid(url)) {
            throw std::invalid_argument("Invalid URL format");
        }
        parse();
    }

    void setURL(const std::string& new_url) {
        if (!isValid(new_url)) {
            throw std::invalid_argument("Invalid URL format");
        }
        url = new_url;
        parse();
    }

    bool validate() const {
        return isValid(url);
    }

    std::string getScheme() const { return scheme; }
    std::string getHost() const { return host; }
    int getPort() const { return port; }
    std::string getPath() const { return path; }
    std::string getQuery() const { return query; }
    std::string getFragment() const { return fragment; }
    std::map<std::string, std::string> getQueryParams() const { return query_params; }

    std::string getURL() const { return url; }
};

// Initialize the regex outside the class
const std::regex URL::url_regex(
    R"(^(https?|ftp):\/\/)"                         // scheme
    R"(([a-zA-Z0-9\-\.]+|\[[0-9a-fA-F:]+\]|\d{1,3}(\.\d{1,3}){3}))" // host (domain or IPv6 or IPv4)
    R"((:\d+)?)"                                    // port (optional)
    R"((\/[^\s?#]*)?)"                              // path (optional)
    R"((\?[^\s#]*)?)"                               // query (optional)
    R"((#[^\s]*)?$)",                               // fragment (optional)
    std::regex::icase);

int main() {
    try {
        URL url("https://example.com:8080/path/to/resource?foo=bar&baz=qux#frag");
        std::cout << "Scheme: " << url.getScheme() << "\n";
        std::cout << "Host: " << url.getHost() << "\n";
        std::cout << "Port: " << url.getPort() << "\n";
        std::cout << "Path: " << url.getPath() << "\n";
        std::cout << "Query: " << url.getQuery() << "\n";
        std::cout << "Fragment: " << url.getFragment() << "\n";

        std::cout << "Query parameters:\n";
        for (const auto& [key, value] : url.getQueryParams()) {
            std::cout << "  " << key << " = " << value << "\n";
        }

        // Modify URL example
        url.setURL("ftp://192.168.0.1/resource?x=1&y=2");
        std::cout << "\nNew URL host: " << url.getHost() << "\n";
        std::cout << "New URL query params:\n";
        for (const auto& [k, v] : url.getQueryParams()) {
            std::cout << "  " << k << " = " << v << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
