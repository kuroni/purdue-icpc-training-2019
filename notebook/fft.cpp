const int LG = 19, MX = 1 << LG;
const double PI = acos(-1);

int reverse_bit(int u) {
    int ans = 0;
    for (int i = 0; i < LG; i++) {
        (ans <<= 1) ^= (u >> i & 1);
    }
    return ans;
}

struct polynomial {
    vector<complex<double>> f;

    polynomial(int _len = 0, int _val = 0) {
        f = vector<complex<double>>(_len, _val);
    }

    polynomial fft(bool inv = false) {
        polynomial ans(MX, 0);
        if (inv) {
            reverse(f.begin() + 1, f.end());
        }
        for (int i = 0; i < f.size(); i++) {
            ans.f[reverse_bit(i)] = f[i];
        }
        for (int len = 1; len < MX; len += len) {
            complex<double> rt(cos(PI / len), sin(PI / len));
            for (int i = 0; i < MX; i += 2 * len) {
                complex<double> w(1, 0);
                for (int j = 0; j < len; j++) {
                    complex<double> u = ans.f[i + j], v = ans.f[i + j + len];
                    ans.f[i + j] = u + w * v;
                    ans.f[i + j + len] = u - w * v;
                    w *= rt;
                }
            }
        }
        if (inv) {
            reverse(f.begin() + 1, f.end());
            for (complex<double> &v : ans.f) {
                v /= MX;
            }
        }
        return ans;
    }

    polynomial operator*(const polynomial &oth) const {
        polynomial ans(MX);
        for (int i = 0; i < MX; i++) {
            ans.f[i] = f[i] * oth.f[i];
        }
        return ans;
    }

    long long coefficient(int pos) {
        return round(abs(f[pos]));
    }
};
