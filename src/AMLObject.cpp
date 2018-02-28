#include <string>
#include <map>
#include <vector>

#include "AMLInterface.h"

using namespace std;

AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp)
{
    std::string id = deviceId + "_" + timeStamp; // @TODO: just like this?
    AMLObject(deviceId, timeStamp, id);
}

AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp, const std::string& id)
{
    m_deviceId = deviceId;
    m_timeStamp = timeStamp;
    m_id = id;
}

AMLObject::~AMLObject(void)
{
}

void AMLObject::addData(const std::string& name, const AMLData& data)
{
    //m_amlDatas.insert( map<string, AMLData>::value_type(name, data) ); // This will be removed after verifying the below works fine.

    // Try to insert a new element into the map and if the key already exists, throw an exeption.
    if (!m_amlDatas.insert(make_pair(name, data)).second)
    {
        // @TODO: throw exeption
    }
}

AMLData AMLObject::getData(const std::string& name) const
{
    map<string, AMLData>::iterator iter = m_amlDatas.find(name);
    if (iter == m_amlDatas.end())
    {
        // The name does not exist.
        // @TODO: throw exeption
    }

    return iter->second;
}

vector<string> AMLObject::getDataNames() const
{
    vector<string> dataNames;
    for (auto const& iter : m_amlDatas)
    {
        dataNames.push_back(iter.first);
    }

    return dataNames;
}

std::string AMLObject::getDeviceId() const
{
    return m_deviceId;
}

std::string AMLObject::getTimeStamp() const
{
    return m_timeStamp;
}