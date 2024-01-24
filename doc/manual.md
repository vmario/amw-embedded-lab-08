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

Celem zadania podstawowego jest włączenie trybu XXXXXXXXXXXX

## Wymagania funkcjonalne

1. Po dwóch sekundach odliczanie zatrzymuje się, a procesor przechodzi w stan XXXXXXXXx

Na wyświetlaczu jest widoczna jedna cyfra z powodu zatrzymania multipleksowania wyświetlacza siedmiosegmentowego.

## Modyfikacja programu

Implementacja algorytmu wymaga zadeklarowania statycznej tablicy o rozmiarze, który najlepiej określić stałą, używaną dalej w algorytmie:

```cpp
constexpr uint8_t SIZE = 20;
static double measures[SIZE];
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Zmienne statyczne i globalne domyślnie inicijalizowane są zerami.}

\begin{algorithm}
\caption{Średnia krocząca $SMA_{size}$}
\begin{algorithmic}[1]
    \State $measures_{index}\gets \Call{adc.temperature}$
    \Comment{zapis bieżącego pomiaru}
    \State $sum \gets 0$
    \For{$i \gets 0$ to $size$}
    \Comment{sumowanie wszystkich $size$ ostatnich pomiarów}
        \State $sum \gets sum + measures_i$
    \EndFor
    \State $index\gets index + 1$
    \Comment{obliczamy kolejny indeks w tablicy $measures$}
    \If{$index \geq size$}
    \Comment{pilnujemy, by nie przekroczyć rozmiaru tablicy}
        \State $index\gets 0$
    \EndIf
    \State \Return {$\frac{sum}{size}$}
    \Comment{zwracamy średnią}
\end{algorithmic}
\end{algorithm}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest wstępne inicjalizacja średniej pierwszym pomiarem.

## Wymagania funkcjonalne

1. Urządzenie od razu po uruchomieniu wskazuje bieżącą temperaturę.

## Modyfikacja programu

Po uruchomieniu urządzenia tablica pomiarów powinna zostać wypełniona wartością pierwszego pomiaru.
