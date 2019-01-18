#include "Implementation.hpp"

std::optional<std::string> Select::getLine() {
	for(auto next = child->getLine(); next.has_value(); next = child->getLine()) {
		if(!next.has_value() || predicate(next.value()))
			return next;
	};
	return {};
};

size_t Select::size() {
	auto result = 0ul;
	while(getLine()) {
		result++;
	}
	return result;
}

std::optional<std::string> Input::getLine() {
	if(i >= lines.size())
		return {};
	return lines[i++];
};

void Input::push_back(std::string line) { lines.push_back(line); }

std::optional<std::string> SelectWithPrefixInt::getLine() {
	int const line = *(int*)"line";
	for(auto next = child->getLine(); next.has_value(); next = child->getLine()) {
		if(!next.has_value() || *((int*)next.value().c_str()) == predicate)
			return next;
	};
	return {};
};

size_t SelectWithPrefixInt::size() {
	auto result = 0ul;
	while(getLine()) {
		result++;
	}
	return result;
}

std::optional<std::string> BulkSelectWithPrefixInt::getLine() {
	for(auto next = child->getLine(); next.has_value(); next = child->getLine()) {
		if(*((int*)next.value().c_str()) == predicate)
			return next;
	};
	return {};
};

size_t BulkSelectWithPrefixInt::size() {
	auto result = 0ul;
	auto& lines = child->getLines();
	for(auto& it : lines) {
		if(*((int*)it.c_str()) == predicate)
			result++;
	}
	return result;
}
