#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

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
    std::sort(all.begin(), all.end());
    auto out_file = freopen("prepared.txt", "w", stdout);
    std::cout << "!!!!!!!!!!$!!!!!!!!!!" << std::endl;
    for (auto it = all.begin(); it < all.end(); ++it) {
        std::cout << *it << '\n';
    }
    std::cout << "~~~~~~~~~~$~~~~~~~~~~" << std::endl;
    fclose(out_file);

}