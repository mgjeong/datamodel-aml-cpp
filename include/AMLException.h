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

namespace AML
{

typedef enum
{
    RESULT_OK = 0,

    INVALID_PARAM = 100,
    INVALID_FILE_PATH,
    INVALID_SCHEMA,
    INVALID_XML_STR,
    INVALID_AML_FORMAT,
    INVALID_AMLDATA_NAME,
    NOT_IMPL,               // @TODO: need to be specified more
    NO_MEMORY,

    KEY_NOT_EXIST,
    KEY_ALREADY_EXIST,

    INVALID_DATA_TYPE,
    KEY_VALUE_NOT_MATCH,

    ERROR = 255

} ResultCode;

namespace Exception
{
    static const char NO_ERROR[]                    = "No Error";

    static const char INVALID_PARAM[]               = "Invalid Parameter";
    static const char INVALID_FILE_PATH[]           = "Invalid File Path";
    static const char INVALID_SCHEMA[]              = "Invalid AutomationML Schema File";
    static const char INVALID_XML_STR[]             = "Invalid XML Style String";
    static const char INVALID_AML_FORMAT[]          = "Invalid AML format";
    static const char INVALID_AMLDATA_NAME[]        = "Invalid AMLData Name";
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
        AMLException(const std::string& msg, ResultCode reason = ERROR)
        : std::runtime_error(msg), m_reason(reason) {}

        static std::string reason(const ResultCode res);

        std::string reason() const
        {
            return reason(m_reason);
        }

        ResultCode code() const
        {
            return m_reason;
        }

    private:
        ResultCode m_reason;
};

} // namespace AML

#ifdef __cplusplus
}
#endif

#endif // AML_EXCEPTION_H_
