cmd_Release/addon.node := c++ -bundle -undefined dynamic_lookup -Wl,-no_pie -Wl,-search_paths_first -mmacosx-version-min=10.13 -arch x86_64 -L./Release -stdlib=libc++  -o Release/addon.node Release/obj.target/addon/cpp2/js_interface.o Release/obj.target/addon/cpp2/car.o Release/obj.target/addon/cpp2/city.o Release/obj.target/addon/cpp2/simulator.o Release/obj.target/addon/cpp2/road.o Release/obj.target/addon/cpp2/node.o Release/obj.target/addon/cpp2/numpy_parser.o 
