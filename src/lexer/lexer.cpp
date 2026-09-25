#include "lexer.hpp"

std::string tokenTypeToString(TokenType type) {
  switch (type) {
  case TokenType::END_OF_FILE:
    return "END_FO_FILE";
  case TokenType::UNKNOWN:
    return "UNKNOWN";
  case TokenType::IDENTIFIER:
    return "IDENTIFIER";
  case TokenType::INT_LITERAL:
    return "INT_LITERAL";
  case TokenType::FLOAT_LITERAL:
    return "FLOAT_LITERAL";
  case TokenType::CHAR_LITERAL:
    return "CHAR_LITERAL";
  case TokenType::STRING_LITERAL:
    return "STRING_LITERAL";
  case TokenType::KW_BREAK:
    return "KW_BREAK";
  case TokenType::KW_CASE:
    return "KW_CASE";
  case TokenType::KW_CHAR:
    return "KW_CHAR";
  case TokenType::KW_CONST:
    return "KW_CONST";
  case TokenType::KW_CONTINUE:
    return "KW_CONTINUE";
  case TokenType::KW_DEFAULT:
    return "KW_DEFAULT";
  case TokenType::KW_DO:
    return "KW_DO";
  case TokenType::KW_F64:
    return "KW_DOUBLE";
  case TokenType::KW_ELSE:
    return "KW_ELSE";
  case TokenType::KW_ENUM:
    return "KW_ENUM";
  case TokenType::KW_EXTERN:
    return "KW_EXTERN";
  case TokenType::KW_F32:
    return "KW_FLOAT";
  case TokenType::KW_FOR:
    return "KW_FOR";
  case TokenType::KW_IF:
    return "KW_IF";
  case TokenType::KW_IMPORT:
    return "KW_IMPORT";
  case TokenType::KW_I16:
    return "KW_I16";
  case TokenType::KW_I32:
    return "KW_I32";
  case TokenType::KW_I64:
    return "KW_I64";
  case TokenType::KW_RETURN:
    return "KW_RETURN";
  case TokenType::KW_SIZEOF:
    return "KW_SIZEOF";
  case TokenType::KW_STATIC:
    return "KW_STATIC";
  case TokenType::KW_STRUCT:
    return "KW_STRUCT";
  case TokenType::KW_SWITCH:
    return "KW_SWITCH";
  case TokenType::KW_UNSIGNED:
    return "KW_UNSIGNED";
  case TokenType::KW_VOID:
    return "KW_VOID";
  case TokenType::KW_VOLATILE:
    return "KW_VOLATILE";
  case TokenType::KW_WHILE:
    return "KW_WHILE";
  case TokenType::KW_TRAIT:
    return "KW_TRAIT";
  case TokenType::KW_THIS:
    return "KW_THIS";
  case TokenType::KW_ALIGNAS:
    return "KW_ALIGNAS";
  case TokenType::KW_ALIGNOF:
    return "KW_ALIGNOF";
  case TokenType::KW_ATOMIC:
    return "KW_ATOMIC";
  case TokenType::KW_BOOL:
    return "KW_BOOL";
  case TokenType::KW_COMPLEX:
    return "KW_COMPLEX";
  case TokenType::KW_GENERIC:
    return "KW_GENERIC";
  case TokenType::KW_IMAGINARY:
    return "KW_IMAGINARY";
  case TokenType::KW_NORETURN:
    return "KW_NORETURN";
  case TokenType::KW_STATIC_ASSERT:
    return "KW_STATIC_ASSERT";
  case TokenType::KW_THREAD_LOCAL:
    return "KW_THREAD_LOCALreturn ";
  case TokenType::PLUS:
    return "PLUS";
  case TokenType::MINUS:
    return "MINUSreturn ";
  case TokenType::STAR:
    return "STAR";
  case TokenType::SLASH:
    return "SLASH";
  case TokenType::PERCENT:
    return "PERCENTreturn ";
  case TokenType::AMP:
    return "AMPreturn ";
  case TokenType::PIPE:
    return "PIPE";
  case TokenType::CARET:
    return "CARET";
  case TokenType::TILDE:
    return "TILDEreturn ";
  case TokenType::BANG:
    return "BANG";
  case TokenType::ASSIGN:
    return "ASSIGNreturn ";
  case TokenType::LT:
    return "LTreturn ";
  case TokenType::GT:
    return "GT";
  case TokenType::QUESTION:
    return "QUESTION";
  case TokenType::COLON:
    return "COLON";
  case TokenType::SEMICOLON:
    return "SEMICOLON";
  case TokenType::COMMA:
    return "COMMA";
  case TokenType::DOT:
    return "DOT";
  case TokenType::LPAREN:
    return "LPARENT";
  case TokenType::RPAREN:
    return "RPAREN";
  case TokenType::LBRACE:
    return "LBRACE";
  case TokenType::RBRACE:
    return "RBRACE";
  case TokenType::LBRACKET:
    return "LBRACKET";
  case TokenType::RBRACKET:
    return "RBRACKET";
  case TokenType::EQ_EQ:
    return "EQ_EQ";
  case TokenType::BANG_EQ:
    return "BANG_EQ";
  case TokenType::LT_EQ:
    return "LT_EQ";
  case TokenType::GT_EQ:
    return "GT_EQ";
  case TokenType::AMP_AMP:
    return "AMP_AMP";
  case TokenType::PIPE_PIPE:
    return "PIPE_PIPE";
  case TokenType::PLUS_PLUS:
    return "PLUS_PLUS";
  case TokenType::PLUS_EQ:
    return "PLUS_EQ";
  case TokenType::MINUS_EQ:
    return "MINUS_EQ";
  case TokenType::STAR_EQ:
    return "STAR_EQ";
  case TokenType::SLASH_EQ:
    return "SLASH_EQ";
  case TokenType::PERCENT_EQ:
    return "PERCENT_EQ";
  case TokenType::AMP_EQ:
    return "AMP_EQ";
  case TokenType::PIPE_EQ:
    return "PIPE_EQ";
  case TokenType::CARET_EQ:
    return "CARET_EQ";
  case TokenType::ARROW:
    return "ARROW";
  case TokenType::ELLIPSIS:
    return "ELLIPSIS";
  case TokenType::MINUS_MINUS:
    return "MINUS_MINUS";
  default:
    return "<ERROR:UNKNOWN>";
  }
}

bool Lexer::isHexPrefix() const {
  return peek() == '0' && (peekNext() == 'x' || peekNext() == 'X');
}

bool Lexer::isBinaryPrefix() const {
  return peek() == '0' && (peekNext() == 'b' || peekNext() == 'B');
}
Lexer::Lexer(std::string source, std::string filename)
    : source_(std::move(source)), filename_(std::move(filename)) {}

bool Lexer::isAtEnd() const { return pos_ >= source_.size(); }

char Lexer::peek() const {
  if (isAtEnd())
    return '\0';
  return source_[pos_];
}

char Lexer::peekNext() const {
  if (pos_ + 1 >= source_.size())
    return '\0';
  return source_[pos_ + 1];
}

char Lexer::advance() {
  if (isAtEnd())
    return '\0';
  char c = source_[pos_++];
  if (c == '\n') {
    line_++;
    col_ = 1;
  } else {
    col_++;
  }
  return c;
}

bool Lexer::match(char expected) {
  if (isAtEnd())
    return false;
  if (source_[pos_] != expected)
    return false;
  advance();
  return true;
}

SourceLocation Lexer::currentLocation() const {
  SourceLocation loc(line_, col_);
  loc.filename = filename_;
  return loc;
}

Token Lexer::makeToken(TokenType type, const std::string &lexeme,
                       SourceLocation loc) const {
  return Token(type, lexeme, loc);
}

void Lexer::skipWhitespaceAndComments() {
  while (!isAtEnd()) {
    char c = peek();
    if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
      advance();
    } else if (c == '/' && peekNext() == '/') {
      while (!isAtEnd() && peek() != '\n')
        advance();
    } else if (c == '/' && peek() == '*') {
      advance();
      advance();
      while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
          advance();
          advance();
          break;
        }
        advance();
      }
    } else {
      break;
    }
  }
}
Token Lexer::identifierOrKeyword() {

  SourceLocation start = currentLocation();
  size_t startPos = pos_;

  while (!isAtEnd() &&
         (std::isalnum(static_cast<unsigned char>(peek()) || peek() == '_')))
    advance();
  std::string text = source_.substr(startPos, pos_ - startPos);
  auto it = keywords.find(text);
  if (it != keywords.end()) {
    return makeToken(it->second, text, start);
  }
  return makeToken(TokenType::IDENTIFIER, text, start);
}
static bool xdigit(char c) {
  return std::isxdigit(static_cast<unsigned char>(c));
}
void Lexer::consumeHexNumber(bool &isFloat) {
  advance();
  advance();

  while (!isAtEnd() && xdigit(peek()))
    advance();
  if (!isAtEnd() && peek() == '.') {
    isFloat = true;
    while (!isAtEnd() && xdigit(peek()))
      advance();
  }

  if (!isAtEnd() && (peek() == 'p' || peek() == 'P')) {
    isFloat = true;
    advance();

    if (!isAtEnd() && (peek() == '+' || peek() == '-'))
      advance();

    while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))) {
      advance();
    }
  }
}

void Lexer::consumeBinaryNumber() {
  advance();
  advance();
  while (!isAtEnd() && (peek() == '0' || peek() == '1')) {
    advance();
  }
}

void Lexer::consumeDecimal(bool &isFloat) {
  while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek())))
    advance();
  if (!isAtEnd() && peek() == '.') {
    advance();
    isFloat = true;
  }
  while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek())))
    advance();

  // Decimal exponent
  if (!isAtEnd() && (peek() == 'e' || peek() == 'E')) {
    isFloat = true;
    advance();

    if (!isAtEnd() && (peek() == '+' || peek() == '-'))
      advance();

    while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))) {
      advance();
    }
  }
}

void Lexer::consumeNumberSuffix() {
  while (!isAtEnd() && std::isalpha(static_cast<unsigned char>(peek()))) {
    advance();
  }
}

Token Lexer::number() {
  SourceLocation start = currentLocation();
  size_t startPos = pos_;
  bool isFloat = false;

  if (isHexPrefix()) {
    consumeHexNumber(isFloat);
  } else if (isBinaryPrefix()) {
    consumeBinaryNumber();
  } else {
    consumeDecimal(isFloat);
  }
  consumeNumberSuffix();
  std::string text = source_.substr(startPos, pos_ - startPos);
  return makeToken(isFloat ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL,
                   text, start);
}

Token Lexer::stringLiteral() {
  SourceLocation start = currentLocation();
  size_t startPos = pos_;
  advance();
  while (!isAtEnd() && peek() != '"') {
    if (peek() == '\\') {
      advance();
      if (!isAtEnd())
        advance();
    } else if (peek() == '\n') {
      break;
    } else {
      advance();
    }
  }
  if (!isAtEnd() && peek() == '"')
    advance();
  std::string text = source_.substr(startPos, pos_ - startPos);
  return makeToken(TokenType::STRING_LITERAL, text, start);
}

Token Lexer::charLiteral() {
  SourceLocation start = currentLocation();
  size_t startPos = pos_;
  advance();
  while (!isAtEnd() && peek() != '\'') {
    if (peek() == '\\') {
      advance();
      if (!isAtEnd())
        advance();
    } else if (peek() == '\n') {
      break;
    } else {
      advance();
    }
  }
  if (!isAtEnd() && peek() == '\'')
    advance();
  std::string text = source_.substr(startPos, pos_ - startPos);
  return makeToken(TokenType::CHAR_LITERAL, text, start);
}

Token Lexer::nextToken() {
  skipWhitespaceAndComments();
  if (isAtEnd()) {
    return makeToken(TokenType::END_OF_FILE, "", currentLocation());
  }
  SourceLocation start = currentLocation();
  char c = peek();

  if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
    return identifierOrKeyword();
  }
  if (std::isdigit(static_cast<unsigned char>(c))) {
    return number();
  }
  if (c == '.') {
    if (peekNext() == '.' && pos_ + 2 < source_.size() &&
        source_[pos_ + 2] == '.') {
      SourceLocation loc = currentLocation();
      advance();
      advance();
      advance();
      return makeToken(TokenType::ELLIPSIS, "...", loc);
    }
    if (std::isdigit(static_cast<unsigned char>(peekNext()))) {
      return number();
    }
    advance();
    return makeToken(TokenType::DOT, ".", start);
  }

  if (c == '"') {
    return stringLiteral();
  }
  if (c == '\'') {
    return charLiteral();
  }

  switch (c) {

  case '+': {
    advance();
    if (match('+'))
      return makeToken(TokenType::PLUS_PLUS, "++", start);
    if (match('='))
      return makeToken(TokenType::PLUS_EQ, "+=", start);
    return makeToken(TokenType::PLUS, "+", start);
  }
  case '-': {
    advance();
    if (match('-'))
      return makeToken(TokenType::MINUS_MINUS, "--", start);
    if (match('>'))
      return makeToken(TokenType::ARROW, "->", start);
    if (match('='))
      return makeToken(TokenType::MINUS_EQ, "-=", start);
    return makeToken(TokenType::MINUS, "-", start);
  }
  case '*': {
    advance();
    if (match('='))
      return makeToken(TokenType::STAR_EQ, "*=", start);
    return makeToken(TokenType::STAR, "*", start);
  }
  case '/': {
    advance();
    if (match('='))
      return makeToken(TokenType::SLASH_EQ, "/=", start);
    return makeToken(TokenType::SLASH, "/", start);
  }
  case '%': {
    advance();
    if (match('='))
      return makeToken(TokenType::PERCENT_EQ, "%=", start);
    return makeToken(TokenType::PERCENT, "%", start);
  }
  case '=': {
    advance();
    if (match('='))
      return makeToken(TokenType::EQ_EQ, "==", start);
    return makeToken(TokenType::ASSIGN, "=", start);
  }
  case '!': {
    advance();
    if (match('='))
      return makeToken(TokenType::BANG_EQ, "!=", start);
    return makeToken(TokenType::BANG, "!", start);
  }
  case '<': {
    advance();
    if (match('='))
      return makeToken(TokenType::LT_EQ, "<=", start);
    return makeToken(TokenType::LT, "<", start);
  }
  case '>': {
    advance();
    if (match('='))
      return makeToken(TokenType::GT_EQ, ">=", start);
    return makeToken(TokenType::GT, ">", start);
  }
  case '&': {
    advance();
    if (match('&'))
      return makeToken(TokenType::AMP_AMP, "&&", start);
    if (match('='))
      return makeToken(TokenType::AMP_EQ, "&=", start);
    return makeToken(TokenType::AMP, "&", start);
  }
  case '|': {
    advance();
    if (match('|'))
      return makeToken(TokenType::PIPE_PIPE, "||", start);
    if (match('='))
      return makeToken(TokenType::PIPE_EQ, "|=", start);
    return makeToken(TokenType::PIPE, "|", start);
  }
  case '^': {
    advance();
    if (match('='))
      return makeToken(TokenType::CARET_EQ, "^=", start);
    return makeToken(TokenType::CARET, "^", start);
  }
  case '(':
    advance();
    return makeToken(TokenType::LPAREN, "(", start);
  case ')':
    advance();
    return makeToken(TokenType::RPAREN, ")", start);
  case '{':
    advance();
    return makeToken(TokenType::LBRACE, "{", start);
  case '}':
    advance();
    return makeToken(TokenType::RBRACE, "}", start);
  case '[':
    advance();
    return makeToken(TokenType::LBRACKET, "[", start);
  case ']':
    advance();
    return makeToken(TokenType::RBRACKET, "]", start);
  case ';':
    advance();
    return makeToken(TokenType::SEMICOLON, ";", start);
  case ',':
    advance();
    return makeToken(TokenType::COMMA, ",", start);
  case ':':
    advance();
    return makeToken(TokenType::COLON, ":", start);
  case '?':
    advance();
    return makeToken(TokenType::QUESTION, "?", start);
  case '~':
    advance();
    return makeToken(TokenType::TILDE, "~", start);
  default: {
    std::string lex(1, c);
    advance();
    return makeToken(TokenType::UNKNOWN, lex, start);
  }
  }
}
std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (true) {
    Token tok = nextToken();
    tokens.push_back(tok);
    if (tok.type == TokenType::END_OF_FILE)
      break;
  }
  return tokens;
}
