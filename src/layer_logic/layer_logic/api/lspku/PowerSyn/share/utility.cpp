//
// Created by zephyr on 2022/4/11.
//

#include "netlist.h"

inline int get_index(std::vector<double> &axis, double value) {
    int index = -1;
    if (value < axis[0])
        index = 0;
    for (int i = 1; i < axis.size(); i++) {
        if (value < axis[i] && value >= axis[i - 1]) {
            index = i;
            break;
        }
    }
    if (value == axis[axis.size() - 1])
        index = int(axis.size()) - 1;
    if (value > axis[axis.size() - 1])
        index = int(axis.size());
    assert(index != -1);
    return index;
}

double PASyn::interpolate(std::vector<double> &x_axis, std::vector<double> &y_axis,
                          std::vector<std::vector<double>> values, double x, double y) {
    int x_index_l, x_index_h, y_index_l, y_index_h;
    double result = -1;
    x_index_h = get_index(x_axis, x);
    y_index_h = get_index(y_axis, y);
    x_index_l = x_index_h - 1;
    y_index_l = y_index_h - 1;

    if (x_index_l >= 0 && x_index_h < x_axis.size() && y_index_l >= 0 && y_index_h < y_axis.size()) {
        double x_y1 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_l][y_index_l]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                        values[x_index_h][y_index_l];
        double x_y2 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_l][y_index_h]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                        values[x_index_h][y_index_h];
        result = ((y_axis[y_index_h] - y) / (y_axis[y_index_h] - y_axis[y_index_l])) * x_y1 +
                 ((y - y_axis[y_index_l]) / (y_axis[y_index_h] - y_axis[y_index_l])) * x_y2;
    } else if (x_index_l < 0 && y_index_l < 0) {
        double x_y1 = values[1][0] + (x - x_axis[1]) / (x_axis[1] - x_axis[0]) * (values[0][0] - values[1][0]);
        double x_y2 = values[1][1] + (x - x_axis[1]) / (x_axis[1] - x_axis[0]) * (values[0][1] - values[1][1]);
        result = x_y2 + (y - y_axis[1]) / (y_axis[0] - y_axis[1]) * (x_y1 - x_y2);
    } else if (x_index_l >= 0 && x_index_h < x_axis.size() && y_index_l < 0) {
        double x_y1 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_l][0]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_h][0];
        double x_y2 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_l][1]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) * values[x_index_h][1];
        result = x_y2 + (y - y_axis[1]) / (y_axis[0] - y_axis[1]) * (x_y1 - x_y2);
    } else if (x_index_h >= x_axis.size() && y_index_l < 0) {
        double x_y1 = values[x_axis.size() - 2][0] +
                      (x - x_axis[x_axis.size() - 2]) / (x_axis[x_axis.size() - 1] - x_axis[x_axis.size() - 2]) *
                      (values[x_axis.size() - 1][0] - values[x_axis.size() - 2][0]);
        double x_y2 = values[x_axis.size() - 2][1] +
                      (x - x_axis[x_axis.size() - 2]) / (x_axis[x_axis.size() - 1] - x_axis[x_axis.size() - 2]) *
                      (values[x_axis.size() - 1][1] - values[x_axis.size() - 2][1]);
        result = x_y2 + (y - y_axis[1]) / (y_axis[0] - y_axis[1]) * (x_y1 - x_y2);
    } else if (x_index_l < 0 & y_index_l >= 0 && y_index_h < y_axis.size()) {
        double y_x1 = ((y_axis[y_index_h] - y) / (y_axis[y_index_h] - y_axis[y_index_l])) * values[0][y_index_l]
                      + ((y - y_axis[y_index_l]) / (y_axis[y_index_h] - y_axis[y_index_l])) * values[0][y_index_h];
        double y_x2 = ((y_axis[y_index_h] - y) / (y_axis[y_index_h] - y_axis[y_index_l])) * values[1][y_index_l]
                      + ((y - y_axis[y_index_l]) / (y_axis[y_index_h] - y_axis[y_index_l])) * values[1][y_index_h];
        result = y_x2 + (x - x_axis[1]) / (x_axis[0] - x_axis[1]) * (y_x1 - y_x2);
    } else if (x_index_h >= x_axis.size() & y_index_l >= 0 && y_index_h < y_axis.size()) {
        double y_x1 = ((y_axis[y_index_h] - y) / (y_axis[y_index_h] - y_axis[y_index_l])) *
                      values[x_axis.size() - 2][y_index_l]
                      + ((y - y_axis[y_index_l]) / (y_axis[y_index_h] - y_axis[y_index_l])) *
                        values[x_axis.size() - 2][y_index_h];
        double y_x2 = ((y_axis[y_index_h] - y) / (y_axis[y_index_h] - y_axis[y_index_l])) *
                      values[x_axis.size() - 1][y_index_l]
                      + ((y - y_axis[y_index_l]) / (y_axis[y_index_h] - y_axis[y_index_l])) *
                        values[x_axis.size() - 1][y_index_h];
        result = y_x1 + (x - x_axis[x_axis.size() - 2]) / (x_axis[x_axis.size() - 1] - x_axis[x_axis.size() - 2]) *
                        (y_x2 - y_x1);
    } else if (x_index_l < 0 && y_index_h >= y_axis.size()) {
        double x_y1 = values[1][y_axis.size() - 2] + (x - x_axis[1]) / (x_axis[1] - x_axis[0]) *
                                                     (values[0][y_axis.size() - 2] - values[1][y_axis.size() - 2]);
        double x_y2 = values[1][y_axis.size() - 1] + (x - x_axis[1]) / (x_axis[1] - x_axis[0]) *
                                                     (values[0][y_axis.size() - 1] - values[1][y_axis.size() - 1]);
        result = x_y1 + (y - y_axis[y_axis.size() - 2]) / (y_axis[y_axis.size() - 1] - y_axis[y_axis.size() - 2]) *
                        (x_y2 - x_y1);
    } else if (x_index_l >= 0 && x_index_h < x_axis.size() && y_index_h >= y_axis.size()) {
        double x_y1 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                      values[x_index_l][y_axis.size() - 2]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                        values[x_index_h][y_axis.size() - 2];
        double x_y2 = ((x_axis[x_index_h] - x) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                      values[x_index_l][y_axis.size() - 1]
                      + ((x - x_axis[x_index_l]) / (x_axis[x_index_h] - x_axis[x_index_l])) *
                        values[x_index_h][y_axis.size() - 1];
        result = x_y1 + (y - y_axis[y_axis.size() - 2]) / (y_axis[y_axis.size() - 1] - y_axis[y_axis.size() - 2]) *
                        (x_y2 - x_y1);
    } else if (x_index_h >= x_axis.size() && y_index_h >= y_axis.size()) {
        double x_y1 = values[x_axis.size() - 2][y_axis.size() - 2] +
                      (x - x_axis[x_axis.size() - 2]) / (x_axis[x_axis.size() - 1] - x_axis[x_axis.size() - 2]) *
                      (values[x_axis.size() - 1][y_axis.size() - 2] - values[x_axis.size() - 2][y_axis.size() - 2]);
        double x_y2 = values[x_axis.size() - 2][y_axis.size() - 1] +
                      (x - x_axis[x_axis.size() - 2]) / (x_axis[x_axis.size() - 1] - x_axis[x_axis.size() - 2]) *
                      (values[x_axis.size() - 1][y_axis.size() - 1] - values[x_axis.size() - 2][y_axis.size() - 1]);
        result = x_y1 + (y - y_axis[y_axis.size() - 2]) / (y_axis[y_axis.size() - 1] - y_axis[y_axis.size() - 2]) *
                        (x_y2 - x_y1);
    } else {
        assert(false);
    }

    return result;
}