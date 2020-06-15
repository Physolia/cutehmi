#ifndef H_EXTENSIONS_TEMPLATES_CPPSKELETON_0_INCLUDE_TEMPLATES_CPPSKELETON_LOGGING_HPP
#define H_EXTENSIONS_TEMPLATES_CPPSKELETON_0_INCLUDE_TEMPLATES_CPPSKELETON_LOGGING_HPP

// This file has been initially autogenerated by 'cutehmi.skeleton.cpp' Qbs module.

#include "internal/platform.hpp"
#include <cutehmi/loggingMacros.hpp>

TEMPLATES_CPPSKELETON_API Q_DECLARE_LOGGING_CATEGORY(templates_cppskeleton_loggingCategory)

namespace templates {
namespace cppskeleton {

inline
const QLoggingCategory & loggingCategory()
{
	return templates_cppskeleton_loggingCategory();
}

}
}

#endif
