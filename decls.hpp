#pragma once

#include "symbols.hpp"

#include <vector>

struct type;
struct expr;
struct stmt;


/// The base class of all declarations in the language. All declarations have
/// a name and type.
struct decl
{
  virtual ~decl() = default;
};


/// Represents a variable declaration.
struct var_decl : decl
{
  var_decl(symbol* n, type* t) : name(n), ty(t), init(nullptr) { }

  /// The name of the declaration.
  symbol* name;

  /// The type of the declaration.
  type* ty;

  /// The initial value of the declaration.
  expr* init;
};


/// A program is represented as a sequence of statements.
struct prog_decl : decl, std::vector<stmt*>
{
};
