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



std::string AML::AMLException::reason(const ResultCode res)
{
    switch (res)
    {
        case AML::RESULT_OK:
            return Exception::NO_ERROR;
        case AML::INVALID_PARAM:
            return Exception::INVALID_PARAM;
        case AML::INVALID_FILE_PATH:
            return Exception::INVALID_FILE_PATH;
        case AML::INVALID_XML_STR:
            return Exception::INVALID_XML_STR;
        case AML::INVALID_AML_FORMAT:
            return Exception::INVALID_AML_FORMAT;
        case AML::INVALID_SCHEMA:
            return Exception::INVALID_SCHEMA;
        case AML::INVALID_AMLDATA_NAME:
            return Exception::INVALID_AMLDATA_NAME;
        case AML::NOT_IMPL:
            return Exception::NOT_IMPL;
        case AML::NO_MEMORY:
            return Exception::NO_MEMORY;

        case AML::KEY_NOT_EXIST:
            return Exception::KEY_NOT_EXIST;
        case AML::KEY_ALREADY_EXIST:
            return Exception::KEY_ALREADY_EXIST;

        case AML::INVALID_DATA_TYPE:
            return Exception::INVALID_DATA_TYPE;
        case AML::KEY_VALUE_NOT_MATCH:
            return Exception::KEY_VALUE_NOT_MATCH;

        default:
            return Exception::UNKNOWN_ERROR;
    }
}
