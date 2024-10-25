#include "lex.h"
#include <ios>
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <stdio.h> 
using namespace std;

struct Expr {
  int value;
  TokenType op;
  Expr* right;
};

int lookahead = 0;

void consume(vector<Token> tokens) {
  lookahead += 1;
}

bool isOp(TokenType type) {
  switch (type) {
    case Plus: 
    case Star:
    case Minus:
      return true;
      break;
    default:
      break;
  };
  return false;
}

Expr expr(vector<Token> tokens) {
  Expr e = {};
  switch (tokens[lookahead].type) {
    case Number:
      e.value = atoi(tokens[lookahead].value.c_str());
      consume(tokens);
      if (isOp(tokens[lookahead].type)) {
	e.op = tokens[lookahead].type;
	consume(tokens);
	e.right = new Expr(expr(tokens));
      }
      break;
    default:
      cerr << "TypeError" << endl;
      break;
  }
  return e;
}

