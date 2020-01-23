#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Operator {
public:
  virtual std::string const* getLine() = 0;
  virtual ~Operator(){};
};

// * Input

class Input : public Operator {
  std::vector<std::string> lines;
  size_t i{};

public:
  std::string const* getLine();
  void push_back(std::string line);
  size_t size() const { return lines.size(); }
  void reset() { i = 0; }
  std::vector<std::string> const& getLines() const { return lines; }
};

// * Select

class Select : public Operator {
  std::unique_ptr<Operator> child;
  std::function<bool(std::string)> predicate;

public:
  Select(std::unique_ptr<Operator>&& c, std::function<bool(std::string)> predicate)
      : child(move(c)), predicate(predicate){};
  std::string const* getLine();
  size_t size();

  std::unique_ptr<Operator> getChildWithOwnership() {
    auto result = move(child);
    child = nullptr;
    return result;
  }
};

class SelectWithPrefixInt : public Operator {
  std::unique_ptr<Operator> child;
  int predicate;

public:
  SelectWithPrefixInt(std::unique_ptr<Operator>&& c, int predicate)
      : child(move(c)), predicate(predicate){};
  std::string const* getLine();
  ;
  size_t size();

  std::unique_ptr<Operator> getChildWithOwnership() {
    auto result = move(child);
    child = nullptr;
    return result;
  }
};

class BulkSelectWithPrefixInt : public Operator {
  std::unique_ptr<Input> child;
  int predicate;

public:
  BulkSelectWithPrefixInt(std::unique_ptr<Input>&& c, int predicate)
      : child(move(c)), predicate(predicate){};
  std::string const* getLine();
  ;
  size_t size();

  std::unique_ptr<Operator> getChildWithOwnership() {
    auto result = move(child);
    child = nullptr;
    return result;
  }
};
