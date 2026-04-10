#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_stub) {
    ASSERT_TRUE(true);
}

// * DEFAULT CONSTRUCTOR *

TEST(test_default_ctor) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

// * DESTRUCTOR *

// no tests

// * COPY CONSTRUCTOR *

TEST(test_copy_ctor_correct_values) {
    List<int> original;
    original.push_back(837);
    original.push_back(-42);
    original.push_back(1903);
    List<int> copy = original;
    ASSERT_EQUAL(copy.front(), 837);
    ASSERT_EQUAL(copy.back(), 1903);
    ASSERT_EQUAL(copy.size(), 3);
}

TEST(test_copy_ctor_independence) {
    List<int> original;
    original.push_back(512);
    original.push_back(-7);
    List<int> copy = original;
    copy.push_back(9999);
    ASSERT_EQUAL(original.size(), 2);
    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_EQUAL(original.back(), -7);
}

TEST(test_copy_ctor_empty) {
    List<int> original;
    List<int> copy = original;
    ASSERT_TRUE(copy.empty());
    ASSERT_EQUAL(copy.size(), 0);
    ASSERT_TRUE(copy.begin() == copy.end());
}

// * ASSIGNMENT OPERATOR *

TEST(test_assignment_correct_values) {
    List<int> original;
    original.push_back(-881);
    original.push_back(0);
    original.push_back(77432);
    List<int> assigned;
    assigned.push_back(1);
    assigned = original;
    ASSERT_EQUAL(assigned.front(), -881);
    ASSERT_EQUAL(assigned.back(), 77432);
    ASSERT_EQUAL(assigned.size(), 3);
}

TEST(test_assignment_independence) {
    List<int> original;
    original.push_back(404);
    original.push_back(-303);
    List<int> assigned;
    assigned = original;
    assigned.push_back(202);
    ASSERT_EQUAL(original.size(), 2);
    ASSERT_EQUAL(assigned.size(), 3);
    ASSERT_EQUAL(original.back(), -303);
}

TEST(test_assignment_self) {
    List<int> list;
    list.push_back(6174);
    list.push_back(-5);
    list.push_back(28);
    List<int> &ref = list;
    list = ref;
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 6174);
    ASSERT_EQUAL(list.back(), 28);
}

// * EMPTY *

TEST(test_empty_default) {
    List<int> list;
    ASSERT_TRUE(list.empty());
}

TEST(test_empty_after_push_and_pop) {
    List<int> list;
    list.push_back(-9183);
    ASSERT_FALSE(list.empty());
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

// * SIZE *

TEST(test_size_grows_and_shrinks) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(1729);
    ASSERT_EQUAL(list.size(), 1);
    list.push_back(-6561);
    ASSERT_EQUAL(list.size(), 2);
    list.pop_front();
    ASSERT_EQUAL(list.size(), 1);
    list.pop_front();
    ASSERT_EQUAL(list.size(), 0);
}

// * FRONT AND BACK *

TEST(test_front_and_back_single_element) {
    List<int> list;
    list.push_back(-31415);
    ASSERT_EQUAL(list.front(), -31415);
    ASSERT_EQUAL(list.back(), -31415);
}

TEST(test_front_and_back_multiple_elements) {
    List<int> list;
    list.push_back(8675);
    list.push_back(309);
    list.push_back(-11235);
    ASSERT_EQUAL(list.front(), 8675);
    ASSERT_EQUAL(list.back(), -11235);
}

// * PUSH FRONT AND PUSH BACK *

TEST(test_push_back_order) {
    List<int> list;
    list.push_back(1111);
    list.push_back(-2222);
    list.push_back(3333);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 1111); ++it;
    ASSERT_EQUAL(*it, -2222); ++it;
    ASSERT_EQUAL(*it, 3333);
}

TEST(test_push_front_order) {
    List<int> list;
    list.push_front(-7777);
    list.push_front(5050);
    list.push_front(-1313);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, -1313); ++it;
    ASSERT_EQUAL(*it, 5050); ++it;
    ASSERT_EQUAL(*it, -7777);
}

TEST(test_push_front_and_back_interleaved) {
    List<int> list;
    list.push_back(4444);
    list.push_front(-9090);
    list.push_back(1234);
    list.push_front(-5678);
    ASSERT_EQUAL(list.front(), -5678);
    ASSERT_EQUAL(list.back(), 1234);
    ASSERT_EQUAL(list.size(), 4);
}

// * POP FRONT AND POP BACK *

TEST(test_pop_front_removes_head) {
    List<int> list;
    list.push_back(2048);
    list.push_back(-4096);
    list.push_back(8192);
    list.pop_front();
    ASSERT_EQUAL(list.front(), -4096);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_pop_back_removes_tail) {
    List<int> list;
    list.push_back(-999);
    list.push_back(1001);
    list.push_back(-1003);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 1001);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_pop_single_element_to_empty) {
    List<int> list;
    list.push_back(65536);
    list.pop_front();
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin() == list.end());
}

// * CLEAR *

TEST(test_clear_empties_list) {
    List<int> list;
    list.push_back(-12345);
    list.push_back(67890);
    list.push_back(-11111);
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_clear_already_empty) {
    List<int> list;
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

// * ITERATOR DEFAULT CONSTRUCTOR *

TEST(test_iterator_default_ctor_equality) {
    List<int>::Iterator first;
    List<int>::Iterator second;
    ASSERT_TRUE(first == second);
}

TEST(test_iterator_default_ctor_not_equal_to_list_iterator) {
    List<int> list;
    list.push_back(-55555);
    List<int>::Iterator default_iterator;
    ASSERT_TRUE(default_iterator != list.begin());
    ASSERT_TRUE(default_iterator != list.end());
}

// * OPERATOR* *

TEST(test_dereference_at_begin) {
    List<int> list;
    list.push_back(314159);
    ASSERT_EQUAL(*list.begin(), 314159);
}

TEST(test_dereference_after_increment) {
    List<int> list;
    list.push_back(-27182);
    list.push_back(99991);
    List<int>::Iterator it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 99991);
}

// * OPERATOR++ *

TEST(test_prefix_increment) {
    List<int> list;
    list.push_back(-161803);
    list.push_back(271828);
    list.push_back(-141421);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, -161803);
    ++it;
    ASSERT_EQUAL(*it, 271828);
    ++it;
    ASSERT_EQUAL(*it, -141421);
    ++it;
    ASSERT_TRUE(it == list.end());
}

TEST(test_postfix_increment_returns_old_position) {
    List<int> list;
    list.push_back(17321);
    list.push_back(-49923);
    List<int>::Iterator it = list.begin();
    List<int>::Iterator old = it++;
    ASSERT_EQUAL(*old, 17321);
    ASSERT_EQUAL(*it, -49923);
}

// * OPERATOR== AND OPERATOR!= *

TEST(test_equality_same_position) {
    List<int> list;
    list.push_back(80808);
    List<int>::Iterator first = list.begin();
    List<int>::Iterator second = list.begin();
    ASSERT_TRUE(first == second);
    ++first;
    ASSERT_TRUE(first != second);
}

TEST(test_equality_end_iterators) {
    List<int> list;
    list.push_back(-32767);
    ASSERT_TRUE(list.end() == list.end());
}

// * BEGIN AND END *

TEST(test_begin_end_empty) {
    List<int> list;
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_begin_points_to_first_element) {
    List<int> list;
    list.push_back(-19999);
    list.push_back(20001);
    ASSERT_EQUAL(*list.begin(), -19999);
}

TEST(test_decrement_end_reaches_last) {
    List<int> list;
    list.push_back(55555);
    list.push_back(-66666);
    List<int>::Iterator it = list.end();
    --it;
    ASSERT_EQUAL(*it, -66666);
}

// * ERASE *

TEST(test_erase_only_element) {
    List<int> list;
    list.push_back(-777777);
    list.erase(list.begin());
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_erase_head) {
    List<int> list;
    list.push_back(13579);
    list.push_back(-24680);
    list.push_back(11223);
    list.erase(list.begin());
    ASSERT_EQUAL(list.front(), -24680);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_erase_tail) {
    List<int> list;
    list.push_back(-99887);
    list.push_back(66554);
    list.push_back(-33221);
    List<int>::Iterator it = list.end();
    --it;
    list.erase(it);
    ASSERT_EQUAL(list.back(), 66554);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_erase_middle) {
    List<int> list;
    list.push_back(10203);
    list.push_back(-40506);
    list.push_back(70809);
    List<int>::Iterator it = list.begin();
    ++it;
    list.erase(it);
    it = list.begin();
    ASSERT_EQUAL(*it, 10203); ++it;
    ASSERT_EQUAL(*it, 70809);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_erase_returns_next_iterator) {
    List<int> list;
    list.push_back(-11111);
    list.push_back(22222);
    list.push_back(-33333);
    List<int>::Iterator next = list.erase(list.begin());
    ASSERT_EQUAL(*next, 22222);
}

// * INSERT *

TEST(test_insert_at_begin) {
    List<int> list;
    list.push_back(-54321);
    list.push_back(98765);
    list.insert(list.begin(), 11111);
    ASSERT_EQUAL(list.front(), 11111);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_insert_at_end) {
    List<int> list;
    list.push_back(19283);
    list.push_back(-74651);
    list.insert(list.end(), 55544);
    ASSERT_EQUAL(list.back(), 55544);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_insert_in_middle) {
    List<int> list;
    list.push_back(-88123);
    list.push_back(44561);
    List<int>::Iterator it = list.begin();
    ++it;
    list.insert(it, -99999);
    it = list.begin();
    ASSERT_EQUAL(*it, -88123); ++it;
    ASSERT_EQUAL(*it, -99999); ++it;
    ASSERT_EQUAL(*it, 44561);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_insert_into_empty_list) {
    List<int> list;
    list.insert(list.end(), -76543);
    ASSERT_EQUAL(list.front(), -76543);
    ASSERT_EQUAL(list.back(), -76543);
    ASSERT_EQUAL(list.size(), 1);
}

TEST(test_insert_returns_iterator_to_new_element) {
    List<int> list;
    list.push_back(30001);
    list.push_back(-60002);
    List<int>::Iterator it = list.begin();
    ++it;
    List<int>::Iterator inserted = list.insert(it, 45678);
    ASSERT_EQUAL(*inserted, 45678);
}

TEST_MAIN()