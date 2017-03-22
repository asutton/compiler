#pragma once

struct type;
struct decl;


/// The base class of all expressions in the language.
struct expr
{
  expr(type* t) : ty(t) { }
  virtual ~expr() = default;

  /// The type of the expression.
  type* ty;
};


/// Represents boolean literals.
struct bool_expr : expr
{
  bool_expr(type* t, bool b) : expr(t), value(b) { }
  
  /// The value of the literal expression.
  bool value;
};


/// Represents integer literals.
struct int_expr : expr
{
  int_expr(type* t, int n) : expr(t), value(n) { }

  /// The value of the literal expression.
  int value;
};


/// Represents a reference to a declaration.
struct ref_expr : expr
{
  ref_expr(type* t, decl* d) : expr(t), ref(d) { }

  /// The referenced declration.
  decl* ref;
};
