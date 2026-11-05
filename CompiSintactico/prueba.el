*** prueba de IF, AND, OR, DO y FOR ***
MAIN
BEGIN
x:y:r:i:j:s ALLOCATE;
INPUT x;
y := 10;

*** 1. IF verdadero ***
IF (x < y) THEN
BEGIN
r := 1;
END
ELSE
BEGIN
r := 0;
END
OUTPUT r;

*** 2. AND ***
IF (x > 0 AND y == 10) THEN
BEGIN
r := 2;
END
ELSE
BEGIN
r := 0;
END
OUTPUT r;

*** 3. OR ***
IF (x > 100 OR y <> 5) THEN
BEGIN
r := 3;
END
ELSE
BEGIN
r := 0;
END
OUTPUT r;

*** 4. IF falso, entra al ELSE ***
IF (x >= 100) THEN
BEGIN
r := 0;
END
ELSE
BEGIN
r := 4;
END
OUTPUT r;

*** 5. IF anidado ***
IF (x > 0) THEN
BEGIN
IF (x <= 5) THEN
BEGIN
r := 0;
END
ELSE
BEGIN
r := 5;
END
END
ELSE
BEGIN
r := 0;
END
OUTPUT r;

*** 6. DO WHILE de 1 a 3 ***
i := 1;
DO
OUTPUT i;
i := i + 1;
WHILE (i <= 3)

*** 7. DO se ejecuta una vez aunque la condicion sea falsa ***
i := 10;
DO
OUTPUT i;
i := i + 1;
WHILE (i < 5)

*** 8. FOR de 1 a 3 ***
FOR i := 1 to 3 do
BEGIN
OUTPUT i;
END

*** 9. FOR con limite variable, suma de 1 a x ***
s := 0;
FOR i := 1 to x do
BEGIN
s := s + i;
END
OUTPUT s;

*** 10. FOR que no entra ***
r := 0;
FOR i := 5 to 1 do
BEGIN
r := 99;
END
OUTPUT r;

*** 11. FOR anidado ***
FOR i := 1 to 2 do
BEGIN
FOR j := 1 to 2 do
BEGIN
s := i * 10 + j;
OUTPUT s;
END
END

*** 12. IF dentro de FOR ***
FOR i := 1 to 4 do
BEGIN
IF (i == 2 OR i == 4) THEN
BEGIN
OUTPUT i;
END
ELSE
BEGIN
r := 0;
END
END

*** 13. DO dentro de FOR ***
FOR i := 1 to 2 do
BEGIN
j := 0;
DO
j := j + i;
WHILE (j < 3)
OUTPUT j;
END
END