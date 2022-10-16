# SEQUENTIAL DATA PROCESSING AND ANALYSIS
	
Numarul de perechi (***"npairs"***) si perechile (***"val"***, ***"time"***) se adauga in lista (***"list"***). Apoi, in functie de argumentele primite in linia de comanda, se apeleaza subprogramul corespunzator, care modifica lista initiala.

*	###	`--e1` - eliminare de exceptii folosind statistici:
	Se parcurge lista, ***"p"*** fiind primul nod din seria de 5 si ***"mid"*** fiind cel din mijloc. Pentru fiecare serie se calculeaza media si deviatia cu ajutorul functiilor `average` si `deviation`, iar daca valoarea nodului din mijloc nu apartine intervalului, este eliminat si numarul perechilor scade.

*	###	`--e2` - eliminare de zgomot prin filtru median:
	Am creat o noua lista (***"new_list"***) care va contine nodurile din mijloc. Pentru fiecare serie de 5 noduri, am apelat subprogramul `mini_list`, care creeaza o noua lista cu cele 5 noduri, care este apoi sortata (functia `sort`). Acest subprogram returneaza un nod care are valoarea si timestamp-ul nodului din mijloc. In `e2`, nodul este adaugat in lista ***"new_list"***, care inlocuieste lista initiala si se modifica numarul de perechi.

*	###	`--e3` - eliminare de zgomot folosind filtrul bazat pe media aritmetica:
	Am creat o noua lista (***"new_list"***) care va contine nodurile cerute. Pentru fiecare serie de 5 noduri, am apelat subprogramul `medie`, care returneaza un nod avand ca valoare media dintre cele 5 noduri si timestamp-ul nodului din mijloc. In `e3`, nodul este adaugat in lista ***"new_list"***, care inlocuieste lista initiala si se modifica numarul de perechi.

*	###	`--u` - uniformizarea frecventei:
	Lista este parcursa de la al doilea element si pana la ultimul, si se calculeaza diferenta (***"dif"***) dintre nodul curent si cel anterior. Daca diferenta apartine intervalului [100,1000], valoarea si timestamp-ul nodului sunt modificate.

*	###	`--c` - completarea datelor lipsa:
	Am declarat 6 noduri care corespund listelor right si left. Am calculat constantele ***w13***, ***w23***, ***w33***. Am parcurs lista, calculand diferenta dintre un element si urmatorul, iar daca aceasta este mai mare de 1000, urmeaza o serie de operatii: Se stabilesc ***left*** si ***right*** si timestamp-ul primului nod de adaugat. In continuare, pentru fiecare nod care va fi adaugat se calculeaza ***"C"***-ul si valoarea (***"f"***), dupa formulele date. Nodul este adaugat dupa nodul curent prin functia `insertAfter`, numarul de perechi creste si se trece la urmatorul nod.

*	###	`--st<delta>` - calculul statisticilor:
	Lista este sortata cu functia `sort`. Am declarat 2 variabile: ***"start"*** si ***"end"*** - capetele primului interval. Se parcurg nodurile din lista, iar daca nodul respectiv se afla in intervalul curent, contorul (***"k"***) creste, in caz contrar, este afisat intervalul si numarul de noduri, iar capetele intervalului cresc cu ***"delta"***.
