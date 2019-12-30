#pragma once

#include <string>
#include "level.h"
#include "logger.h"

/**
 * \file logging.h
 * \brief Global factories and utilities for loggers
 *
 * Provides functions to get/set logger defaults, as well as access into the global
 * logger cache. All loggers are stored there, so they can be statically retrieved from anywhere.
 */

namespace logging {

/**
 * \internal
 *
 * Ensure that the logger cache is initialized correctly
 */
void __ensure_loggers();

/**
 * Set the default logging level for the root logger, and thus all child loggers who
 * inherit from it.
 * \param level Level to log at
 */
void set_default_level(Level* level);

/**
 * Add a logging handler to the root logger, and thus all child loggers who
 * inherit from it.
 * \param handler Handler to add
 */
void add_default_handler(Handler* handler);

/**
 * Remove a logging handler from the root logger, and thus all child loggers who
 * inherit from it
 * \param handler Handler to remove
 * \return Whether the handler was successfully removed
 */
bool remove_default_handler(Handler* handler);

/**
 * Get the root logger. This logger is the top-level ancestor of all loggers.
 * \return Pointer to the root logger
 */
Logger* get_root_logger();

/**
 * Get a logger by name, with automatic namespace resolution. If a logger by that name was retrieved before, it will
 * return that logger. Otherwise, a new logger will be created and added to the cache
 * \param name Name of the logger to get or create
 * \param auto_parent Whether to automatically resolve the logger namespace
 * \return Logger with the given name
 */
Logger* get_logger(const std::string& name, bool auto_parent = true);

}
