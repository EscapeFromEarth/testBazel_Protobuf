- [bazel + protobuf 小练习](#bazel--protobuf-小练习)
		- [特别声明！！](#特别声明)
		- [什么是反射](#什么是反射)
		- [作用](#作用)
		- [环境](#环境)
		- [编译运行](#编译运行)
		- [效果](#效果)

# bazel + protobuf 小练习

### <font color="red">特别声明！！</font>

github 上的 [`EscapeFromEarth`](https://github.com/EscapeFromEarth)、[`SoHard2Name`](https://github.com/SoHard2Name)、[`abcpony`](https://github.com/abcpony)，都是我本人（`NJK`），就是偶尔换来换去而已。项目是本人独立完成的。

作者 `QQ`：`2490273063`

### 什么是反射

> 以下是个人不严谨但好懂的理解。

`Descriptor` 就是单纯描述一个 `message` 或者一个 `message` 的一个 `field` 的**形状规则**的，它定义的是一个类型（而非具体对象）。而反射就是根据**形状规则**以及具体 `message` 对象去获取到此对象的某个具体信息，当你这样理解了之后，就会发现这些用到的函数都挺好理解的。

举个简单的例子：有一条信息记录的是根据触摸一个物品的质感来确定它的材质的一些**规则**（描述符），而有一个具体的物品（一个对象），还有一个执行判断的人（反射）；那么人（反射）有一个功能（方法）就是通过*了解规则和触摸物品*（传入描述符和对象）从而得出物品是什么材质的（对象特征）。这样总能理解了吧，这个时候你再随便看几个相关的函数就会豁然开朗了。

### 作用

> 目的无他，就是练习一下 `bazel` 和反射的应用（我也没想到会写这么久的）。

以下两个功能，算是非常基础的了。

1. 根据一个传入的 `message` 对象的类型，从头到尾、由表及里地提示用户输入对应字段的内容，给这个对象设置值。
2. 根据一个传入的 `message` 对象，生成它对应的 `json` 格式的表示，能够自动避开那些没有置值的字段。

上面所说的 `message` 对象可以是任意只含有 `uint32`、`enum`、`string`、`bytes` 类型的字段的对象，支持 `repeated` 以及消息的多层嵌套。

### 环境

- linux ubuntu 20.04
- bazel 6.4.0
- libprotoc 3.19.4

### 编译运行

先在项目根目录下运行 `protoc ./proto/*.proto --cpp_out=./`。这个“--cpp_out”虽然这样写，但其实生成文件是输出到 proto 文件夹下。

毕竟生成文件就是要拿来用的，自己手动生成得了，而且直接让 `bazel` 帮忙生成很麻烦，我试了好多方法也都不行（如果有佬可以教我用 `bazel` 随时欢迎 + 感谢）。

然后再执行 `bazel build //:test`。

最后 `cd bazel-bin; ./test` 就可以运行了。

### 效果
```markdown
hello world!
------------------------------------
Group
name: 菜鸡组合
num of person(s): 2
Person
name: 张三
gender: MALE
age: 18
id: 123456
num of phone(s): 0
Person
name: 李四
gender: FEMALE
age: 20
id: 654321
num of phone(s): 2
Phone
model: 荣耀
number: 888
Phone
model: 小米
number: 666
------------------------------------
{ "name": "菜鸡组合", "person": [ { "name": "张三", "gender": "MALE", "age": 18, "id": "123456" }, { "name": "李四", "gender": "FEMALE", "age": 20, "id": "654321", "phone": [ { "model": "荣耀", "number": "888" }, { "model": "小米", "number": "666" } ] } ] }
------------------------------------
name: "\350\217\234\351\270\241\347\273\204\345\220\210"
person {
  name: "\345\274\240\344\270\211"
  gender: MALE
  age: 18
  id: "123456"
}
person {
  name: "\346\235\216\345\233\233"
  gender: FEMALE
  age: 20
  id: "654321"
  phone {
    model: "\350\215\243\350\200\200"
    number: "888"
  }
  phone {
    model: "\345\260\217\347\261\263"
    number: "666"
  }
}
```