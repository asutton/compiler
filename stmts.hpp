#pragma once

struct expr;
struct decl;


/// The base class of all statements in the language.
struct stmt
{
  virtual ~stmt() = default;
};


/// A statement that evaluates an expression.
struct expr_stmt : stmt
{
  /// The expression to be evaluated.
  expr* eval;
};

/// A statement that contains a declration.
struct decl_stmt : stmt
{
  /// The declared entity.
  decl* entity;
};
