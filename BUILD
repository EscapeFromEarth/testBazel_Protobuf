# WORKSPACE 为空即可。
# 先运行 `protoc ./proto/*.proto --cpp_out=./`，这个“--cpp_out”虽然这样写，但其实是输出到 proto 文件夹下。
# 然后这边再执行 `bazel build :test`。
# 不用依赖外部环境，必编译成功。

# 注意这个是 cc_library
cc_library(
	name = "test_proto",
	srcs = glob(["proto/*.cc"]),
	hdrs = glob(["proto/*.h"]),
	visibility = ["//visibility:public"],
	linkopts = [
		"-lprotobuf",
	],
)

cc_library(
)

# 注意这个是 cc_binary
cc_binary(
	name = "test",
	srcs = [
		"test.cpp",
	],
	deps = [":test_proto"],
	copts = ["-std=c++17"],
	visibility = ["//visibility:public"],
)
