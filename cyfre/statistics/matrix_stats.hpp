#ifndef MATRIX_STATS_HPP
#define MATRIX_STATS_HPP

#include "../classes/matrix_class.hpp"
#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <utility>

namespace cyfre {
    namespace sts {
        enum OBSERVATIONS
        {
            POPULATION = 0,
            SAMPLE = 1
        };

        template <typename T>
        long double mean(const mat<T> &input) {
            T total = input.sum();
            size_t n = input.height * input.width;
            return (long double) total / (long double) n;
        }

        template <typename T>
        long double median(const mat<T> &input) {
            auto oddmiddle = [](T odd) {
                if (odd == 1)
                    return (long double) 0;
                return std::floor(((long double) odd / (long double) 2));
            };

            if (input.height % 2 == 0 && input.width % 2 == 0) {
                size_t hh = (input.height / 2) - 1;
                size_t hw = (input.width / 2) - 1;

                return ((long double) input.matrix[hh * input.width + hw] +
                        (long double) input.matrix[hh * input.width + hw + 1] +
                        (long double) input.matrix[(hh + 1) * input.width + hw] +
                        (long double) input.matrix[(hh + 1) * input.width + (hw + 1)]) /
                       (long double) 4;
            } else if (input.height % 2 != 0 && input.width % 2 == 0) {
                size_t hh = oddmiddle(input.height);
                size_t hw = (input.width / 2) - 1;
                return ((long double) input.matrix[hh * input.width + hw] +
                        (long double) input.matrix[hh * input.width + hw + 1]) /
                       (long double) 2;
            } else if (input.height % 2 == 0 && input.width % 2 != 0) {
                size_t hh = (input.height / 2) - 1;
                size_t hw = oddmiddle(input.width);
                return ((long double) input.matrix[hh * input.width + hw] +
                        (long double) input.matrix[(hh + 1) * input.width + hw]) /
                       (long double) 2;
            } else if (input.height % 2 != 0 && input.width % 2 != 0) {
                size_t hh = oddmiddle(input.height);
                size_t hw = oddmiddle(input.width);
                return (long double) input.matrix[hh * input.width + hw];
            } else if ((input.height == 1) && (input.height == input.width)) {
                return (long double) input.matrix[0 * input.width + 0];
            }
            return 0;
        }

        template <typename T>
        std::pair<size_t, std::vector<T>> mode(const mat<T> &input) {
            std::map<T, size_t> e_counts;
            for (size_t i = 0; i < input.height; ++i) {
                for (size_t j = 0; j < input.width; ++j) {
                    auto curr = e_counts.find(input.matrix[i * input.width + j]);
                    if (curr == e_counts.end()) {
                        e_counts.insert({input.matrix[i * input.width + j], 1});
                    } else {
                        e_counts[input.matrix[i * input.width + j]]++;
                    }
                }
            }

            size_t max = size_t(std::numeric_limits<size_t>::min());
            for (auto e: e_counts) {
                size_t curr_count = e.second;
                if (curr_count > max) {
                    max = curr_count;
                }
            }

            std::set<T> modes;

            for (auto e: e_counts) {
                T curr_key = e.first;
                size_t curr_count = e.second;
                if (curr_count == max && curr_count != 1) {
                    modes.insert(curr_key);
                }
            }

            if (modes.empty())
                max = 0;

            std::vector<T> pair_second;
            pair_second.reserve(modes.size());
            for (auto e: modes) {
                pair_second.push_back(e);
            }

            return {max, pair_second};
        }

        /// @returns sum of squares
        template <typename T>
        long double sofs(const mat<T> &input) {
            long double input_mean = mean(input);
            long double sum_of_squares = 0;
            for (size_t i = 0; i < input.height; ++i) {
                for (size_t j = 0; j < input.width; ++j) {
                    sum_of_squares += (input.matrix[i * input.width + j] - input_mean) *
                                      (input.matrix[i * input.width + j] - input_mean);
                }
            }
            return sum_of_squares;
        }

        /// @returns variance
        template <typename T>
        long double variance(const mat<T> &input, const OBSERVATIONS type) {
            // long double input_mean = mean(input);
            long double sum_of_squares = sofs(input);
            long double n = input.height * input.width;

            return sum_of_squares / (long double) (n - (long double) type);
        }

        /// @returns standard deviation
        template <typename T>
        long double stddvn(const mat<T> &input, const OBSERVATIONS type) {
            return std::sqrt(variance(input, type));
        }
    } // namespace sts
} // namespace cyfre

#endif