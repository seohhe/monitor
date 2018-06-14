# monitor

Repozytorium zawiera kod rozproszonego monitora. Implementacja wykorzystuje C++ i OpenMPI.

## Opis algorytmu

Istnieje struktura Buff inicjalizowana w pierwszym procesie, która przechowuje współdzielone dane. Zawiera ona również tablicę oznaczającą stany poszczególnych procesów. Znaczenia wartości w tablicy: 
0 - proces nie ubiega się o wejście do sekcji krytycznej 
1 - procesy ubiega się o wejście do sekcji krytycznej
Inne wartości oznaczają zablokowanie na zmiennej warunkowej o konkretnej wartości

W trakcie gdy proces pierwszy znajduje się w sekcji krytycznej odbiera on zgłoszenia od innych procesów (o ich potrzebie wejścia do sekcji krytycznej) i aktualizuje ich stan w strukturze Buff. Po wyjściu z sekcji krytycznej struktura jest przekazywana kolejnemu w kolejce ubiegającemu się procesowi, co jest równoznaczne z przyznaniem dostępu do sekcji krytycznej. Kolejność determinowana jest numerem id procesu. Proces będący w sekcji krytycznej może wykonać metodę wait. Aktualizuje swój stan na wartość zmiennej warunkowej i przesyła strukturę dalej. Nie będzie on obudzony, aż do wykonania przez inny proces metody signal, której parametrem będzie ta sama zmienna warunkowa.

## Opis plików

buffer - struktura współdzielona przez wszystkie procesy
conditional	- klasa zmiennej warunkowej
monitor	- klasa po której dziedziczą implementowane przez użytkownika klasy, zawierająca metody potrzebne do wykonania algorytmu, obsługująca komunikację między procesami

main - utworzenie procesów i uruchomienie algorytmu

consumer - klasa konsumenta implementowana przez użytkownika
producer - klasa producenta implementowana przez użytkownika

## Podsumowanie

Klasa monitor pozwala w łatwy i transparentny sposób implementować klasy rozwiązując problemy które wymagają zastosowania rozproszonego monitora. Niestety rozwiąznie to wymaga zainstalowania na każdym z biorących udział w przetwarzaniu systemów biblioteki OpenMPI.
