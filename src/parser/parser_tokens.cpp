#include "../utils/source_location.hpp"
#include "parser.hpp"

Parser::Parser(std::vector<Token> tokens, std::string filename)
    : tokens_(std::move(tokens)), filename_(std::move(filename)) {}

const Token &Parser::peek() const {
  static Token eof =
      Token(TokenType::END_OF_FILE, "<EOF>", SourceLocation(0, 0));
  eof.loc.filename = filename_;
  if (isAtEnd())
    return eof;
  return tokens_[pos_];
}

const Token &Parser::peekNext() const {
  static Token eof =
      Token(TokenType::END_OF_FILE, "<EOF>", SourceLocation(0, 0));
  eof.loc.filename = filename_;
  if (pos_ + 1 > tokens_.size())
    return eof;
  return tokens_[pos_ + 1];
}

const Token &Parser::previous() const { return tokens_[pos_ - 1]; }

bool Parser::isAtEnd() const {
  return pos_ >= tokens_.size() || tokens_[pos_].type == TokenType::END_OF_FILE;
}

