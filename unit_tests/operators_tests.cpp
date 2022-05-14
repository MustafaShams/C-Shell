#include "gtest/gtest.h"
#include "../src/andconnector.hpp"
#include "../src/commands.hpp"
#include "../src/singlecommand.hpp"
#include "../src/orconnector.hpp"
#include <string>
#include <vector>

TEST(Operators, AndExecute) {
    std::string test_input[] = {"echo", "testing output"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Commands* single_test = new SingleCommand(test_vec1, "command");
    AndConnector* and_test = new AndConnector(single_test, "and");
    EXPECT_EQ(and_test->cmd_type, "and");
    testing::internal::CaptureStdout();
    EXPECT_EQ(and_test->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "testing output\n");

}

TEST(Operators, AndFail) {
    std::string test_input[] = {"ech", "-a"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Commands* single_test = new SingleCommand(test_vec1, "command");
    AndConnector* and_test = new AndConnector(single_test, "and");
    EXPECT_EQ(and_test->cmd_type, "and");
    testing::internal::CaptureStderr();
    EXPECT_EQ(and_test->execute(), false);
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ("Execvp failed: No such file or directory\n", test_output);


}

TEST(Operators, OrExecute) {
    std::string test_input[] = {"echo", "testing output"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Commands* single_test = new SingleCommand(test_vec1, "command");
    OrConnector* or_test = new OrConnector(single_test, "or");
    EXPECT_EQ(or_test->cmd_type, "or");
    testing::internal::CaptureStdout();
    EXPECT_EQ(or_test->execute(), false);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("testing output\n", test_output);

}

TEST(Operators, OrFail) {
    std::string test_input[] = {"ech", "-a"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
    test_vec1.push_back(el);
    }

    Commands* single_test = new SingleCommand(test_vec1, "command");
    OrConnector* or_test = new OrConnector(single_test, "or");
    EXPECT_EQ(or_test->cmd_type, "or");
    testing::internal::CaptureStderr();
    EXPECT_EQ(or_test->execute(), true);
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ("Execvp failed: No such file or directory\n", test_output);
}

TEST(Operators, OperatorsExecute) {
    std::string test_input[] = {"echo", "test1", "&&", "echo", "test2"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Operators* ops_test = new Operators(test_vec1);

    testing::internal::CaptureStdout();
    EXPECT_EQ(ops_test->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("test1\ntest2\n", test_output);

}

TEST(Operators, FindParenthesis) {
    std::string test_input[] = {"(", "test1", "echo", ")"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Operators* ops_test = new Operators(test_vec1);

    EXPECT_EQ(ops_test->arguments.size(), 4);

    std::vector<int> expected_indices;
    expected_indices.push_back(0);
    expected_indices.push_back(3);

    EXPECT_EQ(ops_test->findParenthesis(), expected_indices);
}

TEST(Operators, initializePrecedence) {
    std::string test_input[] = {"(", "test1", "&&", "(", "echo", ")", ")"};
    std::vector<std::string> test_vec1;

    for (auto el : test_input) {
        test_vec1.push_back(el);
    }

    Operators* ops_test = new Operators(test_vec1);
    std::vector<int> expected_indices;
    expected_indices.push_back(0);
    expected_indices.push_back(6);

    EXPECT_EQ(ops_test->arguments.size(), 7);
    EXPECT_EQ(ops_test->findParenthesis(), expected_indices);

    std::vector<std::string> expected_output;
    expected_output.push_back("test1");
    expected_output.push_back("&&");
    expected_output.push_back("(");
    expected_output.push_back("echo");
    expected_output.push_back(")");

    EXPECT_EQ(ops_test->initializePrecedence(expected_indices),
            expected_output);
}
