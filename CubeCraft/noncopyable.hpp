#pragma once
class noncopyable {
public:
	noncopyable() = default;
	noncopyable(noncopyable&) = delete;
	noncopyable(noncopyable&&) = delete;
};
