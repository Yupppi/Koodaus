#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>
#include <chrono>

enum WordOption {
    LETTERS,
    WORD,
};

const int ascii_alph_a = 97;
const int ascii_alph_z = 122;

std::vector<char> Vectorizer (const std::string& input, const int option) {
    
    std::vector<char> character_vector;
    
    if (option == WORD) {
        character_vector.reserve(5);
    } else character_vector.reserve(21);

    for (const auto& characters: input) {
        character_vector.emplace_back(characters);
    }

    if (option == WORD) {
        while (character_vector.size() < 5) {
            character_vector.emplace_back(' ');
        }
    }

    return character_vector;
}

std::vector<char> FilterLetters(const std::string& chars) {
    
    std::vector<char> letters_left;
    letters_left.reserve(26);

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
    index.reserve(5);

    for (size_t i = 0; i < guessed_word.size(); i++) {
        if (guessed_word[i] == ' ') {
            index.emplace_back(i);
        }
    }
    return index;
}

std::vector<std::string> ReadDict() {
    
    std::vector<std::string> dictionary;
    std::string line;
    std::ifstream dict5("words5.txt");

    dictionary.reserve(5757);
    
    if (dict5.is_open())
    {
        while (std::getline(dict5, line)) {
            size_t pos = line.find('\n');
            line = line.substr(0, pos);
            dictionary.emplace_back(line);
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

    const auto push = [&](const auto& w) {
        if (std::ranges::find(dictionary, word) != dictionary.end()) {
            wordvector.emplace_back(w);}};

    std::vector<int> notfound;
    notfound.reserve(5);

    if (known_letters.size() > 0) {
        for (const auto& l: known_letters) {
            if (std::ranges::find(word, l) == word.end()) {
                notfound.emplace_back(0);
                break;
            }
        }

        if (notfound.size() == 0) {
            push(word);
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
    wordvector.reserve(5);

    for (const auto& first_char: letters_left) {
        guessed_word[index[0]] = first_char;

        if (index.size() > 1) {

            for (const auto& second_char: letters_left) {
                guessed_word[index[1]] = second_char;

                if (index.size() > 2) {

                    for (const auto& third_char: letters_left) {
                        guessed_word[index[2]] = third_char;

                        if (index.size() > 3) {

                            for (const auto& fourth_char: letters_left) {
                                guessed_word[index[3]] = fourth_char;
                                SaveWords(guessed_word, known_letters, dictionary, wordvector);
                            }
                        }

                        if (index.size() <= 3) {
                            SaveWords(guessed_word, known_letters, dictionary, wordvector);
                        }
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
    
    std::sort(wordvector.begin(), wordvector.end());

    for (const auto& w: wordvector) {
        WordList << w << '\n';
        std::cout << w << '\n';
    }

    std::cout << wordvector.size() << " words left." << std::endl;
}

int main() {
    std::string input;
    std::cout << "Enter the guessed word with spaces: ";
    std::getline(std::cin, input);
    
    std::string known;
    std::cout << "Enter the known letters: ";
    std::getline(std::cin, known);

    std::vector<char> guessed_word = Vectorizer(input, WORD);
    std::vector<char> known_letters = Vectorizer(known, LETTERS);

    std::string removed_chars;
    std::cout << "Enter the removed letters: ";
    std::getline(std::cin, removed_chars);

    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<char> letters_left = FilterLetters(removed_chars);

    std::vector<int> index = FindEmpty(guessed_word, letters_left);
    std::vector<std::string> dictionary = ReadDict();

    CreateWords(guessed_word, known_letters, letters_left, index, dictionary);
    const auto t2 = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> ms = t2 - t1;
	std::cout << ms.count() << " ms" << std::endl;
}