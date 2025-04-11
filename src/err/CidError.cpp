#include <err/ErrorMacros.h>

std::string cidres = "";

CidError::CidError()
	: CidError(__LINE__, __FILE__, "NOTOK")
{

}
CidError::CidError(int line_, std::string file_, std::string msg_)
    : std::exception{}
	, mLine{ line_ }
	, mFileName{ file_ }
	, mErrorMsg{ msg_ }
{}

CidError::~CidError()
{
}


const char* CidError::what() const noexcept
{
	std::ostringstream str;
	str << "\nError! [LINE]: " << mLine
		<< "\n   [FILE]: " << mFileName
		<< "\n    [ISSUE]: " << mErrorMsg;

	_formattedMsg = str.str();
	return _formattedMsg.c_str();
}