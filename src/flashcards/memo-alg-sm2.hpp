#ifndef ANKI_LITE_MEMO_ALG_SM2_HPP_
#define ANKI_LITE_MEMO_ALG_SM2_HPP_

#include "i-memo-alg.hpp"

void alg_sm2_automatic_tests();

namespace anki_lite
{

class MemoAlgSm2 : public IMemoAlg
{
public:
    virtual void update_viewed_card(ICard &card, int response_quality) const;

protected:

    virtual Interval compute_new_interval(Interval old_intv, int repetition,
                                          int e_factor) const;

    virtual int compute_new_e_factor(int old_e_factor, int response_quality) const;

    friend void ::alg_sm2_automatic_tests();
};

}

#endif
