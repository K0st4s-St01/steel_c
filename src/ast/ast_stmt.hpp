#pragma once
#include "ast_base.hpp"

struct CompoundStmt : Stmt{
  std::vector<StmtPtr> stmts;
};
