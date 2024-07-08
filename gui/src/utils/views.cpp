/*
** EPITECH PROJECT, 2024
** gui
** File description:
** views
*/

#include "utils/views.hpp"

void simple_to_isometric(float *x, float *y)
{
    float tmp_x = *x;
    float tmp_y = *y;

    *x = (tmp_x - tmp_y) * 64 / 90;
    *y = (tmp_x + tmp_y) * 32 / 90;
}

void isometric_to_simple(float *x, float *y)
{
    float tmp_x = *x;
    float tmp_y = *y;

    *x = (tmp_x / 64 + tmp_y / 32) * 90 / 2;
    *y = (tmp_y / 32 - tmp_x / 64) * 90 / 2;
}