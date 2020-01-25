
#include <at_tests>
#include "argparser.h"

void test_args() {
    const char* args[] = {"", "arg1", "-notarg", "--notarg", "arg2", "-not=arg", "--not=arg"};
    ArgParser a = ArgParser(7, args);
    
    ASSERT(a.num_arguments() == 2);
    ASSERT(a.get_argument(0) == "arg1");
    ASSERT(a.get_argument(1) == "arg2");
    
    const char* args2[] = {"", "--no-args-supplied"};
    ArgParser b = ArgParser(2, args2);
    
    ASSERT(b.num_arguments() == 0);
    
    const char* args3[] = {"", "only", "args", "provided"};
    ArgParser c = ArgParser(4, args3);
    
    ASSERT(c.num_arguments() == 3);
    ASSERT(c.get_argument(0) == "only");
    ASSERT(c.get_argument(1) == "args");
    ASSERT(c.get_argument(2) == "provided");
}

void test_flags() {
    const char* args[] = {"", "arg1", "-flagflag", "--flag", "arg2", "-not=flag", "--also-not=flag"};
    ArgParser a = ArgParser(7, args);
    
    ASSERT(a.num_flags() == 9);
    ASSERT(a.has_flag("f"));
    ASSERT(a.has_flag("l"));
    ASSERT(!a.has_flag("x"));
    ASSERT(a.flag_count("g") == 2);
    ASSERT(a.has_flag("flag"));
    
    const char* args2[] = {"", "noflags", "given"};
    ArgParser b = ArgParser(3, args2);
    
    ASSERT(b.num_flags() == 0);
    
    const char* args3[] = {"", "--only", "-flags"};
    ArgParser c = ArgParser(3, args3);
    
    ASSERT(c.num_flags() == 6);
    ASSERT(!c.has_flag("flag"));
    ASSERT(c.has_flag("s"));
}

void test_variables() {
    const char* args[] = {"", "arg1", "-flag", "--flag", "arg2", "-var=1", "--var2=val"};
    ArgParser a = ArgParser(7, args);
    
    ASSERT(a.num_variables() == 2);
    ASSERT(a.has_variable("var"));
    ASSERT(!a.has_variable("foo"));
    ASSERT(a.get_variable("var2") == "val");
    
    const char* args2[] = {"", "novars", "given"};
    ArgParser b = ArgParser(3, args2);
    
    ASSERT(b.num_variables() == 0);
    
    const char* args3[] = {"", "-only=vars", "--are=given"};
    ArgParser c = ArgParser(3, args3);
    
    ASSERT(c.num_variables() == 2);
    ASSERT(c.has_variable("are"));
    ASSERT(!c.has_variable("bar"));
    ASSERT(c.get_variable("only") == "vars");
}

void run_argparse_tests() {
    TEST(test_args)
    TEST(test_flags)
    TEST(test_variables)
}
