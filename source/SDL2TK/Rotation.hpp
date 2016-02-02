#ifndef ROTATION_HPP
#define ROTATION_HPP

namespace SDL2TK
{
    template<typename T>
    constexpr T Pi() { return 3.1415926535897932384626433832795; }

    template<typename T>
    constexpr T Tau() { return Pi<T>() * T(2); }

    template<typename T>
    constexpr T DegreesPerRadian() { return T(180) / Pi<T>(); }

    template<typename T>
    constexpr T RadiansPerDegree() { return Pi<T>() / T(180); }

    template<typename T>
    class Rotation
    {
        public:
            constexpr Rotation() : _radians(0) {}
            constexpr Rotation(const Rotation&) = default;
            ~Rotation() = default;

            Rotation& operator=(const Rotation& other) = default;

            Rotation& operator+=(const Rotation& other)
            {
                _radians = Cycle(_radians + other._radians);
                return *this;
            }

            Rotation& operator-=(const Rotation& other)
            {
                _radians = Cycle(_radians - other._radians);
                return *this;
            }

            constexpr T ToRadians() const
            {
                return _radians;
            }

            constexpr T ToDegrees() const
            {
                return _radians * DegreesPerRadian;
            }

            constexpr Rotation operator-() const
            {
                return Rotation(Cycle(_radians + Pi<T>()));
            }

            const Rotation operator+(const Rotation other) const
            {
                return Rotation(Cycle(_radians + other._radians));
            }

            const Rotation operator-(const Rotation other) const
            {
                return Rotation(Cycle(_radians - other._radians));
            }

            static constexpr Rotation FromRadians(T radians)
            {
                return Rotation(radians);
            }

            static constexpr Rotation FromDegrees(T degrees)
            {
                return Rotation(degrees * RadiansPerDegree<T>());
            }

        private:
            constexpr Rotation(T radians) : _radians(radians) {}

            T _radians;

            static T Cycle(T radians)
            {
                T result = radians;

                if (result < -Pi<T>())
                    result += Tau<T>();
                else if (result >= Pi<T>())
                    result -= Tau<T>();

                return result;
            }
    };

    typedef Rotation<float> RotationF;
    typedef Rotation<double> RotationD;
}

#endif
