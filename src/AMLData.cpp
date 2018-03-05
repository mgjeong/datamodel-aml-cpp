#include <string>
#include <vector>
#include <map>
 
#include "AMLInterface.h"
#include "AMLException.h"

AMLData::AMLData(void)
{
}

AMLData::~AMLData(void)
{
}

void AMLData::setValue(const std::string& key, const std::string& value)
{
    m_values.insert(std::pair<std::string, std::string>(key, value));
}

void AMLData::setValue(const std::string& key, const std::vector<std::string>& value)
{
    m_values.insert(std::pair<std::string, std::vector<std::string>>(key, value));
}

void AMLData::setValue(const std::string& key, const AMLData& value)
{
    m_values.insert(std::pair<std::string, AMLData>(key, value));
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

    throw AMLException(Exception::DATA_INVALID_KEY);
}

std::string AMLData::getValueToStr(const std::string& key) const
{
    for (auto const& element : m_values)
    {
        if (key.compare(element.first) == 0)
        {
            auto type = element.second.which();

            if (type != 0)
            {
                throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
            }
            else
            {
                std::string ret = boost::get<std::string>(element.second);
                return ret;
            }
        }
    }

    throw AMLException(Exception::DATA_INVALID_KEY);
}

std::vector<std::string> AMLData::getValueToStrArr(const std::string& key) const
{
    for (auto const& element : m_values)
    {
        if (key.compare(element.first) == 0)
        {
            auto type = element.second.which();

            if (type != 1)
            {
                throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
            }
            else
            {
                std::vector<std::string> ret = boost::get<std::vector<std::string>>(element.second);
                return ret;
            }
        }
    }

    throw AMLException(Exception::DATA_INVALID_KEY);
}

AMLData AMLData::getValueToAMLData(const std::string& key) const
{
    for (auto const& element : m_values)
    {
        if (key.compare(element.first) == 0)
        {
            auto type = element.second.which();

            if (type != 2)
            {
                throw AMLException(Exception::KEY_VALUE_NOT_MATCH);
            }
            else
            {
                AMLData ret = boost::get<AMLData>(element.second);
                return ret;
            }
        }
    }

    throw AMLException(Exception::DATA_INVALID_KEY);
}
