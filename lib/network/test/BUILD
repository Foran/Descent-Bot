cc_test(
  name='packet_tests',
  size='small',
  srcs=[
    'packetUnitTests.cc',
  ],
  deps=[
    '@gtest//:gtest_main',
    '//lib/network:libpackets',
  ],
  copts=[
    '-Iexternal/gtest/include',
  ],
)
