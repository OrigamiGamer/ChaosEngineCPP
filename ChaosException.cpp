#include <exception>
#include <string>

#define DEFINE_CHAOS_EXCEPTION(name) \
	class name : public Chaos::Exception::ChaosException { \
	public: \
		name(const std::string& message) : Chaos::Exception::ChaosException(message) {} \
	};

namespace Chaos::Exception {
	class ChaosException : public std::exception {
	public:
		ChaosException(const std::string& message) : message(message) {}

		virtual const char* what() const noexcept override
		{
			return message.c_str();
		}

	private:
		std::string message;
	};

	DEFINE_CHAOS_EXCEPTION(NullPointerException);

}
