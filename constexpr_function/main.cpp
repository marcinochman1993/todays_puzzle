template <typename T>
constexpr T min(T a, T b)
{
    return a < b? a: b;
}

int main(int argc, char *argv[])
{
    return min(20, 10);
}
