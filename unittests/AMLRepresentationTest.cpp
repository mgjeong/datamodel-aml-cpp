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

using namespace std;

// helper methods
void printAMLData(AMLData amlData, int depth)
{
    string indent;
    for (int i = 0; i < depth; i++) indent += "    ";

    cout << indent << "{" << endl;

    vector<string> keys = amlData.getKeys();
    for (string key : keys)
    {
        cout << indent << "    \"" << key << "\" : ";

        AMLValueType type = amlData.getValueType(key);
        if (AMLValueType::String == type)
        {
            string valStr = amlData.getValueToStr(key);
            cout << valStr;
        }
        else if (AMLValueType::StringArray == type)
        {
            vector<string> valStrArr = amlData.getValueToStrArr(key);
            cout << "[";
            for (string val : valStrArr)
            {
                cout << val;
                if (val != valStrArr.back()) cout << ", ";
            }
            cout << "]";
        }
        else if (AMLValueType::AMLData == type)
        {
            AMLData valAMLData = amlData.getValueToAMLData(key);
            cout << endl;
            printAMLData(valAMLData, depth + 1);
        }

        if (key != keys.back()) cout << ",";
        cout << endl;
    }
    cout << indent << "}";
}

void printAMLObject(AMLObject amlObj)
{
    cout << "{" << endl;
    cout << "    \"device\" : " << amlObj.getDeviceId() << "," << endl;
    cout << "    \"timestamp\" : " << amlObj.getTimeStamp() << "," << endl;
    cout << "    \"id\" : " << amlObj.getId() << "," << endl;

    vector<string> dataNames = amlObj.getDataNames();

    for (string n : dataNames)
    {
        AMLData data = amlObj.getData(n);

        cout << "    \"" << n << "\" : " << endl;
        printAMLData(data, 1);
        if (n != dataNames.back()) cout << "," << endl;
    }

    cout << "\n}" << endl;
}

namespace AMLRepresentationTest
{
    std::string amlModelFile                = "./TEST_DataModel.aml";
    std::string amlModelFile_invalid_NoCAEX = "./TEST_DataModel_Invalid_NoCAEX.aml";
    std::string amlModelFile_invalid_NoSUCL = "./TEST_DataModel_Invalid_NoSUCL.aml";
    std::string amlDataFile                 = "./TEST_Data.aml";
    std::string dataBinaryFile              = "./TEST_DataBinary";

    // Helper method
    AMLObject TestAMLObject()
    {
        // create AMLObject
        string deviceId = "GTC001";
        string timeStamp = "123456789";

        AMLObject amlObj(deviceId, timeStamp);


        // create "Model" data
        AMLData model;
        model.setValue("ctname", "Model_107.113.97.248");
        model.setValue("con", "SR-P7-970");

        // create "Sample" data
        AMLData axis;
        axis.setValue("x", "20");
        axis.setValue("y", "110");
        axis.setValue("z", "80");

        AMLData info;
        info.setValue("id", "f437da3b");
        info.setValue("axis", axis);

        vector<string> appendix;
        appendix.push_back("52303");
        appendix.push_back("935");
        appendix.push_back("1442");

        AMLData sample;
        sample.setValue("info", info);
        sample.setValue("appendix", appendix);


        // Add Datas to AMLObject
        amlObj.addData("Model", model);
        amlObj.addData("Sample", sample);

        return amlObj;
    }

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

    bool isEqual(vector<string>& vecStr1, vector<string>& vecStr2)
    {
        if (vecStr1.size() != vecStr2.size())     return false;
        if (false == std::equal(vecStr1.begin(), vecStr1.end(), vecStr2.begin())) return false;

        return true;
    }

    bool isEqual(AMLData& data1, AMLData& data2)
    {
        vector<string> keys1 = data1.getKeys();
        vector<string> keys2 = data2.getKeys();

        if (false == isEqual(keys1, keys2)) return false;

        for (string key : keys1)
        {
            AMLValueType type1 = data1.getValueType(key);
            AMLValueType type2 = data2.getValueType(key);
            if (type1 != type2)     return false;

            if (AMLValueType::String == type1)
            {
                string valStr1 = data1.getValueToStr(key);
                string valStr2 = data2.getValueToStr(key);
                if (valStr1 != valStr2) return false;
            }
            else if (AMLValueType::StringArray == type1)
            {
                vector<string> valStrArr1 = data1.getValueToStrArr(key);
                vector<string> valStrArr2 = data2.getValueToStrArr(key);

                if (false == isEqual(valStrArr1, valStrArr2)) return false;
            }
            else if (AMLValueType::AMLData == type1)
            {
                AMLData valAMLData1 = data1.getValueToAMLData(key);
                AMLData valAMLData2 = data2.getValueToAMLData(key);
                
                if (false == isEqual(valAMLData1, valAMLData2)) return false;
            }
        }
        return true;
    }

    bool isEqual(AMLObject& obj1, AMLObject& obj2)
    {
        if (obj1.getDeviceId() != obj2.getDeviceId())   return false;
        if (obj1.getTimeStamp() != obj2.getTimeStamp()) return false;
        if (obj1.getId() != obj2.getId())               return false;

        vector<string> dataNames1 = obj1.getDataNames();
        vector<string> dataNames2 = obj2.getDataNames();

        if (false == isEqual(dataNames1, dataNames2))   return false;

        for (string n : dataNames1)
        {
            AMLData data1 = obj1.getData(n);
            AMLData data2 = obj2.getData(n); // If obj2 does not have n??? -> return false

            if (false == isEqual(data1, data2))         return false;
        }

        return true;
    }

    // Test
    TEST(ConstructRepresentationTest, ValidAML)
    {
        EXPECT_NO_THROW(Representation rep = Representation(amlModelFile));
    }

    TEST(ConstructRepresentationTest, InvalidFilePath)
    {
        EXPECT_THROW(Representation rep = Representation("NoExist.aml"), AMLException);
    }

    TEST(ConstructRepresentationTest, AMLwithoutCAEX)
    {
        EXPECT_THROW(Representation rep = Representation(amlModelFile_invalid_NoCAEX), AMLException);
    }

    TEST(ConstructRepresentationTest, AMLwithoutSUCL)
    {
        EXPECT_THROW(Representation rep = Representation(amlModelFile_invalid_NoSUCL), AMLException);
    }

    TEST(AmlToDataTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject* amlObj = NULL;
        std::string amlStr = TestAML();
        EXPECT_NO_THROW(amlObj = rep.AmlToData(amlStr));

        AMLObject varify = TestAMLObject();
        EXPECT_TRUE(isEqual(*amlObj, varify));

        if (NULL != amlObj) delete amlObj;
    }

    TEST(AmlToDataTest, InvalidAml)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject* amlObj = NULL;
        std::string invalidAmlStr("<invalid />");

        EXPECT_THROW(amlObj = rep.AmlToData(invalidAmlStr), AMLException);

        if (NULL != amlObj)  delete amlObj;
    }

    TEST(DataToAmlTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject amlObj = TestAMLObject();
        std::string amlStr;
        EXPECT_NO_THROW(amlStr = rep.DataToAml(amlObj));

        std::string varify = TestAML();
        EXPECT_EQ(varify.compare(amlStr), 0);
    }

    TEST(ByteToDataTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject* amlObj = NULL;
        std::string binary = TestBinary();
        EXPECT_NO_THROW(amlObj = rep.ByteToData(binary));

        AMLObject varify = TestAMLObject();
        EXPECT_TRUE(isEqual(*amlObj, varify));

        if (NULL != amlObj)  delete amlObj;
    }

    TEST(ByteToDataTest, InvalidByte)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject* amlObj = NULL;
        std::string amlBinary("invalidBinary");
        
        EXPECT_THROW(amlObj = rep.ByteToData(amlBinary), AMLException);

        if (NULL != amlObj)  delete amlObj;
    }

    TEST(DataToByteTest, ConvertValid)
    {
        Representation rep = Representation(amlModelFile);
        AMLObject amlObj = TestAMLObject();
        std::string amlBinary;
        EXPECT_NO_THROW(amlBinary = rep.DataToByte(amlObj));

        std::string varify = TestBinary();
        EXPECT_EQ(varify.compare(amlBinary), 0);
    }
}