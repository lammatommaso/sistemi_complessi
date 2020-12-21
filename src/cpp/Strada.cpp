#include"Strada.h"
#include<iostream>
Strada::Strada() : _contatore(0)
{
    std::random_device generatore;
    std::normal_distribution<double> gaussiana(media_gaussiana,sigma_gaussiana);
    do
    {
        _lunghezza = (short)gaussiana(generatore);
    }
    while(_lunghezza <= lunghezza_minima || _lunghezza > lunghezza_massima);
}  
Strada::Strada(short contatore) : _contatore(contatore)
{
    std::random_device generatore;
    std::normal_distribution<double> gaussiana(media_gaussiana,sigma_gaussiana);
    do
    {
        _lunghezza = (short)gaussiana(generatore);
    }
    while(_lunghezza <= lunghezza_minima || _lunghezza > lunghezza_massima);
    //if(_contatore == -1)
    //    _lunghezza = 0;
}
Strada::Strada(Strada const& strada) : _contatore(strada._contatore), _lunghezza(strada._lunghezza){}
short Strada::contatore() const { return _contatore; }
short Strada::lunghezza(){return _lunghezza;}
void Strada::aggiungi_macchina() { _contatore++; }
void Strada::togli_macchina() { _contatore--; }
