#include "HandEvaluator.h"
#include <algorithm>
#include <map>

using namespace std;

HandEvaluator::HandResult
HandEvaluator::evaluate(const vector<Card>& player,
                        const vector<Card>& community) {

    vector<Card> all = player;
    all.insert(all.end(), community.begin(), community.end());

    sort(all.begin(), all.end(), [](Card a, Card b){
        return a.value > b.value;
    });

    map<int, int> freq;
    for (auto& c : all) {
        freq[c.value]++;
    }

    bool flush = isFlush(all);
    bool straight = isStraight(all);

    int pairs = 0, three = 0, four = 0;
    for (auto& f : freq) {
        if (f.second == 2) pairs++;
        else if (f.second == 3) three++;
        else if (f.second == 4) four++;
    }

    HandResult result{0, {}};


    if (straight && flush) {
        map<int, int> suits;
        int suitIndex = -1;

        for (auto& c : all) {
            suits[c.suit]++;
            if (suits[c.suit] >= 5) {
                suitIndex = c.suit;
            }
        }

        if (suitIndex != -1) {
            vector<int> vals;

            for (auto& c : all) {
                if (find(vals.begin(), vals.end(), c.value) == vals.end() && c.suit == suitIndex) {
                    vals.push_back(c.value);
                }
            }

            sort(vals.begin(), vals.end(), [](int a, int b){
                return a > b;
            });

            int count = 1;
            int k = -1;

            for (size_t j = 0; j + 1 < vals.size(); j++) {
                if (vals[j] == vals[j + 1] + 1) {
                    count++;
                    if (count >= 5) {
                        k = j;
                        break;
                    }
                } else {
                    count = 1;
                }
            }

            if (k >= 4) {
                result.rank = 9;
                for (int j = k - 4; j <= k; j++) {
                    result.values.push_back(vals[j]);
                }
                return result;
            }
        }
    }


    else if (four) {
        result.rank = 8;
        for (auto& f : freq) {
            if (f.second == 4) {
                result.values.push_back(f.first);
                break;
            }
        }
    }

    else if (three && pairs) {
        result.rank = 7;
        for (auto& f : freq) {
            if (f.second == 3) {
                result.values.push_back(f.first);
                break;
            }
        }
    }


    else if (flush) {
        result.rank = 6;
        map<int, int> suits;
        int suitIndex = 0;

        for (auto& c : all) {
            suits[c.suit]++;
            if (suits[c.suit] >= 5) {
                suitIndex = c.suit;
                break;
            }
        }

        for (auto& c : all) {
            if (c.suit == suitIndex) {
                result.values.push_back(c.value);
                if (result.values.size() >= 5) break;
            }
        }
    }


    else if (straight) {
        result.rank = 5;
        vector<int> storage;

        for (auto& c : all) {
            if (find(storage.begin(), storage.end(), c.value) == storage.end()) {
                storage.push_back(c.value);
            }
        }

        sort(storage.begin(), storage.end(), greater<int>());

        int count = 1;
        int k = -1;

        for (size_t j = 0; j + 1 < storage.size(); j++) {
            if (storage[j] == storage[j + 1] + 1) {
                count++;
                if (count >= 5) {
                    k = j;
                    break;
                }
            } else {
                count = 1;
            }
        }

        if (k >= 4) {
            for (int j = k - 4; j <= k; j++) {
                result.values.push_back(storage[j]);
            }
        }
    }


    else if (three) {
        result.rank = 4;
        int tripleValue = 0;

        for (auto& f : freq) {
            if (f.second == 3) {
                tripleValue = f.first;
            }
        }

        result.values.push_back(tripleValue);

        for (auto& c : all) {
            if (c.value != tripleValue) {
                result.values.push_back(c.value);
                if (result.values.size() == 3) break;
            }
        }
    }


    else if (pairs == 2) {
        result.rank = 3;
        vector<int> pairValue;

        for (auto& f : freq) {
            if (f.second == 2) {
                pairValue.push_back(f.first);
            }
        }

        sort(pairValue.begin(), pairValue.end(), greater<int>());

        result.values.push_back(pairValue[0]);
        result.values.push_back(pairValue[1]);

        for (auto& c : all) {
            if (c.value != pairValue[0] && c.value != pairValue[1]) {
                result.values.push_back(c.value);
                break;
            }
        }
    }

    else if (pairs == 1) {
        result.rank = 2;
        int pairValue = 0;

        for (auto& f : freq) {
            if (f.second == 2) {
                pairValue = f.first;
            }
        }

        result.values.push_back(pairValue);

        for (auto& c : all) {
            if (c.value != pairValue) {
                result.values.push_back(c.value);
                if (result.values.size() == 4) break;
            }
        }
    }
    else {
        result.rank = 1;
        for (auto& c : all) {
            result.values.push_back(c.value);
            if (result.values.size() == 5) break;
        }
    }

    return result;
}
bool HandEvaluator::isFlush(const vector<Card>& cards) {
    map<int, int> suitCount;

    for (auto& c : cards) {
        suitCount[c.suit]++;
        if (suitCount[c.suit] >= 5) {
            return true;
        }
    }
    return false;
}

bool HandEvaluator::isStraight(const vector<Card>& cards) {
    vector<int> vals;

    for (auto& c : cards) {
        if (find(vals.begin(), vals.end(), c.value) == vals.end()) {
            vals.push_back(c.value);
        }
    }

    sort(vals.begin(), vals.end());

    int count = 1;
    for (int i = 0; i < vals.size() - 1; i++) {
        if (vals[i] == vals[i + 1] - 1) {
            count++;
            if (count >= 5) return true;
        } else {
            count = 1;
        }
    }

    return false;
}