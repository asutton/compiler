#pragma once

struct type;
struct decl;


/// The base class of all expressions in the language.
struct expr
{
  virtual ~expr() = default;

  /// The type of the expression.
  type* ty;
};


/// Represents boolean literals.
struct bool_expr : expr
{
  bool value;
};


/// Represents integer literals.
struct int_expr : expr
{
  int value;
};


/// Represents a reference to a declaration.
struct ref_expr : expr
{
  ref_expr(decl* d) : ref(d) { }

  /// The referenced declration.
  decl* ref;
};
