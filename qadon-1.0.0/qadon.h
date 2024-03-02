
#ifndef QADON_H
#define QADON_H
#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>

class qadon{

    public:
        qadon(std::string file_path);
        qadon();
        std::string& operator[](std::string key)
        {
            return map[key];
        }

        auto begin() { return map.begin(); }
        auto end() { return map.end(); }
        
        void write(std::string file_path);
        void print();

    private:
        bool parse_line;
        int qadon_bracket;
        std::string line;
        std::unordered_map<std::string,std::string> map;

};


class qadon_bracket_error : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "qadon_bracket_error: qadon file is missing bracket";
        }
};

class qadon_syntax_error : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "qadon_syntax_error: qadon file has incorret syntax. missing colon detected";
        }

};

class qadon_file_error : public std::exception
{
    public:
            const char* what() const throw()
            {
                return "qadon_file_error: file does not exist";
            }
};

#endif