#include "Macchina.h"

Macchina::Macchina() : _passi(0), _passi_locali(0), _destinazione_raggiunta(false)
{
    if(ritardo_massimo != 0)
    {
        srand(time(NULL));
        _ritardo = rand()%ritardo_massimo;
    }
    else
    {
        _ritardo = 0;
    }
}
Macchina::Macchina(short passi) : _passi(passi),_passi_locali(0), _destinazione_raggiunta(false),_ritardo(0){}
Macchina::Macchina(Macchina const& macchina) : _passi(macchina._passi), _passi_locali(macchina._passi_locali), _destinazione_raggiunta(macchina._destinazione_raggiunta),_ritardo(macchina._ritardo) {}
void Macchina::passo_avanti() { _passi++; _passi_locali++; std::cout<<_passi;}
void Macchina::reset_passi_locali(){ _passi_locali = 0; }
void Macchina::riduci_ritardo(){_ritardo--;}
void Macchina::set_destinazione_raggiunta(bool raggiunta){ _destinazione_raggiunta = raggiunta;}
bool Macchina::destinazione_raggiunta()const{return _destinazione_raggiunta;}
short Macchina::ritardo()const{return _ritardo;};
short Macchina::passi()const{return _passi; }
short Macchina::passi_locali()const{return _passi_locali;}


