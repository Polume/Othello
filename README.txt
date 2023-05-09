Afin de lancer le jeu correctement,
vous devrez ouvrir un Terminal Ubuntu dans le dossier du jeu.
Ensuite effectuer une commande make.

Se trouvant dans ce dossier, les fichiers nécessaire a la compilation, un dossier Pictures, un dossier Saves et un dossier Sound
Le dossier Pictures contiens les images utiliser par le jeu.
Le dossier Sound contiens les sons utiliser par le jeu.
Le dossier Saves contien la sauvegarde unique.

Pour plus d'informations sur les commandes et leurs utilitées lire ce qui suit.
make/make all:
	Installe les librairies (si déjà installer, les mets a jours) compile les fichiers et lance le jeu
make install-deps:
	Vous permet d'installer les librairies nécessaireau lancement du jeu
make run:
	Vous permettra de lancer le fichier executable
make game:
	Vous permettra de simplement compiler les fichiers et de creer un fichier executable "game"
make clean:
	Vous permettra de nettoyer vos fichers de compilations et dexecutions, cela gardera seulement les fichiers utils à la compilation.