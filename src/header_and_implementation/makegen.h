
#ifndef MAKEFILE
#define MAKEFILE

#include "qadon-1.0.0/qadon.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

class Makefile {

public:
  // strings
  std::string cxx;
  std::string build_name;
  std::string build_directory;
  std::string main_file_name;
  std::string main_file_directory;

  // vectors
  std::vector<std::string> cxx_flags;
  std::vector<std::string> ld_flags;

  // maps
  std::map<std::string, std::string> source_files;

  // setters
  void set_compiler(std::string cxx_compiler);
  void set_build_name(std::string build_name_in);
  void set_build_directory(std::string build_directory_in);
  void set_main_file_name(std::string main_file_name_in);
  void set_main_file_directory(std::string main_file_directory_in);

  // getters
  std::string get_compiler();
  std::string get_build_name();
  std::string get_build_directory();
  std::string get_main_file_name();
  std::string get_main_file_directory();

  // adders
  void add_cxx_flag(std::string cxx_flag);
  void add_ld_flag(std::string ld_flag);
  void add_source_file(std::string file_name, std::string file_directory);

  // removers
  void remove_cxx_flag(std::string cxx_flag);
  void remove_ld_flag(std::string ld_flag);
  void remove_source_file(std::string file_name);

  // generators
  void generate_make_config();
  void generate_source_config();
  void generate_make_file();

  // readers
  void read_config(std::string config_directory, std::string build_name);

  // parsers
  void parse_cxxflags(std::string cxx_flags_in);
  void parse_ldflags(std::string ld_flags_in);
};

#endif
