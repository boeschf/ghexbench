/*
 * ghex-org
 *
 * Copyright (c) 2014-2022, ETH Zurich
 * All rights reserved.
 *
 * Please, refer to the LICENSE file in the root directory.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#pragma once

#include <limits>
#include <cmath>

namespace ghexbench
{
class accumulator
{
  public: // member types
    using size_type = std::size_t;
    using value_type = double;

  private: // members
    size_type  m_num_samples = 0u;
    value_type m_min = std::numeric_limits<value_type>::max();
    value_type m_max = std::numeric_limits<value_type>::min();
    value_type m_mean = 0;
    value_type m_variance = 0;

  public: // ctors
    accumulator() noexcept = default;
    accumulator(const accumulator&) noexcept = default;
    accumulator(accumulator&&) noexcept = default;
    accumulator(size_type num_samples_, value_type min_, value_type max_, value_type mean_,
        value_type variance_) noexcept
    : m_num_samples(num_samples_)
    , m_min(min_)
    , m_max(max_)
    , m_mean(mean_)
    , m_variance(variance_)
    {
    }
    accumulator& operator=(const accumulator&) noexcept = default;
    accumulator& operator=(accumulator&&) noexcept = default;

  public: // return statistics
    inline size_type  num_samples() const noexcept { return m_num_samples; }
    inline value_type min() const noexcept { return m_min; }
    inline value_type max() const noexcept { return m_max; }
    inline value_type mean() const noexcept { return m_mean; }
    inline value_type variance() const noexcept
    {
        return ((m_num_samples > 1) ? (m_variance / (m_num_samples - 1)) : 0);
    }
    inline value_type stddev() const noexcept
    {
        return (m_num_samples > 1 ? std::sqrt(variance()) : 0);
    }
    inline value_type sum() const noexcept { return m_num_samples * m_mean; }

  public: // add samples
    template<typename InputIterator>
    inline accumulator& operator()(InputIterator first, InputIterator last) noexcept
    {
        for (auto sample_ptr = first; sample_ptr != last; ++sample_ptr) (*this)(*sample_ptr);
        return *this;
    }

    inline accumulator& operator()(value_type sample) noexcept
    {
        m_min = std::min(m_min, sample);
        m_max = std::max(m_max, sample);
        const value_type delta = sample - m_mean;
        m_mean += delta / (++m_num_samples);
        m_variance += delta * (sample - m_mean);
        return *this;
    }

    inline accumulator& operator()(const accumulator& other) noexcept
    {
        if (other.m_num_samples == 0) return *this;
        if (m_num_samples == 0)
        {
            m_num_samples = other.m_num_samples;
            m_min = other.m_min;
            m_max = other.m_max;
            m_mean = other.m_mean;
            m_variance = other.m_variance;
            return *this;
        }
        m_min = std::min(m_min, other.min());
        m_max = std::max(m_max, other.max());
        const auto delta = other.m_mean - m_mean;
        const auto num_samples_new = m_num_samples + other.m_num_samples;
        m_mean += (delta * other.m_num_samples) / num_samples_new;
        m_variance += other.m_variance +
                      (delta * delta * m_num_samples * other.m_num_samples) / num_samples_new;
        m_num_samples = num_samples_new;
        return *this;
    }

  public:
    inline void clear() noexcept
    {
        m_num_samples = 0;
        m_min = std::numeric_limits<value_type>::max();
        m_max = std::numeric_limits<value_type>::min();
        m_mean = 0;
        m_variance = 0;
    }

  public:
    template<class CharT, class Traits = std::char_traits<CharT>>
    friend std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& os, const accumulator& acc)
    {
        os << "[" << acc.min() << "," << acc.mean() << "," << acc.max() << "] (" << acc.stddev()
           << "," << acc.num_samples() << ")";
        return os;
    }
};

} // namespace ghexbench
