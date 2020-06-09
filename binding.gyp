{
    "targets": [
        {
        "target_name": "AbletonLinkAddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "./src/webAudioLink.cpp",
            "./src/index.cpp"
        ],
        "include_dirs": [
            './link/include',
            './link/modules/asio-standalone/asio/include',
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        'conditions': [
            ['OS=="mac"', {
                'defines': ['LINK_PLATFORM_MACOSX=1'],
                'defines!': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
                'xcode_settings': {
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					'CLANG_CXX_LIBRARY': 'libc++',
					'CLANG_CXX_LANGUAGE_STANDARD': 'c++11'
				}
            }],
            ['OS=="linux"', {
                'defines': ['LINK_PLATFORM_LINUX=1']
            }],
            ['OS=="win"', {
                'defines': ['LINK_PLATFORM_WINDOWS=1', '_WIN32_WINNT=0x0501'],
                'defines!': ['_HAS_EXCEPTIONS=0'],
            }],
        ]
        }
    ]
}