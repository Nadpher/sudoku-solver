#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace nadpher
{

template <typename T>
class ResourceManager
{
public:
	static std::shared_ptr<T> get(const std::string& key);

private:
	static std::unordered_map<std::string, std::shared_ptr<T>> resources_;
};

}

