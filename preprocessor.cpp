//
// Created by vahna on 09.04.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include "Finder.h"

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    auto in_file = freopen("words.txt", "r", stdin);
    std::vector<std::string> all;
    std::string buffer;
    int counter = 0;
    while (std::cin >> buffer) {
        for (size_t i = 0; i < buffer.length(); ++i) {
            all.push_back(buffer.substr(i, buffer.length()).append("$").append(buffer.substr(0, i)));
        }
        counter++;
    }
    fclose(in_file);
    std::cerr << "started sorting" << std::endl;
    std::cerr << all.size() << std::endl;
    std::sort(all.begin(), all.end());
    std::cerr << "ended sorting" << std::endl;
    auto out_file = freopen("prepared.txt", "w", stdout);
    std::cout << "!!!!!!!!!!$!!!!!!!!!!" << std::endl;
    for (auto it = all.begin(); it < all.end(); ++it) {
        std::cout << *it << '\n';
    }
    std::cout << "~~~~~~~~~~$~~~~~~~~~~" << std::endl;
    fclose(out_file);
    /*Finder finder("prepared.txt");
    std::vector<std::string> ans;
    std::string pattern;
    std::cin >> pattern;
    finder.find_pattern_in_dictionary(pattern, ans);
    for (auto it = ans.begin(); it < ans.end(); it++) {
        std::cout << *it << std::endl;
    }*/

}