
#include "Finder.h"

int Finder::check_word_(const std::string &word, const std::string &pattern) {
    for (size_t i = 0; i < std::max(word.length(), pattern.length()); ++i) {
        if (i >= pattern.length()) {
            return 0;
        }
        if (word[i] == splitter_char_) {
            return -1;
        }
        if (word[i] < pattern[i]) {
            return -1;
        }
        if (word[i] > pattern[i]) {
            return 1;
        }
    }
}

std::string Finder::extract_string_(long long int pos) {
    processed.seekg(pos, std::ifstream::beg);
    std::string res;
    processed >> res >> res;
    size_t splitter_pos = 0;
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == splitter_char_) {
            splitter_pos = i;
            break;
        }
    }
    return res.substr(0, splitter_pos);
}

std::string Finder::reconstruct_string_(long long int pos) {
    processed.seekg(pos, std::ifstream::beg);
    std::string res;
    processed >> res >> res;
    size_t splitter_pos = 0;
    if (res.length() == 0) {
        return res;
    }
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == splitter_char_) {
            splitter_pos = i;
            break;
        }
    }
    return res.substr(splitter_pos + 1, res.length()).append(res.substr(0, splitter_pos));
}

long long Finder::find_left_border_(const std::string &pattern) {
    processed.seekg(0, std::ifstream::beg);
    long long l = processed.tellg();
    processed.seekg(0, std::ifstream::end);
    long long r = processed.tellg();
    while (r - l > 1) {
        long long m = (r + l) / 2;
        int check_res = check_word_(extract_string_(m), pattern);
        if (check_res >= 0) {
            r = m;
        }
        if (check_res < 0) {
            l = m;
        }
    }
    return r;
}

long long Finder::find_right_border_(const std::string &pattern) {
    processed.seekg(0, std::ifstream::beg);
    long long l = processed.tellg();
    processed.seekg(0, std::ifstream::end);
    long long r = processed.tellg();
    while (r - l > 1) {
        long long m = (r + l) / 2;
        int check_res = check_word_(extract_string_(m), pattern);
        if (check_res <= 0) {
            l = m;
        }
        if (check_res > 0) {
            r = m;
        }
    }
    return l;
}

void Finder::find_pattern_in_dictionary_(const std::string &pattern) {
    if (pattern.length() == 0) {
        closed_ = true;
        return;
    }
    long long l = find_left_border_(pattern);
    long long r = find_right_border_(pattern);
    std::unordered_set<std::string> added; //TODO make generator
    for (long long i = l; i <= r; ++i) {
        if (closed_) { return; }
        std::string extracted = reconstruct_string_(i);
        if (added.insert(extracted).second) {
            std::unique_lock<std::mutex> lk(mutex_);
            ans_.push_back(extracted);
            lk.unlock();
        }
    }
    closed_ = true;
}

std::shared_ptr<std::string> Finder::get_next() {
    while (!closed_) {
        std::unique_lock<std::mutex> lk(mutex_);
        if (last_extracted_ < ans_.size()) {
            auto ret = std::make_shared<std::string>(ans_[last_extracted_]);
            last_extracted_++;
            return ret;
        }
        lk.unlock();
    }
    stop_finding();
    return nullptr;
}

void Finder::insert_new_pattern(const std::string &pattern) {
    last_extracted_ = 0;
    closed_ = false;
    finder_ = std::thread(&Finder::find_pattern_in_dictionary_, this, pattern);
}

Finder::Finder(const std::string &filename) {
    processed.open(filename);
}

void Finder::stop_finding() {
    closed_ = true;
    if (finder_.joinable()) {
        finder_.join();
    }
    ans_.clear();
    last_extracted_ = 0;
}
