#include <gtest/gtest.h>
#include "Level.h"

TEST(Level, LevelLoading1) {
	Level level(1);

	EXPECT_NE(level.getChipie(), nullptr); //chipie non nulle
	EXPECT_EQ(level.getNbBras(), 9); //test du nombre de bras
}
TEST(Level, LevelLoading2) {
	Level level(2);

	EXPECT_NE(level.getChipie(), nullptr); //chipie non nulle
	EXPECT_EQ(level.getNbBras(), 9); //test du nombre de bras
}
TEST(Level, LevelLoading3) {
	Level level(3);

	EXPECT_NE(level.getChipie(), nullptr); //chipie non nulle
	EXPECT_EQ(level.getNbBras(), 9); //test du nombre de bras
}
TEST(Level, LevelLoading4) {
	Level level(4);

	EXPECT_NE(level.getChipie(), nullptr); //chipie non nulle
	EXPECT_EQ(level.getNbBras(), 9); //test du nombre de bras
}
TEST(Level, LevelLoading5) {
	Level level(5);

	EXPECT_NE(level.getChipie(), nullptr); //chipie non nulle
	EXPECT_EQ(level.getNbBras(), 9); //test du nombre de bras
}


TEST(LevelPerformanceTest, Level1) {
	const int levelNumber = 1;
	const int numIterations = 1000;
	double totalTime = 0.0;

	for (int i = 0; i < numIterations; i++) {
		auto startTime = std::chrono::steady_clock::now();

		Level level(levelNumber);

		auto endTime = std::chrono::steady_clock::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		totalTime += elapsedTime.count();
	}
	double averageTime = totalTime / numIterations;

	const double maxLoadingTime = 1.0;
	EXPECT_LT(averageTime, maxLoadingTime);
}

TEST(LevelPerformanceTest, Level2) {
	const int levelNumber = 2;
	const int numIterations = 1000;
	double totalTime = 0.0;

	for (int i = 0; i < numIterations; i++) {
		auto startTime = std::chrono::steady_clock::now();

		Level level(levelNumber);

		auto endTime = std::chrono::steady_clock::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		totalTime += elapsedTime.count();
	}
	double averageTime = totalTime / numIterations;

	const double maxLoadingTime = 1.0;
	EXPECT_LT(averageTime, maxLoadingTime);
}

TEST(LevelPerformanceTest, Level3) {
	const int levelNumber = 3;
	const int numIterations = 1000;
	double totalTime = 0.0;

	for (int i = 0; i < numIterations; i++) {
		auto startTime = std::chrono::steady_clock::now();

		Level level(levelNumber);

		auto endTime = std::chrono::steady_clock::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		totalTime += elapsedTime.count();
	}
	double averageTime = totalTime / numIterations;

	const double maxLoadingTime = 1.0;
	EXPECT_LT(averageTime, maxLoadingTime);
}

TEST(LevelPerformanceTest, Level4) {
	const int levelNumber = 4;
	const int numIterations = 1000;
	double totalTime = 0.0;

	for (int i = 0; i < numIterations; i++) {
		auto startTime = std::chrono::steady_clock::now();

		Level level(levelNumber);

		auto endTime = std::chrono::steady_clock::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		totalTime += elapsedTime.count();
	}
	double averageTime = totalTime / numIterations;

	const double maxLoadingTime = 1.0;
	EXPECT_LT(averageTime, maxLoadingTime);
}

TEST(LevelPerformanceTest, Level5) {
	const int levelNumber = 5;
	const int numIterations = 1000;
	double totalTime = 0.0;

	for (int i = 0; i < numIterations; i++) {
		auto startTime = std::chrono::steady_clock::now();

		Level level(levelNumber);

		auto endTime = std::chrono::steady_clock::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		totalTime += elapsedTime.count();
	}
	double averageTime = totalTime / numIterations;

	const double maxLoadingTime = 1.0;
	EXPECT_LT(averageTime, maxLoadingTime);
}