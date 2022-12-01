#ifndef CYFRE_MM_CONSTRUCTORS_CPP
#define CYFRE_MM_CONSTRUCTORS_CPP

#include "matrix_class.hpp"
#include <iostream>

namespace cyfre {
    /// initializes a 1x1 matrix with a value of zero
    template <class T>
    mat<T>::mat() : matrix(NULL), height(0), width(0) {
#ifdef DISPLAY_FUNC_CALLS
        std::cout << "mat()\n";
        auto start = std::chrono::high_resolution_clock::now();
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
        std::cout << "took " << duration.count() << " nanoseconds\n\n";
#endif
    }

    template <class T>
    mat<T>::mat(T one_value) : matrix(new T[1]), height(1), width(1) {
        matrix[0] = one_value;
    }

    /// initializes a matrix from a text file
    template <class T>
    mat<T>::mat(std::string text_file, char separator) {
        std::ifstream filereader;
        filereader.open(text_file.c_str());

        if (filereader.fail()) {
            throw std::ios_base::failure(
                "\n\nERROR : constructor::mat<T>(\"" + text_file +
                "\")\n"
                "\tinitialization error, text file not found or might not be supported\n"
            );
        }

        std::vector<std::string> strlines;
        std::string tmp;

        while (!filereader.eof()) {
            getline(filereader, tmp);
            strlines.push_back(tmp);
        }

        std::vector<std::vector<std::string>> matrix_strings;
        bool an_integer = true;
        for (size_t i = 0; i < strlines.size(); ++i) {
            std::vector<std::string> row_parse = cyfre::helpers::parse(strlines[i], separator);
            for (size_t j = 0; j < row_parse.size(); ++j) {
                std::pair<bool, bool> isvalid_isrational = cyfre::helpers::isanumber(row_parse[j]);
                if (!isvalid_isrational.first) {
                    throw std::ios_base::failure(
                        "\n\nERROR : constructor::mat<T>(\"" + text_file +
                        "\")\n"
                        "\tinitialization error, invalid number inside the text file:" +
                        text_file + ", on line:" + std::to_string(i) + "\n"
                    );
                }
                if (isvalid_isrational.second)
                    an_integer = false;
            }
            matrix_strings.push_back(row_parse);
        }

        for (size_t i = 1; i < matrix_strings.size(); ++i) {
            if (matrix_strings[i].size() != matrix_strings[i - 1].size()) {
                throw std::length_error(
                    "\n\nERROR : constructor::mat<T>(\"" + text_file +
                    "\")\n"
                    "\tinitialization error, the text file provided an unequal length of rows\n"
                    "\terror occurs in text file after comparison on line " +
                    std::to_string(i) + " & " + std::to_string(i + 1) + "\n"
                );
            }
        }

        height = matrix_strings.size();
        width = matrix_strings[0].size();

        matrix = new T[height * width];

        size_t cnt = 0;
        for (size_t i = 0; i < matrix_strings.size(); ++i) {
            for (size_t j = 0; j < matrix_strings[i].size(); ++j) {
                if (an_integer)
                    matrix[cnt++] = (T) (std::stoll(matrix_strings[i][j]));
                else
                    matrix[cnt++] = (T) (std::stold(matrix_strings[i][j]));
            }
        }
    }

    /// initializes a matrix using a 2 dimension vector : @arg std::vector<std::vector<T>> matrix
    template <class T>
    mat<T>::mat(std::initializer_list<std::initializer_list<T>> matrix) {
        auto outer_it = matrix.begin();
        size_t prev_row_len = (*outer_it).size();

        for (auto &row: matrix) {
            if (row.size() != prev_row_len) {
                throw std::length_error(
                    "\n\nERROR : mat(std::initializer_list<std::initializer_list<T>> matrix)\n"
                    "\tthe inner rows inside std::initializer_list<std::initializer_list<T>> is not equal\n"
                );
            }
        }

        height = matrix.size();
        width = (*outer_it).size();

        this->matrix = new T[height * width];

        for (size_t i = 0; i < height; ++i, ++outer_it) {
            std::copy((*outer_it).begin(), (*outer_it).end(), this->matrix + (i * width));
        }
    }

    /// initializes a matrix using a vector : @arg std::vector<T> matrix
    template <class T>
    mat<T>::mat(std::initializer_list<T> array_vector) : height(1), width(array_vector.size()) {
        matrix = new T[height * width];
        std::copy(array_vector.begin(), array_vector.end(), matrix);
    }

    /// initializes a matrix given a @arg height, @arg width for the matrix shape, and a @arg default_value of all
    /// elements in the matrix
    template <class T>
    mat<T>::mat(const size_t height, const size_t width, const T default_value)
        : matrix(new T[height * width]), height(height), width(width) {
        size_t n = height * width;

        for (size_t i = 0; i < n; ++i) {
            matrix[i] = default_value;
        }
    }

    /// initializes a matrix given a @arg height, @arg width for the matrix shape, that have a random values form the
    /// given @arg lower_bound to @arg upper_bound
    template <class T>
    mat<T>::mat(
        const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound
    )
        : matrix(new T[height * width]), height(height), width(width) {
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937_64 rand_engine(seed);
        std::uniform_real_distribution<float> random_number_float(lower_bound, upper_bound);
        std::uniform_int_distribution<long long> random_number_int(lower_bound, upper_bound);

        size_t n = height * width;

        for (size_t i = 0; i < n; ++i) {
            switch (typechoice) {
                case RANDOM::INTEGER:
                    matrix[i] = random_number_int(rand_engine);
                    break;
                case RANDOM::REAL:
                    matrix[i] = random_number_float(rand_engine);
                    break;
                default:
                    throw std::invalid_argument(
                        "\n\nERROR : mat(const size_t height, const size_t width, const RANDOM typechoice, const T "
                        "lower_bound, const T upper_bound)\n\tinvalid random type"
                    );
            }
        }
    }

    /// initializes a square matrix with a given 'x' scalar values of elements in the main diagonal
    template <class T>
    mat<T>::mat(const TYPE matrix_type, const size_t n, T scalar) {
        if (matrix_type == TYPE::IDENTITY)
            scalar = 1;

        height = width = n;

        matrix = new T[n * n];

        size_t N = n * n;
        for (size_t i = 0; i < N; ++i) {
            matrix[i] = 0;
        }

        for (size_t i = 0; i < n; ++i) {
            matrix[i * width + i] = scalar;
        }
    }

    template <class T>
    mat<T>::mat(const TYPE matrix_type, const size_t n) : mat<T>(matrix_type, n, 0) {
        switch (matrix_type) {
            case TYPE::IDENTITY:
                break;
            case TYPE::NULLZERO:
                break;
            case TYPE::SCALARMATRIX:
                throw std::invalid_argument(
                    "\n\nERROR : mat(TYPE matrix_type, size_t n, T scalar)\n"
                    "\tSCALAR matrix initialization, missing argument\n"
                );
            default:
                throw std::invalid_argument(
                    "\n\nERROR : mat()\n\tmatrix initialization - constructor invalid given an invalid TYPE\n"
                );
        }
    }

    /// copy constructor
    template <class T>
    mat<T>::mat(const mat<T> &original) {
        size_t n = original.height * original.width;

        height = original.height;
        width = original.width;

        matrix = new T[n];

        std::memcpy(matrix, original.matrix, sizeof(T) * n);
    }

    /// move constructor
    template <class T>
    mat<T>::mat(mat<T> &&temporary) {
        height = temporary.height;
        width = temporary.width;
        matrix = temporary.matrix;

        temporary.height = 0;
        temporary.width = 0;
        temporary.matrix = NULL;
    }

    template <class T>
    mat<T>::~mat<T>() {
        if (height && width)
            delete[] matrix;
        height = 0;
        width = 0;
    }
} // namespace cyfre

#endif