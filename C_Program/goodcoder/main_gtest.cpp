#include <stdio.h>
#include "gtest/gtest.h"
#include "parser.h"
#include "user.h"

using vocabulary_parse::Parser;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class Testparser : public ::testing::Test {
    public:
        Testparser() {};

        virtual ~Testparser() {};

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }

    public:
        Parser *_object;
};

TEST_F(Testparser, parse_int_data) {

    _object = new(std::nothrow) Parser();
    ASSERT_TRUE(_object);

    char str[] = "1\t2\t345\n";
    int a = 0;
    int b = 0;
    int c = 0;

    _object->parse_line(str, 3);
    _object->parse_column(0, &a);
    _object->parse_column(1, &b);
    _object->parse_column(2, &c);
    EXPECT_EQ(1, a);
    EXPECT_EQ(2, b);
    EXPECT_EQ(345, c);

    delete _object;
    _object = NULL;
}

TEST_F(Testparser, parse_float_data) {

    _object = new(std::nothrow) Parser();
    ASSERT_TRUE(_object);

    char str[] = "1.1\t2.3\t3.45\n";
    float a = 0;
    float b = 0;
    float c = 0;

    _object->parse_line(str, 3);
    _object->parse_column(0, &a);
    _object->parse_column(1, &b);
    _object->parse_column(2, &c);

    EXPECT_FLOAT_EQ(1.1, a);
    EXPECT_FLOAT_EQ(2.3, b);
    EXPECT_FLOAT_EQ(3.45, c);

    delete _object;
    _object = NULL;
}

TEST_F(Testparser, parse_char_data) {

    _object = new(std::nothrow) Parser();
    ASSERT_TRUE(_object);

    char str[] = "a1b\tc2d\te345f\n";
    char a[8] = {0};
    char b[8] = {0};
    char c[8] = {0};

    _object->parse_line(str, 3);
    _object->parse_column(0, a);
    _object->parse_column(1, b);
    _object->parse_column(2, c);

    EXPECT_STREQ("a1b", a);
    EXPECT_STREQ("c2d", b);
    EXPECT_STREQ("e345f", c);

    delete _object;
    _object = NULL;
}

TEST_F(Testparser, parse_user1_data) {

    _object = new(std::nothrow) Parser();
    ASSERT_TRUE(_object);

    char str[] = "16,18.9,pass";
    MyStruct1 u_test = {0};

    _object->parse_line(str, 1);
    _object->parse_column(0, &u_test);

    EXPECT_EQ(16, u_test.a);
    EXPECT_FLOAT_EQ(18.9, u_test.b);
    EXPECT_STREQ("pass", u_test.c);

    delete _object;
    _object = NULL;
}

TEST_F(Testparser, parse_user2_data) {

    _object = new(std::nothrow) Parser();
    ASSERT_TRUE(_object);

    char str[] = "5:11,22,33,18.9,88";
    MyStruct2 u_test = {0};

    _object->parse_line(str, 1);
    _object->parse_column(0, &u_test);

    EXPECT_EQ(5, u_test.num);
    EXPECT_EQ(11, u_test.array[0]);
    EXPECT_EQ(22, u_test.array[1]);
    EXPECT_EQ(33, u_test.array[2]);
    EXPECT_EQ(18, u_test.array[3]);
    EXPECT_EQ(88, u_test.array[4]);

    delete _object;
    _object = NULL;
}

