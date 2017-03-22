#pragma once

struct type;
struct expr;
struct decl;
struct stmt;


/// The (AST) context is a repository of facilities used to help construct
/// well-formed abstract syntaxt trees.
struct context
{
  context();
  ~context();

  type* bool_ty;
  type* int_ty;
};
