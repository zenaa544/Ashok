 Reverse charecters in each word, while do not alter the positions of the words, lets assume each word is separated by single or multiple spaces in between along with leading or training spaces.

   std::string reverseCharactersInWords(const std::string& s) {
    std::istringstream iss(s);
    std::string word;
    std::ostringstream oss;

    while (iss >> word) {
        std::reverse(word.begin(), word.end());
        oss << word << " ";
    }

    std::string result = oss.str();

    // Remove the trailing space
    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}
