#include "gtest/gtest.h"
#include "../src/parser.hpp"
#include "../src/parser.cpp"
#include "../src/singlecommand.cpp"

TEST(ParseInput, ParserSingleCommand) {
    std::string inputs = "ls;";
    Parser* testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 2);
    EXPECT_EQ(testParser->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser->getTokenVec().at(1), ";");

}

TEST(ParseInput, ParserMultipleCommands) {
    std::string inputs = "ls && echo hey";
    Parser* testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 4);
    EXPECT_EQ(testParser->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser->getTokenVec().at(1), "&&");
    EXPECT_EQ(testParser->getTokenVec().at(2), "echo");
    EXPECT_EQ(testParser->getTokenVec().at(3), "hey");

    std::string inputs2 = "ls || echo test";
    Parser* testParser2 = new Parser(inputs2);
    testParser2->parse_input();
    EXPECT_EQ(testParser2->getTokenVec().size(), 4);
    EXPECT_EQ(testParser2->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser2->getTokenVec().at(1), "||");
    EXPECT_EQ(testParser2->getTokenVec().at(2), "echo");
    EXPECT_EQ(testParser2->getTokenVec().at(3), "test");

    std::string inputs3 = "ls || echo test && mkdir tested;";
    Parser* testParser3 = new Parser(inputs3);
    testParser3->parse_input();
    EXPECT_EQ(testParser3->getTokenVec().size(), 8);
    EXPECT_EQ(testParser3->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser3->getTokenVec().at(1), "||");
    EXPECT_EQ(testParser3->getTokenVec().at(2), "echo");
    EXPECT_EQ(testParser3->getTokenVec().at(3), "test");
    EXPECT_EQ(testParser3->getTokenVec().at(4), "&&");
    EXPECT_EQ(testParser3->getTokenVec().at(5), "mkdir");
    EXPECT_EQ(testParser3->getTokenVec().at(6), "tested");
    EXPECT_EQ(testParser3->getTokenVec().at(7), ";");
}

TEST(ParseInput, ParserQuotes) {
    std::string inputs = "ls; echo \"hello && goodbye\"";
    Parser* testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 4);
    EXPECT_EQ(testParser->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser->getTokenVec().at(1), ";");
    EXPECT_EQ(testParser->getTokenVec().at(2), "echo");
    EXPECT_EQ(testParser->getTokenVec().at(3), "hello && goodbye");

    std::string inputs2 = "\"hello && goodbye\" \"hello & goodbye | hey ; more words\"";
    Parser* testParser2 = new Parser(inputs2);
    testParser2->parse_input();
    EXPECT_EQ(testParser2->getTokenVec().at(1)
             ,"hello & goodbye | hey ; more words");
}

TEST(ParseInput, PrecedenceCommands) {
    std::string inputs = "ls && (echo this is a comment)";
    Parser *testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 9);
    EXPECT_EQ(testParser->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser->getTokenVec().at(1), "&&");
    EXPECT_EQ(testParser->getTokenVec().at(2), "(");
    EXPECT_EQ(testParser->getTokenVec().at(3), "echo");
    EXPECT_EQ(testParser->getTokenVec().at(4), "this");
    EXPECT_EQ(testParser->getTokenVec().at(5), "is");
    EXPECT_EQ(testParser->getTokenVec().at(6), "a");
    EXPECT_EQ(testParser->getTokenVec().at(7), "comment");
    EXPECT_EQ(testParser->getTokenVec().at(8), ")");

    std::string input2 = "(echo A && echo B) || (echo C && echo D)";
    Parser *testParse2 = new Parser(input2);
    testParse2->parse_input();
    EXPECT_EQ(testParse2->getTokenVec().size(), 15);
}

TEST(ParseInput, ParserBrackets) {
    std::string inputs = "[this is a test]";
    Parser* testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 5);
    EXPECT_EQ(testParser->getTokenVec().at(0), "test");
    EXPECT_EQ(testParser->getTokenVec().at(1), "this");
    EXPECT_EQ(testParser->getTokenVec().at(2), "is");
    EXPECT_EQ(testParser->getTokenVec().at(3), "a");
    EXPECT_EQ(testParser->getTokenVec().at(4), "test");
}

TEST(ParseInput, BracketsException) {
    std::string inputs = "[this is a test";
    Parser* testParser = new Parser(inputs);
    testing::internal::CaptureStderr();
    try {
        testParser->parse_input();
    } catch (const std::invalid_argument& ia){
        ASSERT_STREQ("Missing closing bracket.", ia.what());
    }
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(test_output, "Invalid argument: Missing closing bracket.\n");
}

TEST(ParseInput, CommentedCommands) {
    std::string inputs = "ls &&  echo #this is a comment";
    Parser *testParser = new Parser(inputs);
    testParser->parse_input();
    EXPECT_EQ(testParser->getTokenVec().size(), 3);
    EXPECT_EQ(testParser->getTokenVec().at(0), "ls");
    EXPECT_EQ(testParser->getTokenVec().at(1), "&&");
    EXPECT_EQ(testParser->getTokenVec().at(2), "echo");
}

TEST(ParseInput, ConnectorException) {
    std::string inputs = "ls &";
    Parser* testParser = new Parser(inputs);
    testing::internal::CaptureStderr();
    try {
        testParser->parse_input();
    } catch (const std::invalid_argument& ia){
        ASSERT_STREQ("Incorrect connector syntax.", ia.what());
    }
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(test_output,
             "Invalid argument: Incorrect connector syntax.\n");
}

TEST(ParseInput, QuotesException) {
    std::string inputs = "\"ls &";
    Parser* testParser = new Parser(inputs);

    testing::internal::CaptureStderr();
    try {
        testParser->parse_input();
    } catch (const std::invalid_argument& ia){
        ASSERT_STREQ("Missing closing quote.", ia.what());
    }
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(test_output, "Invalid argument: Missing closing quote.\n");
}

TEST(ParseInput, ParenthesisException) {
    std::string inputs = "(()";
    Parser* testParser = new Parser(inputs);
    testing::internal::CaptureStderr();
    try {
        testParser->parse_input();
    } catch (const std::invalid_argument& ia){
        ASSERT_STREQ("Invalid parenthesis syntax.", ia.what());
    }
    std::string test_output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(test_output,
            "Invalid argument: Invalid parenthesis syntax.\n");
}