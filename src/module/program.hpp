#include "../ast/ast_header.hpp"
#include <filesystem>

struct Module{
  std::string name;
  std::filesystem::path module_path;
  std::vector<DeclPtr> declarations;
  bool isEntry = false;
  bool hasMain = false;  
};

struct Program{
  std::string name;
  std::vector<std::unique_ptr<Module>> modules;
};


