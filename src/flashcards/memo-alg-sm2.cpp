#include "memo-alg-sm2.hpp"


/**
 * Compute new interval according to the SM2 formula:
 * I(1):=1
 * I(2):=6
 * for n>2 I(n):=I(n-1)*EF
 *
 * @param[in] e_factor : easiness factor - expressed as an int (1.32 = 132)
 */
Interval MemoAlgSm2::compute_new_interval(Interval old_intv, int repetition,
                                          int e_factor)
{
    Interval intv = 0;
    if (repetition == 1) {
        intv = 1;
    } else if (repetition == 2) {
        intv = 6;
    } else {
        intv = old_intv * e_factor / 100;
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
int MemoAlgSm2::compute_new_e_factor(int old_e_factor, int response_quality)
{
    double e_factor;
    double old_e_factor_d = old_e_factor / 100.0;
    e_factor = old_e_factor_d + (0.1 - (5 - response_quality) *
                                 (0.08 + (5 - response_quality) * 0.02));
    return (int)(e_factor * 100);
}


void MemoAlgSm2::update_viewed_card(ICard &card, int response_quality) const
{
    int new_e_factor = compute_new_e_factor(card.e_factor(), response_quality);
    Interval new_interval = compute_new_interval(card.interval(), card.repetition(),
                                                 new_e_factor);
    card.set_e_factor(new_e_factor);
    card.set_interval(new_interval);
    card.set_last_view_now();
    if (response_quality < 3) {
        card.reset_repetition();
    } else {
        card.inc_repetition();
    }
}
