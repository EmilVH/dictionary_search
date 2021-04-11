
#ifndef FINDINDICT_FINDER_H
#define FINDINDICT_FINDER_H

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <thread>
#include <mutex>

class Finder {
private:
    char splitter_char_ = '$';
    int check_word_(const std::string &word, const std::string &pattern);

    std::string extract_string_(long long pos);

    std::string reconstruct_string_(long long pos);

    long long find_left_border_(const std::string &pattern);

    long long find_right_border_(const std::string &pattern);

    std::thread finder_;
    std::mutex mutex_;
    std::vector<std::string> ans_;
    int last_extracted_ = 0;
    bool closed_ = false;
    std::ifstream processed;

    void find_pattern_in_dictionary_(const std::string &pattern);

public:
    explicit Finder(const std::string &filename);

    std::shared_ptr<std::string> get_next();

    void insert_new_pattern(const std::string &pattern);

    void stop_finding();


};


#endif //FINDINDICT_FINDER_H
