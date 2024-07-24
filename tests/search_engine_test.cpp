#include <gtest/gtest.h>

#include "../lib/index_generator.h"
#include "../lib/index_reader.h"
#include "../lib/response.h"

std::vector<std::string> parse_csv(const fs::path& path) {
    std::string filename = path.string();
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    std::getline(file, line);

    std::vector<std::string> tokens;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        std::vector<size_t> result = {};
    }

    file.close();

    return tokens;
}

TEST(WalkDirectorySuit, TwoDirectoryCase) {
    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    std::function f = [](const fs::path& file) {
        std::cout << "Processing file: " << file << std::endl;
    };
    recursive_directory_walk(root_path, f);
}

TEST(WalkDirectorySuit, LambdaCase) {
    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
}

TEST(WalkDirectorySuit, ReadCase) {
    fs::path root_path = "/home/xunya/CLionProjects/labwork11/META";
    read(root_path, "Skakov!!!!");
}

TEST(RequestSuit, SetCase) {
    std::vector<std::string> words = {"you", "AND", "I"};
    Request<std::string> r(words);

    ASSERT_EQ(r.left, "you");
    ASSERT_EQ(r.operand, "AND");
    ASSERT_EQ(r.right, "I");
}

TEST(RequestSuit, OperandCheckCase) {
    ASSERT_FALSE(is_operand("OR "));
}

TEST(RequestSuit, CopyCase) {
    std::vector<std::string> words = {"you", "AND", "I"};
    Request<std::string> exact(words);

    Request<std::string> r = exact;

    ASSERT_EQ(r.left, "you");
    ASSERT_EQ(r.operand, "AND");
    ASSERT_EQ(r.right, "I");
}

TEST(InputSuit, SimpleCase) {
    std::istringstream input("Too"); // создала ввод
    std::cin.rdbuf(input.rdbuf()); // вызвала cin от поинтера на то что считано - это делает rdbuf
                                   // returns a pointer to the stream buffer before the call,

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");

    std::vector<std::string> expected{"/home/xunya/CLionProjects/labwork11/META/A/B/text.csv",
                                      "1", "3", "4"};

    ASSERT_EQ(actual, expected);
}

TEST(InputSuit, SimpleBracketsCase) {
    std::istringstream input("(Too)");
    std::cin.rdbuf(input.rdbuf());

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");

    std::vector<std::string> expected{"/home/xunya/CLionProjects/labwork11/META/A/B/text.csv",
                                      "1", "3", "4"};

    ASSERT_EQ(actual, expected);
}

TEST(InputSuit, SimpleOperandsCase) {
    std::istringstream input("Too AND to");
    std::cin.rdbuf(input.rdbuf());

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");

    std::vector<std::string> expected{"/home/xunya/CLionProjects/labwork11/META/A/B/text.csv",
                                      "3", "4"};

    ASSERT_EQ(actual, expected);
}

TEST(InputSuit, BracketsOperandsCase) {
    std::istringstream input("(Too AND to) OR tired...");
    std::cin.rdbuf(input.rdbuf());

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");

    std::vector<std::string> expected{"/home/xunya/CLionProjects/labwork11/META/A/B/text.csv",
                                      "4", "3", "1"};

    ASSERT_EQ(actual, expected);
}

TEST(InputSuit, AllBracketsOperandsCase) {
    std::istringstream input("(Too AND to) OR (tired... AND F)");
    std::cin.rdbuf(input.rdbuf());

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");

    std::vector<std::string> expected{"/home/xunya/CLionProjects/labwork11/META/A/B/text.csv",
                                      "4", "3"};

    ASSERT_EQ(actual, expected);
}

TEST(LabworkSeach, SimpleCase) {
    std::istringstream input("Sand");
    std::cin.rdbuf(input.rdbuf());

    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();

    std::vector<std::string> actual =
            parse_csv("/home/xunya/CLionProjects/labwork11/TEMPORARY/temporary_result.csv");
}
