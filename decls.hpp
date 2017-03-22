#pragma once

#include "symbols.hpp"

struct type;
struct expr;


/// The base class of all declarations in the language. All declarations have
/// a name and type.
struct decl
{
  virtual ~decl() = default;

  /// The name of the declaration.
  symbol name;

  /// The type of the declaration.
  type* ty;
};


/// Represents a variable declaration.
struct var_decl : decl
{
  /// The initial value of the declaration.
  expr* init;
};
