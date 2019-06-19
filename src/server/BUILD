load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cmake_external(
    name = "event",
    lib_source = "@com_github_libevent_libevent//:all",
    cache_entries = {
        "EVENT__DISABLE_OPENSSL": "on",
        "EVENT__DISABLE_REGRESS": "on",
        "EVENT__DISABLE_TESTS": "on",
        "EVENT__LIBRARY_TYPE": "STATIC",
        "CMAKE_BUILD_TYPE": "Release",
        # Disable ranlib because it is not handled by bazel, and therefore
        # doesn't respect custom toolchains such as the Android NDK,
        # see https://github.com/bazelbuild/rules_foreign_cc/issues/252
        "CMAKE_RANLIB": "",
    },
    static_libraries = ["libevent.a", "libevent_pthreads.a"],
)


cc_library(
    name = "server",
    srcs = glob(["*.cc", "init/*.cc", "manager/*.cc", "worker/*.cc"]),
    hdrs = glob(["include/*.h"]),
    copts = ["-Isrc/server/include"],
    visibility = ["//visibility:public"],
    deps = [":event"],
    alwayslink = 1,
)