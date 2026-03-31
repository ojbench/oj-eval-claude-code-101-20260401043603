#include <iostream>
using namespace std;

int main() {
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    // a = seconds per minute
    // b = minutes per hour
    // c = hours per day
    // Current time: f hours, e minutes, d seconds

    long long seconds = 0;
    long long curr_d = d, curr_e = e, curr_f = f;

    // We need to find when curr_f == curr_e == curr_d
    while (true) {
        if (curr_f == curr_e && curr_e == curr_d) {
            break;
        }

        // Add one second
        seconds++;
        curr_d++;

        // Handle overflow
        if (curr_d >= a) {
            curr_d = 0;
            curr_e++;

            if (curr_e >= b) {
                curr_e = 0;
                curr_f++;

                if (curr_f >= c) {
                    curr_f = 0;
                }
            }
        }
    }

    cout << seconds << endl;
    return 0;
}
