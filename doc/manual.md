---
title: "Ćwiczenie 8: Tryby oszczędzania energii w mikrokontrolerze"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
...

> First, solve the problem. Then, write the code.
>
> — _John Johnson_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* trybami oszczędzania energii,
* aktywowaniem oszczędzania energii,
* wychodzeniem z trybu oszczędzania energii.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Wyświetlacz odlicza wartości począwszy od `0000`.

# Zadanie podstawowe

Celem zadania podstawowego jest włączenie trybu oszczędzania energii _Power-down_.

## Wymagania funkcjonalne

1. Po dwóch sekundach odliczanie zatrzymuje się, a procesor przechodzi w stan _Power-down_.
1. Przed przejściem procesora w stan _Power-down_ gaszony jest wyświetlacz.

Ponowne uruchomienie systemu możliwe jest po wciśnięciu przycisku `RESET`. Odliczanie zaczyna się jednak wtedy znów od wartości `0`.

## Modyfikacja programu

Mikrokontroler przechodzi w stan oszczędzenia energii (uśpienia) po wywołaniu instrukcji `SLEEP`, zgodnie z konfiguracją rejestru `SMCR`.

Odczytaj w opisie rejestru `SMCR`, jakie bity należy ustawić przed wywołaniem instrukcji `SLEEP`, aby wejść w tryb najgłębszego oszczędzania energii, czyli _Power-down_.

\awesomebox[teal]{2pt}{\faCode}{teal}{Instrukcję asemblerową \lstinline{SLEEP} wywołuje w C++ funkcja \lstinline{sleep_cpu()}.}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Mikrokontrolery posiadają na ogół wiele trybów oszczędzania energii, co pozwala pracować niektórym peryferiałom, a inne wyłączyć. Możliwe jest też wyłączenie niektórych elementów mikrokontrolera bez wchodzenia w tryb oszczędzenia energii.

W trybie \textit{Power-down} wyłączone są wszystkie sygnały zegarowe, dzięki czemu zużycie energii jest minimalne.}

Samo uśpienie procesora nie zawsze wystarcza, by znacząco zredukować zużycie energii. Należy także zadbać o wyłączenie innych elementów systemu mikroprocesorowego. W przypadku naszego urządzenia kluczowe jest zgaszenie wyświetlacza. Aby to zrobić, należy wysłać do rejestrów przesuwnych bajt wypełniony zerami, dzięki czemu segmenty zostaną wygaszone. Bajt sterujący poszczególnymi cyframi można wypełnić wartościami `1`, co też odpowiada wyłączeniu poszczególnych cyfr. Na koniec należy pamiętać o zatrzaśnięciu wpisanej wartości na wyjściach rejestrów przesuwnych:

```cpp
shifter.shift(0xff); // Segmenty.
shifter.shift(0x00); // Cyfry.
shifter.latch(); // Zatrzask.
```

Procedurę usypiania umieść w funkcji `shutdown()`. Odmierzanie opóźnienia 2 sekund możesz zrealizować za pomocą funkcji bibliotecznej `_delay_ms()`. Pamiętaj, że jej użycie wymaga dołączenia odpowiedniego pliku nagłówkowego:

\begin{lstlisting}[language=c++]
#include <util/delay.h>
\end{lstlisting}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest wyjście z trybu oszczędzania energii za pomocą przerwania.

## Wymagania funkcjonalne

1. Po wciśnięciu przycisku _S1_ procesor kontynuuje odliczanie.
1. Po dwóch sekundach od wybudzenia procesor ponownie się usypia.

## Modyfikacja programu

Wznowienie działania nie jest możliwe z poziomu samego programu, gdyż jego wykonywanie jest wstrzymane. W trybie _Power-down_ oscylator taktujący rdzeń procesora i peryferiały takie jak timery są całkowicie wyłączone, więc jedynym sposobem na interakcję z mikrokontrolerem jest dostarczenie sygnału ze świata zewnętrznego, np. w postaci impulsu na pinie wejściowym.

Impuls ten musi być, oczywiście, obsłużony przez przerwanie, gdyż pętla główna jest zatrzymana i nie można jej użyć do sprawdzania stanu wejścia.

Aby włączyć przerwanie od przycisku `S1` należy w funkcji `gpioInitialize()` włączyć przerwanie `PCINT1` dla wejścia `PCINT9`[^1]:

```cpp
PCMSK1 |= _BV(PCINT9);
PCICR |= _BV(PCIE1);
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Pamiętaj o zdefiniowaniu procedury obsługi przerwania \lstinline{PCINT1_vect}, gdyż domyślna obsługa przerwania resetuje procesor.}

[^1]: Tak, w tym mikrokontrolerze `PCINT` raz oznacza przerwanie od GPIO, a raz pin wywołujący to przerwanie…
