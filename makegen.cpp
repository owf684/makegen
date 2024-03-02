#include "makegen.h"



    // setters
    void Makefile::set_compiler(std::string cxx_compiler)
    {
	    cxx = cxx_compiler;
    }	

    void Makefile::set_build_name(std::string build_name_in)
    {
	    build_name = build_name_in;
    }

    void Makefile::set_build_directory(std::string build_directory_in)
    {
	    build_directory = build_directory_in;
    }

    void Makefile::set_main_file_name(std::string main_file_name_in)
    {
	    main_file_name = main_file_name_in;
    }

    void Makefile::set_main_file_directory(std::string main_file_directory_in)
    {
         main_file_directory = main_file_directory_in;
    }

    // getters
    std::string Makefile::get_compiler()
    {
        return cxx;
    }

    std::string Makefile::get_build_name()
    {
        return build_name;
    }

    std::string Makefile::get_build_directory()
    {
        return build_directory;
    }

    std::string Makefile::get_main_file_name()
    {
        return main_file_name;
    }

    std::string Makefile::get_main_file_directory()
    {
        return main_file_directory;
    }

    // adders
    void Makefile::add_cxx_flag(std::string cxx_flag)
    {
	    cxx_flags.push_back(cxx_flag);
    }
    
    void Makefile::add_ld_flag(std::string ldd_flag)
    {
        ld_flags.push_back(ldd_flag);
    }

    void Makefile::add_source_file(std::string file_name, std::string file_directory)
    {
        source_files[file_name] = file_directory;
    }

    // removers
    void Makefile::remove_cxx_flag(std::string cxx_flag)
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

    void Makefile::remove_ld_flag(std::string ld_flag)
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

    void Makefile::remove_source_file(std::string file_name)
    {
        source_files.erase(file_name);
    }


    // generators
    void Makefile::generate_make_config()
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

    void Makefile::generate_source_config()
    {
    qadon source_file_config;

    for(const auto& pair : source_files)
    {
        source_file_config[pair.first] = pair.second;
    }

        source_file_config.write(get_build_name() + ".sourcecfg");
    }

    void Makefile::generate_make_file()
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

        new_makefile.close();

    }

    // readers
    void Makefile::read_config(std::string config_directory, std::string build_name)
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
    void Makefile::parse_cxxflags(std::string cxx_flags_in)
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

        void Makefile::parse_ldflags(std::string ld_flags_in)
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

    int main()
    {

        Makefile test;
        /*
        // setup make file config
        test.set_compiler("g++");
        test.set_build_name("makegen_test");
        test.set_main_file_name("main.cpp");
        test.set_main_file_directory("./testing");
        test.set_build_directory("./");
        test.add_cxx_flag("std=c++20");
        test.add_ld_flag("stdc++");
        test.add_ld_flag("SDL2");
        
        // setup source file config
        test.add_source_file("example.h", "./testing");
        test.add_source_file("another_example.cpp", "./testing");
        test.generate_make_config();
        test.generate_source_config();
        */
        test.read_config("./","print_util");

        test.generate_make_file();
       
        
      return 0;
    }


