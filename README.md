# tema1
	
  In main, este declarata lista ("list"), careia i se aloca memorie dinamic, si se citesc numarul de perechi ("npairs") si perechile ("val", "time"), care se adauga in 
lista. Apoi, in functie de argumentele primite in linia de comanda, se apeleaza subprogramul corespunzator, care modifica lista initiala. In cazul in care argumentul 
este de tip "--st" outputul este diferit, iar acest lucru se marcheaza prin variabila "ok". In caz contrar, se afiseaza numarul de perechi si lista. La final, memoria 
este eliberata.

Pentru argumentul "--e1":
	Am adaugat in structura o noua variablia ("ok") pentru a marca pentru fiecare nod daca trebuie sau nu eliminat si am facut o functie ("init_ok") care initializeaza 
peste tot "ok"-ul cu 0. Se parcurge lista, "p" fiind primul nod din seria de 5 si "mid" fiind cel din mijloc. Pentru fiecare serie se calculeaza media si deviatia cu 
ajutorul functiilor "average" si "deviation", iar daca valoarea nodului din mijloc nu apartine intervalului, "ok" devine 1. Lista este iar parcursa, iar daca "ok"-ul
nodului are valoarea 1, este eliminat si numarul perechilor scade.

Pentru argumentul "--e2":
	Am creat o noua lista ("new_list") care va contine nodurile din mijloc. Pentru fiecare serie de 5 noduri, am apelat subprogramul "mini_list", care creeaza o noua 
lista cu cele 5 noduri, care este apoi sortata (functia "sort"). Acest subprogram returneaza un nod care are valoarea si timestamp-ul nodului din mijloc. In "e2", 
nodul este adaugat in lista "new_list", care inlocuieste lista initiala si se modifica numarul de perechi.

Pentru argumentul "--e3":
	Am creat o noua lista ("new_list") care va contine nodurile cerute. Pentru fiecare serie de 5 noduri, am apelat subprogramul "medie", care returneaza un nod care are 
ca valoare media dintre cele 5 noduri si timestamp-ul nodului din mijloc. In "e3", nodul este adaugat in lista "new_list", care inlocuieste lista initiala si se 
modifica numarul de perechi.

Pentru argumentul "--u":
	Lista este parcursa de la al doilea element si pana la ultimul, si se calculeaza diferenta ("dif") dintre nodul curent si cel anterior. Daca diferenta apartine 
intervalului [100,1000], valoarea si timestamp-ul nodului sunt modificate.

Pentru argumentul "--c":
	Am declarat 6 noduri care corespund listelor right si left. Am calculat constantele w13, w23, w33. Am parcurs lista, calculand diferenta dintre un element si 
urmatorul, iar daca aceasta este mai mare de 1000, urmeaza o serie de operatii: Se stabilesc left si right si timestamp-ul primului nod de adaugat. In continuare, 
pentru fiecare nod care va fi adaugat se calculeaza "C"-ul si valoarea ("f"), dupa formulele date. Nodul este adaugat dupa nodul curent prin functia "insertAfter", 
numarul de perechi creste si se trece la urmatorul nod.

Pentru argumentul "--st<delta>":
	Lista este sortata cu functia "sort". Am declarat 2 variabile: "start" si "end" - capetele primului interval. Cand se ajunge pe ultimul element, "ok" devine 1 si 
se opresc calculele, motiv pentru care conditia instructiunii "while" este "ok == 1". Se parcurg nodurile din lista, si daca nodul respectiv se afla in intervalul 
curent, contorul ("k") creste, daca nu, este afisat intervalul si numarul de noduri, iar capetele intervalului cresc cu "delta".
