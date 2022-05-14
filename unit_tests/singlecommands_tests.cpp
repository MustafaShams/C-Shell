#include "gtest/gtest.h"
#include "../src/singlecommand.hpp"

#include <string>
#include <vector>

TEST(SingleCommandExecute, ExecuteCommand){
    std::vector<std::string> test_vec1;
    std::string test_input1 = "ls";
    test_vec1.push_back(test_input1);

    SingleCommand* test_command1 = new SingleCommand(test_vec1, "command");

    EXPECT_EQ(test_command1->get_cmd().size(), 1);
    EXPECT_EQ(test_command1->get_cmd().at(0), "ls");
    EXPECT_EQ(test_command1->execute(), true);


    std::vector<std::string> test_vec2;
    std::string test_input2[] = {"echo", "testing echo"};
    test_vec2.push_back(test_input2[0]);
    test_vec2.push_back(test_input2[1]);

    SingleCommand* test_command2 = new SingleCommand(test_vec2, "command");

    EXPECT_EQ(test_command2->get_cmd().size(), 2);
    EXPECT_EQ(test_command2->get_cmd().at(0), "echo");
    EXPECT_EQ(test_command2->get_cmd().at(1), "testing echo");
    testing::internal::CaptureStdout();
    EXPECT_EQ(test_command2->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "testing echo\n");
}

TEST(SingleCommandExecute, FailCommand){
    std::vector<std::string> test_vec;
    std::string test_input = "ech";
    test_vec.push_back(test_input);

    SingleCommand* test_command = new SingleCommand(test_vec, "command");

    EXPECT_EQ(test_command->get_cmd().size(), 1);
    EXPECT_EQ(test_command->get_cmd().at(0), "ech");
    testing::internal::CaptureStderr();
    EXPECT_EQ(test_command->execute(), false);
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(test_output, "Execvp failed: No such file or directory\n");
}