###############################################################################
# Copyright 2018 Samsung Electronics All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###############################################################################

#!/bin/bash
set +e
#Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NO_COLOUR="\033[0m"

PROJECT_ROOT=$(pwd)
AML_TARGET_ARCH=x86_64
AML_WITH_DEP=false
AML_BUILD_MODE="release"
AML_LOGGING="off"

install_dependencies() {
    cd ./dependencies
    DEP_ROOT=$(pwd)
    
    FILENAME="protobuf-cpp-3.4.0.tar.gz"
    if [ -e "$FILENAME" ]; then
        echo "Protobuf tar exist"
    else
        wget https://github.com/google/protobuf/releases/download/v3.4.0/protobuf-cpp-3.4.0.tar.gz
    fi

    if [ -d "./protobuf-3.4.0" ]; then
        echo "Protobuf library folder exist"
    else
        tar -xvf protobuf-cpp-3.4.0.tar.gz
    fi

    cd protobuf-3.4.0/
    chmod +x autogen.sh
    ./autogen.sh
    if [ "arm" = ${EZMQ_TARGET_ARCH} ]; then
        echo -e "${BLUE}Protobuf configuring for arm${NO_COLOUR}"
        ./configure --host=arm-linux CC=arm-linux-gnueabi-gcc CXX=arm-linux-gnueabi-g++
        make -j 4
    elif [ "arm64" = ${EZMQ_TARGET_ARCH} ]; then
        echo -e "${BLUE}Protobuf configuring for arm64${NO_COLOUR}"
        ./configure --host=aarch64-unknown-linux-gnu CC=/usr/bin/aarch64-linux-gnu-gcc-4.8 CXX=/usr/bin/aarch64-linux-gnu-g++-4.8
        make -j 4
    elif [ "armhf" = ${EZMQ_TARGET_ARCH} ]; then
        echo -e "${BLUE}Protobuf configuring for armhf${NO_COLOUR}"
        ./configure --host=arm-linux-gnueabihf CC=arm-linux-gnueabihf-gcc-4.8 CXX=arm-linux-gnueabihf-g++-4.8
        make -j 4
    else
        ./configure
        make -j 4
        sudo make install
    fi
    sudo ldconfig
    echo -e "${GREEN}Install dependencies done${NO_COLOUR}"
}

usage() {
    echo -e "${BLUE}Usage:${NO_COLOUR} ./build.sh <option>"
    echo -e "${GREEN}Options:${NO_COLOUR}"
    echo "  --with_dependencies=(default: false)                         :  Build aml along with dependencies [protobuf]"
    echo "  --build_mode=[release|debug](default: release)               :  Build aml library and samples in release or debug mode"
    echo "  --logging=[on|off](default: off)                             :  Build aml library including logs"
    echo "  -c                                                           :  Clean aml repository"
    echo "  -h / --help                                                  :  Display help and exit"
}

build() {
    RELEASE="1"
    LOGGING="0"
    if [ ${AML_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    if [ "debug" = ${AML_BUILD_MODE} ]; then
        RELEASE="0"
    fi
    if [ "on" = ${AML_LOGGING} ]; then
        LOGGING="1"
    fi
    
    scons TARGET_OS=linux TARGET_ARCH=${AML_TARGET_ARCH} RELEASE=${RELEASE} LOGGING=${LOGGING}
    if [ $? -ne 0 ]; then 
        echo -e "\033[31m"Build failed"\033[0m" 
        exit 1 
    fi
}

clean() {
    scons -c
    rm -r "${PROJECT_ROOT}/out/" "${PROJECT_ROOT}/.sconsign.dblite"
    find "${PROJECT_ROOT}" -name "*.memcheck" -delete -o -name "*.gcno" -delete -o -name "*.gcda" -delete -o -name "*.os" -delete -o -name "*.o" -delete
    echo -e "Finished Cleaning"
}

process_cmd_args() {
    while [ "$#" -gt 0  ]; do
        case "$1" in
            --with_dependencies=*)
                AML_WITH_DEP="${1#*=}";
                if [ ${AML_WITH_DEP} = true ]; then
                    echo -e "${GREEN}Build with depedencies${NO_COLOUR}"
                elif [ ${AML_WITH_DEP} = false ]; then
                    echo -e "${GREEN}Build without depedencies${NO_COLOUR}"
                else
                    echo -e "${GREEN}Build without depedencies${NO_COLOUR}"
                    shift 1; exit 0
                fi
                shift 1;
                ;;
            --build_mode=*)
                AML_BUILD_MODE="${1#*=}";
                echo -e "${GREEN}Build mode is: $AML_BUILD_MODE${NO_COLOUR}"
                shift 1;
                ;;
            --logging=*)
                AML_LOGGING="${1#*=}";
                echo -e "${GREEN}Logging option is: $AML_LOGGING${NO_COLOUR}"
                shift 1;
                ;;
            -c)
                clean
                shift 1; exit 0
                ;;
            -h)
                usage; exit 0
                ;;
            --help)
                usage; exit 0
                ;;
            -*)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
            *)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
        esac
    done
}

process_cmd_args "$@"
echo -e "Building AML DataModel library("${AML_TARGET_ARCH}").."
build
echo -e "Done building AML DataModel library("${AML_TARGET_ARCH}")"

exit 0
