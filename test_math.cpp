#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    long long min_seconds = LLONG_MAX;
    long long max_val = min({a, b, c});

    // Try all possible target values
    for (long long target = 0; target < max_val; target++) {
        // Step 1: Find s such that (d + s) % a == target
        long long s1 = (target - d % a + a) % a;

        // Step 2: Now we have s = s1 + k1 * a
        // We need (e + (d + s) / a) % b == target
        // (e + (d + s1 + k1*a) / a) % b == target
        // (e + (d+s1)/a + k1) % b == target

        // Calculate how many minutes have passed with s1 seconds added
        long long mins_passed = (d + s1) / a;
        long long need_mins = (target - e % b + b) % b;

        // We need (mins_passed + k1) % b == need_mins
        // So k1 == (need_mins - mins_passed % b + b) % b
        long long k1 = (need_mins - mins_passed % b + b) % b;

        long long s2 = s1 + k1 * a;

        // Step 3: Now we have s = s2 + k2 * a * b
        // We need (f + (d + s) / (a*b)) % c == target
        long long hours_passed = (d + s2) / (a * b);
        long long need_hours = (target - f % c + c) % c;

        // We need (hours_passed + k2) % c == need_hours
        long long k2 = (need_hours - hours_passed % c + c) % c;

        long long s = s2 + k2 * a * b;

        // Verify the solution
        long long total = d + s;
        if (total % a == target &&
            (e + total / a) % b == target &&
            (f + total / (a * b)) % c == target) {
            min_seconds = min(min_seconds, s);
        }
    }

    cout << min_seconds << endl;
    return 0;
}
