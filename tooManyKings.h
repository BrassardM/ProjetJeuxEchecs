#include <stdexcept>
#pragma once
namespace errors {
	class tooManyKings : public std::logic_error {
	public:
		using logic_error::logic_error;
	};
}