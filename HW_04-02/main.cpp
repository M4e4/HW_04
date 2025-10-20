#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "my_list.h"

TEST_CASE("Complex usage scenario of List", "[List][Scenario]") 
{
    List list;

    REQUIRE(list.Empty());
    REQUIRE(list.Size() == 0);

    list.PushBack(10); // 10
    list.PushBack(20); // 10, 20

    list.PushFront(5); // 5, 10, 20
    list.PushFront(1); // 1, 5, 10, 20

    REQUIRE_FALSE(list.Empty());
    REQUIRE(list.Size() == 4);

    int front = list.PopFront(); // 5, 10, 20
    REQUIRE(front == 1);
    REQUIRE(list.Size() == 3);

    int back = list.PopBack(); // 5, 10
    REQUIRE(back == 20);
    REQUIRE(list.Size() == 2);

    list.PushBack(30); // 5, 10, 30
    list.PushFront(0); // 0, 5, 10, 30
    REQUIRE(list.Size() == 4);

    list.PopFront();
    list.PopFront();
    list.PopBack();
    list.PopBack();

    REQUIRE(list.Empty());
    REQUIRE(list.Size() == 0);
}

TEST_CASE("Pop from empty list throws", "[List][Exceptions]")
{
    List list;

    REQUIRE(list.Empty());
    REQUIRE(list.Size() == 0);

    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
}