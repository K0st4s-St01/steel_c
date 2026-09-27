#pragma once

#include "../ast/ast_header.hpp"
#include "../module/program.hpp"
#include <unordered_set>

class Parser {
private:
  std::vector<Token> tokens_;
  size_t pos_ = 0;
  std::vector<std::string> errors_;
  std::string filename_;
  std::vector<DeclPtr> pending_decls_;
  std::vector<std::string> generic_param_stack_;
  std::unordered_set<std::string> genericParamSet_;
  const Token &peek() const;
  const Token &peekNext() const;
  const Token &previous() const;

private://TOKENS
  bool isAtEnd() const;
  bool check(TokenType t) const;
  bool checkNext(TokenType t) const;
  bool match(TokenType t);
  bool match(std::initializer_list<TokenType> types);
  Token advance();
  Token consume(TokenType t, const std::string &msg);
  void synchronize();
  bool isType(const Token &tok) const;
  bool canBeTypeStart() const;
  bool isAssignementOp(TokenType t) const;

private://DECL
  std::unique_ptr<Module> parseModule();
  DeclPtr parseImport();
  Type parseType();
  DeclPtr parseDeclarationAfterType(Type baseType, SourceLocation start_loc);
  std::unique_ptr<VarDecl> parseVarDecl();
  std::unique_ptr<FunctionDecl>
  parseFunctionDeclTail(Type returnType, std::string name, SourceLocation loc);
  std::vector<Param> parseParamList();
  Param parseParam();
  std::vector<std::string> parseGenericParams();
  std::vector<std::unique_ptr<Type>> parseGenericArgs();
  bool isGenericParam(const std::string &name) const;
  void pushGenericParams(const std::vector<std::string> &params);
  void popGenericParams(const std::vector<std::string> &params);

  DeclPtr parseStruct(Type &baseType, SourceLocation loc);
  DeclPtr parseMethod(Type returnType, std::string name, SourceLocation loc);
  DeclPtr parseEnum(Type &baseType, SourceLocation loc);

private://STMT
  StmtPtr parseStatement();
  StmtPtr parseCompoundStatement();
  StmtPtr parseIfStatement();
  StmtPtr parseWhileStatement();
  StmtPtr parseDoWhileStatement();
  StmtPtr parseForStatement();
  StmtPtr parseSwitchStatement();
  StmtPtr parseCaseStatement();
  StmtPtr parseReturnStatement();
  StmtPtr parseBreakStatement();
  StmtPtr parseContinueStatement();
  StmtPtr parseExpressionStatement();

private://EXPR
  ExprPtr parseExpr();
  ExprPtr parseAssignment();
  ExprPtr parseConditional();
  ExprPtr parseLogicalOr();
  ExprPtr parseLogicalAnd();
  ExprPtr parseBitwiseOr();
  ExprPtr parseBitwiseXor();
  ExprPtr parseBitwiseAnd();
  ExprPtr parseEquality();
  ExprPtr parseRelational();
  ExprPtr parseShift();
  ExprPtr parsePostfix();
  ExprPtr parseCallOrPostfixWithCallee(ExprPtr callee);
  ExprPtr parseInitializer();
  
public:
  explicit Parser(std::vector<Token> tokens,std::string filename="<input>");
  std::unique_ptr<Module> parse();
  const inline std::vector<std::string>& getErrors() const {return errors_;}
};
