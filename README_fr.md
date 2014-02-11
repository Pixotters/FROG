#Projet FROG - Nicolas Cailloux et Julien Sagot

## For Really Outstanding Games

### Présentation brève

Nous souhaitons développer un moteur de développement d'applications, orienté
jeu vidéo. Le but est de faciliter et accélérer la phase de développement en
fournissant des composants redondants : on n'a pas envie de réécrire tout le
temps le même code. Ainsi, les utilisateurs pourront se concentrer sur les
taches plus importantes, comme la conception ou les algorithmes spécifiques à
l'application. La librairie se basera sur SFML, de Laurent Gomila, et sera codée
en C++, pour des développeurs C++.   

### Motivations

Il existe déjà plusieurs moteurs de développement. Pourquoi vouloir développer 
le notre ?  

* parmi les moteurs, beaucoup se basent sur la 3D : dans le cadre d'applications
2D, cela ajoute de la complexité d'utilisation inutile.  
* parmi les moteurs, beaucoup sont disponibles pour windows seulement : le notre
se base sur une librairie portable et sera donc portable. 
* certains sont drag & drop : nous n'aimons pas énormement cette approche, car 
elle peut parfois faire perdre beaucoup de temps (notamment si peu de raccourcis
 claviers sont proposés). 
* la plupart sont fermés : on ne peut pas voir directement le code du moteur, 
pour le modifier à notre guise. Notre projet sera libre, et donc modifiable et 
extensible sans limite. 
* Beaucoup de moteurs ou de logiciels de développement se limitent à un genre : 
combat, jeu de rôle, de plate-forme. Nous aimerions faire quelque chose qui soit
 utilisable dans le plus de situations possibles.  

De plus, savoir utiliser un moteur est une compétence intéressante, mais 
connaître les mécaniques sous-jacentes l'est encore plus.  

### Détails 


Les qualités recherchées pour le moteur sont :   

* Abstraction/généricité : le moteur devrait être suffisament générique pour 
pouvoir être utilisé dans le plus de programmes possibles (ceux-ci étant de type
arbitrairement variés). 
* Simplicité : le but est d'accélérer le développement d'applications, en 
fournissant des composants "déjà prêt à l'utilisation", il ne faudrait donc pas 
gacher ça avec une difficulté d'utilisation rédibitoire.  
* Modularité : on devrait pouvoir utiliser chaque composant le plus 
indépendamment possible des autres. 
* Extensibilité : on devrait pouvoir ajouter facilement d'autres composants dans
 le futur (ou simplement pour d'autres développeurs). 

Les composants auquels on a pensé (soit par nous-même, soit par le biais de 
lectures) sont décrits ci-après. Nous les avons classés selon l'importance 
qu'ils ont, car si le temps manque, ce sera plus facile de déterminer ce dont on
 peut se passer et ce qui est indispensable. Cela peut sembler long mais 
plusieurs fonctionnalités sont en fait faciles et rapides à implémenter.  

#### Minimum syndical 

Si nous ne parvenons pas à faire au moins ça, ce serait une grande déception. 

##### Gestion de la boucle 

Le jeu se déroule dans une boucle : lecture des entrées, réaction aux inputs / 
calcul de la logique de jeu, puis rendu graphique.  
Il faut aussi gérer le temps : selon les machines, le nombre de cycles par 
seconde peut varier grandement. Pour que l'exécution du jeu soit semblable sur 
une machine dépassée et sur une machine haut de gamme récente, il faut amortir 
le temps : ceci se fait via la gestion d'un *deltaTime* (temps écoulé depuis le 
dernier cycle).

##### Machine à états

Ce qu'on appelle un état est une "phase" du jeu : le menu principal, le 
splashscreen, une scène, le menu d'options (...) sont autant d'états différents.
 Pour passer d'un état à un autre, il faut des transitions : ceci crée un 
automate implicite pouvant être géré génériquement via un automate / un graphe.

##### Fichiers 

L'accès aux fichiers est une opération lourde, on veut donc la limiter le plus 
possible. Par exemple, si un fichier est chargé en mémoire, on ne veut pas le 
charger une seconde fois. De même, l'accès aux ressources d'un fichier qui n'est
 pas présent en mémoire peut poser problème : on peut vouloir s'assurer qu'un 
fichier a bien été chargé.  
Il est possible de faire une sorte de mémoïsation, sur les fichiers.

##### Gestion des entrées 

Dans un jeu, il faut une interaction avec l'utilisateur. Elle peut être faite 
via le clavier, la souris, ou même un joystick. Chacune des entrées peut être 
liée à une action, mais une action peut être provoquée par plusieurs entrées 
(par exemple, par le clavier et la manette). Il faut donc gérer ces 
correspondances, tout en permettant une personnalisation facile. On pense à une 
table d'association entre action et touche(s).  

##### Rendu 

La SFML embarque une gestion des fenetres et d'affichage des textures. Nous 
voulons offrir un niveau plus élevé en proposant l'utilisation de calques, de 
vues, mais aussi une gestion convenable des résolutions (pour que le placement 
des éléments se fasse toujours de manière cohérente, quelle que soit la 
configuration des utilisateurs).  

#### Composants pratiques

Nous serons relativement satisfaits si on a réussi à faire tout ceci, car ces 
composants permettent de faire déjà pas mal de choses. Ca n'aura pas été une 
totale perte de temps. 

##### GUI toolkit 

Les menus sont des éléments courants des jeux. On devrait pouvoir en créer le 
plus facilement possible. A la manière de Swing, on devrait pouvoir créer,  
assembler, et dessiner des composants de base comme des boutons, des containers,
 des labels, des zones de texte... 

##### Objets / Entités

Grâce au polymorphisme, il est possible de regrouper dans une hiérarchie les 
objets gérés par le moteur apparaissant au sein d'une scène. 
Ceux-ci seront traités de la même manière par le moteur, mais pourront avoir un 
comportement supplémentaire.  
Par exemple, un projectile et un ennemi sont deux entités distinctes : elles ne 
se comportent pas de la même manière. Par contre, chacune est dessinée et mise à 
jour par le moteur, selon des attributs communs (position, rotation, échelle...).
 Dans l'idéal, les attributs des objets devraient pouvoir être chargés depuis un 
fichier (afin de ne pas recompiler juste pour changer la taille d'un arbre) : 
*data-driven design*, permettant une plus grande flexibilité (au détriment, 
peut-être, de la fiabilité : que faire si le fichier est absent ? Utiliser des 
valeurs par défaut ? Crasher ?). 

##### Animations 

Animer un elément visuel est une fonctionnalité essentielle. Nous pensons 
utiliser des animations par "clip", extraits d'un *spritesheet*. Toutefois, il 
faudrait que l'utilisateur puisse créer son propre système d'animation, et donc 
charger les spritesheet (et les convertir en animations) de manière extensible. 

##### Graphe de scène 

Permet de hiérarchiser les entités d'une scène : si on déplace un container, on 
veut que le contenu se déplace avec ; si le chef d'une escouade bouge, ses 
troufions doivent le suivre.  
Ceci implique l'implémentation d'une gestion de coordonées relatives (à un parent
 par exemple).  

##### Son 

Le son est géré de base dans la SFML, nous ne ferons donc que des surcouches pour
en faciliter l'usage. 

#### Composants avancés

Des fonctionnalités qu'il serait commode d'implémenter car elles se retrouvent 
souvent, mais nous n'aurons probablement pas le temps de toutes les faire.  

##### Collision / physique 

Probablement la tâche la plus longue, ce module met en oeuvre des algorithmes de 
partitionnement de l'espace, de tests de collisions, de gestion de forces. 

##### Vues 

Amélioration des vues, en permettant des caméras multiples, de formes diverses. 
On pense aussi mettre en place le *culling* (consistant à n'afficher que ce qui 
est visible par une caméra, allégeant ainsi le rendu). 

##### Tuiles 

Les niveaux d'un jeu 2D sont souvent représentés par une *Tile Map*, une grille 
de cases où chacune pointe vers une tuile, qui elle possède les propriétés telles
 que le graphique, la possibilité de collision (...). Comme ce système est très 
répandu, il faudrait inclure la création de niveau via des tuiles. Ceci implique 
peut-être la création d'un éditeur de niveaux, ou une très grande génércité du 
parseur : personnalisation de la taille des tuiles, du nombre de calques, des 
propriétés des tuiles.  

##### Ombres 

La gestion des lumières et ombres permettrait un rendu bien plus agréable. 
Plusieurs types de lumières sont utilisés fréquemment : par point, par direction,
 lumière ambiante, ...  
L'ombre sera simplement présente là où il n'y a pas de lumière, mais certaines 
choses doivent être prises en compte : comment gérer les multiples sources 
lumineuses ? Les ombres peuvent être douces, dures, portées, colorés ? 

##### Réseau 

Le jeu est ligne s'est aujourd'hui démocratisé. L'époque où les enfants 
invitaient leurs amis pour jouer à 4 joueurs autour de la console est révolu : 
maintenant ils jouent via internet. Se passer d'un module comme celui-ci entrave 
une grosse partie de la jouabilité d'un titre.  
Ainsi, quelques composants réseaux faciles à utiliser pourraient être mis en 
place, comme un système clients / serveur. 

##### IA 

Une Intelligence Artificielle est bien entendu spécifique à l'application, mais 
il existe des composants de base, ou des modèles : recherches aveugles, recherche
 informées, minmax / alpha-beta, mais aussi graphe d'agents réactifs, ou réseaux
bayésiens.  
Il existe probablement un moyen de proposer un squelette de base pouvant répondre
 à quelques besoins.