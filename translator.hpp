#pragma once

#include "symbols.hpp"
#include "scope.hpp"

#include <vector>


struct token;
struct context;
struct type;
struct expr;
struct decl;
struct stmt;


/// Represents a translation from concrete to abstract syntax. This class
/// defines and implements the semantic actions of the parser.
///
/// \todo Consider making this an abstract class to allow for multiple
/// translation schemes.
struct translator
{
  translator(context&);

  decl* on_program(const std::vector<stmt*>&);

  stmt* on_declaration_statement(decl*);
  stmt* on_expression_statement(expr*);

  decl* on_variable_declaration(type*, symbol*);
  decl* on_variable_completion(decl*, expr*);

  type* on_bool_type();
  type* on_int_type();

  expr* on_add(expr*, expr*);
  expr* on_sub(expr*, expr*);
  expr* on_mul(expr*, expr*);
  expr* on_div(expr*, expr*);
  expr* on_rem(expr*, expr*);
  expr* on_neg(expr*);
  expr* on_true(token*);
  expr* on_false(token*);
  expr* on_int(token*);
  expr* on_id(symbol*);

  symbol* on_identifier(token*);

  /// The context provides facilities for creating abstract syntax trees.
  context* cxt;

  /// The name binding environment.
  environment env;
};
