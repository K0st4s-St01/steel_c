#pragma once
#include "ast_base.hpp"

struct CompoundStmt : Stmt{
  std::vector<StmtPtr> stmts;
};

struct DeclStmt : Stmt{
  DeclPtr decl;
};

struct ExprStmt : Stmt{
  ExprPtr expr;
};
