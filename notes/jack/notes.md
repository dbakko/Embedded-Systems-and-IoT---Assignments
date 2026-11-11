# Appunti registrazione 17 Settembre

## Architettura

I microcontrollori hanno tutto sullo stesso chip (System on Chip): hanno la cpu, memoria RAM, ROM, DACs, timers, ...
Questo permette di avere dispositivi anche molto piccoli.

La `CPU` di arduino UNO ha 32 registri general-purpose a [8bit] e lavora a [16Mhz]. È l'ATMega328P (questo e' il microcontrollore!).
Abbiamo [14 pin] per l'I\O digitale e [6 pin] per gli input analogici.
È un processore RISC.
C'è un registro speciale a 16 bit usato per gestire gli indirizzi di memoria (da 2KiB).

> [!NOTE]
> I registri sono mappati nella memoria SRAM del microcontrollore!
> Per accedere ai registri quindi devi accedere a una particolare area di memoria (all'inizio della SRAM)

In generale i microcontrollori lavorano a 5V o 3.3V (due famiglie). Questo significa che il valore HIGH su un pin sta a 5V o 3.3V.
Questi dispositivi consumano pochissima corrente: circa 40mA.

Ovviamente non c'è nessun tipo di Sistema Operativo!
Semplicemente uploadi il tuo programma (già compilato) e lui esegue quello.

Scriviamo in C/C++ perchè così il codice è portabile su altri microcontrollori (la cui architettura può cambiare, ...).
E poi è un livello di astrazione più alto rispetto Assembly.

Architettura Von Neumann (Fetch, decode, Execute, `Check Interrupt` (process it)):
Il microcontrollore dell'Arduino UNO è collegato tramite bus alla memoria flash (memoria persistente) su cui carichiamo i programmi e la SRAM (che e' quella volatile).
Nella memoria flash c'e' anche il `boot loader` che e' del codice che permette all'arduino di trovare il programma che ha caricato nella flash (se c'è) e caricarlo nella SRAM.
Se il programma non c'è allora si mette ad ascoltare la Serial line per vedere se qualcuno glielo carica.

### Architettura Harvard

Più precisamente questi microcontrollori usano l'architettura `Harvard` che è una variante di quella di Von Neumann:
In questo caso sia i dati che le istruzioni sono memorizzati in aree di memoria fisicamente diverse e si usano Bus diversi.
Ad esempio solitamente il codice risiede nella memoria FLASH (lettura veloce ma scrittura lenta (tanto devo solo leggere il codice, lo scrivo solo una volta all'inizio)), invece i dati stanno in SRAM (lettura e scrittura veloci (costi più alti e richiede più energia))

> [!NOTE]
> Anche nei computer di oggi si ha una architettura simile ma non fisicamente...
> Infatti la memoria virtuale che è gestita dal Sistema Operativo è organizzata in pagine che di solito sono divise tra pagine data e code.
> Questo semplifica la gestione della sicurezza (non puoi scrivere nelle pagine code...)

> [!NOTE]
> Oltre alla SRAM in arduino UNO c'è anche la EEPROM (piccola, solo 1 kilobyte) che è persistente invece (usata per un particolare tipo di dati (?)).

Abbiamo una memoria molto limitata, quindi usala con parsimonio.

## SUPERLOOP Architecture

Prima si esegue l'setup() e poi si esegue loop() all'infinito.
È come avere:
```c
int main(void){
    setup();
    while(true){
        loop();
        // arduino a questo punto fa anche un check per vedere se c'e' qualcosa sulla Serial Line
        // per questo motivo non devi assolutamente fare una funzione loop che non termina mai, altrimenti non viene mai checkata la Serial Line.
    }
}
```

* Pro:
    * Semplice;
    * Reliable;
* Cons:
    * timing non accurato (se fai il polling all'inizio del loop e il loop è molto grosso potresti perderne qualcuno);
    * alto consumo di potenza (vedremo come metterlo in sleep);

## GPIO

Ci sono 14 pin che possono essere usati sia per l'input che per l'output digitale (general purpose).
Puoi scrivere HIGH o LOW oppure leggere HIGH o LOW (o il CHANGE).

Poi ci sono 6 pin per l'input (SOLO INPUT) analogico.
Qui puoi settare un voltaggio tra 0 a 5V.

Ogni pin può anche avere funzionalità aggiuntive.

Ci sono dei registri apposta nell'ATMega328P che ti permettono di settare un dato pin come INPUT o OUTPUT e altri che ti permettono di leggere/scrivere su questi pin.
Noi non arriveremo mai a questo livello, useremo semplicemente le funzioni `pinMode()` (setta la direzione del pin, INPUT o OUTPUT), `digitalWrite()` (scrive HIGH o LOW su un pin), `digitalRead()` (legge se il pin è in HIGH o LOW).

### Esempio blinkare un LED:
```c
    #define LED_PIN 13 //e' il LED builtin

    void setup(){
        pinMode(LED_PIN, OUTPUT);
    }

    void loop(){
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_PIN, LOW);
        delay(1000);
    }
```

> [!IMPORTANT]
> `delay()` fa busy waiting, non è come la sleep di java che è una system call che chiede al sistema operativo di mettere in pausa il programma senza così fare busy waiting.

> [!NOTE]
> ricorda che quando fai `millis()` ti mostra il numero di millisecondi da quando è partito Arduino.

### Esempio Button-LED
Un bottone per l'input e un LED per l'output
![Button-LED](./ButtonLED.png)

Il bottone è collegato da una parte a vcc (5V), dall'altra a un pin di INPUT.
Quando clicco il bottone si chiude il circuito e nel pin di INPUT leggo HIGH (vcc, 5V).

All'inizio nel setup() setuppo gli input e gli output. Nel loop all'inzio pollo lo stato del pin di INPUT.
Se e' HIGH scrivo nel pin di OUTPUT HIGH, viceversa se è LOW scrivo in output (led) LOW.

Attenzione che il polling all'inzio può percepire uno stato che magari cambia istantaneamente dopo ma ormai per un loop intero rimane quello che hai rilevato all'inizio.

## Pin (multiplexed) Functions

Alcuni pin hanno ulteriori funzioni uniche:
Ad esempio i pin 2 e 3 possono gestire interrupt...

## Pin analogici
I pin analogici leggono valori da 0 a 5V. Vanno dal pin A0 al pin A5.
I valori che leggi tramite `analogRead(int PIN)` sono da 0 a 1023 (quindi 1024 valori).
Questo perchè Arduino UNO usa un Analog/digital Converter a 10bit di risoluzione.
Il convertitore prende il valore continuo da 0 a 5V e lo converte in un numero a 10bit.

## Serial Line

Utile per il logging.
L'arduino può comunicare con il computer tramite la Serial Line del cavo USB.
Per fare ciò l'arduino e il computer devono mettersi d'accordo su un baud rate in modo da leggere i bit che si scambiano in modo sincrono.

> [!NOTE]
> Anche lui consiglia di fare anche un test delle componenti (come pensavamo noi con test.cpp).

