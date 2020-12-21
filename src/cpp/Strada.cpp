#include"Strada.h"
#include<iostream>
Strada::Strada() : _contatore(0)
{
    std::random_device generatore;
    std::normal_distribution<double> gaussiana(20,10);
    do
    {
        _lunghezza = (short)gaussiana(generatore);
    }
    while(_lunghezza <= 5);
}  
Strada::Strada(int contatore) : _contatore(contatore)
{
    std::random_device generatore;
    std::normal_distribution<double> gaussiana(20,10);
    do
    {
        _lunghezza = (short)gaussiana(generatore);
    }
    while(_lunghezza <= 5);
}
Strada::Strada(Strada const& strada) : _contatore(strada._contatore), _lunghezza(strada._lunghezza){}
short Strada::contatore() const { return _contatore; }
short Strada::lunghezza(){return _lunghezza;}
void Strada::aggiungi_macchina() { _contatore++; }
void Strada::togli_macchina() { _contatore--; }
