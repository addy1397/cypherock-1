#include <Arduino.h>
#include "../include/recover.h"

void Recover::setNumberOfMnemonics(small numberOfMnemonics){
    this->numberOfMnemonics=numberOfMnemonics;
    this->setProduct();
}
void Recover::setXcor(small xcor[])
{
    for(int i=0;i<numberOfMnemonics;i++)
        this->xcor[i]=xcor[i];
}
void Recover::setYcor(small ycor[])
{
    for(int i=0;i<numberOfMnemonics;i++)
        this->ycor[i]=ycor[i];
}

void Recover::setProduct()
{
    this->product=1;
    for(small i=0;i<numberOfMnemonics;i++)
        this->product=multiply(this->product,xcor[i]);
}

void Recover::setDenominatorXcor()
{
    for(small i=0;i<numberOfMnemonics;i++)
        denominatorXcor[i]=1;
    for(small i=0;i<numberOfMnemonics;i++)
    {
        for(small j=0;j<numberOfMnemonics;j++)
        {
            if(i!=j)
            {
                denominatorXcor[i]=multiply(denominatorXcor[i],subtract(xcor[i],xcor[j]));
            }
        }
    }
}
void Recover::generateShares(){
    
    for(small i=0;i<numberOfMnemonics;i++)
    {
        this->shares[i]=divide(product,xcor[i]);
        if(numberOfMnemonics%2==0)
        {
            this->product=subtract(256,this->product); //in case of odd xcor -1 gets introduced
        }
        this->shares[i]=divide(this->shares[i],this->denominatorXcor[i]);
    }
}

void Recover::displayRecoveredShares(){
    Serial.println("Shares produced are : ");
    for(small i=0;i<this->numberOfMnemonics;i++){
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(this->shares[i]);
    }
}

void recoverShares(small xcor[],small ycor[],small numberOfMnemonics){
	/*
	* Recover shares
	* This order is to be followed
	*/
	Recover recover;
	recover.setNumberOfMnemonics(numberOfMnemonics); //before set x-cor is called
	recover.setXcor(xcor);
	recover.setYcor(ycor);
	recover.setProduct();
	recover.setDenominatorXcor();
	recover.generateShares();
    recover.displayRecoveredShares();
}