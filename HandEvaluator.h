#pragma once

#include <vector>
#include "Card.h"

class HandEvaluator {
public:
    struct HandResult {
        int rank;
        std::vector<int> values;
    };

    static HandResult evaluate(const std::vector<Card>& player,
                               const std::vector<Card>& community);

private:
    static bool isFlush(const std::vector<Card>& cards);
    static bool isStraight(const std::vector<Card>& cards);
};