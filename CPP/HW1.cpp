#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct DNA {
    std::string sequence;
    size_t inversion;
};

size_t calc_inv(const std::string& input) {

    size_t ans{};
    
    for(auto iter = input.begin(); iter != input.end(); ++iter) {
        for(auto ptr = (iter+1); ptr != input.end(); ++ptr) {
            if(*ptr < *iter) {
                ++ans;
            }
        }
    }

    return ans;
}

bool compare(const DNA& a, const DNA& b) { 
    return a.inversion < b.inversion; 
}

int main() {

    unsigned short length{},line{};
    std::cin >> length >> line;
    
    std::vector<DNA> data{};
    
    for(auto i = 0; i < line; ++i) {
        std::string input;
        std::cin >> input;
        
        data.push_back({input, calc_inv(input)});
    }
    
    std::sort(data.begin(), data.end(), compare);

    for(auto s: data) {
        std::cout << s.sequence << std::endl;
    }
}