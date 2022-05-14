#include "gtest/gtest.h"
#include "../src/commands.hpp"
#include "../src/testcommand.hpp"

TEST(TestClass, DefaultFlag) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "fake/directory/test.txt"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 2);
    EXPECT_EQ(test_cmd->flag, "e");
    EXPECT_EQ(test_cmd->path, "fake/directory/test.txt");
}

TEST(TestClass, DirFlag) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-d", "fake/directory/test.txt"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "d");
    EXPECT_EQ(test_cmd->path, "fake/directory/test.txt");
}

TEST(TestClass, FileFlag) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-f", "fake/directory/test.txt"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "f");
    EXPECT_EQ(test_cmd->path, "fake/directory/test.txt");
}

TEST(TestClass, Execute) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-e", "rshell"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "e");
    EXPECT_EQ(test_cmd->path, "rshell");
    testing::internal::CaptureStdout();
    EXPECT_EQ(test_cmd->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "(True)\n");
}

TEST(TestClass, FileExecute) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-f", "rshell"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "f");
    EXPECT_EQ(test_cmd->path, "rshell");
    testing::internal::CaptureStdout();
    EXPECT_EQ(test_cmd->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "(True)\n");
}

TEST(TestClass, DirExecute) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-d", "integration_tests"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "d");
    EXPECT_EQ(test_cmd->path, "integration_tests");
    testing::internal::CaptureStdout();
    EXPECT_EQ(test_cmd->execute(), true);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "(True)\n");
}

TEST(TestClass, FailExecute) {
    std::vector<std::string> path;
    std::string inputs[] = {"test", "-d", "rshell"};

    for (auto &el : inputs) {
        path.push_back(el);
    }

    TestCommand* test_cmd = new TestCommand(path, "test");
    EXPECT_EQ(test_cmd->arguments.size(), 3);
    EXPECT_EQ(test_cmd->flag, "d");
    EXPECT_EQ(test_cmd->path, "rshell");
    testing::internal::CaptureStdout();
    EXPECT_EQ(test_cmd->execute(), false);
    std::string test_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(test_output, "(False)\n");
}