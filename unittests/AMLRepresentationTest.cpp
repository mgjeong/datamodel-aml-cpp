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

#include "Representation.h"
#include "Event.pb.h"
#include "gtest/gtest.h"

namespace AMLRepresentationTest
{
    std::string amlFilePath = "TEST_DataModel.aml";

    // Helper method
    datamodel::Event createSampleEvent()
    {
        datamodel::Event event;
        event.set_device("Robot1");
        event.set_created(10);
        event.set_modified(20);
        event.set_id("id");
        event.set_pushed(10);
        event.set_origin(20);

        datamodel::Reading *reading1 = event.add_reading();
        reading1->set_name("Robot_Model");
        reading1->set_value("SR-P7-R970");
        reading1->set_created(25);
        reading1->set_device("Robot1");
        reading1->set_modified(20);
        reading1->set_id("id1");
        reading1->set_origin(25);
        reading1->set_pushed(1);

        datamodel::Reading *reading2 = event.add_reading();
        reading2->set_name("Robot_SW_Version");
        reading2->set_value("0.0.1");
        reading2->set_created(30);
        reading2->set_device("Robot1");
        reading2->set_modified(20);
        reading2->set_id("id2");
        reading2->set_origin(25);
        reading2->set_pushed(1);

        return event;
    }

    TEST(SampleTest, SampleOK)
    {
        Representation rep = Representation(amlFilePath);
        datamodel::Event event = createSampleEvent();

        // convert 'Event' to 'AML string'
        std::string aml_string = rep.EventToAml(&event);

        EXPECT_EQ(0, 0); //@TODO
    }
}