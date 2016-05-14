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

/*
 * Check if undoOperation doesn't do anything is goals stack is empty.
 */

TEST(GoalUndoTest,undoOperationsNoGoals)
{
  GoalUndo goalUndoObj;
  goalUndoObj.undoOperation();
  ASSERT_EQ("",goalUndoObj.getGoal());
}

/*  
 *  Test if undoOperation removes only the most recent operation.
 */

TEST(GoalUndoTest, removeMostRecentOperation)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.undoOperation(); //Most Imp 
  ASSERT_EQ("proteins",goalUndoObj.getOperations());
}

/*
 *  Test if undoOperation removes most recent operation
 *  along with the goal if it's the last one.
 */

TEST(GoalUndoTest,removeOperationAndGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.undoOperation(); //Most Imp 
  ASSERT_EQ("",goalUndoObj.getGoal());
  ASSERT_EQ("",goalUndoObj.getOperations());
}

/*
 *  Test if the undoOperation(Op) does nothing when there are no goals.
 */

TEST(GoalUndoTest, emptyCheckUndoOperation)
{
  GoalUndo goalUndoObj;
  goalUndoObj.undoOperation("something");
  ASSERT_EQ("",goalUndoObj.getGoal());
  ASSERT_EQ("",goalUndoObj.getOperations());
}

/*
 * Test if undoOperation(Op) removes only match and removes
 * goals as well if it's the only operation. 
 *
 */

TEST(GoalUndoTest, removeOnlyMatch)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.undoOperation("proteins");
  EXPECT_EQ("",goalUndoObj.getGoal());
}

/*
 *  Check if undoOperation(Op) removes operation properly.
 *
 */

TEST(GoalUndoTest, removeMatch)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.undoOperation("proteins");//Imp Test
  ASSERT_EQ("Eat Healthy",goalUndoObj.getGoal());
}

/*
 * Test to check if duplicate operations are not removed.
 *
 */

TEST(GoalUndoTest, removeOnlyFirstMatch)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.addOperation("proteins");
  goalUndoObj.addOperation("proteins");
  goalUndoObj.undoOperation("proteins");//Imp Test
  ASSERT_EQ("proteins carbs proteins",goalUndoObj.getOperations());
}
 
/*
 * If no match is found, undoOperation(Op) does nothing.
 *
 */

TEST(GoalUndoTest, undoOperationNoMatch)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.undoOperation("No Match");//Imp Test
  ASSERT_EQ("proteins carbs",goalUndoObj.getOperations());
}

/*
 * Duplicate goals and duplicate operations
 *
 */

TEST(GoalUndoTest, removeOpFromSingleGoal)
{
  GoalUndo goalUndoObj;
  goalUndoObj.addOperation("Eat Healthy","proteins");
  goalUndoObj.addOperation("Eat Healthy New","proteins");
  goalUndoObj.addOperation("carbs");
  goalUndoObj.undoOperation("proteins");
  ASSERT_EQ("carbs",goalUndoObj.getOperations());
  goalUndoObj.undoOperation(); //Removes Eat Healthy New
  goalUndoObj.undoOperation(); //Remove Everything
  ASSERT_EQ("",goalUndoObj.getGoal());
}

