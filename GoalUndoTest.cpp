/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
 
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/*
 *  Test getGoal function to return empty string
 *  when there are no goals.
 */

TEST(GoalUndoTest, getEmptyGoal)
{
  std::string empty = "";
  GoalUndo goalUndoObj;
  ASSERT_EQ(empty,goalUndoObj.getGoal());
}

/*
 *  Test getGoal to check if it return proper latest goal.
 */

TEST(GoalUndoTest, getLatestGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("Sleep Well","10pm");
  ASSERT_NE("Eat Healthy",goalUndoObj.getGoal());
  ASSERT_EQ("Sleep Well",goalUndoObj.getGoal());
}

/*
 *  Test undoGoal to check if it undoes only the latest 
 *  goal and its operations.
 */

TEST(GoalUndoTest, undoLatestGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Sleep Well","10pm");
  goalUndoObj.addOperation("Eat Healthy","proteins");
  //Check if goal is added
  ASSERT_EQ("Eat Healthy",goalUndoObj.getGoal());
  goalUndoObj.undoGoal(); //Most imp
  ASSERT_NE("",goalUndoObj.getGoal());
  ASSERT_EQ("Sleep Well",goalUndoObj.getGoal());
}

/*  
 * Test undoGoal to check if it does nothing when called
 * on empty list.
 */

TEST(GoalUndoTest, undoEmptyGoalList)
{
  GoalUndo goalUndoObj;
  goalUndoObj.undoGoal();
  ASSERT_EQ("",goalUndoObj.getGoal());
}

