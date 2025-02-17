# Description:
#   Boost C++ Library

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Boost Software License

exports_files(["LICENSE_1_0.txt"])

cc_library(
    name = "boost",
    srcs = glob([
        "boost/**/*.hpp",
    ]) + glob([
        "boost/predef/**/*.h",
    ]) + [
        "boost/predef.h",
        "libs/iostreams/src/gzip.cpp",
        "libs/iostreams/src/zlib.cpp",
        "libs/regex/src/c_regex_traits.cpp",
        "libs/regex/src/cpp_regex_traits.cpp",
        "libs/regex/src/cregex.cpp",
        "libs/regex/src/fileiter.cpp",
        "libs/regex/src/icu.cpp",
        "libs/regex/src/instances.cpp",
        "libs/regex/src/internals.hpp",
        "libs/regex/src/posix_api.cpp",
        "libs/regex/src/regex.cpp",
        "libs/regex/src/regex_debug.cpp",
        "libs/regex/src/regex_raw_buffer.cpp",
        "libs/regex/src/regex_traits_defaults.cpp",
        "libs/regex/src/static_mutex.cpp",
        "libs/regex/src/usinstances.cpp",
        "libs/regex/src/w32_regex_traits.cpp",
        "libs/regex/src/wc_regex_traits.cpp",
        "libs/regex/src/wide_posix_api.cpp",
        "libs/regex/src/winstances.cpp",
    ],
    includes = [
        ".",
    ],
    deps = [
        "@com_github_madler_zlib//:z",
    ],
)
