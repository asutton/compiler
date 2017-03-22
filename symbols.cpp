#include "symbols.hpp"


symbol* 
symbol_table::insert(const std::string& str)
{
  auto result = syms.insert({str, nullptr});
  return &result.first->first;
}

symbol*
symbol_table::find(const std::string& str)
{
  auto iter = syms.find(str);
  return &iter->first;
}
