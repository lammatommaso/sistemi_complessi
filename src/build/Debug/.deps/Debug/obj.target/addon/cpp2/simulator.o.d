cmd_Debug/obj.target/addon/cpp2/simulator.o := g++ -o Debug/obj.target/addon/cpp2/simulator.o ../cpp2/simulator.cpp '-DNODE_GYP_MODULE_NAME=addon' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' '-DDEBUG' '-D_DEBUG' '-DV8_ENABLE_CHECKS' -I/home/simone/.cache/node-gyp/10.19.0/include/node -I/home/simone/.cache/node-gyp/10.19.0/src -I/home/simone/.cache/node-gyp/10.19.0/deps/openssl/config -I/home/simone/.cache/node-gyp/10.19.0/deps/openssl/openssl/include -I/home/simone/.cache/node-gyp/10.19.0/deps/uv/include -I/home/simone/.cache/node-gyp/10.19.0/deps/zlib -I/home/simone/.cache/node-gyp/10.19.0/deps/v8/include -I../cpp2  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -fPIC -g -O0 -fno-rtti -std=gnu++1y -MMD -MF ./Debug/.deps/Debug/obj.target/addon/cpp2/simulator.o.d.raw   -c
Debug/obj.target/addon/cpp2/simulator.o: ../cpp2/simulator.cpp \
 ../cpp2/simulator.h ../cpp2/car.h ../cpp2/city.h ../cpp2/road.h \
 ../cpp2/node.h ../cpp2/numpy_parser.h
../cpp2/simulator.cpp:
../cpp2/simulator.h:
../cpp2/car.h:
../cpp2/city.h:
../cpp2/road.h:
../cpp2/node.h:
../cpp2/numpy_parser.h: