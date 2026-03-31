#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    // a = seconds per minute
    // b = minutes per hour
    // c = hours per day
    // Current time: f hours, e minutes, d seconds

    long long min_seconds = LLONG_MAX;
    long long max_val = min({a, b, c});

    // Try all possible target values where all three pointers could align
    for (long long target = 0; target < max_val; target++) {
        // We need to find s such that:
        // (d + s) % a == target
        // (e + (d + s) / a) % b == target
        // (f + (d + s) / (a*b)) % c == target

        // Start with seconds constraint: (d + s) % a == target
        // So s = target - d (mod a)
        long long s_base;
        if (target >= d) {
            s_base = target - d;
        } else {
            s_base = a + target - d;
        }

        // Now iterate through values s = s_base + k*a for various k
        // and check if both minute and hour conditions are satisfied
        // Maximum we need to check is a*b*c seconds (one full cycle)
        long long max_check = a * b * c;

        for (long long s = s_base; s < max_check; s += a) {
            long long total_sec = d + s;
            long long sec_display = total_sec % a;
            long long min_display = (e + total_sec / a) % b;
            long long hour_display = (f + total_sec / (a * b)) % c;

            if (sec_display == target && min_display == target && hour_display == target) {
                min_seconds = min(min_seconds, s);
                break;  // Found for this target, no need to check further
            }
        }
    }

    cout << min_seconds << endl;
    return 0;
}
