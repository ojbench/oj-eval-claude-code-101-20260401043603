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
        // (d + s) % a == target         ... (1)
        // (e + (d + s) / a) % b == target   ... (2)
        // (f + (d + s) / (a*b)) % c == target ... (3)

        // From (1): s ≡ (target - d) (mod a)
        // Let s = s1 + k1 * a for some k1 >= 0
        long long s1 = (target - d + a) % a;

        // Substitute into (2):
        // (e + (d + s1 + k1*a) / a) % b == target
        // (e + (d + s1)/a + k1) % b == target
        long long base_min = (d + s1) / a;
        // (e + base_min + k1) % b == target
        // k1 ≡ (target - e - base_min) (mod b)
        long long k1 = ((target - e - base_min) % b + b) % b;

        // So s = s1 + k1*a + k2*a*b for some k2 >= 0
        long long s2 = s1 + k1 * a;

        // Substitute into (3):
        // (f + (d + s2 + k2*a*b) / (a*b)) % c == target
        // (f + (d + s2)/(a*b) + k2) % c == target
        long long base_hour = (d + s2) / (a * b);
        // k2 ≡ (target - f - base_hour) (mod c)
        long long k2 = ((target - f - base_hour) % c + c) % c;

        long long s = s2 + k2 * a * b;

        // Verify
        long long total_sec = d + s;
        long long sec_display = total_sec % a;
        long long min_display = (e + total_sec / a) % b;
        long long hour_display = (f + total_sec / (a * b)) % c;

        if (sec_display == target && min_display == target && hour_display == target) {
            min_seconds = min(min_seconds, s);
        }
    }

    cout << min_seconds << endl;
    return 0;
}
