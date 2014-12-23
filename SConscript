# -*- mode: python -*-

Import("env")

env.Library(target='mongohello',
            source=['src/hello/hello.cpp',
                    'src/hello/hello_options.cpp'
                    ],
            LIBDEPS_DEPENDENTS=['$BUILD_DIR/mongo/${PROGPREFIX}mongod${PROGSUFFIX}'],
            SYSLIBDEPS=env.get('HELLO_SYSLIBDEPS', []))


# env.CppUnitTest('hello_test',
#                 ['src/hello/hello_test.cpp'],
#                 LIBDEPS=['mongohello',
#                          '$BUILD_DIR/mongo/bson',
#                          '$BUILD_DIR/mongo/network',
#                          ])

