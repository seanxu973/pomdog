# Examples:
# gyp build/unit_tests.gyp --depth=. -f xcode --generator-output=./build.xcodefiles/
{
  'includes': ['common.gypi'],
  'make_global_settings': [
    ['CXX','/usr/bin/clang++'],
    ['LINK','/usr/bin/clang++'],
  ],
  'target_defaults': {
    'include_dirs': [
      '../include',
      '../third_party/boost/include',
    ],
    'configurations': {
      'Debug': {
        'msvs_settings': {
          'VCLinkerTool': {
            'GenerateDebugInformation': 'true', # /DEBUG
          },
        },
      }, # Debug
    },
    'msvs_settings':{
      'VCCLCompilerTool': {
        'WarningLevel': '4',   # /W4
        'WarnAsError': 'true', # /WX
      },
    },
    'xcode_settings': {
      'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
      'MACOSX_DEPLOYMENT_TARGET': '10.8', # OS X Deployment Target: 10.8
    },
  },
  'targets': [
    {
      'target_name': 'unit_tests',
      'product_name': 'unit_tests',
      'type': 'executable',
      'mac_bundle': 1,
      'dependencies': [
        'pomdog.gyp:pomdog-core',
      ],
      'include_dirs': [
        '../include',
        '../third_party/iutest/include'
      ],
      'sources': [
        '../test/FrameworkTest/main.cpp',
        '../test/FrameworkTest/Math/ColorTest.cpp',
        '../test/FrameworkTest/Math/Coordinate2DTest.cpp',
        '../test/FrameworkTest/Math/Vector2Test.cpp',
        '../test/FrameworkTest/Math/Vector3Test.cpp',
        '../test/FrameworkTest/Math/Vector4Test.cpp',
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': ['-std=c++11','-stdlib=libc++'],
        'OTHER_LDFLAGS': ['-stdlib=libc++'],
      },
      'conditions': [
        ['OS == "mac"', {
          'defines': ['IUTEST_OS_LINUX'] # badcode
        }], # OS == "mac"
      ],
    },
  ],# "targets"
}
