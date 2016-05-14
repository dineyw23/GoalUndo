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
 *  addOperations without any goal to test if operation if copied 
 *  to goal correctly.   
 *
 */

TEST(GoalUndoTest, addNewOpOnlyWithoutGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Trial");
  goalUndoObj.addOperation("TrialOperation 2");
  EXPECT_EQ("Trial",goalUndoObj.getGoal());
  ASSERT_EQ("Trial TrialOperation 2",goalUndoObj.getOperations()); 
}

/*
 * Test to check if addOperation functions adds goal and 
 * operations properly.
 */

TEST(GoalUndoTest, addOpWithGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  EXPECT_EQ("Eat Healthy",goalUndoObj.getGoal());
  ASSERT_EQ("proteins carbs",goalUndoObj.getOperations());
}

/*
 * Add empty string to operations which should be copied to  
 * Goal.
 */

TEST(GoalUndoTest, addNewOpWithoutGoalEmpty)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("");
  ASSERT_EQ("",goalUndoObj.getGoal());
  ASSERT_EQ("",goalUndoObj.getOperations());
}

/*
 *  Add empty string to addOperation(newGoal,newOp) function.
 *  If both arg are empty.
 */

TEST(GoalUndoTest, addNewGoalandOpEmpty)
{
  GoalUndo goalUndoObj;
  std::string empty = "";
  goalUndoObj.addOperation(empty,empty);
  ASSERT_EQ(empty,goalUndoObj.getGoal());
  ASSERT_EQ(empty,goalUndoObj.getOperations());
  goalUndoObj.addOperation("only goal",empty);
  goalUndoObj.addOperation(empty,"only operation");
}

/* 
 * Test where first argument is empty and second is valid.
 */

TEST(GoalUndoTest,addEmptyGoalValidOp)
{
  GoalUndo goalUndoObj;
  std::string empty = "";
  goalUndoObj.addOperation("","Valid operation");
  ASSERT_EQ(empty,goalUndoObj.getGoal());
}

/*
 * Test where first argument is valid and second is empty.
 */

TEST(GoalUndoTest,addValidGoalEmptyOp)
{
  GoalUndo goalUndoObj;
  std::string empty = "";
  goalUndoObj.addOperation("Valid Goal",empty);
  ASSERT_EQ(empty,goalUndoObj.getGoal());
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
 *  Test for getOperations to return all names with spaces.
 *
 */

TEST(GoalUndoTest, getAllOpsFromRecentGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.addOperation("carbsPlus");
  ASSERT_EQ("proteins carbs carbsPlus",goalUndoObj.getOperations());
}

/*
 * Test for all operations to return nothing when no goals
 */

TEST(GoalUndoTest, getOpsEmptyString)
{
  GoalUndo goalUndoObj;
  ASSERT_EQ("",goalUndoObj.getOperations());
}

/*
 *  Test if getOperation returns all spaces, some spaces and top most only.
 */

TEST(GoalUndoTest,getAllSpacesInOperations)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation(" "," ");
  goalUndoObj.addOperation(" ");
  goalUndoObj.addOperation(" ");
  EXPECT_EQ("     ",goalUndoObj.getOperations());
  goalUndoObj.addOperation("GoalNew","NewOperation");
  ASSERT_EQ("NewOperation",goalUndoObj.getOperations());
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


