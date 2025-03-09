#pragma once

template <typename T, typename U> struct IsSame {
    static constexpr bool value = false;
};

template <typename T> struct IsSame<T, T> {
    static constexpr bool value = true;
};

template <typename T> struct IsIntegral {
    static constexpr bool value = false;
};

template <> struct IsIntegral<int> {
    static constexpr bool value = true;
};

template <> struct IsIntegral<long> {
    static constexpr bool value = true;
};

template <> struct IsIntegral<short> {
    static constexpr bool value = true;
};

template <> struct IsIntegral<char> {
    static constexpr bool value = true;
};

template <typename T> struct IsFloatingPoint {
    static constexpr bool value = false;
};

template <> struct IsFloatingPoint<float> {
    static constexpr bool value = true;
};

template <> struct IsFloatingPoint<double> {
    static constexpr bool value = true;
};

template <> struct IsFloatingPoint<long double> {
    static constexpr bool value = true;
};
