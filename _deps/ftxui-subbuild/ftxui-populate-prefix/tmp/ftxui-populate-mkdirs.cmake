# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-src"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-build"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/tmp"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/src"
  "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/aidenallen/Desktop/COP4530/Homework/proj5/proj5_pt2/spellcheck/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
