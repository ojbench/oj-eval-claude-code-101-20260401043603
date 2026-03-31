#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    long long min_seconds = LLONG_MAX;
    long long max_val = min({a, b, c});

    // For each possible target value that all three could display
    for (long long target = 0; target < max_val; target++) {
        // Calculate minimum seconds needed for seconds pointer to show 'target'
        long long s_for_sec;
        if (target >= d) {
            s_for_sec = target - d;
        } else {
            s_for_sec = a - d + target;
        }

        // Now enumerate values s = s_for_sec + k*a until we find one where
        // minutes and hours also show 'target'
        // We only need to check up to b*c iterations (worst case)
        for (long long k = 0; k < b * c; k++) {
            long long s = s_for_sec + k * a;
            long long total = d + s;

            long long min_val = (e + total / a) % b;
            long long hour_val = (f + total / (a * b)) % c;

            if (min_val == target && hour_val == target) {
                min_seconds = min(min_seconds, s);
                break; // Found earliest for this target
            }
        }
    }

    cout << min_seconds << endl;
    return 0;
}
