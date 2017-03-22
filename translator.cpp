#include "translator.hpp"
#include "tokens.hpp"
#include "types.hpp"
#include "exprs.hpp"
#include "decls.hpp"
#include "stmts.hpp"
#include "context.hpp"


translator::translator(context& c)
  : cxt(&c)
{ }

decl*
translator::on_program(const std::vector<stmt*>& ss)
{
  prog_decl* prog = new prog_decl();
  for (stmt* s : ss)
    prog->push_back(s);
  return prog;
}

stmt*
translator::on_declaration_statement(decl* d)
{
  return new decl_stmt(d);
}

stmt*
translator::on_expression_statement(expr* e)
{
  return new expr_stmt(e);
}

decl*
translator::on_variable_declaration(type* t, symbol* n)
{
  // FIXME: Check for an existing declaration of n.
  var_decl* var = new var_decl(n, t);
  // FIXME: Add the declaration of n as a variable.
  return var;
}

decl*
translator::on_variable_completion(decl* d, expr* e)
{
  var_decl* var = static_cast<var_decl*>(d);
  // FIXME: Verify that the type of the initializer matches the declared
  // type of the variable.
  var->init = e;
  return var;
}


type*
translator::on_bool_type()
{
  return cxt->bool_ty;
}

type*
translator::on_int_type()
{
  return cxt->int_ty;
}

expr*
translator::on_add(expr* e1, expr* e2)
{
  return nullptr;
}

expr*
translator::on_sub(expr* e1, expr* e2)
{
  return nullptr;
}

expr*
translator::on_mul(expr* e1, expr* e2)
{
  return nullptr;
}

expr*
translator::on_div(expr* e1, expr* e2)
{
  return nullptr;
}

expr*
translator::on_rem(expr* e1, expr* e2)
{
  return nullptr;
}

expr*
translator::on_neg(expr*)
{
  return nullptr;
}

expr*
translator::on_true(token*)
{
  return new bool_expr(cxt->bool_ty, true);
}

expr*
translator::on_false(token*)
{
  return new bool_expr(cxt->bool_ty, false);
}

expr*
translator::on_int(token* tok)
{
  int_token* num = static_cast<int_token*>(tok);
  return new int_expr(cxt->int_ty, num->value);
}

expr*
translator::on_id(symbol* sym)
{
  // FIXME: Implement lookup.
  return nullptr; 
}


symbol* 
translator::on_identifier(token* tok)
{
  id_token* id = dynamic_cast<id_token*>(tok);
  return id->sym;
}
