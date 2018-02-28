#ifndef AML_INTERFACE_H_
#define AML_INTERFACE_H_

#include <string>
#include <vector>
#include <map>

enum class AMLValueType
{
    String,
    StringArray,
    AMLData
};
 
class AMLData
{
public:
    AMLData(void);
    virtual ~AMLData(void);

    void                        setValue(std::string key, std::string value);
    void                        setValue(std::string key, std::vector<std::string> value);
    void                        setValue(std::string key, AMLData value);

    std::string                 getValueToStr(std::string key);
    std::vector<std::string>    getValueToStrArr(std::string key);
    AMLData                     getValueToAMLData(std::string key);
    std::vector<std::string>    getKeys();
    AMLValueType                getValueType(std::string key);
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

private:
    std::string m_deviceId;
    std::string m_timeStamp;
    std::string m_id;
    mutable std::map<std::string, AMLData> m_amlDatas;
};

#endif // AML_INTERFACE_H_