#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_push_front) {
    List<int> list;
    list.push_front(10);
    ASSERT_EQUAL(list.front(), 10);
    list.push_front(20);
    ASSERT_EQUAL(list.front(), 20);
    ASSERT_EQUAL(list.back(), 10);
    list.push_front(30);
    ASSERT_EQUAL(list.front(), 30);
    ASSERT_EQUAL(list.back(), 10);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_push_back){
    List<int> list;
    list.push_back(10);
    ASSERT_EQUAL(list.back(), 10);
    list.push_back(20);
    ASSERT_EQUAL(list.back(), 20);
    ASSERT_EQUAL(list.front(), 10);
    list.push_front(30);
    ASSERT_EQUAL(list.back(), 30);
    ASSERT_EQUAL(list.front(), 10);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_pop_front_back){
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 20);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 20);
}

TEST(test_copies){
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    List<int> list2(list);
    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_EQUAL(list2.front(), 10);
    ASSERT_EQUAL(list2.back(), 30);
    list.pop_front();
    ASSERT_EQUAL(list2.size(), 3);
    List<int> list3;
    list3 = list;
    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_EQUAL(list2.front(), 10);
    ASSERT_EQUAL(list2.back(), 30);
}

TEST(test_iterators){
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 10);
    it = list.end();
    ASSERT_EQUAL(*it, 30);
    --it;
    ASSERT_EQUAL(*it, 20);
    ++it;
    ASSERT_EQUAL(*it, 30);
}

TEST(test_insert) {
    List<int> list;
    list.push_back(10);
    list.push_back(3);
    List<int>::Iterator it = list.begin();
    ++it;
    list.insert(it, 2);
    it = list.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(list.size(), 3);
}

TEST_MAIN()
