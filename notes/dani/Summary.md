# Summary  
  
**Componenti:**  
  
- Display  
- Bottone 1, led verde 1, led rosso 1  
- Bottone 2, led verde 2, led rosso 2  
- Potenziometro  
- Resistenze (per i led)  
  
**Fase pre-partita**  
  
1. Led verdi spenti, led rossi in fade alternativamente  
2. Sull’LCD scorre su una riga sola: *Welcome to the React! Game. Press Buttons to Start*  
3. Bisogna premere tutti e due Bottone 1 e Bottone 2 per cominciare la partita  
4. Se non viene fatto entro 10 secondi, Arduino va in deep sleep mode, si può risvegliare premendo b1 o b2  
5. Tramite potenziometro viene scelta la difficoltà del gioco in 4 livelli (1,2,3,4)  
  
**Fase partita cominciata**  
  
1. A partita cominciata, sull’LCD c’è scritto *Go!* e il punteggio di P1 e P2 è a zero (si dovrebbe trovare agli angoli bassi del display)  
2. Ad ogni round, i LED vengono spenti e l’LCD viene pulito, quindi parte un timer (gestito da un parametro chiamato MAX_WAIT) che identifica il tempo in cui appare il numero random N  
3. Quindi, ogni giocatore dovrà reagire entro un tempo T1, e premere il numero di volte il bottone corrispondente ad N (++dobbiamo in qualche modo gestire le concorrenze? Immagino che arduino riesca a leggere due input in contemporanea e quindi fare i “calcoli” in parallelo)++  
4. Se il giocatore indovina, si accende il led verde corrispondente per 2 secondi e il punteggio incrementa di 1  
5. Se il giocatore preme prima che il numero venga rivelato oppure lo preme non esattamente N volte, il suo LED diventa rosso per 2 secondi e il suo punteggio decremento sempre di 1  
6. Se nessun giocatore preme il bottone entro il tempo limite T1, il gioco va in stato “GAME OVER”, l’LCD recita *Game Over - The winner is XX* per 10 secondi (c’è anche il caso di pareggio, quindi XX può essere P1,P2,TIE), quindi si ricomincia dallo stato “prepartita”. (++Servirà forse una variabile “STATE” e una funzione per ogni stato di gioco?)++  
7. Alla fine di ogni round negli angoli del display c’è il punteggio di ciascun player  
8. Ad ogni round la difficoltà aumenta, perchè il tempo limite T1 viene decrementato di un parametro F che dipende dalla difficoltà selezionata tramite il potenziometro  
  
Accorgimenti  
  
1.  Dividere i parametri per tipologia: tempi, stati (del gioco), difficoltà, variabile che decremento il tempo  
2. Gestire la “concorrenza?”  
3. Si passa al round successivo sia che si indovina che si scazza  
