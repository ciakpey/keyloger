# Keyloger
Un simple keyloger, qui utiliser xinput pour recuperer les characteres, xmodmap pour recuperer le keymap du clavier
## Compilation
```bash
make
```
## Utilisation
Il suffit d'appeler 
```bash
./main id_duclavier fichier_de_sortie
```
Pour trouver son id, voir ```bash xinput```

Le format d'enregistrement est characteres+tappées+en+même+temps heure
