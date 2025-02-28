#include <string_view>
using namespace std::literals::string_view_literals;
constexpr auto inputdata = R"(Monkey 0:
  Starting items: 71, 56, 50, 73
  Operation: new = old * 11
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 7

Monkey 1:
  Starting items: 70, 89, 82
  Operation: new = old + 1
  Test: divisible by 7
    If true: throw to monkey 3
    If false: throw to monkey 6

Monkey 2:
  Starting items: 52, 95
  Operation: new = old * old
  Test: divisible by 3
    If true: throw to monkey 5
    If false: throw to monkey 4

Monkey 3:
  Starting items: 94, 64, 69, 87, 70
  Operation: new = old + 2
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 6

Monkey 4:
  Starting items: 98, 72, 98, 53, 97, 51
  Operation: new = old + 6
  Test: divisible by 5
    If true: throw to monkey 0
    If false: throw to monkey 5

Monkey 5:
  Starting items: 79
  Operation: new = old + 7
  Test: divisible by 2
    If true: throw to monkey 7
    If false: throw to monkey 0

Monkey 6:
  Starting items: 77, 55, 63, 93, 66, 90, 88, 71
  Operation: new = old * 7
  Test: divisible by 11
    If true: throw to monkey 2
    If false: throw to monkey 4

Monkey 7:
  Starting items: 54, 97, 87, 70, 59, 82, 59
  Operation: new = old + 8
  Test: divisible by 17
    If true: throw to monkey 1
    If false: throw to monkey 3
)"sv;
