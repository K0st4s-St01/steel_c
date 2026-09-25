#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
namespace fs = std::filesystem;
#include "lexer/lexer.hpp"

std::string read_file(const std::string &filename) {
  std::ifstream input(filename);

  if (!input)
    std::cerr << "cannot open file" << filename << "\n";

  std::ostringstream str_builder;
  str_builder << input.rdbuf();

  return str_builder.str();
}

void print_tokens(const std::vector<Token> &token_vec) {
  for (auto &tok : token_vec) {

    std::cout << tokenTypeToString(tok.type) << " '" << tok.lexeme << "' ["
              << tok.loc.line << ":" << tok.loc.col << "]\n";
  }
}

int main(int argc, char **argv) {
  std::vector<std::string> inputFiles;
  bool dumpTokens = false;
  if (argc < 2) {
    std::cout << "please provide files to compile";
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    std::string a = argv[i];
    if (a == "--tokens") {
      dumpTokens = true;
    } else
      inputFiles.push_back(a);
  }

  for (auto &inputFile : inputFiles) {
    std::string src = read_file(inputFile);
    Lexer lex(src, inputFile);
    auto current = lex.tokenize();
    if (dumpTokens) {
      print_tokens(current);
    }
  }
  return 0;
}
