workspace(
  name = "descentbot",
)

new_http_archive(
  name = "gtest",
  url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
  sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
  build_file = "thirdparty/gtest.BUILD",
  strip_prefix = "googletest-release-1.8.0",
)

new_http_archive(
    name = "cpplint_archive",
    url = "https://pypi.python.org/packages/95/42/27a16ef7fc609aba82bec923e2d29a1fa163bc95a267eaf1acc780e949fc/cpplint-1.3.0.tar.gz#md5=4809419eb86d4d9930ab6c0ce248c0cc",
    sha256 = "6876139c3944c6dc84cc9095b6c4be3c5397b534b0c00230ba59c4b893936719",
    build_file = "thirdparty/cpplint.BUILD",
    strip_prefix = "cpplint-1.3.0"
)

# This com_google_protobuf repository is required for proto_library rule.
# It provides the protocol compiler binary (i.e., protoc).
http_archive(
    name = "com_google_protobuf",
    strip_prefix = "protobuf-master",
    urls = ["https://github.com/google/protobuf/archive/master.zip"],
)
load("@com_google_protobuf//:protobuf.bzl", "check_protobuf_required_bazel_version")
check_protobuf_required_bazel_version()

# This com_google_protobuf_cc repository is required for cc_proto_library
# rule. It provides protobuf C++ runtime. Note that it actually is the same
# repo as com_google_protobuf but has to be given a different name as
# required by bazel.
http_archive(
    name = "com_google_protobuf_cc",
    strip_prefix = "protobuf-master",
    urls = ["https://github.com/google/protobuf/archive/master.zip"],
)

# Similar to com_google_protobuf_cc but for Java (i.e., java_proto_library).
http_archive(
    name = "com_google_protobuf_java",
    strip_prefix = "protobuf-master",
    urls = ["https://github.com/google/protobuf/archive/master.zip"],
)

new_http_archive(
    name = "org_xmlsoft_libxml2",
    sha256 = "f63c5e7d30362ed28b38bfa1ac6313f9a80230720b7fb6c80575eeab3ff5900c",
    strip_prefix = "libxml2-2.9.7",
    url = "http://xmlsoft.org/sources/libxml2-2.9.7.tar.gz",
    build_file = "thirdparty/libxml2.BUILD"
)

new_http_archive(
    name = "com_googleapis_zlib",
    build_file = "thirdparty/zlib.BUILD",
    sha256 = "36658cb768a54c1d4dec43c3116c27ed893e88b02ecfcb44f2166f9c0b7f2a0d",
    strip_prefix = "zlib-1.2.8",
    url = "http://bazel-mirror.storage.googleapis.com/zlib.net/zlib-1.2.8.tar.gz",
)