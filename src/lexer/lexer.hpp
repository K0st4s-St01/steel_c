#pragma once

#include "../utils/source_location.hpp"
#include <string>
#include <unordered_map>
#include <vector>

enum class TokenType {
  END_OF_FILE,
  UNKNOWN,
  IDENTIFIER,
  // Literals
  INT_LITERAL,
  FLOAT_LITERAL,
  CHAR_LITERAL,
  STRING_LITERAL,
  // Keywords
  KW_BREAK,
  KW_CASE,
  KW_CHAR,
  KW_CONST,
  KW_CONTINUE,
  KW_DEFAULT,
  KW_DO,
  KW_F64,
  KW_ELSE,
  KW_ENUM,
  KW_EXTERN,
  KW_F32,
  KW_FOR,
  KW_IF,
  KW_IMPORT,
  KW_I16,
  KW_I32,
  KW_I64,
  KW_RETURN,
  KW_SIZEOF,
  KW_STATIC,
  KW_STRUCT,
  KW_SWITCH,
  KW_UNSIGNED,
  KW_VOID,
  KW_VOLATILE,
  KW_WHILE,
  KW_TRAIT,
  KW_THIS,

  KW_ALIGNAS,       // _Alignas
  KW_ALIGNOF,       // _Alignof
  KW_ATOMIC,        // _Atomic
  KW_BOOL,          // _Bool
  KW_COMPLEX,       // _Complex
  KW_GENERIC,       // _Generic
  KW_IMAGINARY,     // _Imaginary
  KW_NORETURN,      // _Noreturn
  KW_STATIC_ASSERT, // _Static_assert
  KW_THREAD_LOCAL,  // _Thread_local

  // Operators & Punctuation
  PLUS,
  MINUS,
  STAR,
  SLASH,
  PERCENT,
  AMP,
  PIPE,
  CARET,
  TILDE,
  BANG,
  ASSIGN,
  LT,
  GT,
  QUESTION,
  COLON,
  SEMICOLON,
  COMMA,
  DOT,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  LBRACKET,
  RBRACKET,
  // Multi-char operators
  EQ_EQ,
  BANG_EQ,
  LT_EQ,
  GT_EQ,
  AMP_AMP,
  PIPE_PIPE,
  PLUS_PLUS,
  PLUS_EQ,
  MINUS_EQ,
  STAR_EQ,
  SLASH_EQ,
  PERCENT_EQ,
  AMP_EQ,
  PIPE_EQ,
  CARET_EQ,
  ARROW,
  ELLIPSIS,
  MINUS_MINUS
};

std::string tokenTypeToString(TokenType type);

struct Token {
  TokenType type;
  std::string lexeme;
  SourceLocation loc;
  Token(TokenType type, std::string lexeme, SourceLocation loc)
      : type(type), lexeme(std::move(lexeme)), loc(loc) {}
};

class Lexer {
public:
  explicit Lexer(std::string source, std::string filename = "<input>");
  Token nextToken();
  std::vector<Token> tokenize();
  bool isAtEnd() const;

  static inline const std::unordered_map<std::string, TokenType> &keywords = {
      {"break", TokenType::KW_BREAK},
      {"case", TokenType::KW_CASE},
      {"char", TokenType::KW_CHAR},
      {"const", TokenType::KW_CONST},
      {"continue", TokenType::KW_CONTINUE},
      {"default", TokenType::KW_DEFAULT},
      {"do", TokenType::KW_DO},
      {"f64", TokenType::KW_F64},
      {"else", TokenType::KW_ELSE},
      {"enum", TokenType::KW_ENUM},
      {"extern", TokenType::KW_EXTERN},
      {"f32", TokenType::KW_F32},
      {"for", TokenType::KW_FOR},
      {"if", TokenType::KW_IF},
      {"import", TokenType::KW_IMPORT},
      {"i16", TokenType::KW_I16},
      {"i32", TokenType::KW_I32},
      {"i64", TokenType::KW_I64},
      {"return", TokenType::KW_RETURN},
      {"sizeof", TokenType::KW_SIZEOF},
      {"static", TokenType::KW_STATIC},
      {"struct", TokenType::KW_STRUCT},
      {"switch", TokenType::KW_SWITCH},
      {"unsigned", TokenType::KW_UNSIGNED},
      {"void", TokenType::KW_VOID},
      {"volatile", TokenType::KW_VOLATILE},
      {"while", TokenType::KW_WHILE},
      {"trait", TokenType::KW_TRAIT},
      {"this", TokenType::KW_THIS},

      {"_Alignas", TokenType::KW_ALIGNAS},
      {"_Alingof", TokenType::KW_ALIGNOF},
      {"_Atomic", TokenType::KW_ATOMIC},
      {"bool", TokenType::KW_BOOL},
      {"_Complex", TokenType::KW_COMPLEX},
      {"_Generic", TokenType::KW_GENERIC},
      {"_Imaginary", TokenType::KW_IMAGINARY},
      {"_Noreturn", TokenType::KW_NORETURN},
      {"_Static_assert", TokenType::KW_STATIC_ASSERT},
      {"_Thread_local", TokenType::KW_THREAD_LOCAL}};

private: // helpers
  bool isHexPrefix() const;
  bool isBinaryPrefix() const;
  void consumeHexNumber(bool &isFloat);
  void consumeBinaryNumber();
  void consumeDecimal(bool &isFloat);
  void consumeNumberSuffix();

private:
  std::string source_;
  std::string filename_;
  size_t pos_ = 0;
  int line_ = 1;
  int col_ = 1;

  char peek() const;
  char peekNext() const;
  char advance();
  bool match(char expected);
  void skipWhitespaceAndComments();
  Token makeToken(TokenType type, const std::string &lexeme,
                  SourceLocation loc) const;
  Token identifierOrKeyword();
  Token number();
  Token stringLiteral();
  Token charLiteral();

  SourceLocation currentLocation() const;
};
