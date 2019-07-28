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
  visibility=[
    '//lib/config:__pkg__',
  ],
)
