#include "AMLException.h"

std::string AMLException::reason(const AMLResult res)
{
    switch (res)
    {
        case AML_RESULT_OK:
            return Exception::NO_ERROR;
        case AML_INVALID_PARAM:
            return Exception::INVALID_PARAM;
        case AML_INVALID_FILE_PATH:
            return Exception::INVALID_FILE_PATH;
        case AML_INVALID_XML_STR:
            return Exception::INVALID_XML_STR;
        case AML_INVALID_AML_FORMAT:
            return Exception::INVALID_AML_FORMAT;
        case AML_INVALID_SCHEMA:
            return Exception::INVALID_SCHEMA;
        case AML_NOT_IMPL:
            return Exception::NOT_IMPL;
        case AML_NO_MEMORY:
            return Exception::NO_MEMORY;

        default:
            return Exception::UNKNOWN_ERROR;
    }
}