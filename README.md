# HALDA

Naprogramujte datovou strukturu Halda (Min-Heap).

Programujeme **Min-Heap** tudíž první prvek je vždy nejmenší z celé datové struktury. Pro Min-Heap platí jednoduché pravidlo, řekněme, že máme index 'Q' pro prvky na indexu '**Q * 2**' a 
'**Q * 2 + 1**' (následníci) vždy platí, že jsou větší než prvek na samotném indexu '**Q**'(předchůdce)

Konečná halda může vypadat následovně:
***
|   Prvky    | 5 | 6 | 20 | 25 | 7 | 21 | 22 | 26 | 27 |
|------------|---|---|----|----|---|----|----|----|----|
|Index v poli| 0 | 1 | 2  | 3  | 4 | 5  | 6  | 7  | 8  |
***

Jelikož začínáme na nultém prvku, tak pokud si chceme toto pravidlo zkontrolovat, musíme k indexu připočíst 1 (V kódu však nemusíme).

Např. prvek na indexu 3 (20) musí být menší jak prvky na indexu 6 (21) a 7 (22).

**Příklad vkládání do haldy:**

![Heap Insert](docs/heap_insert.gif)

**Příklad mazání nejmenšího prvku v haldě:**

![Heap DeleteMin](docs/heap_deletemin.gif)

Ve svém programu můžete využít funkci Heap_Print, která vypíše samotný prvek s jeho indexem, tak i jeho potomky.

*  Program musí být univerzální a být schopen pojmout libovolné množství záznamů.
*  Počáteční maximální počet položek v haldě je 4
*  Pokud halda překročí maximální počet položek, zdvojnásobíme její velikost

**Poznámky:**

Nezapomeňte na dynamicky alokovanou paměť, pro kterou poslouží knihovna 'mymalloc.h'

Pro porovnávání dvou prvků využijte funkce 'Data_Cmp' z knihovny 'data.h'


Následuje krátký popis funkcí, které potřebujeme ke správné funkci naší haldy (podrobnější popis můžete najít v hlavičkovém souboru 'heap.h'). 


### V jazyce C implementujte následující funkce:

**Heap_Init** - Inicializuje haldu

**Heap_Insert** - Vloží prvek na poslední místo a pokud jeho předchůdce je větší, prohodíme tyto 2 prvky a tento krok provádíme, 
dokud náš prvek není větší než předchůdce a nebo se náš prvek nedostane na první pozici

**Heap_Destruct** - Uvolní naalokovanou paměť. Nastaví jednotlivé položky haldy na nulové hodnoty. 
    
**Heap_FindMin** - Navrátí nejmenší prvek, který se v datové struktuře nachází

**Heap_DeleteMin** - Odebere nejmenší prvek z haldy. Prvek z poslední pozice přesuneme na první pozici
avšak místo s předchůdci ho porovnáme s jeho následovníky, a prohazujeme opět dokud následnovníci nebudou větší než náš prvek

**Heap_Empty** - Tato funkce nám sdělí jestli je naše halda prázdná či obsahuje nějaký prvek

**Heap_Count** - Funkce, která nám sdělí kolik prvků se právě nachází v haldě.

**Heap_Process** - Iteruje haldou a s každým prvkem provede definovanou opraci.


# HEAP

The task is Min-Heap -> The first element (index 0) is always the smallest from the whole data structure. Min-Heap has a simple rule, lets say we have index 'Q',
the element on the index '**Q * 2**' and '**Q * 2 + 1**' (childrens) are **always bigger** that the item itself on position '**Q**' (father).

The final Min-Heap could look like this : 

***
|     Items    | 5 | 6 | 20 | 25 | 7 | 21 | 22 | 26 | 27 |
|--------------|---|---|----|----|---|----|----|----|----|
|Index in array| 0 | 1 | 2  | 3  | 4 | 5  | 6  | 7  | 8  |
***

Since we're starting at index 0, for easier check let's say that index 0 is index 1 just for now, the item on index 3 (20) has to be always smaller that the items on the index 6 (21) and 7 (22).

**Example of inserting item in heap:**

![Heap Insert](docs/heap_insert.gif)

**Example of deleting an item with the lowest value:**

![Heap DeleteMin](docs/heap_deletemin.gif)

In your program you can easily print your heap using Heap_Print, which will print the item itself and his childrens. 

*  Program has to be universal and be able to store any amount of items
*  The starting maximum number of items in heap is 4
*  If the heap reaches its maximum number of items, double its size

**Notes:**

For allocating memory don't forget to use the functions from library 'mymalloc.h'

For comparing items use the function 'Data_Cmp' from library 'data.h'


A brief description of functions, that we need for our heap to work properly (More detailed description can be found in header file 'heap.h').

### In C language implement those functions:

**Heap_Init** - Initializes the heap

**Heap_Insert** - Inserts the item at the end of heap and if the father item is bigger, we switch those items,
this happens until our item isn't bigger than his father item or the item get's to the first position.

**Heap_Destruct** - Releases the allocated memory. Sets each heap item to zero.

**Heap_FindMin** - Returns the smallest item in the heap.

**Heap_DeleteMin** - Deletes and returns the smallest item in heap. The item that is at the end of the heap we move to the first place,
then we compare it with his childrens and swap them until the rules are met.

**Heap_Empty** - Returns if our heap is empty or if there's an item.

**Heap_Count** - Returns the amount of items stored in heap.

**Heap_Process** - Iterates through the heap and performs defined operation with each node.
