#include <makegen.h>

int main()
{
    Makefile new_makefile; 
    new_makefile.read_config("./","fuzzy_engine");
    new_makefile.generate_make_file("./output/");
    new_makefile.generate_make_file("./output/");
    new_makefile.generate_source_config("./output/");
    new_makefile.generate_make_config("./output/");
    return 0;
}
