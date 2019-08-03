proto_library(
  name='libudp_packet_type_proto',
  srcs=[
    'udp_packet_type.proto',
  ],
)

cc_proto_library(
  name='libnetwork_cc_proto',
  deps=[
    ':libudp_packet_type_proto',
  ],
  visibility=[
    '//lib/network:__pkg__',
  ],
)
