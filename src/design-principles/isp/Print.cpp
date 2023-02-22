//
// Created by HRF on 2023/2/22.
// P17
// 接口隔离：将复杂的接口分离为多个单独的接口，以避免强制实现者必须实现某些他们实际上并不需要的接口
//

#include <vector>

using namespace std;

struct Document;


struct IPrinter {
    virtual void print(vector<Document *> docs) = 0;
};

struct IScanner {
    virtual void scan(vector<Document *> docs) = 0;
};

struct IFax {
    virtual void fax(vector<Document *> docs) = 0;
};

struct Printer : IPrinter {
    void print(vector<Document *> docs) override {};
};

struct Scanner : IScanner {
    void scan(vector<Document *> docs) override {};
};

struct Fax : IFax {
    void fax(vector<Document *> docs) override {};
};


struct IMachine : IPrinter, IScanner, IFax {
};

struct Machine : IMachine {
    IPrinter &printer;
    IScanner &scanner;
    IFax &faxer;

    Machine(IPrinter &printer, IScanner &scanner, IFax &faxer) : printer{printer}, scanner{scanner}, faxer{faxer} {};

    void print(vector<Document*> docs) override {
        printer.print(docs);
    }

    void scan(vector<Document*> docs) override {
        scanner.scan(docs);
    }

    void fax(vector<Document*> docs) override {
        faxer.fax(docs);
    }
};

struct MyFavouritePrinter : IMachine {
    void print(vector<Document *> docs) override {};

    void fax(vector<Document *> docs) override {};

    void scan(vector<Document *> docs) override {};
};
