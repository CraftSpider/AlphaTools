
#include "reflection/errors.h"

namespace reflect {

reflection_error::reflection_error(const std::string& msg) : runtime_error(msg) {}

not_reflected::not_reflected(const std::string& msg) : reflection_error(msg) {}

already_reflected::already_reflected(const std::string& msg) : reflection_error(msg) {}

invalid_size::invalid_size(const std::string& msg) : reflection_error(msg) {}

invalid_type::invalid_type(const std::string& msg) : reflection_error(msg) {}

variant_error::variant_error(const std::string& msg) : reflection_error(msg) {}

}