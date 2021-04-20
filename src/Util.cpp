#include "Util.h"

/**
 * Output a vector of doubles to a stream.
 * @param stream the stream to write to.
 * @param vector the vector of doubles to write.
 * @return the stream.
 */
std::ostream &operator << (std::ostream &stream, const std::vector<double> &vector) {
    for (auto i = 0; i < vector.size() - 1; i++) {
        stream << vector[i] << ", ";
    }
    stream << vector[vector.size() - 1];
    return stream;
}
