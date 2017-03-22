#pragma once

#include "symbols.hpp"

#include <unordered_map>

struct context;
struct token;
struct type;
struct expr;
struct decl;
struct stmt;

/// A binding environment associates symbols with their declarations.
struct environment
{
  /// Register a new binding between a name and its declaration.
  void insert(symbol*, decl*);

  /// Lookup the current binding for a symbol. Returns nullptr if the symbol
  /// is unbound.
  decl* find(symbol*);

  std::unordered_map<symbol*, decl*> map;
};
