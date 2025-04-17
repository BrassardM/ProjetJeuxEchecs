#include <stdexcept>
#pragma once

class tooManyKings : public std::logic_error {
public:
	using logic_error::logic_error;
};