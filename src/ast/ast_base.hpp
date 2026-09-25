#pragma once

#include "../lexer/lexer.hpp"
#include "../utils/source_location.hpp"
#include <memory>
#include <sstream>
#include <vector>

struct ASTNode {
  SourceLocation loc_;
  ASTNode(SourceLocation loc) : loc_(loc) {}
};
enum class Type_of_Type { STRUCT, ENUM };
struct Type {
  std::vector<std::string> specifiers;
  std::vector<TokenType> specTokens;
  int pointer_depth = 0;
  Type_of_Type type_of_type;
  std::string tag;
  std::vector<std::unique_ptr<Type>> generic_args;

  std::string to_string() const {
    std::ostringstream str_builder;
    for (auto &s : specifiers) {
      str_builder << s << " ";
    }
    if (!tag.empty()) {
      str_builder << tag << "";

      if (!generic_args.empty()) {
        str_builder << "<";
        for (size_t i = 0; i < generic_args.size(); i++) {
          if (i)
            str_builder << ",";
          str_builder << generic_args[i]->to_string();
        }
        str_builder << ">" << " ";
      }
    }

    for (int i = 0; i < pointer_depth; i++) {
      str_builder << "*";
    }

    return str_builder.str();
  }
  Type() = default;
};

struct Expr :ASTNode{using ASTNode::ASTNode;};
struct Stmt :ASTNode{using ASTNode::ASTNode;};
struct Decl :ASTNode{using ASTNode::ASTNode;};
