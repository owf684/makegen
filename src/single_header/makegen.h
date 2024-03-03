
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
  void set_compiler(std::string cxx_compiler)
  {
    cxx = cxx_compiler;
  }

  void set_build_name(std::string build_name_in)
  {
    build_name = build_name_in;
  }

  void set_build_directory(std::string build_directory_in)
  {
    build_directory = build_directory_in;
  }

  void set_main_file_name(std::string main_file_name_in)
  {
    main_file_name = main_file_name_in;
  }

  void set_main_file_directory(std::string main_file_directory_in)
  {
    main_file_directory = main_file_directory_in;
  }

  // getters
  std::string get_compiler()
  {
    return cxx;
  }

  std::string get_build_name()
  {
    return build_name;
  }

  std::string get_build_directory()
  {
    return build_directory;
  }

  std::string get_main_file_name()
  {
    return main_file_name;
  }

  std::string get_main_file_directory()
  {
    return main_file_directory;
  }

  // adders
  void add_cxx_flag(std::string cxx_flag)
  {
    cxx_flags.push_back(cxx_flag);
  }

  void add_ld_flag(std::string ld_flag)
  {
    ld_flags.push_back(ld_flag);
  }

  void add_source_file(std::string file_name, std::string file_directory)
  {
    source_files[file_name] = file_directory;
  }

  // removers
  void remove_cxx_flag(std::string cxx_flag)
  {
     bool cxx_flag_found = false;
        int i = 0;

        for(auto& flags : cxx_flags)
        {

            if (flags == cxx_flag)
            {
                cxx_flag_found = true;
                cxx_flags.erase(cxx_flags.begin()+i);
                break;
            }

            i++;
        }
  }
  void remove_ld_flag(std::string ld_flag)
  {
     bool ld_flag_found = false;
        int i = 0;

        for(auto& flags : ld_flags)
        {
            if ( flags == ld_flag )
            {
                ld_flag_found = true;
                ld_flags.erase(ld_flags.begin()+i);
                break;
            }
            ++i;
        }
  }
  void remove_source_file(std::string file_name)
  {
    source_files.erase(file_name);
  }

  // generators
  void generate_make_config()
  {
     qadon make_file_config;

        make_file_config["cxx"] = get_compiler();
        make_file_config["build_name"] = get_build_name();
        make_file_config["build_directory"] = get_build_directory();
        make_file_config["main_file_name"] = get_main_file_name();
        make_file_config["main_file_directory"] = get_main_file_directory();

        std::string CXXFLAGS = "CXXFLAGS= ";
        for(auto& flags : cxx_flags)
        {
            CXXFLAGS += " -"+flags;
        }
        make_file_config["cxx_flags"] = CXXFLAGS;

        std::string LDFLAGS = "LDFLAGS= ";
        for(auto& flags : ld_flags)
        {
            LDFLAGS += " -"+flags;
        }

        make_file_config.write(get_build_name() + ".makecfg");
  }

  void generate_source_config()
  {
    qadon source_file_config;

    for(const auto& pair : source_files)
    {
        source_file_config[pair.first] = pair.second;
    }

        source_file_config.write(get_build_name() + ".sourcecfg");
  }

  void generate_make_file()
  {
        std::ofstream new_makefile("Makefile");

        // writing CXX
        new_makefile << "CXX= " << get_compiler() << "\n";

        // writing CXXFLAGS
        std::string CXXFLAGS = "CXXFLAGS=";
        for(auto&flags : cxx_flags)
        {
            CXXFLAGS += " -" + flags;
        }
        new_makefile << CXXFLAGS << "\n";

        // writing LDFLAGS
        std::string LDFLAGS = "LDFLAGS=";
        for(auto&flags : ld_flags)
        {
            LDFLAGS += " -l"+flags;
        }
        new_makefile << LDFLAGS << "\n\n";

        // writing all
        new_makefile << "all: " << get_build_name() << "\n\n";

        // writing build_name and object file composition of entire build
        std::string main_object_file = get_main_file_name().substr(0,get_main_file_name().find('.')) + ".o";
        std::string back_slash = "\\";
 
        new_makefile << get_build_name() << ": " + main_object_file + " " + back_slash.substr(0,1) + "\n";

        for(const auto& pair : source_files)
        {
            std::string source_file_name = pair.first;
            int dot_index = source_file_name.find('.');
            source_file_name = source_file_name.substr(0,dot_index);
            new_makefile <<  "\t" + source_file_name + ".o " + back_slash.substr(0,1) + "\n";
        }

        // write build rule    
        new_makefile << "\n\t$(CXX) $(CXXFLAGS) $(LDFLAGS) -o " + get_build_name() + " " + get_build_directory() + main_object_file + " " + back_slash.substr(0,1) + "\n";
        for(const auto& pair : source_files)
        {
            std::string source_file_name = pair.first;
            int dot_index = source_file_name.find('.');
            source_file_name = source_file_name.substr(0,dot_index);
            new_makefile << "\t" + get_build_directory() + source_file_name + ".o " + back_slash.substr(0,1) + "\n";
        }

        // write rest of object files
       new_makefile << "\n\n" + main_object_file + ": \n";
       new_makefile << "\t $(CXX) $(CXXFLAGS) $(LDFLAGS) -c " + main_file_directory + main_file_name + " -o " + build_directory+main_object_file + "\n\n"; 
        
        for(const auto& pair : source_files)
        {
            std::string source_file_name = pair.first;
            int dot_index = source_file_name.find('.');
            source_file_name = source_file_name.substr(0,dot_index);
            new_makefile << source_file_name + ".o: \n";
            new_makefile << "\t $(CXX) $(CXXFLAGS) $(LDFLAGS) -c " + pair.second+pair.first + " -o " + get_build_directory() + source_file_name+".o\n\n";
        }

        new_makefile << "clean: " << std::endl;
        new_makefile << "\t rm -f " + get_build_directory() + "*.o " + get_build_name();
        new_makefile.close();
   
  }

  // readers
  void read_config(std::string config_directory, std::string build_name)
  {
          std::string s_makecfg = config_directory + "/" + build_name + ".makecfg";
        std::string s_sourcecfg = config_directory + "/" + build_name + ".sourcecfg";
        qadon q_makecfg(s_makecfg);
        qadon q_sourcecfg(s_sourcecfg);

        q_makecfg.print();
        q_sourcecfg.print();

        set_compiler(q_makecfg["cxx"]);
        set_build_name(q_makecfg["build_name"]);
        set_build_directory(q_makecfg["build_directory"]);
        set_main_file_name(q_makecfg["main_file_name"]);
        set_main_file_directory(q_makecfg["main_file_directory"]);

        parse_cxxflags(q_makecfg["cxx_flags"]);
        parse_ldflags(q_makecfg["ld_flags"]);

        source_files.clear();
        for (const auto& pair: q_sourcecfg)
        {
            source_files[pair.first] = pair.second;
        }
  }

  // parsers
  void parse_cxxflags(std::string cxx_flags_in)
  {
           // iterate through cxx flags
        std::string parsed_string = "";
        bool end_of_var_name = false;
        bool f = false;
        bool e = false;
        int i = 0;
        for(auto& c : cxx_flags_in)
        {
            // during the first few iterations we ne need to ignore characters CXXFLAGS and = since 
            // they are not needed in the cxx_flags_vector
            if ( ( parsed_string == "CXXFLAGS=" | parsed_string == "CXXFLAGS =" )&& !end_of_var_name)
            {
                end_of_var_name = true;
                parsed_string = "";
            } else if (!end_of_var_name) {
            
                parsed_string += c;

            }

            // once the first part of the string is ignored we will iterate through the remaining characters
            // and extract the cxx flags from the string
            if (end_of_var_name)
            {
    
                // concantenate chars after char '-' has been located
                 if (f && !e)         
                {
                    if (c != '-')
                    {
                    parsed_string += c;
                    } 
                    // we've reached the end of the cxx flag so we set the end flag true
                    else if (c == '-')
                    {
                        e = true;
                    }
                }           
                // the char '-' has been located. this is the start of the 
                else if (!f && c == '-')
                {
                    f = true;
            
                }
               
                // add cxx flag to the vector when f && e are true or the end of the string has been reached
                if (f && e || i == cxx_flags_in.size()-1)
                {
                    add_cxx_flag(parsed_string);
                    parsed_string = "";
                    e = false; 
                }
            
            }

            i++;
        }
  }
  void parse_ldflags(std::string ld_flags_in)
  {
  
        // iterate through cxx flags
        std::string parsed_string = "";
        bool end_of_var_name = false;
        bool f = false;
        bool e = false;
        int i = 0;
        for(auto& c : ld_flags_in)
        {
            // during the first few iterations we ne need to ignore characters CXXFLAGS and = since 
            // they are not needed in the cxx_flags_vector
            if ( ( parsed_string == "LDFLAGS=" | parsed_string == "LDFLAGS =" )&& !end_of_var_name)
            {
                end_of_var_name = true;
                parsed_string = "";
            } else if (!end_of_var_name) {
            
                parsed_string += c;

            }

            // once the first part of the string is ignored we will iterate through the remaining characters
            // and extract the cxx flags from the string
            if (end_of_var_name)
            {
    
                // concantenate chars after char '-' has been located
                 if (f && !e)         
                {
                    if (c != '-')
                    {
                    parsed_string += c;
                    } 
                    // we've reached the end of the cxx flag so we set the end flag true
                    else if (c == '-')
                    {
                        e = true;
                    }
                }           
                // the char '-' has been located. this is the start of the 
                else if (!f && c == '-')
                {
                    f = true;
            
                }
               
                // add cxx flag to the vector when f && e are true or the end of the string has been reached
                if (f && e || i == ld_flags_in.size()-1)
                {
                    add_ld_flag(parsed_string.substr(1,parsed_string.size()-1));
                    parsed_string = "";
                    e = false; 
                }
            
            }

            i++;
        }  
  }
};

#endif
