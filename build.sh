#!/bin/bash
export FW_VERSION="v1.0.0"

ninja -C obj/debug -t clean
cmake -B obj/debug . -G Ninja -DTYPE=debug -DCMAKE_TOOLCHAIN_FILE=sdk/toolchain/toolchain.cmake
ninja -C obj/debug
