#include "Implementation.hpp"

std::string const* Select::getLine() {
	for(auto next = child->getLine(); next; next = child->getLine()) {
		if(!next || predicate(*next))
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

std::string const* Input::getLine() {
	if(i >= lines.size())
		return {};
	return &lines[i++];
};

void Input::push_back(std::string line) { lines.push_back(line); }

std::string const* SelectWithPrefixInt::getLine() {
	int const line = *(int*)"line";
	for(auto next = child->getLine(); next; next = child->getLine()) {
		if(!next || *((int*)(*next).c_str()) == predicate)
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

std::string const* BulkSelectWithPrefixInt::getLine() {
	for(auto next = child->getLine(); next; next = child->getLine()) {
		if(*((int*)(*next).c_str()) == predicate)
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
