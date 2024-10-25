#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <strstream>
#include <vector>
#include "parser.h"
using namespace std;

string asmTemplateFirstHalf = "section .data\nfmt db \"The result is: %d\", 10, 0\nsection .text\nextern printf\nglobal main\nmain:\n";

string asmTemplateSecondHalf = "mov rdi, fmt\nmov rsi, rax\nmov rax, 0\ncall printf\nmov rax, 60\nmov rdx, 0\nsyscall";

void emit(Expr e) {
  if (e.right != nullptr) {
    Expr t = *e.right;
    ostrstream stream;

    switch (e.op) {
      case Plus:
	stream << "add rax, ";
	stream << t.value;
	stream << "\n";
	asmTemplateFirstHalf += stream.str();
	break;
      case Minus:
	stream << "sub rax, ";
	stream << t.value;
	stream << "\n";
	asmTemplateFirstHalf += stream.str();
	break;
      default:
	break;
    }

    emit(t);
  }
  return;
}

int main()
{
  string path = "index.maf";
  ifstream file(path);

  if (!file.is_open()) {
    cerr << "Failed to open file";
  }

  string line;
  getline(file, line);
  vector<Token> tokens = tokenize(line);

  Expr b = expr(tokens);
  ostrstream stream;
  stream << "mov rax, ";
  stream << b.value;
  stream << "\n";
  asmTemplateFirstHalf += stream.str();
  emit(b);

  ofstream generated("./out/app.asm");
  generated << asmTemplateFirstHalf + asmTemplateSecondHalf;
  generated.close();
}

