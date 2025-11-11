#include "Infor.h"

Infor::Infor(string Id, string name) : Id(Id), name(name) {}

string Infor::getId() const { return Id; }
string Infor::getName() const { return name; }

Infor::~Infor() {}
