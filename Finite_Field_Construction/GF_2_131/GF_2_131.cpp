//
// Created by kkoog on 2018/10/5.
//

#include "GF_2_131.h"


vector<bool> GF_2_131::and_BIT(vector<bool> a, vector<bool> b) {
    vector<bool> result;
    if (a.size() == b.size()){
        vector<bool> _result(a.size(), false);
        for (int i = 0; i < a.size(); ++i) {
            _result[i] = a[i] & b[i];
        }
        result = _result;
    } else {
        vector<bool> h_deg;
        vector<bool> l_deg;
        if (a.size() > b.size()) {
            h_deg = a;
            l_deg = b;
        } else {
            h_deg = b;
            l_deg = a;
        }
        vector<bool> _result(h_deg.size(), false);
        for (int i = 0; i < h_deg.size(); ++i) {
            if (i < l_deg.size()) {
                _result[i] = h_deg[i] & l_deg[i];
            } else {
                _result[i] = h_deg[i] & 0;
            }
        }
        result = _result;
    }
    return result;
}

vector<bool> GF_2_131::xor_BIT(vector<bool> a, vector<bool> b) {
    vector<bool> result;
    if (a.size() == b.size()){
        vector<bool> _result(a.size(), false);
        for (int i = 0; i < a.size(); ++i) {
            _result[i] = a[i] ^ b[i];
        }
        result = _result;
    } else {
        vector<bool> h_deg;
        vector<bool> l_deg;
        if (a.size() > b.size()) {
            h_deg = a;
            l_deg = b;
        } else {
            h_deg = b;
            l_deg = a;
        }
        vector<bool> _result(h_deg.size(), false);
        for (int i = 0; i < h_deg.size(); ++i) {
            if (i < l_deg.size()) {
                _result[i] = h_deg[i] ^ l_deg[i];
            } else {
                _result[i] = h_deg[i] ^ 0;
            }
        }
        result = _result;
    }
    while (result.size() <= 260) {
        result.push_back(false);
    }
    return result;
}

vector<bool> GF_2_131::left_shift_BIT(vector<bool> a, int position) {
    vector<bool> result(a);
    int org_size = result.size() - 1;
    while (result.size() <= a.size() + position) {
        result.push_back(false);
    }
    if (position == 0) {
        return result;
    } else {
        for (int i = org_size; i >= 0; --i) {
            result[i + position] = result[i];
            result[i] = false;
        }
        return result;
    }
}

vector<bool> GF_2_131::right_shift_BIT(vector<bool> a, int position) {
    vector<bool> result(a);
    int org_size = a.size();
    while (result.size() <= a.size() + position) {
        result.push_back(false);
    }
    if (position == 0) {
        return  result;
    } else {
        for (int i = 0; i < org_size; ++i) {
            result[i] = result[i + position];
            result[i + position] = false;
        }
        return result;
    }
}

int GF_2_131::vector_degree(vector<bool> v){
    int deg = 0;
    for (int i = v.size() - 1; i >= 0; --i) {
        if (v[i] == true){
            deg = i;
            break;
        } else {
            continue;
        }
    }
    return deg;
}

void GF_2_131::refresh() {
    int deg = 0;
    for (int j = this->Polynomials.size() - 1; j >= 0; --j) {
        if (this->Polynomials[j] != 0) {
            deg = j;
            break;
        }
    }
    this->degree = deg;
    if (this->degree > POLY_MAX_DEGREE) {
        flag = false;
    } else {
        flag = true;
    }
}

GF_2_131::GF_2_131() {
    //init P(x) -> p(x) = x^131 + x^13 + x^2 + x + 1
    while (P_x.size() != P_x_DEGREE + 1){
        P_x.clear();
        for (int i = 0; i < P_x_DEGREE + 1; ++i) {
            if (i == 131 || i == 13 || i == 2 || i == 1 || i == 0){
                P_x.push_back(true);
            } else {
                P_x.push_back(false);
            }
        }
    }
    // No parameter: do nothing
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    // Refresh the data in subject:
    refresh();
}

GF_2_131::GF_2_131(int DEC_num) {
    //init P(x) -> p(x) = x^131 + x^13 + x^2 + x + 1
    while (P_x.size() != P_x_DEGREE + 1){
        P_x.clear();
        for (int i = 0; i < P_x_DEGREE + 1; ++i) {
            if (i == 131 || i == 13 || i == 2 || i == 1 || i == 0){
                P_x.push_back(true);
            } else {
                P_x.push_back(false);
            }
        }
    }
    //Change DEC number into BIN number and fill the vector<bool> ploy*
    int temp = DEC_num;
    vector<bool> t;
    while (temp >= 1) {
        t.push_back((bool)(temp % 2));
        temp /= 2;
    }
    this->Polynomials = t;
    // Fill the vector, length of pioys is at least 131
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    // Refresh the data & value in object:
    refresh();

}

GF_2_131::GF_2_131(int *index, int length) {
    //init P(x) -> p(x) = x^131 + x^13 + x^2 + x + 1
    while (P_x.size() != P_x_DEGREE + 1){
        P_x.clear();
        for (int i = 0; i < P_x_DEGREE + 1; ++i) {
            if (i == 131 || i == 13 || i == 2 || i == 1 || i == 0){
                P_x.push_back(true);
            } else {
                P_x.push_back(false);
            }
        }
    }
    // Fill polynomials with 0, length = max(array[])
    // Set the degree coffins in array "index" to 1
    sort(index, index + length);
    int max_degree = index[length - 1];
    while (this->Polynomials.size() <= max_degree) {
        this->Polynomials.push_back(false);
    }
    for (int j = 0; j < length; ++j) {
        this->Polynomials[index[j]] = true;
    }
    // Fill the vector, length of pioys is at least 131
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    // Refresh the data in subject:
    refresh();
}

GF_2_131::GF_2_131(vector<bool> p) {
    //init P(x) -> p(x) = x^131 + x^13 + x^2 + x + 1
    while (P_x.size() != P_x_DEGREE + 1){
        P_x.clear();
        for (int i = 0; i < P_x_DEGREE + 1; ++i) {
            if (i == 131 || i == 13 || i == 2 || i == 1 || i == 0){
                P_x.push_back(true);
            } else {
                P_x.push_back(false);
            }
        }
    }
    //the poly = p
    this->Polynomials = p;
    // Fill the vector, length of pioys is at least 131
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    // Refresh the data in subject:
    refresh();
}

void GF_2_131::add(GF_2_131 that) {
    // input can be any degree poly
    this->Polynomials = xor_BIT(this->Polynomials, that.Polynomials);
    //after add in GF(2^131), result has been operated by mod p(x)
    // mod p(x) -> degree < 131
    this->mod();
    refresh();
}

void GF_2_131::sub(GF_2_131 that) {
    this->add(that);
}

void GF_2_131::mod() {
    if (this->getDegree() < P_x_DEGREE) {
        return;
    } else {
        vector<bool> rest(this->Polynomials);
        int temp = 0;
        while (vector_degree(rest) >= P_x_DEGREE) {
            temp = vector_degree(rest) - P_x_DEGREE;
            vector<bool> t_v = left_shift_BIT(this->P_x, temp);
            //rest = left_shift_BIT(rest, temp);
            rest = xor_BIT(t_v, rest);
            int a = 0;
        }
        if (vector_degree(rest) <= POLY_MAX_DEGREE) {
            vector<bool> t;
            for (int i = 0; i < POLY_MAX_DEGREE + 1; ++i) {
                t.push_back(rest[i]);
            }
            this->Polynomials = t;
            refresh();
        }
    }
}

void GF_2_131::multip(GF_2_131 that) {
    vector<bool> temp;
    for (int i = that.getDegree(); i >= 0; --i) {
        if (that.Polynomials[i] == false) {
            continue;
        } else {
            vector<bool> m(this->Polynomials);
            m = left_shift_BIT(m, i);
            temp = xor_BIT(temp, m);
        }
    }
    this->setPolynomials(temp);
    if (vector_degree(temp) > POLY_MAX_DEGREE) {
        this->mod();
    }
    refresh();
}

void GF_2_131::inverse() {
    vector<bool> b(1, true);
    vector<bool> c(1, false);
    vector<bool> u = this->Polynomials;
    vector<bool> v = this->P_x;
    int temp;
    while (vector_degree(u) != 0) {
        temp = vector_degree(u) - vector_degree(v);
        if (temp < 0) {
            vector<bool> t = u;
            u = v;
            v = t;              // u <--> v
            t = b;
            b = c;
            c = t;              // b <--> c
            temp *= -1;            // j = -j
        }
        u = xor_BIT(u, left_shift_BIT(v, temp));
        b = xor_BIT(b, left_shift_BIT(c, temp));
    }
    this->setPolynomials(b);
    this->mod();
    refresh();
}

void GF_2_131::square() {
    GF_2_131 t(this->Polynomials);
    this->multip(t);
    refresh();
}

int GF_2_131::getDegree() {
    return this->degree;
}

vector<bool> GF_2_131::getPolynomials() {
    return this->Polynomials;
}

bool GF_2_131::getFlag() {
    return this->flag;
}

void GF_2_131::setPolynomials(int DEC_num) {
    int temp = DEC_num;
    vector<bool> t;
    while (temp >= 1) {
        t.push_back((bool)(temp % 2));
        temp /= 2;
    }
    this->Polynomials = t;
    // Fill the vector, length of pioys is at least 131
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    refresh();
}

void GF_2_131::setPolynomials(vector<bool> p) {
    this->Polynomials = p;
    // Fill the vector, length of pioys is at least 131
    while (this->Polynomials.size() < POLY_MAX_DEGREE + 1) {
        this->Polynomials.push_back(false);
    }
    refresh();
}

string GF_2_131::Poly_toString() {
    string ploy;
    if (this->degree == 0) {
        if (this->Polynomials[0] == 0) {
            ploy = "0";
        } else {
            ploy = "1";
        }
        return ploy;
    } else {
        if (this->Polynomials[0] == true){
            ploy += "1 + ";
        }
        if (this->Polynomials[1] == true) {
            ploy += "x + ";
        }
        for (int i = 2; i < this->Polynomials.size(); ++i) {
            if (this->Polynomials[i] != false){
                ploy += "x^";
                stringstream ss;
                ss << i;
                string temp;
                ss >> temp;
                ploy += temp;
                ploy += " + ";
            }
        }
    }
    if (ploy.substr(ploy.length() - 2, ploy.length()) == "+ "){
        ploy = ploy.substr(0, ploy.length() - 2);
    }
    return ploy;
}

string GF_2_131::P_x_toString() {
    string p = "x^131 + x^13 + x^2 + x + 1";
    return p;
}

void GF_2_131::printPoly_BIN() {
    for (int i = this->degree; i >= 0; --i) {
        cout << this->Polynomials[i];
    }
}