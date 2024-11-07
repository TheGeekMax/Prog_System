# TD-4

## Exercice 12

### questions terminee

12.1
12.2
12.3
12.4

### réponses au questions

#### 12.1

il creer 10 threads (et les executes), chaque thread imprime l'id (de 1 a MAX(=10)) puisle programme attends que les 10 threads se terminent

#### 12.2

TODO

#### 12.4

le compteur n'affiche pas 4 000 000. pour eviter cela, il faudrait rajouter un mutex sur la section critique, pour eviter que plusieurs threads modifient la meme variable en meme temps

#### 12.5

car les 2 fonctions execute du code qui ne se font pas en temps atomique.
dans le cas de la fonction insert on peut avoir 

Thread 1 : affectation de e->next = head
Thread 2 : affectation de e->next = head
Thread 1 : affectation de head = e
Thread 2 : affectation de head = e

dans le cas la, le head du Thead 1 se fait ecraser par celuis du thread 2

dans le cas de la fonction recevoir, l'operation a += n est en realité 3 operations :

1. lecture de a
2. addition de n
3. ecriture de a

on peut avoir du coup:

Thread 1 : lecture de compte_en_banque
Thread 2 : lecture de compte_en_banque
Thread 1 : addition de montant
Thread 2 : addition de montant
Thread 1 : ecriture de compte_en_banque
Thread 2 : ecriture de compte_en_banque

dans ce cas la, le resultat final est compte_en_banque + montant , alors qu'il devrait etre compte_en_banque + 2*montant

