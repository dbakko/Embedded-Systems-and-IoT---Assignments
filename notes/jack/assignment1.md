# Note per il primo assignment

Per stampare le stringhe usa:
```cpp
Serial.print("Ciao");
```

Prima devi avere impostato:
```cpp
Serial.begin(9600); //baud rate (servono per sincronizzare i bit sul canale)
```

You can pass flash-memory based strings to Serial.print() by wrapping them with F(). For example:
```cpp
Serial.print(F("Hello World"))
```

> [!NOTE]
> A cosa serve la roba qui sopra?

Dichiarare una variabile `static` dentro una funzione fa si che quella variabile venga dichiarata solo alla prima chiamata e poi rimane il valore della chiamata precedente.
L'ho utilizzata in core.cpp

---

## Architettura

Guardando il codice qui: `https://github.com/pslab-unibo/esiot-2026-2027/blob/master/lab-activities/lab-activity-03/superloop_interrupt_example/`:
`react.ino` deve restare il più semplice possibile.
Ci metti solo uno switch che a seconda dello stato in cui ci si trova chiama una funzionalità di `core.cpp` (`kernel.h` gestisce i cambiamenti tra stati).
Gli stati possibili sono definiti in `core.h`; in `core.cpp` sono definite le operazioni da svolgere (funzioni da chiamare) nel caso ci si trovi in un qualche stato.
Il modulo input è abbastanza auto esplicativo... gestisce il potenziometro e i buttons in questo caso
Il modulo output è usato per azionare i led (anche il display?)

> [!NOTE]
> per attivare la modalità debug (stampa messaggi nel serial monitor) scommenta la riga in kernel.h

