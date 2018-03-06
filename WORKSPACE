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
