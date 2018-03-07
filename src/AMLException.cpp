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

        case AML_OBJECT_INVALID_KEY:
            return Exception::OBJECT_INVALID_KEY;
        case AML_OBJECT_KEY_DUP:
            return Exception::OBJECT_KEY_DUP;

        case AML_INVALID_DATA_TYPE:
            return Exception::INVALID_DATA_TYPE;
        case AML_DATA_INVALID_KEY:
            return Exception::DATA_INVALID_KEY;
        case AML_KEY_VALUE_NOT_MATCH:
            return Exception::KEY_VALUE_NOT_MATCH;

        default:
            return Exception::UNKNOWN_ERROR;
    }
}
