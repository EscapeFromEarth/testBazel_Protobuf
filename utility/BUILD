cc_library(
    name = "utility_comm",
    hdrs = [
        "messagecontext.h",
        "singleton.h",
    ],
    linkopts = ["-lprotobuf"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "fillmessage",
    srcs = ["fillmessage.cpp"],
    hdrs = ["fillmessage.h"],
    visibility = ["//visibility:public"],
    deps = [":utility_comm"],
	copts = ["-std=c++17"],
)

cc_library(
    name = "messagetojson",
    srcs = ["messagetojson.cpp"],
    hdrs = ["messagetojson.h"],
    visibility = ["//visibility:public"],
    deps = [":utility_comm"],
	copts = ["-std=c++17"],
)

cc_library(
    name = "utility",
    visibility = ["//visibility:public"],
    deps = [
        ":fillmessage",
        ":messagetojson",
    ],
)
