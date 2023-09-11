#pragma once

struct Vector2 {
    public:
        float x;
        float y;

        Vector2(float x = 0.f, float y = 0.f);
        Vector2(Vector2 const &other);
        Vector2 &operator=(Vector2 const &other);
        bool operator==(Vector2 const &other) const;
        ~Vector2();
};
