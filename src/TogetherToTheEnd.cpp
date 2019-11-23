#include <iostream>
#include <cstring>
#include <fstream>

int r_solve(const std::string &a, const std::string &b, std::string &c, int i, int j, int k);

void solve(const std::string &a, const std::string &b, std::string &c, std::ofstream &output);

int dp[1001][1001];

int main() {
    std::string infile, outfile;
    std::cout << "Enter name of input file: ";
    std::cin >> infile;
    std::cout << "Enter name of output file: ";
    std::cin >> outfile;

    std::ifstream input(infile);
    std::ofstream output(outfile);
    if (input.is_open()) {
        std::string a, b, c;
        while (std::getline(input, a) && std::getline(input, b) && std::getline(input, c)) {
            solve(a, b, c, output);
        }
    }
}

void solve(const std::string &a, const std::string &b, std::string &c, std::ofstream &output) {
    memset(dp, -1, sizeof(dp));
    if (r_solve(a, b, c, 0, 0, 0)) {
        int i = 0, j = 0, k = 0;
        while ((i < a.size() || j < b.size()) && k < c.size()) {
            if (i < a.size() && dp[i + 1][j] == 1) c[k++] = toupper(a[i++]);
            else {
                j++;
                k++;
            }
        }
        output << c << std::endl;
    } else {
        output << "*** NOT A MERGE ***" << std::endl;
    }
}


int r_solve(const std::string &a, const std::string &b, std::string &c, int i, int j, int k) {
    if (dp[i][j] != -1) return dp[i][j];
    int &ret = dp[i][j];
    if (i >= a.size() && j >= b.size() && k >= c.size()) {
        return ret = 1;
    }
    ret = 0;
    if (i < a.size() && a[i] == c[k]) {
        ret = ret | r_solve(a, b, c, i + 1, j, k + 1);
    }
    if (j < b.size() && b[j] == c[k]) {
        ret = ret | r_solve(a, b, c, i, j + 1, k + 1);
    }
    return ret;
}