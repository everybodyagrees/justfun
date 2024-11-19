#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find and print the LCS
string lcs(const string &s1, const string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Create a 2D vector to store lengths of LCS suffixes
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build the dp array in bottom-up manner
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Now, reconstruct the LCS from dp array
    int index = dp[m][n];
    string lcs_seq(index, ' '); // string to store LCS sequence

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_seq[index - 1] = s1[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs_seq;
}

int main() {
    string s1, s2;

    // Take input from the user
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    // Get the LCS and its length
    string lcs_seq = lcs(s1, s2);
    int lcs_length = lcs_seq.size();

    cout << "Length of LCS: " << lcs_length << endl;
    cout << "LCS sequence: " << lcs_seq << endl;

    return 0;
}
