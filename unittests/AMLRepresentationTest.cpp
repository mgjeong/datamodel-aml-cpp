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

#include <iostream>
#include <string>
#include <fstream>

#include "Representation.h"
#include "AMLException.h"
#include "gtest/gtest.h"

namespace AMLRepresentationTest
{
    std::string amlModelFile                = "./TEST_DataModel.aml";
    std::string amlModelFile_invalid_NoCAEX = "./TEST_DataModel_Invalid_NoCAEX.aml";
    std::string amlModelFile_invalid_NoRCL  = "./TEST_DataModel_Invalid_NoRCL.aml";
    std::string amlModelFile_invalid_NoSUCL = "./TEST_DataModel_Invalid_NoSUCL.aml";
    std::string amlDataFile                 = "./TEST_Data.aml";
    std::string dataBinaryFile              = "./TEST_DataBinary";

    // Helper method
    // datamodel::Event TestEvent()
    // {
    //     datamodel::Event event;
    //     event.set_device("Robot1");
    //     event.set_created(10);
    //     event.set_modified(20);
    //     event.set_id("id");
    //     event.set_pushed(30);
    //     event.set_origin(40);

    //     datamodel::Reading *reading1 = event.add_reading();
    //     reading1->set_name("Robot_Model");
    //     reading1->set_value("SR-P7-R970");
    //     reading1->set_created(50);
    //     reading1->set_device("Robot1");
    //     reading1->set_modified(51);
    //     reading1->set_id("id1");
    //     reading1->set_origin(52);
    //     reading1->set_pushed(53);

    //     datamodel::Reading *reading2 = event.add_reading();
    //     reading2->set_name("Robot_SW_Version");
    //     reading2->set_value("0.0.1");
    //     reading2->set_created(61);
    //     reading2->set_device("Robot1");
    //     reading2->set_modified(62);
    //     reading2->set_id("id2");
    //     reading2->set_origin(63);
    //     reading2->set_pushed(64);

    //     return event;
    // }

    std::string TestAML()
    {
        std::ifstream t(amlDataFile);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        return str;
    }

    std::string TestBinary()
    {
        std::ifstream t(dataBinaryFile);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        return str;
    }

    // bool isEqual(datamodel::Event* event1, datamodel::Event* event2)
    // {
    //     if (!event1 || !event2)                       return false;

    //     if (event1->device() != event2->device())     return false;
    //     if (event1->pushed() != event2->pushed())     return false;
    //     if (event1->id() != event2->id())             return false;
    //     if (event1->created() != event2->created())   return false;
    //     if (event1->modified() != event2->modified()) return false;
    //     if (event1->origin() != event2->origin())     return false;
        
    //     int size1 = event1->reading_size();
    //     int size2 = event2->reading_size();
    //     if (size1 != size2) return false;

    //     for (int i = 0; i < size1; i++)
    //     {
    //         datamodel::Reading reading1 = event1->reading(i);
    //         datamodel::Reading reading2 = event2->reading(i);

    //         if (reading1.device() != reading2.device())     return false;
    //         if (reading1.pushed() != reading2.pushed())     return false;
    //         if (reading1.name() != reading2.name())         return false;
    //         if (reading1.value() != reading2.value())       return false;
    //         if (reading1.id() != reading2.id())             return false;
    //         if (reading1.created() != reading2.created())   return false;
    //         if (reading1.modified() != reading2.modified()) return false;
    //         if (reading1.origin() != reading2.origin())     return false;
    //     }
        
    //     return true;
    // }

    // Test
    TEST(ConstructRepresentationTest, ValidAML)
    {
        EXPECT_NO_THROW(Representation rep = Representation(amlModelFile));
    }
/*
    TEST(ConstructRepresentationTest, InvalidFilePath)
    {
        EXPECT_THROW(Representation rep = Representation("NoExist.aml"), AMLException);
    }

    TEST(ConstructRepresentationTest, AMLwithoutCAEX)
    {
        EXPECT_THROW(Representation rep = Representation(amlModelFile_invalid_NoCAEX), AMLException);
    }

    TEST(ConstructRepresentationTest, AMLwithoutRCL)
    {
        EXPECT_THROW(Representation rep = Representation(amlModelFile_invalid_NoRCL), AMLException);
    }

    TEST(ConstructRepresentationTest, AMLwithoutSUCL)
    {
        EXPECT_THROW(Representation rep = Representation(amlModelFile_invalid_NoSUCL), AMLException);
    }

    TEST(AmlToEventTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event* event = NULL;
        std::string amlStr = TestAML();
        EXPECT_NO_THROW(event = rep.AmlToEvent(amlStr));

        datamodel::Event varify = TestEvent();
        EXPECT_TRUE(isEqual(event, &varify));

        if (NULL != event)  delete event;
    }

    TEST(AmlToEventTest, InvalidAml)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event* event = NULL;
        std::string invalidAmlStr("<invalid />");

        EXPECT_THROW(event = rep.AmlToEvent(invalidAmlStr), AMLException);

        if (NULL != event)  delete event;
    }

    TEST(EventToAmlTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event event = TestEvent();
        std::string amlStr;
        EXPECT_NO_THROW(amlStr = rep.EventToAml(&event));

        std::string varify = TestAML();
        EXPECT_EQ(varify.compare(amlStr), 0);
    }

    TEST(EventToAmlTest, NullParam)
    {
        Representation rep = Representation(amlModelFile);
        std::string amlStr;
        EXPECT_THROW(amlStr = rep.EventToAml(nullptr), AMLException);
    }

    //@TODO: Is this needed? If it is, what could be 'invalid event'?
    //TEST(EventToAmlTest, InvalidEvent) {}

    TEST(ByteToEventTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event* event = NULL;
        std::string binary = TestBinary();
        EXPECT_NO_THROW(event = rep.ByteToEvent(binary));

        datamodel::Event varify = TestEvent();
        EXPECT_TRUE(isEqual(event, &varify));

        if (NULL != event)  delete event;
    }

    TEST(ByteToEventTest, InvalidByte)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event* event = NULL;
        std::string amlBinary("invalidBinary");
        
        EXPECT_THROW(event = rep.ByteToEvent(amlBinary), AMLException);

        if (NULL != event)  delete event;
    }

    TEST(EventToByteTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        datamodel::Event event = TestEvent();
        std::string amlBinary;
        EXPECT_NO_THROW(amlBinary = rep.EventToByte(&event));

        std::string varify = TestBinary();
        EXPECT_EQ(varify.compare(amlBinary), 0);
    }

    TEST(EventToByteTest, NullParam)
    {
        Representation rep = Representation(amlModelFile);
        std::string byteStr;
        EXPECT_THROW(byteStr = rep.EventToByte(nullptr), AMLException);
    }
*/
    //@TODO: Is this needed? If it is, what could be 'invalid event'?
    //TEST(EventToByteTest, InvalidEvent) {}
}