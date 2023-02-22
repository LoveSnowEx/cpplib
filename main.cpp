#include "list/list.hpp"
#include <cstdio>
#include <list>
#include <random>
#include <cassert>

void testList() {
    size_t size = 10'000;
    using std::list;
    list<int> a;
    List<int> b;
    std::random_device rd;
    std::uniform_int_distribution<int> numGen(-1000, 1000);
    std::uniform_int_distribution<int> actionGen(0, 1000);
    for(int i = 0; i < size; ++i) {
        int num = numGen(rd);
        printf("(%d) push: %d\n", i, num);
        a.push_back(num);
        b.pushBack(num);
    }

    printf("size: %d, %d\n", a.size(), b.size());
    if(a.size() != b.size()) {
        printf("error: size not equal\n");
        exit(1);
    }
    // return;

    int testTimes = size / 2;

    for(int i = 0; i < testTimes; ++i) {
        auto ita = a.begin();
        auto itb = b.begin();
        int action = actionGen(rd);
        int num = numGen(rd);
        switch(action%8) {
        case 0:
            a.push_front(num);
            b.pushFront(num);
            break;
        case 1:
            a.pop_front();
            b.popFront();
            break;
        case 2:
            a.push_back(num);
            b.pushBack(num);
            break;
        case 3:
            a.pop_back();
            b.popBack();
            break;
        case 4:
            for(int j = 0; j < num; ++j) {
                if(++ita == a.end()) {
                    ++ita;
                }
                if(++itb == b.end()) {
                    ++itb;
                }
            }
            break;
        case 5:
            for(int j = 0; j < num; ++j) {
                if(--ita == a.end()) {
                    --ita;
                }
                if(--itb == b.end()) {
                    --itb;
                }
            }
            break;
        case 6:
            a.insert(ita, num);
            b.insert(itb, num);
            break;
        case 7:
            a.erase(ita);
            b.erase(itb);
            break;
        default:
            break;
        }
        if(a.size() != b.size()) {
            printf("act: %d\n", action%8);
            printf("size: %d, %d\n", a.size(), b.size());
            printf("error: size not equal\n");
            exit(1);
        }
    }

    printf("size: %d, %d\n", a.size(), b.size());
    if(a.size() != b.size()) {
        printf("error: size not equal\n");
        exit(1);
    }

    auto ita = a.begin();
    auto itb = b.begin();
    for(; ita != a.end() && itb != b.end(); ++ita, ++itb) {
        if(*ita != *itb) {
            printf("error: val equal\n");
            exit(1);
        }
    }
}

int main() {
    testList();
    return 0;
}