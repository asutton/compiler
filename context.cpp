#include "context.hpp"
#include "types.hpp"


context::context()
  : bool_ty(new bool_type()),
    int_ty(new int_type())
  { }

  context::~context()
  {
    delete bool_ty;
    delete int_ty;
  }
  