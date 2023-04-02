cmake_minimum_required(VERSION 3.20)
project(wcRay)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/core)
include_directories(src/geometries)
include_directories(src/material)
include_directories(src/pdf)
include_directories(src/texture)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(wcRay
        src/core/camera.cpp
        src/core/camera.h
        src/core/color.cpp
        src/core/color.h
        src/core/common.cpp
        src/core/common.h
        src/core/main.cpp
        src/core/onb.cpp
        src/core/onb.h
        src/core/path_tracing.h
        src/core/ray.cpp
        src/core/ray.h
        src/core/rt_stb_image.cpp
        src/core/stb_image.h
        src/core/vec.cpp
        src/core/vec.h
        src/geometries/aabb.cpp
        src/geometries/aabb.h
        src/geometries/box.cpp
        src/geometries/box.h
        src/geometries/bvh.cpp
        src/geometries/bvh.h
        src/geometries/flip_face.cpp
        src/geometries/flip_face.h
        src/geometries/hit.h
        src/geometries/hittable_list.cpp
        src/geometries/hittable_list.h
        src/geometries/moving_sphere.cpp
        src/geometries/moving_sphere.h
        src/geometries/rectangle.cpp
        src/geometries/rectangle.h
        src/geometries/rotate.cpp
        src/geometries/rotate.h
        src/geometries/sphere.cpp
        src/geometries/sphere.h
        src/geometries/translate.cpp
        src/geometries/translate.h
        src/geometries/triangle.cpp
        src/geometries/triangle.h
        src/geometries/volumn.cpp
        src/geometries/volumn.h
        src/material/dielectric.cpp
        src/material/dielectric.h
        src/material/diffuse_light.cpp
        src/material/diffuse_light.h
        src/material/isotropic.cpp
        src/material/isotropic.h
        src/material/lambertian.cpp
        src/material/lambertian.h
        src/material/material.h
        src/material/metal.cpp
        src/material/metal.h
        src/pdf/cosine_pdf.cpp
        src/pdf/cosine_pdf.h
        src/pdf/hittable_pdf.cpp
        src/pdf/hittable_pdf.h
        src/pdf/mixture_pdf.cpp
        src/pdf/mixture_pdf.h
        src/pdf/pdf.h
        src/texture/alternating_texture.cpp
        src/texture/alternating_texture.h
        src/texture/image_texture.cpp
        src/texture/image_texture.h
        src/texture/noise_texture.cpp
        src/texture/noise_texture.h
        src/texture/texture.h)
