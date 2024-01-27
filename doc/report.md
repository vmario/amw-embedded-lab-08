---
title: "Ćwiczenie 8: Tryby oszczędzania energii w mikrokontrolerze"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usetikzlibrary{positioning}
...

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

W jakich trybach można wykorzystać _Timer2_ do wyjścia ze stanu uśpienia?

\awesomebox[violet]{2pt}{\faBook}{violet}{Podsumowanie trybów oszczędzania energii można znaleźć w rozdziale \textit{Power Management and Sleep Modes} w sekcji \textit{Sleep Modes} dokumentacji mikrokontrolera.}

\vspace{3cm}

Jakie peryferiały działają w każdym trybie?

\vspace{3cm}

## Zadanie rozszerzone

Jaki jest pobór prądu przez mikrokontroler działający w normalnym trybie (_Active Supply Current_) przy taktowaniu 16&nbsp;MHz i napięciu zasilania 5V?

\awesomebox[violet]{2pt}{\faBook}{violet}{Skorzystaj z sekcji \textit{ATmega328P Typical Characteristics} dokumentacji mikrokontrolera.}

\vspace{3cm}

Jaki jest pobór prądu przez mikrokontroler działający w trybie _Power-down_ (_Power-down Supply Current_) przy napięciu zasilania 5V w temperaturze pokojowej[^1]?

[^1]: Watchdog jest wyłączony (_Watchdog Timer Disabled_).

\vspace{3cm}

Ile razy włączenie trybu \textit{Power-down} może wydłużyć działanie urządzenia zasilanego z baterii?

\vspace{3cm}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

Dlaczego przy określonym napięciu zasilania pobór prądu w normalnym trybie pracy zależy od częstotliwości taktowania, a w trybie _Power-down_ od temperatury?
