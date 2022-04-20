#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

int CharInt(int N, char c, vector <char> mnojestvo) {
    for (int i = 0; i < N; i++)
    {
        if (mnojestvo[i] == c)
            return i;
    }
}

bool proverka_Ass(int N, char** keli, vector <char> mnojestvo) {
    bool prov = true;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            for (int z = 0; z < N; z++)
            {
                if (keli[x][CharInt(N, keli[y][z], mnojestvo)] != keli[CharInt(N, keli[x][y], mnojestvo)][z])
                    prov = false;
            }
        }
    }
    return prov;
}

bool true_elems(vector <char> X_i, vector <char> X_i_next) {
    if (X_i.size() != X_i_next.size())
        return true;
    else {
        for (int j = 0; j < X_i.size(); j++) {
            if (X_i[j] != X_i_next[j])
                return true;
        }
    }
    return false;
}

bool unique_elem(vector <char> ch, char elem) {
    for (int j = 0; j < ch.size(); j++) {
        if (elem == ch[j])
            return false;
    }
    return true;
}

void postr_podpol(int N, vector <char> mnojestvo, int M, vector <char> X, char** keli) {
    int i = 0;
    vector <char> X_i;
    vector <char> X_i_next;
    vector <char> X_dop;
    vector <char> X_res;
    for (int j = 0; j < M; j++) {
        X_i.push_back(X[j]);
        X_res.push_back(X[j]);
        X_i_next.push_back(X[j]);
    }
    for (int j = 0; j < X_i.size(); j++) {
        for (int k = 0; k < X_i.size(); k++) {
            char x_y = keli[CharInt(N, X_i[j], mnojestvo)][CharInt(N, X_i[k], mnojestvo)];
            if (unique_elem(X_dop, x_y)) {
                X_dop.push_back(x_y);
            }
        }
    }
    for (int j = 0; j < X_dop.size(); j++) {
        if (unique_elem(X_res, X_dop[j])) {
            X_res.push_back(X_dop[j]);
        }
        if (unique_elem(X_i_next, X_dop[j])) {
            X_i_next.push_back(X_dop[j]);
        }
    }

    int sch = 1;
    while (true_elems(X_i, X_i_next) || sch == 1) {
        sch = 0;
        X_i.clear();
        for (int j = 0; j < X_i_next.size(); j++) {
            X_i.push_back(X_i_next[j]);
        }
        X_dop.clear();
        for (int j = 0; j < X_i.size(); j++) {
            for (int k = 0; k < X_i.size(); k++) {
                int x_y = keli[CharInt(N, X_i[j], mnojestvo)][CharInt(N, X_i[k], mnojestvo)];
                if (unique_elem(X_dop, x_y)) {
                    X_dop.push_back(x_y);
                }
            }
        }
        for (int j = 0; j < X_dop.size(); j++) {
            if (unique_elem(X_i_next, X_dop[j])) {
                X_i_next.push_back(X_dop[j]);
            }
        }
        for (int j = 0; j < X_i_next.size(); j++) {
            if (unique_elem(X_res, X_i_next[j])) {
                X_res.push_back(X_i_next[j]);
            }
        }
        sort(X_res.begin(), X_res.end());
        if (X_res.size() == N) {
            for (int j = 0; j < X_res.size(); j++) {
                cout << X_res[j] << ", ";
            }
            break;
        }
    }
    for (int j = 0; j < X_res.size(); j++) {
        cout << X_res[j] << ", ";
    }
}

void proverka_1(int N, vector <char> mnojestvo, int M, vector <char> podmnojestvo, char** keli) {

    cout << endl;
    if (proverka_Ass(N, keli, mnojestvo) == true) {
        postr_podpol(N, mnojestvo, M, podmnojestvo, keli);
    }
    else
        cout << "Не ассоциативна" << endl;


}

bool unique_matr(vector < vector <int> >matrix_res, vector < vector < vector <int> > > res_all_matr) {
    for (int i = 0; i < res_all_matr.size(); i++)
    {
        if (matrix_res == res_all_matr[i])
            return false;
    }
    return true;
}

void second_bin(int N, vector < vector < vector <int> > > res_all_matr) {
    int razmer = res_all_matr.size();
    int dps = 0;
    while (res_all_matr.size() != razmer || dps == 0) {
        razmer = res_all_matr.size();
        dps = 1;
        for (int g_now = 0; g_now < razmer; g_now++)
        {
            for (int g = 0; g < razmer; g++)
            {
                vector < vector <int> >  matrix_res;
                vector <int> s(N, 0);
                for (int jh = 0; jh < N; jh++)
                {
                    matrix_res.push_back(s);
                }
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        for (int k = 0; k < N; k++) {
                            if (res_all_matr[g_now][i][k] == 1 && res_all_matr[g][k][j] == 1) {
                                matrix_res[i][j] = 1;
                                break;
                            }
                        }
                    }
                }
                if (unique_matr(matrix_res, res_all_matr)) {
                    res_all_matr.push_back(matrix_res);
                }
            }
        }
    }
    cout << "Получаем: " << endl;
    for (int g = 0; g < res_all_matr.size(); g++)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << res_all_matr[g][i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
}

bool unique_word(string A_i, vector <string> s_predst) {
    for (int i = 0; i < s_predst.size(); i++)
    {
        if (A_i == s_predst[i])
            return false;
    }
    return true;
}

void third_sootn(int T, vector <string> A, int R, vector < pair < string, string > > relations) {
    vector <string> s_predst;
    //длина слова = 1
    for (int i = 0; i < T; i++)
    {
        if (unique_word(A[i], s_predst)) {

        }
    }
}

bool unique_word_on_pair(string word, vector < pair < string, string > > relations, string& sec_pair) {
    for (int i = 0; i < relations.size(); i++)
    {
        if (word == relations[i].first) {
            sec_pair = relations[i].second;
            return false;
        }
    }
    return true;
}

vector<string> word_vector(string word)
{
    vector<string> convert_word;
    for (int i = 0; i < word.size(); ++i)
        convert_word.push_back(word.substr(i, 1));

    return(convert_word);
}

vector <string> S;

void th_alg(string& word, vector <string>& A_ofr, int& max_w, string& new_word, string& rec_word, vector < pair < string, string > >& relations)
{
    if (!unique_word(word, A_ofr))
        return;

    vector<string> word_now = word_vector(word);

    int sch = 2;
    while (sch <= max_w)
    {
        for (int i = word_now.size() - 1; i >= 0; --i)
        {
            if (sch > word.size() || sch > i + 1)
                break;
            int j;
            string f_part = "";
            for (j = i; j > i - sch; --j)
                f_part = word_now[j] + f_part;
            string s_pair = "";
            if (!unique_word_on_pair(f_part, relations, s_pair))
            {
                rec_word = "";
                vector<string> part_ = word_vector(s_pair);

                for (int k = 0; k < j; ++k)
                    rec_word = rec_word + word_now[k];

                rec_word = rec_word + s_pair;

                for (int k = i + 1; k < word_now.size(); ++k)
                    rec_word = rec_word + word_now[k];

                if (rec_word.size() < word.size())
                {
                    A_ofr.push_back(word);
                    A_ofr.push_back(rec_word);
                    return;
                }
                else if (!unique_word(rec_word, A_ofr))
                    return;
                else
                    th_alg(rec_word, A_ofr, max_w, new_word, rec_word, relations);
            }
            if (!unique_word(word, A_ofr))
                return;
        }
        sch++;
    }

    if (rec_word.size() == word.size() && rec_word < word && unique_word(word, A_ofr) && unique_word(rec_word, A_ofr))
    {
        S.push_back(rec_word);
        A_ofr.push_back(word);
        A_ofr.push_back(rec_word);
        return;
    }

    S.push_back(word);
    A_ofr.push_back(word);
    A_ofr.push_back(rec_word);
    return;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    vector <char> mnojestvo;
    vector <char> podmnojestvo;
    vector <string> A;
    vector <string> A_ofr;
    vector < vector < vector <int> > > all_matr;
    vector < vector < vector <int> > > res_all_matr;
    int sposob, i, j, N, M, T, matr_count, R_count, R;
    int max_w = 0;
    cout << "Введите, что хотите сделать: " << endl;
    cout << "1 - построение подполугрупп по таблице Кэли" << endl;
    cout << "2 - построение полугруппы бинарных отношений по заданному порождающему множеству" << endl;
    cout << "3 - построение полугруппы по порождающему множеству и определяющим соотношениям" << endl;
    cin >> sposob;

    if (sposob == 1)
    {

        cout << "Введите размерность полугруппы: " << endl;
        cin >> N;
        if (N == 0) {
            cout << "Ошибка";
            return 0;
        }
        cout << "Введите множество для полугруппы S: " << endl;
        char vv;
        for (int i = 0; i < N; i++) {
            cin >> vv;
            mnojestvo.push_back(vv);
        }
        char** keli;
        keli = new char* [N];
        cout << "Таблица Кэли полугруппы S: " << endl;
        for (int i = 0; i < N; i++) {
            keli[i] = new char[N];
            for (int j = 0; j < N; j++) {
                cin >> keli[i][j];
            }
        }
        cout << "Введите размерность подмножества: " << endl;
        cin >> M;
        if (M == 0) {
            cout << "Ошибка";
            return 0;
        }
        cout << "Введите подмножество X: " << endl;
        char podvv;
        for (int i = 0; i < M; i++) {
            cin >> podvv;
            podmnojestvo.push_back(podvv);
        }
        proverka_1(N, mnojestvo, M, podmnojestvo, keli);
    }
    else if (sposob == 2)
    {
        cout << "Введите размерность : " << endl;
        cin >> N;
        if (N == 0) {
            cout << "Ошибка";
            return 0;
        }
        cout << "Количество матриц : " << endl;
        cin >> matr_count;
        if (matr_count == 0) {
            cout << "Ошибка";
            return 0;
        }
        for (int l = 0; l < matr_count; l++)
        {
            cout << "Введите матрицу бинарного отношения №" << l + 1 << ": " << endl;
            vector < vector <int> > matrix1(N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int vvod_ch;
                    cin >> vvod_ch;
                    matrix1[i].push_back(vvod_ch);
                }
            }
            res_all_matr.push_back(matrix1);
        }

        second_bin(N, res_all_matr);
    }
    else if (sposob == 3) {
        cout << "Введите количество символов в алфавите A: " << endl;
        int T;
        cin >> T;
        cout << "Введите конечное множество символов А (алфавит): " << endl;
        string vvod_A;
        for (int i = 0; i < T; i++) {
            cin >> vvod_A;
            A.push_back(vvod_A);
            S.push_back(vvod_A);
            A_ofr.push_back(vvod_A);
        }
        cout << "Введите количество пар в определяющем соотношении R: " << endl;
        int R_count;
        cin >> R_count;
        vector < pair < string, string > > relations;
        relations.resize(R_count);
        cout << "Введите определяющее соотношение R (так: R1 R2): " << endl;
        for (int i = 0; i < R_count; i++) {
            string vvod_R1;
            string vvod_R2;
            cin >> vvod_R1 >> vvod_R2;
            if (vvod_R1.size() > max_w)
                max_w = vvod_R1.size();
            if (vvod_R2.size() > max_w)
                max_w = vvod_R2.size();
            if (vvod_R1.size() < vvod_R2.size())
                relations.push_back(make_pair(vvod_R2, vvod_R1));
            else if (vvod_R1.size() > vvod_R2.size())
                relations.push_back(make_pair(vvod_R1, vvod_R2));
            else
            {
                if (vvod_R1 < vvod_R2)
                    relations.push_back(make_pair(vvod_R2, vvod_R1));
                else
                    relations.push_back(make_pair(vvod_R1, vvod_R2));
            }
        }
        int len = 1;
        vector <string>  dop_A;
        dop_A = A;
        string new_word;
        string rec_word;
        while (!dop_A.empty())
        {
            ++len;
            for (int i = 0; i < dop_A.size(); i++)
            {
                string word_w = dop_A[i];
                for (int i = 0; i < A.size(); i++)
                {
                    string let = A[i];
                    string word_w_let = word_w + let;
                    rec_word = "";
                    th_alg(word_w_let, A_ofr, max_w, new_word, rec_word, relations);
                }
            }
            dop_A.clear();
            for (int i = 0; i < S.size(); i++)
            {
                if (S[i].size() == len)
                    dop_A.push_back(S[i]);
            }
        }

        cout << "Полная система представителей: S = { ";
        for (int i = 0; i < S.size(); i++)
        {
            cout << S[i] << " ";
        }
        cout << " }" << endl;
    }
    else
        cout << "Ошибка" << endl;

    cout << endl;
}
