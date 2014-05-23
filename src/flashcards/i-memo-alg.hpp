#ifndef ANKI_LITE_I_MEMO_ALG_HPP_
#define ANKI_LITE_I_MEMO_ALG_HPP_

#include "card.hpp"

namespace anki_lite
{

/**
 * Interface used as a base for various memo algorithms.
 */
class IMemoAlg
{
public:

    virtual void update_viewed_card(ICard &card, int response_quality) const = 0;

    virtual ~IMemoAlg() {};

protected:

    virtual Interval compute_new_interval(Interval old_intv, int repetition,
                                          int e_factor) const = 0;

    virtual int compute_new_e_factor(int old_e_factor, int response_quality) const = 0;
};

} // namespace anki_lite

#endif
