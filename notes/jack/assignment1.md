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
