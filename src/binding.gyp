{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "cpp/js_interface.cpp", "cpp/main.cpp", "cpp/Macchina.cpp", "cpp/Citta.cpp", "cpp/Dio.cpp", "cpp/Strada.cpp"],
      "include_dirs": ["cpp"],
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