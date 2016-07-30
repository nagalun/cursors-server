{
  'targets': [
    {
      'target_name': 'uws',
      'sources': [
        'src/Extensions.cpp',
        'src/HTTPSocket.cpp',
        'src/Network.cpp',
        'src/Server.cpp',
        'src/UTF8.cpp',
        'src/WebSocket.cpp',
        'src/addon.cpp'
      ],
      'conditions': [
        ['OS=="linux"', {
          'cflags_cc': [ '-std=c++11' ],
          'cflags_cc!': [ '-fno-exceptions', '-std=gnu++0x', '-fno-rtti' ],
          'cflags!': [ '-fno-omit-frame-pointer' ],
          'ldflags!': [ '-rdynamic' ],
          'ldflags': [ '-s' ]
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
            'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
            'CLANG_CXX_LIBRARY': 'libc++',
            'GCC_GENERATE_DEBUGGING_SYMBOLS': 'NO',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'GCC_THREADSAFE_STATICS': 'YES',
            'GCC_OPTIMIZATION_LEVEL': '3',
            'GCC_ENABLE_CPP_RTTI': 'YES',
            'OTHER_CFLAGS!': [ '-fno-strict-aliasing' ]
          }
        }],
        ['OS=="win"', {
          'cflags_cc': [],
          'cflags_cc!': [],
          'defines': [
            'NODEJS_WINDOWS'
          ]
        }]
       ]
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': [ 'uws' ],
      'actions': [
        {
          'action_name': 'move_lib',
          'inputs': [
            '<@(PRODUCT_DIR)/uws.node'
          ],
          'outputs': [
            'uws'
          ],
          'action': ['cp', '<@(PRODUCT_DIR)/uws.node', 'uws_<!@(node -p process.platform)_<!@(node -p process.versions.modules).node']
        }
      ]
    }
  ]
}
