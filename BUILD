cc_library(
  name = "level-data",
  srcs = [
    "mission.cpp",
    "missionmanager.cpp",
    "hog.cpp",
    "hogmanager.cpp",
    "file.cpp",
    "fstreamptr.cpp",
    "rdl.cpp",
  ],
  hdrs = [
    "mission.h",
    "missionmanager.h",
    "hog.h",
    "hogmanager.h",
    "file.h",
    "fstreamptr.h",
    "rdl.h",
  ],
  copts = [
    "-pedantic",
    "-I/usr/include/libxml2",
    "-std=c++11",
  ],
  deps = [
    ":log",
    ":math",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "log",
  srcs = [
    "log.cpp",
    "log_driver.cpp",
  ],
  hdrs = [
    "log.h",
    "log_driver.h",
  ],
  copts = [
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "xml",
  srcs = [
    "xml.cpp",
  ],
  hdrs = [
    "xml.h",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  linkopts = [
    "-lxml2",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "config",
  srcs = [
    "config.cpp",
  ],
  hdrs = [
    "config.h",
  ],
  deps = [
    ":xml",
    ":log",
    ":log-raw",
    ":log-file",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "connection",
  srcs = [
    "connection.cpp",
    "connectionmanager.cpp",
  ],
  hdrs = [
    "connection.h",
    "connectionmanager.h",
  ],
  deps = [
    ":network",
    ":log",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "network",
  srcs = [
    "network.cpp",
    "packets.cpp",
  ],
  hdrs = [
    "network.h",
    "packets.h",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "log-file",
  srcs = [
    "log_driver_file.cpp",
  ],
  hdrs = [
    "log_driver_file.h",
  ],
  deps = [
    ":log",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "log-raw",
  srcs = [
    "log_driver_raw.cpp",
  ],
  hdrs = [
    "log_driver_raw.h",
  ],
  deps = [
    ":log",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "math",
  srcs = [
    "math.cpp",
  ],
  hdrs = [
    "math.h",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "descent-bot",
  srcs = [
    "main.cpp",
  ],
  deps = [
    ":level-data",
    ":log",
    ":config",
    ":connection",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
)

cc_test(
  name = "test-hog",
  srcs = [
    "test_hog.cpp",
    "test_hog.h",
  ],
  deps = [
    "@gtest//:main",
    ":level-data",
  ],
  size = "small",
)