#ifndef ANKI_LITE_I_MEMO_ALG_HPP_
#define ANKI_LITE_I_MEMO_ALG_HPP_

/**
 * Interface used as a base for various memo algorithms.
 */
class IMemoAlg
{
public:

    virtual void update_viewed_card(ICard &card, int response_quality) const = 0;

protected:

    virtual Interval compute_new_interval(Interval old_intv, int repetition,
                                          int e_factor) = 0;

    virtual int compute_new_e_factor(int old_e_factor, int response_quality) = 0;
};

#endif
