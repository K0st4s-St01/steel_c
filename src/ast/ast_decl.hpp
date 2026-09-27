#pragma once
#include "ast_base.hpp"

struct ImportDecl : Decl{
  std::string module;
};

struct VarDecl :Decl{
  Type type;
  std::string name;
  ExprPtr init;
  bool isArray = false;
  ExprPtr arraySize;
};

struct Param{
  Type type;
  std::string name;
  SourceLocation loc;
};

struct FunctionDecl : Decl{
  Type returnType;
  std::string name;
  std::vector<Param> params;
  bool isVarArgs;
  bool isPrototype;
  StmtPtr bodt;
};

struct StructDecl : Decl{
  std::string name;
  std::vector<std::string> genericParams;
  std::vector<std::unique_ptr<VarDecl>> fields;
};

struct Enumerator{
  std::string name;
  std::unique_ptr<Type> payload;
};

struct EnumDecl : Decl{
  std::string name;
  std::vector<Enumerator> enumerators;
};


