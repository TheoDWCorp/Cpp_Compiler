#ifndef FOO_PARSER
#define FOO_PARSER

void test_ta();
unordered_map<string,int> create_map_index_column(vector<vector<string>> table_analyse);
void test_resd();
string getAction(vector<vector<string>> table_analyse,string element, string state);
int get_length_reduction(int index_reduction);
string get_res_reduction(int index_reduction);
string getAction(vector<vector<string>> table_analyse,string element, int state);
vector<string> getExpected(vector<vector<string>> table_analyse,int state);
#endif // TEST
