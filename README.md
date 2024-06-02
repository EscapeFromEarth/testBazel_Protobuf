# 测试 bazel + protobuf

效果如下：
```markdown
hello world!
Group
name: 111
num of person(s): 1
Person
name: njk
gender: MALE
id: 123456
num of phone(s): 1
Phone
model: honor
number: 666
name: "111"
person {
  name: "njk"
  gender: MALE
  id: "123456"
  phone {
    model: "honor"
    number: "666"
  }
}
```