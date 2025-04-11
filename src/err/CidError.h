#pragma once
#include <exception>
#include <sstream>
#include <string>


class CidError : public std::exception 
{
	int mLine;
	std::string mFileName;
	std::string mErrorMsg;

public:

	CidError();
	CidError(int line_, std::string file_, std::string msg_);
	~CidError() override final;
	CidError(const CidError&) = default;
	CidError& operator=(const CidError&) = default;
	CidError(CidError&&) = default;
	CidError& operator=(CidError&&) = default;
	mutable std::string _formattedMsg;

	const char* what() const noexcept override;
	
	

};