#include <random>

inline float getRandomNumber(const float min, const float max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_real_distribution distribution(min, max);
    return distribution(generator);
}
