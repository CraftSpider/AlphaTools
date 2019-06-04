#pragma once

#include <string>
#include <vector>
#include <map>
#include "types.h"

/**
 * \file argparser.h
 * \brief Defines the AlphaTools argument parser
 *
 * \author CraftSpider
 */

/**
 * \brief Parses input arguments from the command line
 *
 * An ArgParser takes an array and number of input arguments, and then allows
 * parsing data from the input arguments, or checking for various flags and
 * options
 */
class ArgParser {
    
    std::string invokation;
    std::vector<std::string> raw_args;
    
    std::vector<std::string> flags;
    std::vector<std::string> arguments;
    std::map<std::string, std::string> variables;

public:
    
    /**
     * \brief Base constructor for the ArgParser
     *
     * Constructor taking an int length and an array of C-strings, for
     * construction from the main function of a program
     *
     * \param argc Number of arguments
     * \param argv Array of argument strings
     */
    ArgParser(int argc, char** argv);
    
    /**
     * \brief The total number of flags
     *
     * Returns the total number of flags in the input arguments.
     * A flag is any argument prefixed by one or two dashes, without an equals
     * sign anywhere in it. With one dash, each character is considered its
     * own flag. With two dashes, the flag is the whole rest of the argument.
     *
     * \return Total number of command line flags
     */
    ulong num_flags();
    /**
     * \brief The total number of positional arguments
     *
     * Returns the total number of positional input arguments.
     * An argument is positional if it is not prefixed by one or two dashes.
     *
     * \return Total number of positional arguments
     */
    ulong num_arguments();
    /**
     * \brief The total number of variables
     *
     * Returns the total number of variables in the input arguments.
     * A variable is any argument prefixed by one or two dashes, that contains
     * an equals sign anywhere in it. The string before the equals sign becomes
     * the variable name, and the string after becomes its value.
     *
     * \return Total number of variable arguments
     */
    ulong num_variables();
    
    bool has_flag(const std::string& flag);
    uint flag_count(const std::string& flag);
    
    std::string get_argument(uint index);
    
    bool has_variable(const std::string& var);
    std::string get_variable(const std::string& var);
    
};


