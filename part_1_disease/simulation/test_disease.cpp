#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Disease.h"

TEST_CASE("Disease values") {
    Disease d(5, 0.3);
    CHECK(d.getDuration() == 5);
    CHECK(d.getInfectivity() == doctest::Approx(0.3));
}