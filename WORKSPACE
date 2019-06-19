workspace(name = "tenvoy")

# Install (download) and configure rules_foreign_cc
load("//bazel:install_rules_foreign_cc_dependencies.bzl", "install_rules_foreign_cc_dependencies")
install_rules_foreign_cc_dependencies()
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

load("//bazel:install_tenvoy_dependencies.bzl", "install_tenvoy_dependencies")
install_tenvoy_dependencies()
