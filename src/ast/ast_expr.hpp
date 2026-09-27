#pragma once
#include "ast_base.hpp"
struct LiteralExpr : Expr {
  Token token;
};

struct IdentifierExpr : Expr {
  std::string name;
};

struct BinaryExpr : Expr {
  TokenType op;
  std::string op_lexme;
  ExprPtr left, right;
};

struct AssignmentExpr : Expr {
  TokenType op;
  std::string lexme;
  ExprPtr target, value;
};

struct UnaryExpr : Expr {
  TokenType op;
  std::string lexme;
  ExprPtr operand;
};

struct MemberExpr : Expr {
  ExprPtr Object;
  std::string member;
};

struct ArrayAccessExpr : Expr {
  ExprPtr arr, index;
};

struct ContditionalExpr : Expr {
  ExprPtr cond, thenExpr, elseExpr;
};

struct SizeofExpr : Expr {
  bool isType;
  Type type;
  ExprPtr expr;
};

struct CastExpr : Expr {
  Type type;
  ExprPtr expr;
};

struct InitListExpr : Expr {
  std::vector<ExprPtr> elements;
};
