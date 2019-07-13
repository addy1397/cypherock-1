#ifndef RECOVER_H
#define RECOVER_H

#include "Share.h"
#include "constants.h"
#include "gf256.h"

class Recover{
    small xcor[MAX_SHARES];
    small ycor[MAX_SHARES];
    small denominatorXcor[MAX_SHARES];
    small numberOfMnemonics;
    small product;
    small sum;
    small shares[MAX_SHARES];

public:
    void setXcor(small xcor[]);
    void setYcor(small ycor[]);
    void setNumberOfMnemonics(small numberOfMnemonics);
    void setProduct();
    void generateShares();
    void setDenominatorXcor();
    void displayRecoveredShares();
};

void recoverShares(small xcor[],small ycor[],small numberOfMnemonics);
#endif