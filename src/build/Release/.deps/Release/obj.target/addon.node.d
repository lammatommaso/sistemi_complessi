cmd_Release/obj.target/addon.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=addon.node -o Release/obj.target/addon.node -Wl,--start-group Release/obj.target/addon/cpp2/js_interface.o Release/obj.target/addon/cpp2/car.o Release/obj.target/addon/cpp2/city.o Release/obj.target/addon/cpp2/simulator.o Release/obj.target/addon/cpp2/road.o Release/obj.target/addon/cpp2/node.o -Wl,--end-group 
