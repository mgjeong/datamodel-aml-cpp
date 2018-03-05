#ifndef AML_INTERFACE_H_
#define AML_INTERFACE_H_

#include <string>
#include <vector>
#include <map>

#include <boost/variant.hpp>

class AMLData;

typedef std::map<std::string, boost::variant<std::string, std::vector<std::string>, AMLData>> AMLMap;

enum class AMLValueType
{
    String = 0,
    StringArray,
    AMLData
};

class AMLObject
{
public:
    AMLObject(const std::string& deviceId, const std::string& timeStamp);
    AMLObject(const std::string& deviceId, const std::string& timeStamp, const std::string& id);
    virtual ~AMLObject(void);

    void                        addData(const std::string& name, const AMLData& data);

    AMLData                     getData(const std::string& name) const;
    std::vector<std::string>    getDataNames() const;
    std::string                 getDeviceId() const;
    std::string                 getTimeStamp() const;
    std::string                 getId() const;

private:
    const std::string m_deviceId;
    const std::string m_timeStamp;
    const std::string m_id;
    mutable std::map<std::string, AMLData> m_amlDatas;
};

class AMLData
{
public:
    AMLData(void);
    virtual ~AMLData(void);

    void                        setValue(const std::string& key, const std::string& value);
    void                        setValue(const std::string& key, const std::vector<std::string>& value); 
    void                        setValue(const std::string& key, const AMLData& value);

    std::string                 getValueToStr(const std::string& key) const;
    std::vector<std::string>    getValueToStrArr(const std::string& key) const;
    AMLData                     getValueToAMLData(const std::string& key) const;
    std::vector<std::string>    getKeys() const;
    AMLValueType                getValueType(const std::string& key) const;

private:
    AMLMap m_values;
};

#endif // AML_INTERFACE_H_