cc_library(
  name = "libconfig",
  srcs = [
    "config.cc",
  ],
  hdrs = [
    "config.h",
  ],
  deps = [
    "//:xml",
    "//:log",
    "//:log-raw",
    "//:log-file",
  ],
  copts = [
    "-I/usr/include/libxml2",
  ],
  visibility = ["//visibility:public"],
)
