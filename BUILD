# 注意这个是 cc_library
cc_library(
	name = "test_comm",
	deps = [
		"//proto:test_proto",
		"//utility:utility",
	],
	visibility = ["//visibility:public"],
)

# 注意这个是 cc_binary
cc_binary(
	name = "test",
	srcs = ["test.cpp"],
	deps = [":test_comm"],
	copts = ["-std=c++14"],
	visibility = ["//visibility:public"],
)
