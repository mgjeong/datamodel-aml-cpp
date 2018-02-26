#ifndef AML_INTERFACE_H_
#define AML_INTERFACE_H_

#include <string>
#include <vector>

class AMLObject
{
    AMLObject(std::string deviceId, std::string timeStamp);
    virtual ~AMLObject(void);

    void                        addData(std::string name, AMLData data);

    AMLData                     getData(std::string name);
    std::vector<std::string>    getDataNames();
    std::string                 getDeviceId();
    std::string                 getTimeStamp();
};

enum class AMLValueType
{
    String,
    StringArray,
    AMLData
};
 
class AMLData
{
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

#endif // AML_INTERFACE_H_