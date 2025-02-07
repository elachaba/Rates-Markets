//
// Created by Aymane on 03/02/2025.
//

#ifndef INTERESTRATEMODEL_HPP
#define INTERESTRATEMODEL_HPP
#include <iostream>


class InterestRateModel {
private:
    double rate_;

public:
    explicit InterestRateModel(double rate);

    virtual ~InterestRateModel() = default;

    /**
     * calculates the discount factor between times t1 and t2.
     * @param t1 start time.
     * @param t2 end time
     * @return exp(-rate_ * (t2 - t1))
     */
    double discount(double t1, double t2) const;

    /**
     * calculates the capitalization factor between times t1 and t2
     * @param t1 start time
     * @param t2 end time
     * @return exp(rate * (t2 - t1))
     */
    double account(double t1, double t2) const;

    double getRate() const;

};



#endif //INTERESTRATEMODEL_HPP
