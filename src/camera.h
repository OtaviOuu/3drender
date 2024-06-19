#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

typedef struct
{

    vec3_t position;
    // Cada componente da terna representa a rotação em seus respectivos eixos
    vec3_t rotation;
    float fov_angle;

} camera_t;

#endif