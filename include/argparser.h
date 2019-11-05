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
    
    /**
     * \brief Check whether a flag was given
     *
     * Returns whether a given flag was passed in any argument. This works for
     * both single and multi-character flags
     *
     * \param flag Flag to check for
     * \return Whether flag was passed
     */
    bool has_flag(const std::string& flag);
    
    /**
     * \brief Get the number of times a flag appears
     *
     * Returns the total number of times a single flag appeared in the input.
     * Accepts both single and multi-character flags. Will return 0 if flag
     * did not appear at all, as you would expect.
     *
     * \param flag Flag to get count of
     * \return Number of times flag appeared
     */
    uint flag_count(const std::string& flag);
    
    /**
     * \brief Get a positional argument by index
     *
     * Returns the positional argument at a given index. If the index is outside
     * the range of arguments, will throw an error
     *
     * \param index Index of the desired argument
     * \return The argument at that position
     */
    std::string get_argument(uint index);
    
    /**
     * \brief Check whether a variable was supplied
     *
     * Returns whether a given variable was passed in any argument. Does not
     * check that it contains a non-empty value, simply that it exists at all
     *
     * \param var Variable to check for
     * \return Whether the variable was passed
     */
    bool has_variable(const std::string& var);
    
    /**
     * \brief Get the value of a variable
     *
     * Returns the value of a given variable. This value may be empty or invalid
     * for the expected type, so do not attempt to blindly cast this result to
     * a different type
     *
     * \param var Variable to get value of
     * \return Value of the variable
     */
    std::string get_variable(const std::string& var);
    
};


