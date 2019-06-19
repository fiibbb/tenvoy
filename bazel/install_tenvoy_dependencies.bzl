load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

BUILD_ALL_CONTENT = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

def install_tenvoy_dependencies():
    _com_github_libevent_libevent()

def _com_github_libevent_libevent():
    http_archive(
        name = "com_github_libevent_libevent",
        build_file_content = BUILD_ALL_CONTENT,
        urls = ["https://github.com/libevent/libevent/archive/3b1864b625ec37c3051512845982f347f4cc5621.tar.gz"],
        strip_prefix = "libevent-3b1864b625ec37c3051512845982f347f4cc5621",
    )
    native.bind(
        name = "event",
    )
