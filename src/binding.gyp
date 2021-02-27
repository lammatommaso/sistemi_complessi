{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "cpp2/js_interface.cpp", "cpp2/car.cpp", "cpp2/city.cpp", "cpp2/simulator.cpp", "cpp2/road.cpp", "cpp2/node.cpp"],
      "include_dirs": ["cpp2"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}