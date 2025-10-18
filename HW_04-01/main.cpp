#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("List::Empty() reflects current state", "[List][Empty]")
{
    List list;

    SECTION("List is empty after default construction")
    {
        REQUIRE(list.Empty());
    }

    SECTION("List is not empty after PushFront")
    {
        list.PushFront(1);
        REQUIRE_FALSE(list.Empty());
    }

    SECTION("List is not empty after PushBack")
    {
        list.PushBack(1);
        REQUIRE_FALSE(list.Empty());
    }

    SECTION("List becomes empty after Push and PopFront")
    {
        list.PushFront(1);
        list.PopFront();
        REQUIRE(list.Empty());
    }

    SECTION("List becomes empty after Push and PopBack") 
    {
        list.PushBack(1);
        list.PopBack();
        REQUIRE(list.Empty());
    }
}

TEST_CASE("List::Size returns correct number of elements", "[List][Size]") 
{
    List list;

    SECTION("Size is 0 after construction") 
    {
        REQUIRE(list.Size() == 0);
    }

    SECTION("Size is 1 after PushFront")
    {
        list.PushFront(1);
        REQUIRE(list.Size() == 1);
    }

    SECTION("Size is 1 after PushBack") 
    {
        list.PushBack(2);
        REQUIRE(list.Size() == 1);
    }

    SECTION("Size is 2 after PushFront and PushBack") 
    {
        list.PushFront(1);
        list.PushBack(2);
        REQUIRE(list.Size() == 2);
    }

    SECTION("Size is 0 after Push and Pop") 
    {
        list.PushBack(1);
        list.PopBack();
        REQUIRE(list.Size() == 0);
    }
}

TEST_CASE("List::Clear removes all elements", "[List][Clear]") 
{
    List list;

    SECTION("Clear on empty list does not crash") 
    {
        list.Clear();
        REQUIRE(list.Empty());
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear after PushFront")
    {
        list.PushFront(1);
        list.Clear();
        REQUIRE(list.Empty());
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear after multiple PushBack")
    {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        list.Clear();
        REQUIRE(list.Empty());
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear twice in a row")
    {
        list.PushFront(1);
        list.Clear();
        list.Clear();
        REQUIRE(list.Empty());
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear after mixed PushFront/PushBack") 
    {
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(3);
        list.Clear();
        REQUIRE(list.Empty());
        REQUIRE(list.Size() == 0);
    }
}