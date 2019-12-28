#pragma once

#define AT_CONCATENATE(a, b) a##b
#define AT_EXPAND_CONCAT(a, b) AT_CONCATENATE(a, b)
