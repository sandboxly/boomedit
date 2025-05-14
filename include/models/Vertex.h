#ifndef VERTEX_H
#define VERTEX_H

struct Vertex {
    float x;
    float y;

    Vertex(float xCoord = 0.0f, float yCoord = 0.0f)
        : x(xCoord), y(yCoord) {}
};

#endif // VERTEX_H
