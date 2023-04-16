#include "list.h"
#include <gtest.h>
#include <forward_list>
#include <stdexcept>
class Fixture : public ::testing::Test
{
public:
	List<int> List_;
	List<int>::iterator center;

	std::forward_list<int> control;

	std::forward_list<int>::iterator center_control;
	const int REMOVE_EL = 5;

    Fixture() :List_(List<int>()), control(std::forward_list<int>())
	{
		List_.push_front(5);
		List_.push_front(15);
		List_.push_front(25);
		List_.push_front(5);

		center = List_.begin();

		List_.push_front(35);
		List_.push_front(85);
		List_.push_front(5);

		control.push_front(5);
		control.push_front(15);
		control.push_front(25);
		control.push_front(5);

		center_control = control.begin();

		control.push_front(35);
		control.push_front(85);
		control.push_front(5);

		//5 85 35 5 15 25 5
	}

	bool compare_with_control(List<int> lt)
	{
		while (!control.empty() && !lt.empty())
		{
			int x = lt.front(); lt.pop_front();
			int y = control.front(); control.pop_front();
			if (x != y)
				return false;
		}

		return control.empty() && lt.empty();
	}
};


TEST(List, can_create)
{
	ASSERT_NO_THROW(List<int> List_);
}

TEST_F(Fixture, can_clear)
{
	ASSERT_NO_THROW(List_.clear());
}


TEST(List, can_clear_empty_List)
{
	List<int> List_;
	ASSERT_NO_THROW(List_.clear());
}



TEST_F(Fixture, can_assign)
{
	List<int> tmp;
	ASSERT_NO_THROW(tmp = List_);
}

TEST_F(Fixture, size_of_assigned_List_equl_size_of_init_List)
{
	List<int> tmp;
	tmp = List_;
	EXPECT_EQ(List_.size(), tmp.size());
	
}

TEST_F(Fixture, can_assign_himself)
{
	List<int> List_;
	ASSERT_NO_THROW(List_ = List_);
}

TEST(List, can_check_empty)
{
	List<int> List_;
	EXPECT_EQ(List_.empty(), true);
}

TEST_F(Fixture, can_create_copy)
{
	ASSERT_NO_THROW(List<int> List2(List_));
}

TEST(List, can_push_front)
{
	List<int> List_;
	ASSERT_NO_THROW(List_.push_front(5));
}

TEST_F(Fixture, coorect_push_front)
{
	List_.push_front(999);
	control.push_front(999);
	EXPECT_TRUE(compare_with_control(List_));
}
TEST(List, can_push_back)
{
	List<int> List_;
	ASSERT_NO_THROW(List_.push_front(5));
}

TEST(List, can_insert_after_first)
{
	List<int> List_;
	List_.push_front(5);
	ASSERT_NO_THROW(List_.insert_after(List_.begin(), 78));
}

TEST_F(Fixture, correct_front)
{
	EXPECT_EQ(List_.front(), control.front());
}

TEST(List, correct_back)
{
	List<int> List;
	List.push_front(50);
	List.push_front(100);
	EXPECT_EQ(List.front(), 100);
}

TEST_F(Fixture, can_erase_after_first)
{
	ASSERT_NO_THROW(List_.erase_after(center));
}

TEST_F(Fixture, can_reduce_size)
{
	ASSERT_NO_THROW(List_.resize(1));
}

TEST_F(Fixture, can_increase_size)
{
	ASSERT_NO_THROW(List_.resize(50));
}

TEST_F(Fixture, coorect_reduce_size)
{
	List_.resize(2);
	control.resize(2);
	EXPECT_TRUE(compare_with_control(List_));
}

TEST_F(Fixture, coorect_increase_size)
{
	List_.resize(50);
	control.resize(50);
	EXPECT_TRUE(compare_with_control(List_));
}

TEST_F(Fixture, can_remove)
{
	ASSERT_NO_THROW(List_.remove(REMOVE_EL));
}

TEST_F(Fixture, correct_remove)
{
	List_.remove(REMOVE_EL);
	control.remove(REMOVE_EL);
	EXPECT_TRUE(compare_with_control(List_));
}

TEST_F(Fixture, correct_reverse)
{
	List_.reverse();
	control.reverse();
	EXPECT_TRUE(compare_with_control(List_));
}

TEST_F(Fixture, move_constructor_no_throw)
{
	EXPECT_NO_THROW(auto tmp = std::move(List_));
}

TEST_F(Fixture, move_assigment_no_throw)
{
	List<int> tmp;
	tmp.push_front(52);
	EXPECT_NO_THROW(tmp = std::move(List_));
}

TEST_F(Fixture, correct_move_constructor)
{
	EXPECT_NO_THROW(compare_with_control(std::move(List_)));
}

TEST_F(Fixture, correct_move_assigmaent)
{
	List<int> tmp;
	tmp = std::move(List_);
	EXPECT_NO_THROW(compare_with_control(tmp));
}


TEST_F(Fixture, can_erase_after)
{
	ASSERT_NO_THROW(List_.erase_after(center));
}

TEST_F(Fixture, can_insert_after)
{
	ASSERT_NO_THROW(List_.insert_after(center, 6));
}

TEST_F(Fixture, correct_erase_after)
{
	List_.erase_after(center);
	control.erase_after(center_control);
	EXPECT_TRUE(compare_with_control(List_));

}

TEST_F(Fixture, correct_insert_after)
{

	List_.insert_after(center, 6);
	control.insert_after(center_control, 6);
	EXPECT_TRUE(compare_with_control(List_));
}

TEST(List, can_pop_front)
{
	List<int> List;
	List.push_front(5);
	ASSERT_NO_THROW(List.pop_front());
}

TEST_F(Fixture, coorect_pop_front)
{
	List_.pop_front();
	control.pop_front();
	EXPECT_TRUE(compare_with_control(List_));
}

