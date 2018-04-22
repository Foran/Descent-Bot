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
  name = "libxml",
  srcs = [
    "xml.cc",
  ],
  hdrs = [
    "xml.h",
  ],
  deps = [
    "@org_xmlsoft_libxml2//:libxml2"
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
    ':libxml',
    '//src/lib/log:liblog',
    '//src/lib/log:liblog-raw',
    '//src/lib/log:liblog-file',
  ],
  copts = [
    '-I/usr/include/libxml2',
  ],
  visibility = ['//visibility:public'],
)
