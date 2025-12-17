### Zadanie 1

samo CAS nie wystarcza bo nie pozwala odroznic logicznie usunietych wezlow od aktywnych:

(ex1.png)

Jak pomaga *marked*
*marked* w węźle rozróżnia logiczne i fizyczne jego usuniecie. Dzieki *marked* inne watki widza ze element juz nie jest w zbiorze nawet jesli fizycznie jest na liscie, co sprawia ze nie dochodzi do sytacji odzywania usunietych węzłach lub udanego CAS-a na wezlektóry nie powinien byc juz uzywany.

Dzieki `AtomicMarkableReference<T>` mozemy atomowo sprawdzic i zmienic `next` i `marked`.
To daje nam, że mamy informacje czy `pred.next` nadal wskazuje na `curr` i czy `curr` nie ma `marked` = True. 