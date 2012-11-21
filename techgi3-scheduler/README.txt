Technische Grundlagen der Informatik 3 - Systemprogrammierung
Aufgabe 3


In diesem Archiv finden Sie das Testprogramm und eine leere
C-Datei f�r jedes zu implementierende Schedulingverfahren
(Round Robin fuer t=1s und t=3s sind in einer gemeinsamen Datei zu finden).
Die Dateien FIFO.c, SJN.c, RR.c und RR_MLF.c (freiwillig) sind zu ergaenzen.
Die anderen Dateien sollen nicht ver�ndert werden.

Damit das Testprogramm erkennen kann, welche der Verfahren
bereits implementiert sind, �ndern Sie bitte den
R�ckgabewert der Funktion init_XX auf 1.



Im cs-Netz des IRB kann das Programm direkt nach dem
Entpacken mit

 > make

�bersetzt werden. Zum Starten f�hren Sie

 > ./scheduler

bzw.

 > make run

aus.



Die Vorgabe enth�lt diesmal keine weiterf�hrenden
Abh�ngigkeiten und sollte mit jedem C-Compiler unabh�ngig
vom Betriebssystem �bersetzt werden k�nnen. Evtl. m�ssen
Sie mit dem Befehl

 > make depend

im Makefile die Abh�ngigkeiten an ihr System anpassen.

Nachdem Sie jedes Verfahren implementiert haben und jeweils den
R�ckgabewert der Funktion init_XX angepasst haben,
wird f�r alle Verfahren eine Statistik angezeigt.

Folgende Fehlermeldungen k�nnte das Testprogramm ausgeben:
Fehler innerhalb der Funktionstests:
ERROR!!! Scheduler switched to invalid task id (X)!

  Der Scheduler hat zu einer TaskID gewechselt, die niemals angemeldet wurde.
  Falls X=-1 k�nnte es sein, dass der Scheduler keinen Task ausgew�hlt hat,
  obwohl es noch laufbereite Tasks gibt.

ERROR!!! Scheduler switched to task X, but task Y has arrived earlier!

  Bei FIFO: Task X wurde ausgew�hlt, obwohl Task Y vorher angemeldet wurde.


ERROR!!! Scheduler switched to task X, but task Y hasn't finished yet!

  Bei FIFO: Task X wurde ausgew�hlt, obwohl Task Y noch nicht fertig ist.


ERROR!!! Scheduler switched to task X, but task Y is shorter!

  Bei SJN: Die Task sollen in der falschen Reihenfolge ausgef�hrt werden. Task Y
  ist k�rzer als Task X und muss daher vor X laufen.


ERROR!!! Scheduler ran the same Task (X) twice!

  Bei RR: Der Scheduler hat zwei mal hintereinander in unterschiedlichen
  Zeitscheiben den selben Task ausgew�hlt.


ERROR!!! Task X had more cpu time than task Y!

  Die Rechenzeit, die Task X zugeteilt wurde, unterscheidet sich um mehr als
  delta von der Rechenzeit von Task Y.


ERROR!!! Task XX is still running but should have finished by now!

  Tritt im Fifo-Test aus, wenn ein Task nach seiner Beendigung weiterl�uft.


Fehler innerhalb der zuf�llig generierten Tests:

semantic test: seems to be not implemented - check return value of init_XX

  Diese Meldung erscheint immer, wenn Sie ein Verfahren
  noch nicht als implementiert gekennzeichnet haben. �ndern
  Sie den R�ckgabewert der Funktion init_XX um die
  Tests f�r das Verfahren XX freizugeben.


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
