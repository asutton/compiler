#pragma once


/// The base class of all types in the language.
struct type 
{
  virtual ~type() = default;
};


/// Represents the object type 'bool'.
struct bool_type : type
{

};


/// Represents the object type 'int'.
struct int_type : type
{

};


/// Represents the type `t&`. Note that `t` must be an object type.
struct ref_type : type
{
  ref_type(type* t) : obj(t) { }

  /// The object type.
  type* obj;
};
