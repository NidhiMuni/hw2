#include "user.h"
using namespace std;

#include <iomanip>

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
  //added setprecition
    os << name_ << " "  << std::setprecision(2) << setiosflags(ios::fixed) << balance_ << " " << type_ << endl;
}
