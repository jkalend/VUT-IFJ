[![codecov](https://codecov.io/gh/jkalend/IFJ/branch/main/graph/badge.svg?token=ZEX0EW8QX8)](https://codecov.io/gh/jkalend/IFJ)

# IFJ
## IFJ projekt - 2022/2023

Implementace překladače jazyka IFJ22 (podmnožina jazyka PHP) v jazyce C.

Byl uplatněn algoritmus prediktivního syntatktického analyzátoru.  
Pro analýzu výrazů byl použit algoritmus precedence.

## Překlad
```
cmake -B build -S . && cmake --build build
```

## Spuštění
- Překladac očekává soubor s kódem v jazyce IFJ22 na standardním vstupu.
```
./build/IFJ
```

## Testování:
 - Testováno převážně pomocí [studenstkých testů](https://github.com/galloj/IFJ22_Tester)

## Rozdělení práce:
 - Jan Kalenda: Precedenční SA, generátor(operátory), testovací kostra, vedení tymu, sémantická analýza, CI/CD
 - Tereza Kubincov́a: Prediktivní SA, generátor(if,while,funkce) tabulka symbol̊u, makefile, sémantická analýza
 - Jaroslav Streit: Lexikální analýza, generátor(builtins), testy
 - Jan Vacula: Dokumentace, testy

## Hodnocení projektu:

Procentuální hodnocení modulů překladače:  
Lexikální analýza (detekce chyb): 100 % (165/165)  
Syntaktická analýza (detekce chyb): 90 % (188/208)  
Sémantická analýza (detekce chyb): 90 % (330/363)  
Interpretace přeloženého kódu (základní): 95 % (272/285)  
Interpretace přeloženého kódu (výrazy, vest. funkce): 96 % (178/185)  
Interpretace přeloženého kódu (komplexní): 66 % (246/370)  
STRNUM 0 % (0/100)  
BOOLTHEN 0 % (0/150)  
CYCLES 22 % (22/100)  
FUNEXP 100 % (150/150)  
GLOBAL 0 % (0/50)  
OPERATORS 0 % (0/100)  
Celkem bez rozšíření: 87 % (1379/1576)  