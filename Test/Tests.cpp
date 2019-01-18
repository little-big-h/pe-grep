#define CATCH_CONFIG_MAIN
#include "Implementation.hpp"
#include <catch2/catch.hpp>
using namespace std;


TEST_CASE("Simple filter test") {
  auto lines = make_unique<Input>();
  lines->push_back("not line");
  for(size_t i = 0; i < 4; i++)
    lines->push_back("line " + to_string(i));
  auto s = Select(move(lines), [](string s) -> bool { return s.compare(0, 4, "line") == 0; });
  REQUIRE(s.size() == 4);
}


TEST_CASE("Simple prefix filter test") {
  auto lines = make_unique<Input>();
  lines->push_back("not line");
  for(size_t i = 0; i < 4; i++)
    lines->push_back("line " + to_string(i));
  int const line = *(int*)"line";
  auto s = SelectWithPrefixInt(move(lines), line);
  REQUIRE(s.size() == 4);
}
