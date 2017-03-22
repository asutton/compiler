#pragma once

#include <string>
#include <unordered_map>


/// A symbol is a pointer to a string the symbol table.
using symbol = const std::string*;


/// The symbol table stores the strings representing each identifer in
/// the input source. 
///
/// Each symbols is associated with an object to be determined later.
struct symbol_table
{
  /// Inserts a new symbol into the symbol table. If the symbol already
  /// exists, no changes are made. Returns the inserted or existing symbol.
  symbol insert(const std::string&);

  /// Returns the symbol corresponding to the string. If the symbol is not
  /// in the table, this returns nullptr.
  symbol find(const std::string&);

private:
  std::unordered_map<std::string, void*> syms;
};


