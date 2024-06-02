#pragma once

// 注意这种情况只适用于完全不需要传参创建并且不需要手动进行特殊的初始化的情况。
// 注意这个东西不能放在几个成员声明的中间，否则它之后的几个声明固定是 private，
// 最好直接放类名下一行，再开始写别的。
#define Singleton(ClassName) \
public: \
	static ClassName* GetSingleton() { \
		static ClassName Singleton; \
		return &Singleton; \
	} \
private: \
	ClassName() = default; \
	~ClassName() = default; \
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;
