/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// ---------- test match function ----------
TEST(GuesserTest, correct_guess) {
	string secret = "my secret";
	Guesser g(secret);
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, one_incorrect_guess) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, two_incorrect_guesses) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, three_incorrect_guesses) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.match(secret), false);
}

TEST(GuesserTest, reset_guesses_after_correct) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match(secret);
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, remaining_not_above_3_after_correct) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.match(secret), false);
}

TEST(GuesserTest, locked_early) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("something totally wrong");
    ASSERT_EQ(g.match(secret), false);
}

TEST(GuesserTest, cant_be_above_32_chars) {
	string secret(33, 'a');
	Guesser g(secret);
    ASSERT_EQ(g.match(secret), false);
}

TEST(GuesserTest, truncate_secret_above_32_chars) {
	string secret(33, 'a');
	Guesser g(secret);
    ASSERT_EQ(g.match(string(32, 'a')), true);
}

TEST(GuesserTest, can_be_32_chars) {
	string secret(32, 'a');
	Guesser g(secret);
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, non_alpha) {
	string secret = "123456789?! /.,<>+++";
	Guesser g(secret);
    ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, non_alpha_validation) {
	string secret = "123456789?!/.,<>+++";
	Guesser g(secret);
	ASSERT_EQ(g.match("123456789?!/.,<>++++"), false);
}

TEST(GuesserTest, non_alpha_distance) {
	string secret = "123456789?!/.,<>+++";
	Guesser g(secret);
	g.match("123456789?!/.,<>++++");
	g.match("123456789?!/.,<>++++");
	ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, non_alpha_locking) {
	string secret = "123456789?!/.,<>+++";
	Guesser g(secret);
	g.match("123456789?!/.,<>+++++++++");
	ASSERT_EQ(g.match(secret), false);
}

TEST(GuesserTest, zero_length_secret) {
	string secret = "";
	Guesser g(secret);
	ASSERT_EQ(g.match(secret), true);
}

TEST(GuesserTest, zero_length_secret_incorrect_guess) {
	string secret = "";
	Guesser g(secret);
	ASSERT_EQ(g.match(" "), false);
}

TEST(GuesserTest, zero_length_secret_cant_lock) {
	string secret = "";
	Guesser g(secret);
	g.match("                    ");
	ASSERT_EQ(g.match(secret), true);
}

// ---------- test remaining function ----------
TEST(GuesserTest, correct_guess_resets_remaining) {
	string secret = "my secret";
	Guesser g(secret);
    ASSERT_EQ(g.remaining(), 3);
}

TEST(GuesserTest, incorrect_guess_decrements_remaining) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
    ASSERT_EQ(g.remaining(), 2);
}

TEST(GuesserTest, three_incorrect_guesses_drains_remaining) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.remaining(), 0);
}

TEST(GuesserTest, remaining_not_below_zero) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
    ASSERT_EQ(g.remaining(), 0);
}

TEST(GuesserTest, reset_remaining_after_correct) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match(secret);
    ASSERT_EQ(g.remaining(), 3);
}

TEST(GuesserTest, dont_reset_remaining_after_three_incorrect) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("my secret ");
	g.match("my secret ");
	g.match("my secret ");
	g.match(secret);
    ASSERT_EQ(g.remaining(), 0);
}

TEST(GuesserTest, locked_early_doesnt_affect_remaining) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("something totally wrong");
    ASSERT_EQ(g.remaining(), 2);
}

TEST(GuesserTest, remaining_decrements_after_locked) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("something totally wrong");
	g.match("my secret ");
    ASSERT_EQ(g.remaining(), 1);
}

TEST(GuesserTest, remaining_decrements_after_locked_even_if_correct) {
	string secret = "my secret";
	Guesser g(secret);
	g.match("something totally wrong");
	g.match("my secret");
    ASSERT_EQ(g.remaining(), 1);
}

