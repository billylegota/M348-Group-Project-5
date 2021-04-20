#pragma once
#ifndef CHAPTER_6_UTIL_H
#define CHAPTER_6_UTIL_H

#include <ostream>
#include <vector>


/**
 * Output a vector of doubles to a stream.
 * @param stream the stream to write to.
 * @param vector the vector of doubles to write.
 * @return the stream.
 */
std::ostream &operator<<(std::ostream &stream, const std::vector<double> &vector);

#endif // CHAPTER_6_UTIL_H
