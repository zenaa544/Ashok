Given a string s, reverse the string without reversing its individual words. Words are separated by spaces.

Note: The string may contain leading or trailing spaces, or multiple spaces between two words. The returned string should only have a single space separating the words, and no extra spaces should be included.

Examples :

Input: s = " i like this program very much "
Output: "much very program this like i"
Explanation: After removing extra spaces and reversing the whole string (not individual words), the input string becomes "much very program this like i". 


  std::string reverseWords(std::string s) {
    std::istringstream iss(s);
    std::string word;
    std::vector<std::string> words;

    // Extract words from the input string
    while (iss >> word) {
        words.push_back(word);
    }

    // Reverse the order of words
    std::reverse(words.begin(), words.end());

    // Join the words back into a string with a single space
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) oss << " ";  // Add space before second word onwards
        oss << words[i];        // Add the word
    }

    return oss.str();
}
