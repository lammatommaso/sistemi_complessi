//NOTA: per semplicità tutti e soli gli incroci hanno i semafori

#define rosso false
#define verde true

class Macchina {
  private
    List<Nodo> percorso; //es. 1 - 10: 1, 3, 5, 8, 2, 10
    Nodo[] strada_attuale = Nodo[2];
    //int velocità, offset; ...
    int passi; //aumenta di 1 tutte le volte che faccio un passo - cioè puoi_attraversare == true
    int cicli_persi; //aumenta di 1 tutte le volte che perdo un ciclo - cioè puoi_attraversare == false
    //consideriamo il rapporto passi/(passi + cicli_persi)

  public
    void vai_avanti();
    /* avanza con l'offset OPPURE se siamo in fondo alla strada chiama
     * strada_attuale[1].vai_avanti()
     * vai_avanti(){
     *  if (puoi_attraversare(b,c))
     *    strada_attuale = (c,d)
     *  }
     * }
     */
};

interface Nodo { //template in C++?
  int nome;
  bool puoi_attraversare();
  /*
   * bool puoi_attraversare(int a, int b){
   *    if (this.incrocio() == true){
   *      sem.P();
   *      if (semaforo == verde)
   *          sem.v(); return true;
   *        else
   *          sem.V(); return false;
   *    }
   *  }
   * NOTA: il nodo potrebbe essere una semplice congiunzione tra due strade: ----o-----
   * in quel caso puoi_attraversare dovrebbe solo restituire b.sono_pieno()
  */
};

class Strada {
  Nodo inizio;
  Nodo fine;
  int lunghezza;
  //n_auto_attuale;
  //int limite_velocità,  ...
  //bool sono_pieno(){ return n_auto==lunghezza };
};

Semaphore sem; int semaforo;

List<Macchina> macchine;

/* Thread 1: thread per le macchine
 * le macchine sono nella lista delle macchine
 * questo thread è fatto tipo così:
 * while (true){
 *  for (macchina in macchine){
 *    macchina.vai_avanti();
 *  }
 * }
 *
 * Thread 2: thread per i semafori
 * while(true){
 *  sem.P()
 *  semaforo = rosso
 *  sem.V()
 *  sleep(1000)
 *  sem.P()
 *  semaforo = verde
 *  sem.V()
 *  sleep(1000)
 */

Strada[][] matrice_adiacenza = Strada[N][N];


/* Problema: le rotonde?
 * tipo 1:                            tipo 2:
 *      |                                |
 *      |                           ___./'\.____
 * -----o-----                          \./
 *      |                                |
 *      |
*/


//main
/*
 1. generare la città (matrice_adiacenza con le strade)

 2. generare la lista delle macchine e assegnare ad ognuna un percorso (random oppure ottimo)

 3. far partire il thread dei semafori stradali

 4. far partire il thread delle macchine


*/
