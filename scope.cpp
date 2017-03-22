#include "scope.hpp"

void
environment::insert(symbol* s, decl* d)
{
  /// FIXME: Make sure this doesn't fail.
  map.insert({s, d});
}

decl*
environment::find(symbol* s)
{
  auto iter = map.find(s);
  if (iter != map.end())
    return iter->second;
  else
    return nullptr;
}
