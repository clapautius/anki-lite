#ifndef ANKI_LITE_I_MEMO_ALG_HPP_
#define ANKI_LITE_I_MEMO_ALG_HPP_

#include "i-memo-alg.hpp"

class MemoAlgSm2 : IMemoAlg
{
public:
    virtual void update_viewed_card(ICard &card, int response_quality) const;

protected:

    virtual Interval compute_new_interval(Interval old_intv, int repetition,
                                          double e_factor) const;

    virtual int compute_new_e_factor(int old_e_factor, int response_quality) const;

};

#endif
