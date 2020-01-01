#pragma once

#include <string>
#include <sstream>
#include "types.h"

/**
 * \file console.h
 * \brief POSIX console code manipulation
 */

/**
 * \brief Terminal functionality
 *
 * The term namespace holds both functions and constants for terminal
 * manipulation
 */
namespace term {

/**
 * Generate a code that sets the icon name and window title to a given string
 *
 * \param name Name to set the icon and window to
 * \return Generated escape code
 */
std::string SET_ICON_TITLE(std::string name);

/**
 * Generate a code that sets the icon name to a given string
 *
 * \param name Name to set the icon to
 * \return Generated escape code
 */
std::string SET_ICON(std::string name);

/**
 * Generate a code that sets the window title to a given string
 *
 * \param name Name to set the window to
 * \return Generated escape code
 */
std::string SET_TITLE(std::string name);

/**
 * Generate a code to scroll the screen buffer up by a given number of lines
 *
 * \param n Number of lines to scroll
 * \return Generated escape code
 */
std::string SCROLL_UP(ushort n = 1);

/**
 * Generate a code to scroll the screen buffer down by a given number of lines
 *
 * \param n Number of lines to scroll
 * \return Generated escape code
 */
std::string SCROLL_DOWN(ushort n = 1);

constexpr char ALT_BUFFER[] = "\033[?1049h";
constexpr char MAIN_BUFFER[] = "\033[?1049l";

/**
 * \brief Cursor manipulation
 *
 * The curs namespace allows easy manipulation of the cursor. Moving it around,
 * settings its position, or hiding/showing it
 */
namespace curs {

/**
 * Generate a code to move the cursor up by a given number of lines
 *
 * \param n Number of lines to move
 * \return Generated escape code
 */
std::string UP(ushort n = 1);

/**
 * Generate a code to move the cursor down by a given number of lines
 *
 * \param n Number of lines to move
 * \return Generated escape code
 */
std::string DOWN(ushort n = 1);

/**
 * Generate a code to move the cursor forward by a given number of characters
 *
 * \param n Number of characters to move
 * \return Generated escape code
 */
std::string FORWARD(ushort n = 1);

/**
 * Generate a code to move the cursor back by a given number of characters
 *
 * \param n Number of characters to move
 * \return Generated escape code
 */
std::string BACKWARD(ushort n = 1);

/**
 * Generate a code to move the cursor to the beginning of the Nth line below it
 *
 * \param n Number of lines to move
 * \return Generated escape code
 */
std::string DOWN_LINE(ushort n = 1);

/**
 * Generate a code to move the cursor to the beginning of the Nth line above it
 *
 * \param n Number of lines to move
 * \return Generated escape code
 */
std::string UP_LINE(ushort n = 1);

/**
 * Set the horizontal cursor position to a given value
 *
 * \param n X position to go to
 * \return Generated escape code
 */
std::string SET_HORIZONTAL(ushort n = 1);

/**
 * Set the vertical cursor position to a given value
 *
 * \param n Y position to go to
 * \return Generated escape code
 */
std::string SET_VERTICAL(ushort n = 1);

/**
 * Set the vertical and horizontal positions of the cursor
 *
 * \param x X position to go to
 * \param y Y position to go to
 * \return Generated escape code
 */
std::string SET_POS(ushort x = 1, ushort y = 1);

constexpr char SAVE[] = "\033[s";
constexpr char RESTORE[] = "\033[u";
constexpr char ENABLE_BLINK[] = "\033[?12h";
constexpr char DISABLE_BLINK[] = "\033[?12l";
constexpr char SHOW[] = "\033[?25h";
constexpr char HIDE[] = "\033[?25l";

}

/**
 * \brief Text manipulation
 *
 * The text namespace allows easy manipulation of text on screen. Inserting,
 * deleting, and clearing text.
 */
namespace text {

/**
 * Generate a code to insert some number of blank characters at the cursor
 *
 * \param n Number of characters to insert. Defaults to 1
 * \return Generated escape code
 */
std::string INSERT(ushort n = 1);

/**
 * Generate a code to delete some number of characters at the cursor
 *
 * \param n Number of characters to delete
 * \return Generated escape code
 */
std::string DELETE(ushort n = 1);

/**
 * Generate a code to erase some number of characters from behind the cursor
 *
 * \param n Number of characters to erase
 * \return Generated escape code
 */
std::string ERASE(ushort n = 1);

/**
 * Generate a code to insert some number of blank lines at the cursor
 *
 * \param n Number of lines to insert
 * \return Generated escape code
 */
std::string INSERT_LINE(ushort n = 1);

/**
 * Generate a code to delete some number of lines at the cursor
 *
 * \param n Number of lines to delete
 * \return Generated escape code
 */
std::string DELETE_LINE(ushort n = 1);

/**
 * Clear the screen. Option is one of three values:
 * 0: erases from beginning to cursor
 * 1: erases from cursor to end
 * 2: erases from beginning to end
 * 3: erases from beginning to end and clears the scrollback buffer
 *
 * \param option Clear setting
 * \return Escape code
 */
std::string CLEAR(ushort option = 2);

/**
 * Clear the current line. Option is one of three values:
 * 0: erases from beginning to cursor
 * 1: erases from cursor to end
 * 2: erases from beginning to end
 * 3: erases from beginning to end and clears the scrollback buffer
 *
 * \param option Clear setting
 * \return Escape code
 */
std::string CLEAR_LINE(ushort option = 2);

}

/**
 * \brief Visual effects
 *
 * The effect namespace implements visual effects, such as blink or invert.
 * It contains no functions, all effects are hardcoded escape strings
 */
namespace effect {

constexpr char BOLD[] = "\033[1m";
constexpr char DIM[] = "\033[2m";
constexpr char UNDERLINE[] = "\033[4m";
constexpr char BLINK[] = "\033[5m";
constexpr char INVERTED[] = "\033[7m";
constexpr char HIDDEN[] = "\033[8m";

constexpr char RESET[] = "\033[0m";
constexpr char RESET_BOLD[] = "\033[21m";
constexpr char RESET_DIM[] = "\033[22m";
constexpr char RESET_UNDERLINE[] = "\033[24m";
constexpr char RESET_BLINK[] = "\033[25m";
constexpr char RESET_INVERTED[] = "\033[27m";
constexpr char RESET_HIDDEN[] = "\033[28m";

}

/**
 * \brief Foreground Colors
 *
 * The fore namespace provides the escape codes for foreground colors
 */
namespace fore {

constexpr char DEFAULT[] = "\033[39m";
constexpr char BLACK[] = "\033[30m";
constexpr char RED[] = "\033[31m";
constexpr char GREEN[] = "\033[32m";
constexpr char YELLOW[] = "\033[33m";
constexpr char BLUE[] = "\033[34m";
constexpr char MAGENTA[] = "\033[35m";
constexpr char CYAN[] = "\033[36m";
constexpr char LIGHT_GRAY[] = "\033[37m";
constexpr char DARK_GRAY[] = "\033[90m";
constexpr char LIGHT_RED[] = "\033[91m";
constexpr char LIGHT_GREEN[] = "\033[92m";
constexpr char LIGHT_YELLOW[] = "\033[93m";
constexpr char LIGHT_BLUE[] = "\033[94m";
constexpr char LIGHT_MAGENTA[] = "\033[95m";
constexpr char LIGHT_CYAN[] = "\033[96m";
constexpr char WHITE[] = "\033[97m";

}

/**
 * \brief Background colors
 *
 * The back namespace provides the escape codes for background colors
 */
namespace back {

constexpr char DEFAULT[] = "\033[49m";
constexpr char BLACK[] = "\033[40m";
constexpr char RED[] = "\033[41m";
constexpr char GREEN[] = "\033[42m";
constexpr char YELLOW[] = "\033[43m";
constexpr char BLUE[] = "\033[44m";
constexpr char MAGENTA[] = "\033[45m";
constexpr char CYAN[] = "\033[46m";
constexpr char LIGHT_GRAY[] = "\033[47m";
constexpr char DARK_GRAY[] = "\033[100m";
constexpr char LIGHT_RED[] = "\033[101m";
constexpr char LIGHT_GREEN[] = "\033[102m";
constexpr char LIGHT_YELLOW[] = "\033[103m";
constexpr char LIGHT_BLUE[] = "\033[104m";
constexpr char LIGHT_MAGENTA[] = "\033[105m";
constexpr char LIGHT_CYAN[] = "\033[106m";
constexpr char WHITE[] = "\033[107m";

}

constexpr char RESET_ALL[] = "\033[0m\033[39m\033[49m";

}
