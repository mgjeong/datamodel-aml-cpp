#include <iostream>
#include <string>

#include "Representation.h"
#include "Event.pb.h"

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

/*
    Raw Data1 (name : "Model")
    {
        "ctname": "Model_107.113.97.248",
        "con": "SR-P7-970"
    }

    Raw Data2 (name : "Sample")
    {
        "info": {
            "id": "f437da3b",
            "axis": {
                "x": "20",
                "y": "110"
                "z": "80"
            }
        },
        "appendix": [
            "935",
            "52303",
            "1442"
        ]
    }
*/

int main() {
    // construct Representation object
    Representation* rep = new Representation("data_modeling.aml");


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
    appendix.push_back("935");
    appendix.push_back("52303");
    appendix.push_back("1442");

    AMLData sample;
    sample.setValue("info", info);
    sample.setValue("appendix", appendix);


    // Add Datas to AMLObject
    amlObj.addData("Model", model);
    amlObj.addData("Sample", sample);


    // Convert AMLObject to AMLstring(XML)
    string aml_string = rep->DataToAml(&amlObj);
    cout << aml_string << endl;
    cout << "-------------------------------------------------------------" << endl;

    // Convert AMLstring(XML) to AMLObject
    AMLObject* data_from_aml = rep->AmlToData(aml_string);
    printAMLObject(*data_from_aml);
    cout << "-------------------------------------------------------------" << endl;

    delete data_from_aml;
}