proto_library(
  name='libconfig_proto',
  srcs=[
    'config.proto',
  ],
)

cc_proto_library(
  name='libconfig_cc_proto',
  deps=[
    ':libconfig_proto',
  ],
)

cc_library(
  name = 'libconfig',
  srcs = [
    'config.cc',
  ],
  hdrs = [
    'config.h',
  ],
  deps = [
    ':libconfig_cc_proto',
    '//lib/context:libcomponent',
    '//lib/context:libcontext',
    '//src/lib/log:liblog',
    '//src/lib/log:liblog-raw',
    '//src/lib/log:liblog-file',
  ],
  visibility = ['//visibility:public'],
)
