
cmake_minimum_required (VERSION 3.11)

# --- Fetch ftxui --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG origin/main
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)

endif()

# ------------------------------------------------------------------------------

project(ftxui-starter
  LANGUAGES CXX
  VERSION 1.0.0
)

add_library(hashtable OBJECT hashtable.h)
add_executable(proj5.x spellcheck.cpp $<TARGET_OBJECTS:hashtable>)

target_include_directories(proj5.x PRIVATE src)

target_link_libraries(proj5.x
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
