load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def install_rules_foreign_cc_dependencies():
    http_archive(
        name = "rules_foreign_cc",
        sha256 = "980c1b74f5c18ea099889b0fb0479ee34b8a02845d3d302ecb16b15d73d624c8",
        strip_prefix = "rules_foreign_cc-a0dc109915cea85909bef586e2b2a9bbdc6c8ff5",
        urls = ["https://github.com/bazelbuild/rules_foreign_cc/archive/a0dc109915cea85909bef586e2b2a9bbdc6c8ff5.tar.gz"],
    )
