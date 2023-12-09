#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>

const int ascii_alph_a = 97;
const int ascii_alph_z = 122;

std::vector<char> Vectorizer (const std::string& input) {
    std::vector<char> guessed_word;
    for (const auto& characters: input) {
        guessed_word.push_back(characters);
    }
    return guessed_word;
}

std::vector<char> Filter(const std::string& chars) {
    std::vector<char> letters_left;
    for (int i: std::ranges::iota_view{ascii_alph_a, ascii_alph_z + 1}) {
        if (chars.find(char(i)) > sizeof(chars)) {
            letters_left.push_back(char(i));
        }
    }
    return letters_left;
}

std::vector<int> FindEmpty(std::vector<char>& guessed_word,
                            const std::vector<char>& letters_left) {

    std::vector<int> index;
    for (int i = 0; i < guessed_word.size(); i++) {
        if (guessed_word[i] == ' ') {
            index.push_back(i);
        }
    }
    return index;
}

std::vector<std::string> ReadDict() {
    std::vector<std::string> dictionary;
    std::string line;
    std::ifstream dict5("words5.txt");
    if (dict5.is_open())
    {
        while (std::getline(dict5, line)) {
            size_t pos = line.find('\n');
            line = line.substr(0, pos);
            dictionary.push_back(line);
        }
        dict5.close();
    }
    return dictionary;
}

void SaveWords(const std::vector<char>& guessed_word,
                const std::vector<char>& known_letters,
                const std::vector<std::string>& dictionary,
                std::vector<std::string>& wordvector) {
    
    std::string word = "";  
    for (const auto& character: guessed_word) {
        word += character;
    }

    const auto push = [&](auto w) {
        if (std::ranges::find(dictionary, word) != dictionary.end()) {
            wordvector.push_back(word);
        }
    };

    if (known_letters.size() > 0) {
        for (const auto& l: known_letters) {
            if (std::ranges::find(word, l) != word.end()) {
                push(word);
            }
        }
    } else {
        push(word);
    }
}

void CreateWords(std::vector<char>& guessed_word,
                const std::vector<char>& known_letters,
                const std::vector<char>& letters_left,
                const std::vector<int>& index,
                const std::vector<std::string>& dictionary) {
    
    std::ofstream WordList("possible_words.txt");
    std::vector<std::string> wordvector;

    for (const auto& first_char: letters_left) {
        guessed_word[index[0]] = first_char;

        if (index.size() > 1) {

            for (const auto& second_char: letters_left) {
                guessed_word[index[1]] = second_char;

                if (index.size() > 2) {

                    for (const auto& third_char: letters_left) {
                        guessed_word[index[2]] = third_char;

                        SaveWords(guessed_word, known_letters, dictionary, wordvector);
                    }
                }

                if (index.size() <= 2) {
                    SaveWords(guessed_word, known_letters, dictionary, wordvector);
                }
            }
        }
        if (index.size() <= 1) {
            SaveWords(guessed_word, known_letters, dictionary, wordvector);
        }
    }

    for (const auto& w: wordvector) {
        WordList << w << '\n';
        std::cout << w << '\n';
    }
}

int main() {
    std::string input;
    std::cout << "Enter the guessed word with spaces: ";
    std::getline(std::cin, input);
    
    std::string known;
    std::cout << "Enter the known letters: ";
    std::getline(std::cin, known);

    std::vector<char> guessed_word = Vectorizer(input);
    std::vector<char> known_letters = Vectorizer(known);

    std::string removed_chars;
    std::cout << "Enter the removed letters: ";
    std::getline(std::cin, removed_chars);
    // std::string removed_chars = "";

    std::vector<char> letters_left = Filter(removed_chars);

    std::vector<int> index = FindEmpty(guessed_word, letters_left);
    std::vector<std::string> dictionary = ReadDict();

    CreateWords(guessed_word, known_letters, letters_left, index, dictionary);
}