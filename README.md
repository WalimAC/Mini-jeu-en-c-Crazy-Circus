<div align="center">
  <a href="https://iutparis-seine.u-paris.fr">
    <img src="https://medias.podcastics.com/podcastics/podcasts/artwork/universite-paris-cite.png.23d93fd89c820e5e702963c782b2214f.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Mini-jeu en C - Crazy Circus | BUT Informatique</h3>

  <p align="center">
    Application en ligne de commande reproduisant le jeu algorithmique Crazy Circus.
    <br>
    <i>⚠️ | Projet universitaire réalisé dans le cadre de la SAE S1.02.</i>
    <br />
    <br />
    <a href="https://wamor.free.nf/?i=1#contact">Signaler un bug</a>
  </p>
</div>

## À propos du projet

Cette application console implémente le jeu **Crazy Circus**, un jeu de logique basé sur des manipulations de piles.  
Elle a été développée en langage C dans le cadre de la SAE 1.02 – Comparaison d’approches algorithmiques (BUT Informatique - Semestre 1).

Le programme permet à plusieurs joueurs de s’affronter en proposant des séquences d’ordres pour transformer une position initiale en position cible.

---

⛔️ | **Contraintes du projet :**

- Respect strict du format d’entrée / sortie (correction automatique).
- Lecture obligatoire de la configuration via un fichier `crazy.cfg`.
- Gestion complète d’une partie (plusieurs tours).
- Structuration du code en fichiers `.c` et `.h`.
- Documentation obligatoire des éléments déclarés dans les `.h`.

---

## Règles du jeu

Le jeu met en scène 3 animaux :

- LION  
- OURS  
- ELEPHANT  

Ils sont répartis sur deux podiums :

- 🔵 | BLEU  
- 🔴 | ROUGE  

Les animaux peuvent être empilés (structure de pile).

### Ordres disponibles

| Ordre | Action |
|-------|--------|
| KI | Sommet BLEU → ROUGE |
| LO | Sommet ROUGE → BLEU |
| SO | Échange des sommets |
| NI | Bas BLEU → Haut BLEU |
| MA | Bas ROUGE → Haut ROUGE |

---

## Fonctionnement

### Lancement du programme

```bash
./crazy JR MZ DP
```

Conditions :

- Minimum 2 joueurs
- Noms distincts obligatoires

---

### Fichier de configuration

Le fichier `crazy.cfg` doit contenir :

```
OURS ELEPHANT LION
KI LO SO NI MA
```

Conditions :

- Minimum 2 animaux
- Minimum 3 ordres valides
- Sinon → arrêt immédiat avec message informatif

---

### Déroulement d’un tour

1. Affichage des ordres autorisés  
2. Affichage de la position initiale et cible  
3. Les joueurs proposent une séquence :

```
DP KIMALONI
```

4. Si :
   - Identité inconnue → message d’erreur
   - Mauvaise séquence → joueur éliminé du tour
   - Bonne séquence → +1 point et nouveau tour

La partie se termine lorsque toutes les cartes ont été jouées.

---

## Affichage final

Les scores sont affichés :

- Par score décroissant
- Par ordre alphabétique en cas d’égalité

Exemple :

```
JR 21
DP 1
MZ 1
```

---

## Concepts algorithmiques utilisés

- Structures de données (pile)
- Manipulation de chaînes
- Lecture de fichiers
- Gestion des entrées utilisateur
- Modularité (.c / .h)
- Gestion d’erreurs
- Logique de comparaison d’états

---

## Structure du projet

```
Mini-jeu-en-c-Crazy-Circus/
│
├── src/
│   ├── crazy.cfg
│   ├── animal.c
│   ├── animal.h
│   ├── config.c
│   ├── config.h
│   ├── jeu.c
│   ├── jeu.h
│   ├── joueur.c
│   ├── joueur.h
│   ├── podium.c
│   ├── podium.h
│   ├── situation.c
│   ├── situation.h
│   ├── test.c

│
├── main.c
├── rapport.pdf
```

---

## Compilation avec

```bash
gcc
```

---

## Exécution

```bash
./crazy Nom1 Nom2 Nom3
```

---

## Langage utilisé & IDE

<img src="https://upload.wikimedia.org/wikipedia/commons/1/19/C_Logo.png" alt="Logo C" width="40" height="40">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9a/Visual_Studio_Code_1.35_icon.svg/2048px-Visual_Studio_Code_1.35_icon.svg.png" alt="Logo VScode" width="40" height="40">

---

## Contexte pédagogique

Projet réalisé dans le cadre du BUT Informatique – Semestre 1  
SAE S1.02 : Comparaison d’approches algorithmiques  

---

## Crédits

`Sujet : Denis Poitrenaud (règles, contraintes, format de correction)`  
<br/>
`Développement : Walim AMOR-CHELIHI`
