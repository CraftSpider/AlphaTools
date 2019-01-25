
#include "test_console.h"
#include "console.h"
#include "tests/test.h"

void test_effect() {
    using namespace term;
    std::cout << effect::RESET << "RESET";
    std::cout << effect::BOLD << "BOLD" << effect::RESET_BOLD;
    std::cout << effect::DIM << "DIM" << effect::RESET_DIM;
    std::cout << effect::UNDERLINE << "UNDERLINE" << effect::RESET_UNDERLINE;
    std::cout << effect::BLINK << "BLINK" << effect::RESET_BLINK;
    std::cout << effect::INVERTED << "INVERTED" << effect::RESET_INVERTED;
    std::cout << effect::HIDDEN << "HIDDEN" << effect::RESET_HIDDEN;
    std::cout << std::endl;
}

void test_foreground() {
    using namespace term;
    std::cout << fore::DEFAULT << "DEFAULT";
    std::cout << fore::BLACK << "BLACK" << fore::DEFAULT;
    std::cout << fore::RED << "RED" << fore::DEFAULT;
    std::cout << fore::GREEN << "GREEN" << fore::DEFAULT;
    std::cout << fore::YELLOW << "YELLOW" << fore::DEFAULT;
    std::cout << fore::BLUE << "BLUE" << fore::DEFAULT;
    std::cout << fore::MAGENTA << "MAGENTA" << fore::DEFAULT;
    std::cout << fore::CYAN << "CYAN" << fore::DEFAULT;
    std::cout << fore::LIGHT_GRAY << "LIGHT_GRAY" << fore::DEFAULT;
    std::cout << fore::DARK_GRAY << "DARK_GRAY" << fore::DEFAULT;
    std::cout << fore::LIGHT_RED << "LIGHT_RED" << fore::DEFAULT;
    std::cout << fore::LIGHT_GREEN << "LIGHT_GREEN" << fore::DEFAULT;
    std::cout << fore::LIGHT_YELLOW << "LIGHT_YELLOW" << fore::DEFAULT;
    std::cout << fore::LIGHT_BLUE << "LIGHT_BLUE" << fore::DEFAULT;
    std::cout << fore::LIGHT_MAGENTA << "LIGHT_MAGENTA" << fore::DEFAULT;
    std::cout << fore::LIGHT_CYAN << "LIGHT_CYAN" << fore::DEFAULT;
    std::cout << fore::WHITE << "WHITE" << fore::DEFAULT;
    std::cout << std::endl;
}

void test_background() {
    using namespace term;
    std::cout << back::DEFAULT << "DEFAULT";
    std::cout << back::BLACK << "BLACK" << back::DEFAULT;
    std::cout << back::RED << "RED" << back::DEFAULT;
    std::cout << back::GREEN << "GREEN" << back::DEFAULT;
    std::cout << back::YELLOW << "YELLOW" << back::DEFAULT;
    std::cout << back::BLUE << "BLUE" << back::DEFAULT;
    std::cout << back::MAGENTA << "MAGENTA" << back::DEFAULT;
    std::cout << back::CYAN << "CYAN" << back::DEFAULT;
    std::cout << back::LIGHT_GRAY << "LIGHT_GRAY" << back::DEFAULT;
    std::cout << back::DARK_GRAY << "DARK_GRAY" << back::DEFAULT;
    std::cout << back::LIGHT_RED << "LIGHT_RED" << back::DEFAULT;
    std::cout << back::LIGHT_GREEN << "LIGHT_GREEN" << back::DEFAULT;
    std::cout << back::LIGHT_YELLOW << "LIGHT_YELLOW" << back::DEFAULT;
    std::cout << back::LIGHT_BLUE << "LIGHT_BLUE" << back::DEFAULT;
    std::cout << back::LIGHT_MAGENTA << "LIGHT_MAGENTA" << back::DEFAULT;
    std::cout << back::LIGHT_CYAN << "LIGHT_CYAN" << back::DEFAULT;
    std::cout << back::WHITE << "WHITE" << back::DEFAULT;
    std::cout << std::endl;
}

void run_console_tests() {
    TEST(test_effect)
    TEST(test_foreground)
    TEST(test_background)
}