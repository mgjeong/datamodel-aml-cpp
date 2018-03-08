/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#ifndef AML_EXCEPTION_H_
#define AML_EXCEPTION_H_

#include <stdexcept>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    AML_RESULT_OK = 0,

    AML_INVALID_PARAM = 100,
    AML_INVALID_FILE_PATH,
    AML_INVALID_SCHEMA,
    AML_INVALID_XML_STR,
    AML_INVALID_AML_FORMAT,
    AML_NOT_IMPL,               // @TODO: need to be specified more
    AML_NO_MEMORY,

    AML_KEY_NOT_EXIST,
    AML_KEY_ALREADY_EXIST,

    AML_INVALID_DATA_TYPE,
    AML_KEY_VALUE_NOT_MATCH,

    AML_ERROR = 255

} AMLResult;

namespace Exception 
{
    static const char NO_ERROR[]                    = "No Error";

    static const char INVALID_PARAM[]               = "Invalid Parameter";
    static const char INVALID_FILE_PATH[]           = "Invalid File Path";
    static const char INVALID_SCHEMA[]              = "Invalid AutomationML Schema File";
    static const char INVALID_XML_STR[]             = "Invalid XML Style String";
    static const char INVALID_AML_FORMAT[]          = "Invalid AML format";
    static const char NOT_IMPL[]                    = "Not Implemented";
    static const char NO_MEMORY[]                   = "No Momory";

    static const char KEY_NOT_EXIST[]               = "Key does Not Exist";
    static const char KEY_ALREADY_EXIST[]           = "Key already Exists";

    static const char INVALID_DATA_TYPE[]           = "Invalid AMLData Type";
    static const char KEY_VALUE_NOT_MATCH[]         = "Not Matching AMLData Key and Value";

    static const char UNKNOWN_ERROR[]               = "Unknown Error";
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

#ifdef __cplusplus
}
#endif

#endif // AML_EXCEPTION_H_
