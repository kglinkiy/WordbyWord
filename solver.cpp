
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

#define ALPHABET_SIZE 33
const char ConsoleSample[ALPHABET_SIZE] = { -96, -95, -94, -93, -92, -91, -15, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -20, -21, -22, -19, -18, -17 };
const char FstreamSample[ALPHABET_SIZE] = { -32, -31, -30, -29, -28, -27, -72, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -4, -5, -6, -3, -2, -1 };

struct {
 unsigned child[ALPHABET_SIZE];
 bool isLeaf;
} node;
node NullNode = {NULL};

vector<node> Trie;
set<string> Res;
vector<string> Output;

void TrieAddWord(string &S) {
 unsigned CurrentNode(0);

 for (auto i(S.begin()); i != S.end(); ++i) {
  if (Trie[CurrentNode].child[*i] == 0) {
   Trie.push_back(NullNode);
   Trie[CurrentNode].child[*i] = Trie.size() - 1;
   CurrentNode = Trie.size() - 1;
  }
  else {
   CurrentNode = Trie[CurrentNode].child[*i];
  }
 }
 Trie[CurrentNode].isLeaf = true;
}

void EncodeString(string &S, const char Sample[]) {
 for (auto i(S.begin()); i != S.end(); ++i) {
  for (char j(0); j != ALPHABET_SIZE; ++j) {
   if (*i == Sample[j]) {
    *i = j;
    break;
   }
  }
 }
}

void LoadDictonary(char [id20019287|*Filename]) {
 ifstream in(Filename);
 string Buff;

 while (!in.eof()) {
  in » Buff;
  EncodeString(Buff, FstreamSample);
  TrieAddWord(Buff);
 }

 in.close();
}

bool cmp(string A, string B) {
 if (A.size() >= B.size()) {
  return false;
 }
 else return true;
}

void GuessWordBypass(unsigned N, __int8 X, bool Used[], string &S, string W, short &L) {
 if (W.size() > L) return;
 for (__int8 i(0); i != S.size(); ++i) {
  if (i == X) continue;
  if (!Used[i]) {
   if (Trie[N].child[S[i]] != 0) {
    Used[i] = true;
    GuessWordBypass(Trie[N].child[S[i]], i, Used, S, W + S[i], L);
    Used[i] = false;
   }
  }
  if (Trie[N].isLeaf && W.size() == L) {
   Res.insert(W);
  }
 }
}

void GuessWord(string &S, short &L) {
 bool *Used = new bool [S.size()];
 memset(Used, 0, S.size());
 for (__int8 i(0); i != S.size(); ++i) {
  if (Trie[0].child[S[i]] != 0) {
   Used[i] = true;
   GuessWordBypass(Trie[0].child[S[i]], i, Used, S, S.substr(i, 1), L);
   Used[i] = false;
  }
 }
 delete [] Used;
}

void WordsmaniaCheatBypass(unsigned N, __int8 X, bool Used[], string &S, string W) {
 __int8 TransitDenied[13] = {0};

 for (__int8 i(-2); i <= 2; i += 2)
 TransitDenied[i + 6] = true;

  for (__int8 i(-3); i <= 3; i += 3)
 TransitDenied[i + 6] = true;

 if (X % 5 == 0)
 for (__int8 i(-6); i <= 4; i += 5)
 TransitDenied[i + 6] = true;

 if (X < 5)
 for (__int8 i(-6); i <= -4; ++i)
 TransitDenied[i + 6] = true;

 if (X % 5 == 4)
 for (__int8 i(-4); i <= 6; i += 5)
 TransitDenied[i + 6] = true;

 if (X >= 20)
 for (__int8 i(4); i <= 6; ++i)
 TransitDenied[i + 6] = true;

 for (__int8 i(-6); i <= 6; ++i) {
 if(TransitDenied[i + 6]) continue;

 __int8 tmp = X + i;
 if (!Used[tmp]) {
 if (Trie[N].child[S[tmp]] != 0) {
 Used[tmp] = true;
 WordsmaniaCheatBypass(Trie[N].child[S[tmp]], tmp, Used, S, W + S[tmp]);
 Used[tmp] = false;
 }
 }
 if (Trie[N].isLeaf) {
 Res.insert(W);
 }
 }
}

void WordsmaniaCheat(string &S) {
 bool Used[25] = {0};
 for (__int8 i(0); i != 25; ++i) {
  if (Trie[0].child[S[i]] != 0) {
   Used[i] = true;
   WordsmaniaCheatBypass(Trie[0].child[S[i]], i, Used, S, S.substr(i, 1));
   Used[i] = false;
  }
 }
}

int main() {
 Trie.push_back(NullNode);
 LoadDictonary("Dictonary.txt");

 string Word;
 char mode;

 while (true) {
  cin » mode;
  switch (mode) {
  case '1':
   short L;
   cin » Word » L;
   EncodeString(Word, ConsoleSample);
   GuessWord(Word, L);
   break;
  case '2':
   cin » Word;
   EncodeString(Word, ConsoleSample);
   WordsmaniaCheat(Word);
   break;
  }
  cout « "==================" « endl;

  for (auto i(Res.begin()); i != Res.end(); ++i) {
   Output.push_back(*i);
  }
  Res.clear();
  if(mode == '2') sort(Output.begin(), Output.end(), cmp);
  for (auto i(Output.begin()); i !=Output.end(); ++i) {
   for (auto j((*i).begin()); j != (*i).end(); ++j) {
    cout « ConsoleSample[*j];
   }
   cout « endl;
  }
  cout « "==================" « endl « endl;
  Output.clear();
 }

 return 0;
}
