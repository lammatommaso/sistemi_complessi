cmd_Release/obj.target/addon/cpp2/simulator.o := g++ -o Release/obj.target/addon/cpp2/simulator.o ../cpp2/simulator.cpp '-DNODE_GYP_MODULE_NAME=addon' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-DV8_DEPRECATION_WARNINGS' '-DV8_IMMINENT_DEPRECATION_WARNINGS' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-D__STDC_FORMAT_MACROS' '-DOPENSSL_NO_PINSHARED' '-DOPENSSL_THREADS' '-DBUILDING_NODE_EXTENSION' -I/home/simone/.cache/node-gyp/12.16.2/include/node -I/home/simone/.cache/node-gyp/12.16.2/src -I/home/simone/.cache/node-gyp/12.16.2/deps/openssl/config -I/home/simone/.cache/node-gyp/12.16.2/deps/openssl/openssl/include -I/home/simone/.cache/node-gyp/12.16.2/deps/uv/include -I/home/simone/.cache/node-gyp/12.16.2/deps/zlib -I/home/simone/.cache/node-gyp/12.16.2/deps/v8/include -I../cpp2  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer -fno-rtti -std=gnu++1y -MMD -MF ./Release/.deps/Release/obj.target/addon/cpp2/simulator.o.d.raw   -c
Release/obj.target/addon/cpp2/simulator.o: ../cpp2/simulator.cpp \
 ../cpp2/simulator.h ../cpp2/car.h ../cpp2/city.h ../cpp2/road.h \
 ../cpp2/node.h ../cpp2/numpy_parser.h
../cpp2/simulator.cpp:
../cpp2/simulator.h:
../cpp2/car.h:
../cpp2/city.h:
../cpp2/road.h:
../cpp2/node.h:
../cpp2/numpy_parser.h: