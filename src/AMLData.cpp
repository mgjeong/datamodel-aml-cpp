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

#include <string>
#include <vector>
#include <map>
 
#include "AMLInterface.h"
#include "AMLException.h"
#include "AMLLogger.h"

#define TAG "AMLData"

// For logging
#define TYPE(type)  (type)==0 ? "String" : ((type)==1 ? "String Vector" : "AMLData")

AMLData::AMLData(void)
{
}

AMLData::~AMLData(void)
{
}

void AMLData::setValue(const std::string& key, const std::string& value)
{
    if (!m_values.insert(std::pair<std::string, std::string>(key, value)).second)
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }
}

void AMLData::setValue(const std::string& key, const std::vector<std::string>& value)
{
    if (!m_values.insert(std::pair<std::string, std::vector<std::string>>(key, value)).second)
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }
}

void AMLData::setValue(const std::string& key, const AMLData& value)
{
    if (!m_values.insert(std::pair<std::string, AMLData>(key, value)).second)
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }
}

std::vector<std::string> AMLData::getKeys() const
{
    std::vector<std::string> keys;
    for (auto const& element : m_values)
    {
        keys.push_back(element.first);
    }

    return keys;
}

AMLValueType AMLData::getValueType(const std::string& key) const
{
    for (auto const& element : m_values)
    {
        if (key.compare(element.first) == 0)
        {
            auto type = element.second.which();

            if (type == 0)
            {
                return AMLValueType::String;
            }
            else if (type == 1)
            {
                return AMLValueType::StringArray;
            }
            else if (type == 2)
            {
                return AMLValueType::AMLData;
            }
        }
    }

    AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
    throw AMLException(Exception::KEY_NOT_EXIST);
}

const std::string& AMLData::getValueToStr(const std::string& key) const
{
    auto iter = m_values.find(key);
    if (iter == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_NOT_EXIST);
    }
    else if (0 != iter->second.which())
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }

    return boost::get<std::string>(iter->second);
}

const std::vector<std::string>& AMLData::getValueToStrArr(const std::string& key) const
{
    auto iter = m_values.find(key);
    if (iter == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_NOT_EXIST);
    }
    else if (1 != iter->second.which())
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }

    return boost::get<std::vector<std::string>>(iter->second);
}

const AMLData& AMLData::getValueToAMLData(const std::string& key) const
{
    auto iter = m_values.find(key);
    if (iter == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_NOT_EXIST);
    }
    else if (2 != iter->second.which())
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }

    return boost::get<AMLData>(iter->second);
}
