#ifndef AML_EXCEPTION_H_
#define AML_EXCEPTION_H_

#include <stdexcept>
#include <string>

typedef enum 
{
	AML_RESULT_OK = 0,

	AML_INVALID_PARAM = 100,
	AML_INVALID_FILE_PATH,
	AML_INVALID_SCHEMA,
	AML_INVALID_XML_STR,
	AML_INVALID_SUC,
	AML_INIT_FAILED,
	AML_ADD_IE_FAILED,
	AML_NOT_IMPL,

	AML_ERROR = 255

} AMLResult;

namespace Exception 
{
	static const char NO_ERROR[]                	= "No Error";
	
	static const char INVALID_PARAM[]          		= "Invalid Parameter";
	static const char INVALID_FILE_PATH[]       	= "Invalid File Path";
	static const char INVALID_SCHEMA[]				= "Invalid AutomationML Schema File";
	static const char INVALID_XML_STR[]				= "Invalid XML Style String";
	static const char INVALID_SUC[]					= "Invalid SystemUnitClass Name";
	static const char INIT_FAILED[]					= "Failed Initialize";
	static const char ADD_IE_FAILED[]				= "Failed Add AutomationML InternalElement";
	static const char NOT_IMPL[]					= "Not Implemented";

	static const char UNKNOWN_ERROR[]				= "Unknown Error";
}

class AMLException : public std::runtime_error 
{
	public:
		AMLException(const std::string& msg, AMLResult reason = AML_ERROR)
		: std::runtime_error(msg), m_reason(reason) {}

		static std::string reason(const AMLResult res);

		std::string reason() const
		{
			return reason(m_reason);
		}

		AMLResult code() const
		{
			return m_reason;
		}

	private:
		AMLResult m_reason;
};

#endif // AML_EXCEPTION_H_
