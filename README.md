# t-armory-scan
Ce projet est une implémentation d'un outil de reconnaissance réseau basique, codé en C Système. Il effectue un scan synchrone des ports TCP pour déterminer les services actifs sur une machine cible.

# DXP - Recon 

Objectif et Mécanisme

L'outil est conçu pour interroger la plage de ports système (0 à 1024) en utilisant une séquence simple : socket → connect → close.
Fonction Technique	Rôle Critique
Gestion du Timeout	Le scanner utilise setsockopt (SO_RCVTIMEO/SO_SNDTIMEO) pour imposer un délai maximal de 2 secondes. Ceci est essentiel pour éviter le blocage indéfini sur les ports filtrés (silent drop) ou silencieux, un problème inhérent aux connexions TCP synchrones.
Vérification d'État	Le statut du port est déterminé par le code de retour de connect() (0 pour ouvert, -1 pour fermé/erreur).
Endianness	Utilisation de htons() pour garantir la bonne conversion des ports de l'ordre local à l'ordre réseau.

📝 Compétences Validées

    Maîtrise des Sockets TCP (création et destruction de la ressource à chaque itération).

    Gestion des appels bloquants et configuration des options de socket (setsockopt).

    Manipulation des structures réseau (struct sockaddr_in) et des arguments de ligne de commande (av[1]).
