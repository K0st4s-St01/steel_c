#pragma once
#include "ast_base.hpp"
#include <optional>

struct CompoundStmt : Stmt {
  std::vector<StmtPtr> stmts;
};

struct DeclStmt : Stmt {
  DeclPtr decl;
};

struct ExprStmt : Stmt {
  ExprPtr expr;
};

struct IfStmt : Stmt {
  ExprPtr condition;
  StmtPtr thenBranch;
  StmtPtr elseBranch;
};

struct WhileStmt : Stmt {
  ExprPtr condition;
  StmtPtr body;
};

struct DoWhileStmt : Stmt {
  ExprPtr condition;
  StmtPtr body;
};

struct ForStmt : Stmt {
  ExprPtr init, condition, incr;
  StmtPtr body;
};

struct ReturnStmt : Stmt{
  std::optional<std::string> label;
  ExprPtr ret;
};

struct BreakSmt : Stmt{
  std::optional<std::string> label;
};

struct ContinueStmt : Stmt{
  std::optional<std::string> label;
};

struct LabelStmt : Stmt{
  std::string label;
  StmtPtr stmt;
};

struct SwithStmt{
  ExprPtr condition;
  StmtPtr body;
};

struct CaseStmt{
  ExprPtr cond;
  StmtPtr body;
};

struct DefaultStmt{
  StmtPtr body;
};
