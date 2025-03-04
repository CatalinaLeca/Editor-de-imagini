# **Editor de imagini**
Autor: **Leca Maria Cătălina - 315CA**  
Copyright © 2023-2024  
Materia: **Programarea Calculatoarelor și Limbaje de Programare 1**  
Tema 3 - **Editor de imagini (Procesare de imagini în C)**  

---

## 📖 **Descrierea Proiectului**
Acest proiect este un editor de imagini simplu, implementat în limbajul C. Suportă imagini în formatele **PGM (grayscale)** și **PPM (color)**, atât în **format text (ASCII)**, cât și **format binar**. Programul oferă funcționalități de bază pentru procesarea imaginilor, inspirate din editorii grafici, precum **Photoshop**.

Gigel, un student entuziast de anul 1, și-a propus să implementeze un editor de imagini simplificat, ce poate încărca, modifica și salva imagini în aceste formate. Proiectul urmează principiile de selecție și transformare a imaginilor, folosind o interfață text.

---

## ⚙️ **Funcționalități principale**
Programul implementează mai multe comenzi pentru procesarea imaginilor:

### 🔹 **Încărcare și salvare imagini**
- `LOAD <fisier>` → Încarcă o imagine PGM/PPM în memorie.
- `SAVE <fisier> [ascii]` → Salvează imaginea în format text sau binar.

### 🔹 **Selecția și manipularea regiunilor din imagine**
- `SELECT <x1> <y1> <x2> <y2>` → Selectează o regiune dreptunghiulară a imaginii.
- `SELECT ALL` → Selectează întreaga imagine.
- `CROP` → Taie imaginea la dimensiunea selecției curente.

### 🔹 **Procesare și modificare imagini**
- `HISTOGRAM <x> <y>` → Afișează histograma imaginii grayscale.
- `EQUALIZE` → Aplică egalizarea histogramei asupra unei imagini grayscale.
- `APPLY <FILTER>` → Aplică un filtru de procesare a imaginii color, unde `<FILTER>` poate fi:
  - `EDGE` → Detectarea marginilor
  - `SHARPEN` → Clarificare
  - `BLUR` → Estompare
  - `GAUSSIAN_BLUR` → Estompare Gaussiană

### 🔹 **Ieșire din program**
- `EXIT` → Închide programul și eliberează memoria.

---

## 🛠️ **Descrierea implementării**
Pentru gestionarea imaginilor, am creat structura `img`, care reține formatul imaginii, dimensiunile, valoarea maximă a unui pixel și datele propriu-zise, stocate fie într-o matrice de valori `int` (pentru imaginile grayscale), fie într-o matrice de structuri `rgb` (pentru imaginile color). De asemenea, am creat structura `coordinates` pentru a gestiona selecția curentă.

Pentru citirea comenzilor de la tastatură, am implementat un mecanism de parsare a inputului. Prima parte a comenzii este citită separat pentru a verifica rapid dacă este validă, iar restul argumentelor sunt preluate și verificate.

### 🔹 **Încărcarea imaginilor (`LOAD`)**
- Am creat funcții dedicate pentru alocarea dinamică a matricei de pixeli.
- O funcție citește primele două caractere dintr-un fișier pentru a determina formatul imaginii.
- În cazul fișierelor text (`P2`, `P3`), citirea se face cu `fscanf()`, iar pentru cele binare (`P5`, `P6`), am folosit `fread()`.
- O funcție auxiliară gestionează ignorarea comentariilor (`#`).

### 🔹 **Selectarea zonei (`SELECT`)**
- Dacă este specificat `ALL`, se selectează întreaga imagine.
- Pentru o selecție manuală, parametrii sunt verificați pentru a preveni erori: se asigură că sunt 4 numere, că sunt pozitive, că nu depășesc dimensiunile imaginii și că sunt în ordine corectă.

### 🔹 **Decuparea imaginii (`CROP`)**
- Se creează o imagine auxiliară în care se copiază doar zona selectată.
- Imaginea veche este eliberată din memorie și înlocuită cu cea decupată.

### 🔹 **Histograma (`HISTOGRAM`)**
- Se creează un vector de frecvență pentru valorile pixelilor.
- Se calculează distribuția pixelilor și se normalizează în funcție de valoarea maximă.

### 🔹 **Egalizarea imaginii (`EQUALIZE`)**
- Se calculează distribuția pixelilor și se aplică formula de transformare a histogramei.
- Se utilizează `round()` pentru a obține valori întregi și `clamp()` pentru a limita rezultatele în intervalul [0, 255].

### 🔹 **Aplicarea filtrelor (`APPLY`)**
- Am creat o structură `kernel` care stochează o matrice 3x3 și un factor de normalizare.
- Filtrarea imaginii se realizează prin convoluție: fiecare pixel este înlocuit cu suma ponderată a pixelilor vecini.
- Pentru fiecare canal de culoare (R, G, B), se aplică operația corespunzătoare.
- La final, valorile sunt clamped în intervalul valid [0, 255].

### 🔹 **Salvarea imaginilor (`SAVE`)**
- Se scriu datele imaginii fie în format text (`fprintf()`), fie binar (`fwrite()`).
- Se verifică dacă parametrul `ascii` este specificat pentru a alege formatul corespunzător.

### 🔹 **Ieșirea din program (`EXIT`)**
- Înainte de închidere, memoria este eliberată prin funcția `free_image()` pentru a evita **memory leaks**.
- Dacă nu există o imagine încărcată, se afișează un mesaj corespunzător.

---

## 🏁 **Exemplu de utilizare**
```bash
> LOAD imagine.pgm
Loaded imagine.pgm

> SELECT 10 10 50 50
Selected 10 10 50 50

> CROP
Image cropped

> APPLY SHARPEN
APPLY SHARPEN done

> SAVE rezultat.pgm ascii
Saved rezultat.pgm

> EXIT
```

## 🎯 **Concluzie**
Acest editor de imagini oferă funcționalități esențiale pentru manipularea imaginilor în format **PGM/PPM**. Programul respectă cerințele temei, gestionând corect memoria și operând eficient asupra imaginilor.

Structurile de date utilizate, împreună cu metodele implementate pentru procesarea imaginilor, asigură o execuție optimă și o gestionare corectă a memoriei. Fiecare funcționalitate a fost testată și verificată pentru a garanta o manipulare corectă a imaginilor, atât în format **grayscale**, cât și **color**.

Editorul permite încărcarea, selectarea, procesarea și salvarea imaginilor într-un mod intuitiv, având o interfață bazată pe linia de comandă. Prin utilizarea tehnicilor precum convoluția pentru aplicarea filtrelor sau normalizarea histogramei pentru egalizare, programul demonstrează principii fundamentale din procesarea imaginilor.

Acest proiect oferă o bază solidă pentru înțelegerea și dezvoltarea ulterioară a aplicațiilor de procesare a imaginilor, fiind un punct de plecare excelent pentru extinderea funcționalităților în viitor.

🚀 **Proiect realizat cu pasiune pentru Programarea Calculatoarelor!** 🚀
