# DataModel AML library (cpp)
datamodel-aml-cpp is a library which provides the way to present raw data(key/value based) to AutomationML(AML) standard format.
 - Transform raw data to AML data(XML).
 - Serialization / Deserialization AML data using protobuf.


## Prerequisites ##
- SCons
  - Version : 2.3.0 or above
  - [How to install](http://scons.org/doc/2.3.0/HTML/scons-user/c95.html)

- Boost
  - Version : 1.55.0 or above
  - [How to install](http://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html)


## How to build ##
1. Goto: ~/datamodel-aml-cpp/
2. Run the script:

   ```
   ./build.sh <options>       : Native build for x86_64
   ./build_arm.sh <options>   : Native build for armhf [Raspberry pi board])

**Notes** </br>
(a) For getting help about script option: **$ ./build.sh --help** </br>
(b) Currently, Script needs sudo permission for installing protobuf libraries. In future need for sudo will be removed by installing those libraries in aml library.


## How to run ##

### Prerequisites ###
 Built datamodel-aml-cpp library

### Sample ###
1. Goto: ~/datamodel-aml-cpp/out/linux/{ARCH}/{MODE}/samples/
2. export LD_LIBRARY_PATH=../
3. Run the sample:
    ```
     ./sample
    ```

## Usage guide for datamodel-aml-cpp library (for microservices)

1. The microservice which wants to use aml APIs has to link following libraries:</br></br>
   **(A) If microservice wants to link aml dynamically following are the libraries it needs to link:**</br>
        - aml.so</br>
   **(B) If microservice wants to link aml statically following are the libraries it needs to link:**</br>
        - aml.a</br>
2. Reference ezmq library APIs : [docs/docs/html/index.html](docs/docs/html/index.html)


</br></br>