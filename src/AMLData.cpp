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
#include <iostream>

#include "AMLInterface.h"
#include "AMLException.h"
#include "AMLLogger.h"

#define TAG "AMLData"

// For logging
#define TYPE(type)  (type)==0 ? "String" : ((type)==1 ? "String Vector" : "AMLData")

using namespace std;

AMLData::AMLData(void)
{
}

AMLData::AMLData(const AMLData& t) 
{
    this->m_values = t.m_values;
}

AMLData::~AMLData(void)
{
}

void AMLData::setValue(const std::string& key, const std::string& value)
{   
    std::string* temp_value = new std::string(value);
    void* val = static_cast<void*>(temp_value);
    AMLValue* amlVal = new AMLValue();
    amlVal->type = AMLValueType::String;
    amlVal->m_value = val;

    if (m_values.find(key) == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }

    m_values[key] = amlVal;    
}

void AMLData::setValue(const std::string& key, const std::vector<std::string>& value)
{
    std::vector<std::string>* temp_value = new std::vector<std::string>(value);
    //std::vector<std::string>* temp_value = const_cast<std::vector<std::string>*>(&value);
    void* val = static_cast<void*>(temp_value);
    AMLValue* amlVal = new AMLValue();
    amlVal->type = AMLValueType::StringArray;
    amlVal->m_value = val;
    
    if (m_values.find(key) == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }

    m_values[key] = amlVal;
}

void AMLData::setValue(const std::string& key, const AMLData& value)
{
    AMLData* temp_value = new AMLData(value);
    //AMLData* temp_value = const_cast<AMLData*>(&value);

    void* val = static_cast<void*>(temp_value);
    AMLValue* amlVal = new AMLValue;
    amlVal->type = AMLValueType::AMLData;
    amlVal->m_value = val;

    if (m_values.find(key) == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key already exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }
    
    m_values[key] = amlVal;
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
    // for (auto const& element : m_values)
    // {
    //     if (key.compare(element.first) == 0)
    //     {
    //         auto type = element.second.which();

    //         if (type == 0)
    //         {
    //             return AMLValueType::String;
    //         }
    //         else if (type == 1)
    //         {
    //             return AMLValueType::StringArray;
    //         }
    //         else if (type == 2)
    //         {
    //             return AMLValueType::AMLData;
    //         }
    //     }
    // }

    for(auto const& element : m_values)
    {
        if(key.compare(element.first) == 0)
        {
            AMLValueType type = element.second->type;

            return type;
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
    else if (AMLValueType::String != iter->second->type)
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }
    //return boost::get<std::string>(iter->second);
    return *static_cast<std::string*>(iter->second->m_value);
}

const std::vector<std::string>& AMLData::getValueToStrArr(const std::string& key) const
{
    auto iter = m_values.find(key);
    if (iter == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_NOT_EXIST);
    }
    else if (AMLValueType::StringArray != iter->second->type)
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }

    //return boost::get<std::vector<std::string>>(iter->second);
    return *static_cast<std::vector<std::string>*>(iter->second->m_value);
}

const AMLData& AMLData::getValueToAMLData(const std::string& key) const
{
    auto iter = m_values.find(key);
    if (iter == m_values.end())
    {
        AML_LOG_V(ERROR, TAG, "Key does not exist in AMLData : %s", key.c_str());
        throw AMLException(Exception::KEY_NOT_EXIST);
    }
    //else if (2 != iter->second.which())
    else if (AMLValueType::AMLData != iter->second->type)
    {
        AML_LOG_V(ERROR, TAG, "'%s' has a value of %s type", key.c_str(), TYPE(iter->second.which()));
        throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
    }

    //return boost::get<AMLData>(iter->second);
    return *static_cast<AMLData*>(iter->second->m_value);
}
