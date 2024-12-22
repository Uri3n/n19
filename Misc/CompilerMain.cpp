/*
* Copyright (c) 2024 Diago Lima
* All rights reserved.
*
* This software is licensed under the BSD 3-Clause "New" or "Revised" license
* found in the LICENSE file in the root directory of this project's source tree.
*/

#define CURRENT_TEST "/Users/Diago/Desktop/compiler_tests/test2.txt"

#include <Core/Try.hpp>
#include <Frontend/Lexer.hpp>
#include <Core/Bytes.hpp>
#include <Core/ConIO.hpp>
#include <Core/Time.hpp>
#include <iostream>
#include <Core/ArgParse.hpp>

using namespace n19;

struct foo {
  int x;
  int y;
};

// struct MyArgs : argp::Parser {
//   int64_t& num_jobs  = arg<int64_t>("--num-jobs", "-j", "numba of jobs");
//   sys::String& name  = arg<sys::String>("--input", "-i", "the input file.", "Default value!!!");
//   bool& verbose      = arg<bool>("--verbose", "-v", "verbose mode");
// };

int main(int argc, char** argv){

  const auto time = time::LocalTime::from_utc();
  if(!time) {
    return 1;
  }

  std::cout << time->strings().format() << std::endl;

  // std::vector<sys::String> strs = { "--num-jobs=42069", "--verbose=false" };
  //
  // MyArgs args;
  // auto res = args.style(argp::ArgStyle::UNIX)
  //   .take_argv(std::move(strs))
  //   .parse(outs());
  //
  // if(!res) {
  //   return 1;
  // }
  //
  // std::cout << "num_jobs=" << args.num_jobs << '\n';
  // std::cout << "name=" << args.name << '\n';
  // std::cout << std::boolalpha << "verbose=" << args.verbose << std::endl;
  //
  // args.help(outs());
  //
  // try {
  //   const auto file = MUST(FileRef::open(CURRENT_TEST));
  //   auto lxr = Lexer::create(*file);
  //   if(!lxr) {
  //     return 1;
  //   }
  //
  //   lxr.value()->dump();
  // } catch(const std::exception& e) {
  //   std::cerr << "EXCEPTION: " << e.what() << std::endl;
  // }

  outs().flush();
  errs().flush();
  return 0;
}


