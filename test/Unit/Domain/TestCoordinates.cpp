#include <gtest/gtest.h>

#include <Domain/Coordinates.h>

TEST(TestCoordinates, nonEqualCoordinatesShouldReturnFalse) {
    Coordinates a = Coordinates(1, 1);
    Coordinates b = Coordinates(1, 0);

    Coordinates c = Coordinates(1, 1);
    Coordinates d = Coordinates(0, 1);

    ASSERT_FALSE(a.equal(b));
    ASSERT_FALSE(c.equal(d));
}

TEST(TestCoordinates, equalCoordinatesShouldReturnTrue) {
    Coordinates a = Coordinates(1, 1);
    Coordinates b = Coordinates(1, 1);

    ASSERT_TRUE(a.equal(b));
}

class CoordinateDistanceParameterizedTestFixture : public ::testing::TestWithParam<std::pair<std::pair<Coordinates, Coordinates>, double>> {

};

TEST_P(CoordinateDistanceParameterizedTestFixture, distanceAreCalculatedCorrectly) {
    std::pair<std::pair<Coordinates, Coordinates>, double> dataset = GetParam();

    ASSERT_NEAR(dataset.first.first.calculateDistance(dataset.first.second), dataset.second, 0.000001);
}

INSTANTIATE_TEST_CASE_P(
        CoordinateDistanceTest,
        CoordinateDistanceParameterizedTestFixture,
        ::testing::Values(
                std::make_pair(std::make_pair(Coordinates(1,  1),  Coordinates(1,  1)), 0.0),
                std::make_pair(std::make_pair(Coordinates(0,  0),  Coordinates(0,  1)), 1.0),
                std::make_pair(std::make_pair(Coordinates(0,  0),  Coordinates(1,  0)), 1.0),
                std::make_pair(std::make_pair(Coordinates(1,  0),  Coordinates(0,  0)), 1.0),
                std::make_pair(std::make_pair(Coordinates(0,  1),  Coordinates(0,  0)), 1.0),
                std::make_pair(std::make_pair(Coordinates(0,  0),  Coordinates(2,  2)), 2.828427),
                std::make_pair(std::make_pair(Coordinates(2,  2),  Coordinates(0,  0)), 2.828427),
                std::make_pair(std::make_pair(Coordinates(-7, -4), Coordinates(17, 6)), 26.0),
                std::make_pair(std::make_pair(Coordinates(17, 6), Coordinates(-7, -4)), 26.0)
        )
);