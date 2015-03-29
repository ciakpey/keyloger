# Ne pas utiliser
Il y a un bug dans l'implementation des listes chainées, je pense car au bout d'un certain momemt le script devient ingérable


# Keyloger
Un simple keyloger, qui utilise ```xinput``` pour recuperer les characteres, ```xmodmap``` pour recuperer le keymap du clavier
## Compilation
```bash
make
```
## Utilisation
Il suffit d'appeler 
```bash
./main id_du_clavier fichier_de_sortie
```
Pour trouver son id, voir ```xinput```

Le format d'enregistrement est characteres+tappées+en+même+temps heure
