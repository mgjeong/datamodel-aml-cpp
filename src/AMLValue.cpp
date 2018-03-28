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
#include <vector>
#include <map>
 
#include "AMLInterface.h"
#include "AMLException.h"
#include "AMLLogger.h"

#define TAG "AMLValue"

using namespace std;

AMLValue::AMLValue()
{
}

AMLValue::~AMLValue()
{
    if(type == AMLValueType::String)
    {
        delete static_cast<std::string*>(m_value);    
    }
    else if(type == AMLValueType::StringArray)
    {
        delete static_cast<std::vector<std::string>*>(m_value);
    }
    else
    {
        delete static_cast<AMLData*>(m_value);
    }
}
