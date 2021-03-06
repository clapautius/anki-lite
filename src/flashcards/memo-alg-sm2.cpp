#include <math.h>
#include "memo-alg-sm2.hpp"

namespace anki_lite
{

/**
 * Compute new interval according to the SM2 formula:
 * I(1):=1
 * I(2):=6
 * for n>2 I(n):=I(n-1)*EF
 * I(x) = in days.
 *
 * @param[in] e_factor : easiness factor - expressed as an int (1.32 = 132)
 */
Interval MemoAlgSm2::compute_new_interval(Interval old_intv, int repetition,
                                          int e_factor) const
{
    Interval intv = 0;
    if (repetition == 1) {
        intv = 1;
    } else if (repetition == 2) {
        intv = 6;
    } else {
        intv = static_cast<Interval>(
          round(old_intv * (static_cast<double>(e_factor) / 100)));
    }
    return intv;
}


/**
 * Compute new easiness factor according to SM2 formula:
 * EF':=EF+(0.1-(5-q)*(0.08+(5-q)*0.02))
 * where:
 * EF' - new value of the E-Factor,
 * EF - old value of the E-Factor,
 * q - quality of the response in the 0-5 grade scale.
 * If EF is less than 1.3 then let EF be 1.3.
 */
int MemoAlgSm2::compute_new_e_factor(int old_e_factor, int response_quality) const
{
    double e_factor;
    double old_e_factor_d = old_e_factor / 100.0d;
    e_factor = old_e_factor_d + (0.1d - (5 - response_quality) *
                                 (0.08d + (5 - response_quality) * 0.02d));
    return (int)(e_factor * 100);
}


void MemoAlgSm2::update_viewed_card(ICard &card, int response_quality) const
{
    card.set_last_view_now();
    card.inc_repetition();
    int new_e_factor = compute_new_e_factor(card.e_factor(), response_quality);
    Interval new_interval = compute_new_interval(card.interval(), card.repetition(),
                                                 new_e_factor);
    if (new_e_factor < 130) {
        new_e_factor = 130;
    }
    if (response_quality < 3) {
        card.reset_repetition();
    } else {
        card.set_e_factor(new_e_factor);
        card.set_interval(new_interval);
    }
}

}
