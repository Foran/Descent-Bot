workspace(
  name='descentbot',
)

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

http_archive(
  name='gtest',
  urls=[
    'https://github.com/google/googletest/archive/release-1.8.0.zip',
  ],
  sha256='f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf',
  build_file='@//thirdparty:gtest.BUILD',
  strip_prefix='googletest-release-1.8.0',
)

http_archive(
  name='cpplint_archive',
  urls=[
    'https://pypi.python.org/packages/95/42/27a16ef7fc609aba82bec923e2d29a1fa163bc95a267eaf1acc780e949fc/cpplint-1.3.0.tar.gz#md5=4809419eb86d4d9930ab6c0ce248c0cc',
  ],
  sha256='6876139c3944c6dc84cc9095b6c4be3c5397b534b0c00230ba59c4b893936719',
  build_file='@//thirdparty:cpplint.BUILD',
  strip_prefix='cpplint-1.3.0',
)

http_archive(
  name='com_github_gflags_gflags',
  urls=[
    'https://github.com/gflags/gflags/archive/v2.2.0.zip',
  ],
  sha256='99f9e8b63ea53e4b23f0fd0f68a6f1e397d5512be36716c17cc75966a90f0d57',
  strip_prefix='gflags-2.2.0',
)

bind(
  name='gflags',
  actual='@com_github_gflags_gflags//:gflags',
)

bind(
  name='gflags_nothreads',
  actual='@com_github_gflags_gflags//:gflags_nothreads',
)

http_archive(
  name='build_stack_rules_proto',
  urls=[
    'https://github.com/stackb/rules_proto/archive/2f4e4f62a3d7a43654d69533faa0652e1c4f5082.tar.gz',
  ],
  sha256='ad2bd886ed2ca0f5891ee58415bf875839787ae44414e178f468685a8b5d0bb1',
  strip_prefix='rules_proto-2f4e4f62a3d7a43654d69533faa0652e1c4f5082',
)

load('@build_stack_rules_proto//cpp:deps.bzl', 'cpp_proto_library', 'cpp_grpc_library')

cpp_proto_library()

cpp_grpc_library()

http_archive(
  name='com_googleapis_zlib',
  build_file='@//thirdparty:zlib.BUILD',
  sha256='36658cb768a54c1d4dec43c3116c27ed893e88b02ecfcb44f2166f9c0b7f2a0d',
  strip_prefix='zlib-1.2.8',
  urls=[
    'http://bazel-mirror.storage.googleapis.com/zlib.net/zlib-1.2.8.tar.gz',
  ],
)
