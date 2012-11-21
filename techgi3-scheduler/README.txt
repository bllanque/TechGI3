Technische Grundlagen der Informatik 3 - Systemprogrammierung
Aufgabe 3


In diesem Archiv finden Sie das Testprogramm und eine leere
C-Datei für jedes zu implementierende Schedulingverfahren
(Round Robin fuer t=1s und t=3s sind in einer gemeinsamen Datei zu finden).
Die Dateien FIFO.c, SJN.c, RR.c und RR_MLF.c (freiwillig) sind zu ergaenzen.
Die anderen Dateien sollen nicht verändert werden.

Damit das Testprogramm erkennen kann, welche der Verfahren
bereits implementiert sind, ändern Sie bitte den
Rückgabewert der Funktion init_XX auf 1.



Im cs-Netz des IRB kann das Programm direkt nach dem
Entpacken mit

 > make

übersetzt werden. Zum Starten führen Sie

 > ./scheduler

bzw.

 > make run

aus.



Die Vorgabe enthält diesmal keine weiterführenden
Abhängigkeiten und sollte mit jedem C-Compiler unabhängig
vom Betriebssystem übersetzt werden können. Evtl. müssen
Sie mit dem Befehl

 > make depend

im Makefile die Abhängigkeiten an ihr System anpassen.

Nachdem Sie jedes Verfahren implementiert haben und jeweils den
Rückgabewert der Funktion init_XX angepasst haben,
wird für alle Verfahren eine Statistik angezeigt.

Folgende Fehlermeldungen könnte das Testprogramm ausgeben:
Fehler innerhalb der Funktionstests:
ERROR!!! Scheduler switched to invalid task id (X)!

  Der Scheduler hat zu einer TaskID gewechselt, die niemals angemeldet wurde.
  Falls X=-1 könnte es sein, dass der Scheduler keinen Task ausgewählt hat,
  obwohl es noch laufbereite Tasks gibt.

ERROR!!! Scheduler switched to task X, but task Y has arrived earlier!

  Bei FIFO: Task X wurde ausgewählt, obwohl Task Y vorher angemeldet wurde.


ERROR!!! Scheduler switched to task X, but task Y hasn't finished yet!

  Bei FIFO: Task X wurde ausgewählt, obwohl Task Y noch nicht fertig ist.


ERROR!!! Scheduler switched to task X, but task Y is shorter!

  Bei SJN: Die Task sollen in der falschen Reihenfolge ausgeführt werden. Task Y
  ist kürzer als Task X und muss daher vor X laufen.


ERROR!!! Scheduler ran the same Task (X) twice!

  Bei RR: Der Scheduler hat zwei mal hintereinander in unterschiedlichen
  Zeitscheiben den selben Task ausgewählt.


ERROR!!! Task X had more cpu time than task Y!

  Die Rechenzeit, die Task X zugeteilt wurde, unterscheidet sich um mehr als
  delta von der Rechenzeit von Task Y.


ERROR!!! Task XX is still running but should have finished by now!

  Tritt im Fifo-Test aus, wenn ein Task nach seiner Beendigung weiterläuft.


Fehler innerhalb der zufällig generierten Tests:

semantic test: seems to be not implemented - check return value of init_XX

  Diese Meldung erscheint immer, wenn Sie ein Verfahren
  noch nicht als implementiert gekennzeichnet haben. Ändern
  Sie den Rückgabewert der Funktion init_XX um die
  Tests für das Verfahren XX freizugeben.


ERROR!!! All tasks should have been finished now(X)!!!

  Zum Zeitpunkt X sollten alle Tasks abgearbeitet sein.


ERROR in strategie XX!!! task Y could run now!

  Der Scheduler XX liefert keinen Task zurueck, obwohl noch zu
  bearbeitende Tasks offen sind.


ERROR in strategie XX!!! More tasks terminated than started!

  Der Scheduler hat insgesamt zu viele tasks zurueckgegeben.


ERROR in strategie XX!!! Computing time and length of task Y don't match!

  Die Rechenzeit, die der Task y brauchte,
  entspricht nicht seiner urspruenglichen Laenge.


ERROR in strategie XX!!! Tried to run a task (Y), that has already finished!

  Es ist ein Task aktiv, der seine Arbeit bereits beendet hatte.


ERROR in strategie XX!!! starting time(Y) + ... doesn't match actual time-step Z!

  Aufsummiert muessen Startzeit, Wartezeit und Rechenzeit stets
  dem aktuellen Simulationsschritt entsprechen.
