#pragma once

#include "overload.hpp"
#include "forEach.hpp"

// namu universal DECL macro:
//  NAMU_DECL is generalized API used to describe the metadata of class in namu.
//  NAMU_DECL can be used to define detailed metadata about a class by chaining sub-command sets.
//  with NAMU macro, I can clarify that those INIT_META, VISIT are should be after of NAMU macro.
//  and limit the scope of availbility.
//  these macros which are available only inside of NAMU macro are called to sub-commands.
//
// Usage:
//  use NAMU_DECL macro at declaration of your class.
//
//  class Foo {
//      NAMU_DECL(cmd1(arg1, arg2, ...), cmd2(arg1, arg2, ...), ...)
//
//  public:
//      ...and your codes...
//  };

#define _ON_EACH_DECL(cmd) __NAMU__DECL_##cmd
#define NAMU(...) NAMU_EACH(_ON_EACH_DECL, __VA_ARGS__)
