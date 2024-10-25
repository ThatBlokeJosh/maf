#include <regex>
#include <string>
#include <vector>
using namespace std;

enum TokenType {
  Number,
  Plus,
  Star,
  Minus,
  Empty,
};

struct Token {
  string value;
  TokenType type;
};

class Lexeme {
  public:
    string expression;
    TokenType token;

    Lexeme(string expression, TokenType token) {
      this->expression = expression;
      this->token = token;
    }

    Token match(string line) {
      regex r(this->expression); 
      smatch m;

      regex_search(line, m, r);

      for(auto v: m) {
	if (v.length() > 0) {
	  return {v, this->token};
	}
      }
      return {"", Empty};
    }
};

vector<Lexeme> lexemes = {
  {"^\\d[\\d ]*", Number},
  {"^[+][ ]*", Plus},
  {"^[-][ ]*", Minus},
  {"^[*][ ]*", Star},
};


vector<Token> tokenize(string line) {
  vector<Token> tokens = {};

  int it = line.length(); 
  while (it > 0) {
    for (int i = 0; i < lexemes.size(); ++i) {
      string subLine = line.substr(line.length() - it);
      Token token = lexemes[i].match(subLine);
      it -= token.value.length();
      if (token.type != Empty) {
	tokens.push_back(token);
	break;
      }
    }
  }

  return tokens;
}
