#ifndef SOFTWAREPATHTRACING_PDF_HPP
#define SOFTWAREPATHTRACING_PDF_HPP

class PDF {
public:
    [[nodiscard]] virtual double value(const vec3 &direction) const = 0;

    [[nodiscard]] virtual vec3 generate() const = 0;
};

#endif //SOFTWAREPATHTRACING_PDF_HPP
