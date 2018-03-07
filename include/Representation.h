#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "AMLInterface.h"

#ifdef __cplusplus
extern "C"
{
#endif

class Representation
{
public:
    Representation(const std::string amlFilePath);
    virtual ~Representation(void);

    /**
     * @fn std::string DataToAml(const AMLObject& amlObject) const
     * @brief       This function converts AMLObject to AML(XML) string to match the AML model information which is set by constructor.
     * @param       amlObject [in] AMLObject to be converted.
     * @return      AML(XML) string converted from amlObject.
     * @exception   AMLException If the schema of amlObject does not match to AML model information
     */
    std::string DataToAml(const AMLObject& amlObject) const;

    /**
     * @fn AMLObject* AmlToData(const std::string& xmlStr) const
     * @brief       This function converts AML(XML) string to AMLObject to match the AML model information which is set by constructor.
     * @param       xmlStr [in] AML(XML) string to be converted.
     * @return      AMLObject converted from amlObject.
     * @exception   AMLException If the schema of amlObject does not match to AML model information
     * @note        AMLObject instance will be allocated and returned, so it should be deleted after use.
     */
    AMLObject* AmlToData(const std::string& xmlStr) const;

    std::string DataToByte(const AMLObject& amlObject) const;
    AMLObject* ByteToData(const std::string& byte) const;

private:
    class AMLModel;
    AMLModel* m_amlModel;
};

#ifdef __cplusplus
}
#endif

#endif // REPRESENTAITON_H_