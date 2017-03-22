#pragma once

struct expr;
struct decl;


/// The base class of all statements in the language.
struct stmt
{
  virtual ~stmt() = default;
};


/// A statement that evaluates an expression, discarding the result.
struct expr_stmt : stmt
{
  expr_stmt(expr* e) : expression(e) { }

  /// The statement's expression.
  expr* expression;
};

/// A statement that contains a declaration.
struct decl_stmt : stmt
{
  decl_stmt(decl* d) : entity(d) { }

  /// The declared entity.
  decl* entity;
};
