#ifndef LABWORK11_REQUEST_PARSER_H
#define LABWORK11_REQUEST_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const std::vector<std::string> logical_operands = {"OR", "AND"};

bool is_operand(const std::string& word);

template<typename T>
struct Request {
    std::string operand;
    T left;
    T right;

    Request() = default;

    Request(const Request& other) = default;

    explicit Request(const std::vector<T>& words);

    Request& operator=(Request other) {
        std::swap(operand, other.operand);
        std::swap(left, other.left);
        std::swap(right, other.right);
        return *this;
    }
};

template<typename T>
Request<T>::Request(const std::vector<T>& words) {
    if ((words.size() != 1) && (words.size() != 3)) {
        throw std::invalid_argument("Incorrect size in brackets");
    }
    if (is_operand(words[0])) {
        throw std::invalid_argument("Incorrect logic");
    }
    left = words[0];
    if (words.size() == 3) {
        if (!is_operand(words[1])) {
            throw std::invalid_argument("Incorrect logic");
        }
        if (is_operand(words[2])) {
            throw std::invalid_argument("Incorrect logic");
        }
        operand = words[1];
        right = words[2];
    }
}

bool is_operand(const std::string& word) {
    return std::find(logical_operands.begin(), logical_operands.end(), word) != logical_operands.end();
}

class Input {
private:
    std::string input_string;

    struct BracketsInput {
        Request<std::string> brackets_request;
        std::vector<std::string> words;

        std::vector<std::string> set_words(const std::string& brackets_words);

        [[nodiscard]] Request<std::string> set_brackets_request() const;

        explicit BracketsInput(const std::string& brackets_words) : words(set_words(brackets_words)) {
            brackets_request = set_brackets_request();
        }
    };

    std::string set_input();

public:
    Input() : input_string(set_input()) {}

    Request<Request<std::string>> get_request();
};

std::string Input::set_input() {
    const int max_chars = 41;
    char buffer[max_chars + 1];

    std::cin.getline(buffer, max_chars);
    buffer[std::cin.gcount()] = '\0';

    int chars_read = std::cin.gcount();

    if (chars_read == 41) {
        throw std::invalid_argument("Max length of input_string is 40 chars");
    }

    std::string res(buffer);
    return res;
}

Request<Request<std::string>> Input::get_request() {
    std::vector<Request<std::string>> request_list;
    std::string operand;

    for (size_t i = 0; i < input_string.size(); ++i) {
        std::string substring;
        if (input_string[i] == '(') {
            ++i;
            while ((i < input_string.size()) && (input_string[i] != ')')) {
                substring += input_string[i];
                ++i;
            }
            if (input_string[i] != ')') {
                throw std::invalid_argument("Expected bracket");
            }
            ++i;
        }
        while ((i < input_string.size()) &&
               !std::isspace(static_cast<unsigned char>(input_string[i]))) {
            substring += input_string[i];
            ++i;
        }
        if (is_operand(substring)) {
            if (!operand.empty()) {
                throw std::invalid_argument("Too many operands");
            }
            operand = substring;
            substring.resize(0);
        } else {
            BracketsInput inp(substring);
            request_list.push_back(inp.brackets_request);
            substring.resize(0);
        }
    }


    Request<Request<std::string>> res;

    if ((request_list.size() != 1) && (request_list.size() != 2)) {
        throw std::invalid_argument("Invalid length of request");
    }

    res.left = request_list[0];
    if (request_list.size() == 1) {
        return res;
    }

    res.operand = operand;
    res.right = request_list[1];

    return res;
}

std::vector<std::string> Input::BracketsInput::set_words(const std::string& brackets_words) {
    std::string current_word;
    std::vector<std::string> temp_words;

    for (int i = 0; i < brackets_words.size(); ++i) {
        current_word += brackets_words[i];
        if (std::isspace(static_cast<unsigned char>(brackets_words[i + 1]))) {
            temp_words.push_back(current_word);
            current_word.resize(0);
            ++i;
        }
    }
    if (!current_word.empty()) {
        temp_words.push_back(current_word);
    }

    return temp_words;
}

Request<std::string> Input::BracketsInput::set_brackets_request() const {
    return Request(words);
}

#endif //LABWORK11_REQUEST_PARSER_H
