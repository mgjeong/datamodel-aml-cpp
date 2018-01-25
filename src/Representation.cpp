#include <string>
//#include <stdexcept>
#include <sstream>

#include <iostream>
using namespace std;


#include "Representation.h"
#include "Event.pb.h"
#include "AML.pb.h"

#include "pugixml.hpp"

static const char CAEX_FILE[]                   = "CAEXFile";
static const char INSTANCE_HIERARCHY[]          = "InstanceHierarchy";
static const char ROLE_CLASS_LIB[]              = "RoleClassLib";
static const char ROLE_CLASS[]                  = "RoleClass";
static const char SYSTEM_UNIT_CLASS_LIB[]       = "SystemUnitClassLib";
static const char SYSTEM_UNIT_CLASS[]           = "SystemUnitClass";
static const char INTERNAL_ELEMENT[]            = "InternalElement";
static const char ATTRIBUTE[]                   = "Attribute";
static const char ADDITIONAL_INFORMATION[]      = "AdditionalInformation";

static const char NAME[]                        = "Name";
static const char VALUE[]                       = "Value";
static const char VERSION[]                     = "Version";
static const char ATTRIBUTE_DATA_TYPE[]         = "AttributeDataType";
static const char DESCRIPTION[]                 = "Description";
static const char REF_BASE_SYSTEM_UNIT_PATH[]   = "RefBaseSystemUnitPath";
static const char REF_ROLE_CLASS_PATH[]         = "RefRoleClassPath";
static const char REF_BASE_CLASS_PATH[]         = "RefBaseClassPath";
static const char SUPPORTED_ROLE_CLASS[]        = "SupportedRoleClass";

static const char EDGE_COREDATA[]               = "Edge_CoreData";
static const char EVENT[]                       = "Event";
static const char DATA[]                        = "Data";

static const char KEY_NAME[]                    = "name";
static const char KEY_VALUE[]                   = "value";
static const char KEY_DEVICE[]                  = "device";
static const char KEY_ID[]                      = "id";
static const char KEY_PUSHED[]                  = "pushed";
static const char KEY_CREATED[]                 = "created";
static const char KEY_MODIFIED[]                = "modified";
static const char KEY_ORIGIN[]                  = "origin";

#define IS_NAME(node, name)     (std::string((node).attribute(NAME).value()) == (name))
#define ADD_VALUE(node, value)  (node).append_child(VALUE).text().set((value).c_str())

// for test ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PRINT_NODE(node)    for (pugi::xml_node tool = (node).first_child(); tool; tool = tool.next_sibling()) \
                            {\
                                std::cout << "Tool:";\
                                for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())\
                                {\
                                     std::cout << " " << attr.name() << "=" << attr.value();\
                                }\
                                std::cout << std::endl;\
                            }\
                            std::cout<<std::endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void extractAttribute(T* attr, pugi::xml_node xmlNode);

template <class T>
void extractInternalElement(T* ie, pugi::xml_node xmlNode);

template <class T>
void extractProtoAttribute(pugi::xml_node xmlNode, T* attr);

template <class T>
void extractProtoInternalElement(pugi::xml_node xmlNode, T* ie);

template <typename T>
std::string toString(const T& t)
{
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

class Representation::AMLModel
{
public:
    AMLModel (const std::string& amlFilePath)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(amlFilePath.c_str());
        if (pugi::status_ok != result.status) {/*@TODO*/}
    
        m_doc = new pugi::xml_document(); // @TODO: try{}catch(std::bad_alloc& ba){printf("bad_alloc caught: %s ", ba.what());}
        m_doc->reset(doc);

        pugi::xml_node xmlCaexFile = m_doc->child(CAEX_FILE);
        if (NULL == xmlCaexFile) {/*@TODO*/}

        m_roleClassLib = xmlCaexFile.child(ROLE_CLASS_LIB);
        if (NULL == m_roleClassLib) {/*@TODO*/}
        
        m_systemUnitClassLib = xmlCaexFile.child(SYSTEM_UNIT_CLASS_LIB);
        if (NULL == m_systemUnitClassLib) {/*@TODO*/}

        // remove unnecessary info
        while (xmlCaexFile.child(INSTANCE_HIERARCHY))       xmlCaexFile.remove_child(INSTANCE_HIERARCHY);
        while (xmlCaexFile.child(ADDITIONAL_INFORMATION))   xmlCaexFile.remove_child(ADDITIONAL_INFORMATION);
    }
    
    ~AMLModel()
    {
        delete m_doc;
    }
    
    datamodel::Event* constructEvent(pugi::xml_document* xml_caex)
    {
        datamodel::Event* event = new datamodel::Event();

        pugi::xml_node xml_ih = xml_caex->child(CAEX_FILE).child(INSTANCE_HIERARCHY); // xml_ih might have next_sibling(INSTANCE_HIERARCHY)

        pugi::xml_node xml_event;
        for (xml_event = xml_ih.child(INTERNAL_ELEMENT); xml_event; xml_event = xml_event.next_sibling(INTERNAL_ELEMENT))
        {
            if (std::string(xml_event.attribute(NAME).value()) == EVENT) break; // What if there are more than 2 events?
        }

        for (pugi::xml_node xml_attr = xml_event.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
        {
            if      (IS_NAME(xml_attr, KEY_DEVICE))     event->set_device   (xml_attr.child(VALUE).text().as_string());
            else if (IS_NAME(xml_attr, KEY_ID))         event->set_id       (xml_attr.child(VALUE).text().as_string());
            else if (IS_NAME(xml_attr, KEY_PUSHED))     event->set_pushed   (xml_attr.child(VALUE).text().as_llong());
            else if (IS_NAME(xml_attr, KEY_CREATED))    event->set_created  (xml_attr.child(VALUE).text().as_llong());
            else if (IS_NAME(xml_attr, KEY_MODIFIED))   event->set_modified (xml_attr.child(VALUE).text().as_llong());
            else if (IS_NAME(xml_attr, KEY_ORIGIN))     event->set_origin   (xml_attr.child(VALUE).text().as_llong());
        }

        pugi::xml_node xml_data;
        for (xml_data = xml_event.child(INTERNAL_ELEMENT) ; xml_data; xml_data = xml_data.next_sibling(INTERNAL_ELEMENT))
        {
            if (std::string(xml_data.attribute(NAME).value()) == DATA)
            {
                datamodel::Reading *reading = event->add_reading();

                for (pugi::xml_node xml_attr = xml_data.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
                {
                    if      (IS_NAME(xml_attr, KEY_DEVICE))     reading->set_device   (xml_attr.child(VALUE).text().as_string());
                    else if (IS_NAME(xml_attr, KEY_ID))         reading->set_id       (xml_attr.child(VALUE).text().as_string());
                    else if (IS_NAME(xml_attr, KEY_NAME))       reading->set_name     (xml_attr.child(VALUE).text().as_string());
                    else if (IS_NAME(xml_attr, KEY_VALUE))      reading->set_value    (xml_attr.child(VALUE).text().as_string());
                    else if (IS_NAME(xml_attr, KEY_PUSHED))     reading->set_pushed   (xml_attr.child(VALUE).text().as_llong());
                    else if (IS_NAME(xml_attr, KEY_CREATED))    reading->set_created  (xml_attr.child(VALUE).text().as_llong());
                    else if (IS_NAME(xml_attr, KEY_MODIFIED))   reading->set_modified (xml_attr.child(VALUE).text().as_llong());
                    else if (IS_NAME(xml_attr, KEY_ORIGIN))     reading->set_origin   (xml_attr.child(VALUE).text().as_llong());
                }
            }
        }

        return event;
    }

    pugi::xml_document* constructXmlDoc(const datamodel::Event* event)
    {
        pugi::xml_document* xml_doc = new pugi::xml_document();

        // initialize AML
        pugi::xml_node xml_caexFile = initializeAML(xml_doc);
        
        // add InstanceHierarchy
        pugi::xml_node xml_ih = xml_caexFile.append_child(INSTANCE_HIERARCHY);
        xml_ih.append_attribute(NAME) = EDGE_COREDATA;

        // add Event as InternalElement
        pugi::xml_node xml_event = addInternalElement(xml_ih, EVENT);

        for (pugi::xml_node xml_attr = xml_event.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
        {
            if      (IS_NAME(xml_attr, KEY_DEVICE))     ADD_VALUE(xml_attr, event->device());
            else if (IS_NAME(xml_attr, KEY_ID))         ADD_VALUE(xml_attr, event->id());
            else if (IS_NAME(xml_attr, KEY_PUSHED))     ADD_VALUE(xml_attr, toString(event->pushed()));
            else if (IS_NAME(xml_attr, KEY_CREATED))    ADD_VALUE(xml_attr, toString(event->created()));
            else if (IS_NAME(xml_attr, KEY_MODIFIED))   ADD_VALUE(xml_attr, toString(event->modified()));
            else if (IS_NAME(xml_attr, KEY_ORIGIN))     ADD_VALUE(xml_attr, toString(event->origin()));
        }

        // add Data(s) as InternalElement
        for (int i = 0, size = event->reading_size(); i < size; i++)
        {
            datamodel::Reading reading = event->reading(i);

            pugi::xml_node xml_data = addInternalElement(xml_event, DATA);

            for (pugi::xml_node xml_attr = xml_data.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
            {
                if      (IS_NAME(xml_attr, KEY_DEVICE))     ADD_VALUE(xml_attr, reading.device());
                else if (IS_NAME(xml_attr, KEY_NAME))       ADD_VALUE(xml_attr, reading.name());
                else if (IS_NAME(xml_attr, KEY_ID))         ADD_VALUE(xml_attr, reading.id());
                else if (IS_NAME(xml_attr, KEY_VALUE))      ADD_VALUE(xml_attr, reading.value());
                else if (IS_NAME(xml_attr, KEY_PUSHED))     ADD_VALUE(xml_attr, toString(reading.pushed()));
                else if (IS_NAME(xml_attr, KEY_CREATED))    ADD_VALUE(xml_attr, toString(reading.created()));
                else if (IS_NAME(xml_attr, KEY_MODIFIED))   ADD_VALUE(xml_attr, toString(reading.modified()));
                else if (IS_NAME(xml_attr, KEY_ORIGIN))     ADD_VALUE(xml_attr, toString(reading.origin()));
            }
        }
       
        return xml_doc;
    }

    void appendModel(pugi::xml_document* xml_doc)    
    {
        // append RoleClassLib and SystemUnitClassLib
        xml_doc->child(CAEX_FILE).append_copy(m_roleClassLib);
        xml_doc->child(CAEX_FILE).append_copy(m_systemUnitClassLib);
    }

private:
    pugi::xml_document* m_doc;
    pugi::xml_node m_roleClassLib;
    pugi::xml_node m_systemUnitClassLib;

    pugi::xml_node initializeAML(pugi::xml_document* xml_doc)
    {
        pugi::xml_node xml_decl = xml_doc->prepend_child(pugi::node_declaration);
        xml_decl.append_attribute("version") = "1.0";
        xml_decl.append_attribute("encoding") = "utf-8";
        xml_decl.append_attribute("standalone") = "yes"; // @TODO: required?

        pugi::xml_node xml_caexFile = xml_doc->append_child(CAEX_FILE);
        xml_caexFile.append_attribute("FileName") = "test.aml"; // @TODO: set by application? or randomly generated? or using time stamp of event
        xml_caexFile.append_attribute("SchemaVersion") = "2.15";
        xml_caexFile.append_attribute("xsi:noNamespaceSchemaLocation") = "CAEX_ClassModel_V2.15.xsd";
        xml_caexFile.append_attribute("xmlns:xsi") = "http://www.w3.org/2001/XMLSchema-instance";

        return xml_caexFile;
    }

    pugi::xml_node addInternalElement(pugi::xml_node xml_ih, const std::string suc_name)
    {
        pugi::xml_node xml_ie = xml_ih.append_child(INTERNAL_ELEMENT);

        for (pugi::xml_node xml_suc = m_systemUnitClassLib.child(SYSTEM_UNIT_CLASS); xml_suc; xml_suc = xml_suc.next_sibling(SYSTEM_UNIT_CLASS))
        {
            if (std::string(xml_suc.attribute(NAME).value()) == suc_name)
            {
                // set Name
                xml_ie.append_attribute(NAME) = suc_name.c_str();

                // set RefBaseSystemUnitPath
                std::string refBaseSystemUnitPath;
                refBaseSystemUnitPath.append(m_systemUnitClassLib.attribute(NAME).value());
                refBaseSystemUnitPath.append("/");
                refBaseSystemUnitPath.append(suc_name);
                xml_ie.append_attribute(REF_BASE_SYSTEM_UNIT_PATH) = refBaseSystemUnitPath.c_str();

                // set Attribute(s)
                for (pugi::xml_node xml_attr = xml_suc.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
                {
                    xml_ie.append_copy(xml_attr);
                }

                // set SupportedRoleClass
                xml_ie.append_copy(xml_suc.child(SUPPORTED_ROLE_CLASS));

                break;
            }
        }

        return xml_ie;
    }
};

Representation::Representation(const std::string amlFilePath) : m_amlModel (new AMLModel(amlFilePath))
{
}

Representation::~Representation(void)
{
    delete m_amlModel;
}

datamodel::Event* Representation::AmlToEvent(const std::string& xmlStr)
{
    pugi::xml_document dataXml;
    pugi::xml_parse_result result = dataXml.load_string(xmlStr.c_str());
    if (pugi::status_ok != result.status) {/*@TODO*/}

    datamodel::Event *event = m_amlModel->constructEvent(&dataXml);
    if (NULL == event) {/*@TODO*/} //assert?

    return event;
}

std::string Representation::EventToAml(const datamodel::Event* event)
{
    pugi::xml_document* xml_doc = m_amlModel->constructXmlDoc(event);
    
    m_amlModel->appendModel(xml_doc);

    std::ostringstream stream;
    xml_doc->save(stream);

    delete xml_doc;

    return stream.str();
}



datamodel::Event* Representation::ByteToEvent(const std::string byte)
{
    datamodel::CAEXFile* caex = new datamodel::CAEXFile();
    caex->ParseFromString(byte);

    pugi::xml_document* xml_doc = new pugi::xml_document();

    pugi::xml_node xml_decl = xml_doc->prepend_child(pugi::node_declaration);
    xml_decl.append_attribute("version") = "1.0";
    xml_decl.append_attribute("encoding") = "utf-8";
    xml_decl.append_attribute("standalone") = "yes";

    pugi::xml_node xml_caex = xml_doc->append_child(CAEX_FILE);
    xml_caex.append_attribute("FileName") = caex->filename().c_str();
    xml_caex.append_attribute("SchemaVersion") = caex->schemaversion().c_str();
    xml_caex.append_attribute("xsi:noNamespaceSchemaLocation") = caex->xsi().c_str();
    xml_caex.append_attribute("xmlns:xsi") = caex->xmlns().c_str();

    for(datamodel::InstanceHierarchy ih: caex->instancehierarchy()) {
        pugi::xml_node xml_ih = xml_caex.append_child(INSTANCE_HIERARCHY);
        xml_ih.append_attribute(NAME) = ih.name().c_str();

        extractProtoInternalElement(xml_ih, &ih);


    }

    datamodel::Event *event = m_amlModel->constructEvent(xml_doc);

    return event;
}

std::string Representation::EventToByte(const datamodel::Event* event)
{
    // convert Event to XML object
    pugi::xml_document* xml_doc = m_amlModel->constructXmlDoc(event);
    
    // convert XML object to AML proto object
    std::vector<datamodel::InstanceHierarchy*> ihList;

    datamodel::CAEXFile* caex = new datamodel::CAEXFile();

    pugi::xml_node xml_caex = xml_doc->child(CAEX_FILE);
    caex->set_filename(xml_caex.attribute("FileName").value());
    caex->set_schemaversion(xml_caex.attribute("SchemaVersion").value());
    caex->set_xsi(xml_caex.attribute("xsi:noNamespaceSchemaLocation").value());
    caex->set_xmlns(xml_caex.attribute("xmlns:xsi").value());

    for (pugi::xml_node xml_ih = xml_doc->child(CAEX_FILE).child(INSTANCE_HIERARCHY); xml_ih; xml_ih = xml_ih.next_sibling(INSTANCE_HIERARCHY))
    {
        datamodel::InstanceHierarchy* ih = caex->add_instancehierarchy();
        //datamodel::InstanceHierarchy* ih = new datamodel::InstanceHierarchy();

        ih->set_name    (xml_ih.attribute(NAME).value());
      //ih->set_version (xml_ih.child_value(VERSION)); // @TODO: required?
        
        extractInternalElement<datamodel::InstanceHierarchy>(ih, xml_ih);
    }

    std::string binary;
    caex->SerializeToString(&binary);  // @TODO: constructXmlDoc currently ensures that xml_doc has only one InstanceHierarchy.

    return binary;
}


template <class T>
void extractProtoAttribute(pugi::xml_node xmlNode, T* attr)
{   
    for (datamodel::Attribute att: attr->attribute()) {
        pugi::xml_node xml_attr = xmlNode.append_child(ATTRIBUTE);

        xml_attr.append_attribute(NAME) = att.name().c_str();
        xml_attr.append_attribute(ATTRIBUTE_DATA_TYPE) = att.attributedatatype().c_str();

        extractProtoAttribute(xml_attr, &att);
         
        xml_attr.append_child(VALUE).text().set(att.value().c_str());
    }

    return;
}

template <class T>
void extractProtoInternalElement(pugi::xml_node xmlNode, T* ie)
{
    for (datamodel::InternalElement sie: ie->internalelement()) {
        pugi::xml_node xml_ie = xmlNode.append_child(INTERNAL_ELEMENT);

        xml_ie.append_attribute(NAME) = sie.name().c_str();
        xml_ie.append_attribute(REF_BASE_SYSTEM_UNIT_PATH) = sie.refbasesystemunitpath().c_str();

        extractProtoAttribute(xml_ie, &sie);
        extractProtoInternalElement(xml_ie, &sie);

        if(nullptr != &sie.supportedroleclass()) {
            if(nullptr != &sie.supportedroleclass().refroleclasspath()) {
                pugi::xml_node xml_src = xml_ie.append_child(SUPPORTED_ROLE_CLASS);
                xml_src.append_attribute(REF_ROLE_CLASS_PATH) = sie.supportedroleclass().refroleclasspath().c_str();
            }
        }
    }
    
    return;
}


template <class T>
void extractAttribute(T* attr, pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlAttr = xmlNode.child(ATTRIBUTE); xmlAttr; xmlAttr = xmlAttr.next_sibling(ATTRIBUTE))
    {
        datamodel::Attribute* attr_child = attr->add_attribute();

        attr_child->set_name              (xmlAttr.attribute(NAME).value());
        attr_child->set_attributedatatype (xmlAttr.attribute(ATTRIBUTE_DATA_TYPE).value());
      //attr->set_description       (xmlAttr.child_value(DESCRIPTION)); //@TODO: required?

        extractAttribute<datamodel::Attribute>(attr_child, xmlAttr);

        pugi::xml_node xmlValue = xmlAttr.child(VALUE);
        if (NULL != xmlValue)
        {
            attr_child->set_value(xmlValue.text().as_string());
        }
    }

    return;
}

template <class T>
void extractInternalElement(T* ie, pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlIe = xmlNode.child(INTERNAL_ELEMENT); xmlIe; xmlIe = xmlIe.next_sibling(INTERNAL_ELEMENT))    
    {
        datamodel::InternalElement* ie_child = ie->add_internalelement();

        ie_child->set_name                    (xmlIe.attribute(NAME).value());
        ie_child->set_refbasesystemunitpath   (xmlIe.attribute(REF_BASE_SYSTEM_UNIT_PATH).value());
        
        extractAttribute<datamodel::InternalElement>(ie_child, xmlIe);
        extractInternalElement<datamodel::InternalElement>(ie_child, xmlIe);

        pugi::xml_node xmlSrc = xmlIe.child(SUPPORTED_ROLE_CLASS);
        if (NULL != xmlSrc)
        {
            datamodel::SupportedRoleClass* src = new datamodel::SupportedRoleClass();
            src->set_refroleclasspath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

            ie_child->set_allocated_supportedroleclass(src);
        }
    }

    return;
}
