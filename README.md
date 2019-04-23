<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/150px-42_Logo.svg.png" align="right" />

# mlx_img pour les studs 42

### Introduction

En tant qu'étudiant 42 ayant fait la branche graphique, j'ai pu me rendre compte que la documentation sur la notion d'image de la mlx n'était pas forcément très fournie.

Dans ce guide, je partirais du principe que vous connaissez deja les bases expliquées dans les videos de 42. (mlx_init, mlx_loop, mlx_create_windows, mlx_put_pixel)

Ce guide n'a pas pour ambition d'apporter de réponse parfait. Il s'appuira sur mon experience personnelle. Il se peut donc qu'il y ait des erreurs.

### Les images mlx c'est quoi ?

Comme tout le monde le sait, les images/photos sont composées de milliers de pixel. Si vous êtes ici, vous savez que la mlx permet d'afficher des pixels sur la fenêtre grâce à la fonction mlx_put_pixel. Or, cette fonction ne permet d'afficher que pixel par pixel. De plus, elle est obligé de creer un pixel (Elle ne modfie pas le pixel) et elle doit afficher directement le pixel a l'écran. Cela genere beaucoup d'appel système et cela rend votre programme lent.

Les images mlx sont bien plus performante car elles sont generer en tant qu'image complete. Il y a donc pas d'appel systeme pour la création des pixels. Puisqu'ici, vous le verrai, vos pixels sont stockés dans une string. De plus, l'affichage se fait une fois pour tous les pixels. Et non pas a chaques pixels.

Vous le verrez, les images mlx permettent de faire beaucoup de chose.

### La structure image

```C
typedef struct	s_img
{
	void  *img; /* pointer qui permet d'identifier l'image */
	char  *img_str; /* string contenant tous les pixels de l'image */
	int   bits; /* nombre de bits par pixels */
	int   size_line; /*  taille de la img_str*/
	int   endian; /* permet de signifier la fin d'une image*/
}               t_img;
```

Elle n'est pas obligatoire mais je la conseil très fortement. En effet, les images sont définies par plusieurs variables.
Pour ma part, je n'ai jamais eu a utiliser les 3 int de cette structure. J'esseyerai donc de vous les expliquer au mieux.

### La création d'une image

```C
mlx_new_image(void *mlx_ptr, int largeur, int hauteur)
```

Cette fonction vous renvoie un pointeur image qui permet a votre programme de reconnaitre l'image sur laquelle vous travaillée.

### Récupération de la *img_str

La *img_str est une chaîne de carracteres qui va regrouper tout les pixels de votre image. C'est cette string que vous devrez modifier pour modfier vos pixels. Pour la recuperer on utilise :

```C
img_str = mlx_get_data_addr(void *img, int *bits, *int size_line, *int endian);
```

Tout d'abord, la fonction a besoin du pointer de votre image. De cette façon, la fonction vous renvera les informations sur l'image que vous souhaitez.

Ensuite, on constate que la fonction attends des int* c'est-à-dire qu'il faut lui envoyer des adresses de variable int.

Vous l'aurez compris, c'est grâce a cette fonction que vous pouvez recuperer toutes les informations sur votre images.

### Modifier un pixel

C'est sans doute la partie la plus difficile. Mais n'ayez crainte vous allez y arriver.

À la difference de la fonction mlx_put_pixel, vous ne devrez pas créer un pixel à afficher dans votre image. En réalité, la fonction mlx_new_image créée une image complète avec des pixels vides. (Pixels noirs) Vous pouvez modifier les pixels de cette image en modifiant la string retournée par mlx_get_data_addr.

Le problème, c'est qu'il n'y a pas de fonction de la mlx pour le faire correctement. Une fonction mlx_put_pixel_image par exemple. Il faut donc créer la votre. Dans ce git, il y a la fonction put_pixel_image. Cette fonction est assez complexe car elle a été optimisée au maximum. Je vais donc vous l'expliquer.

### Afficher une image dans une fenêtre

```C
mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img, int corner_left_x, int corner_left_y)
```
Rien de plus simple, on passe en argument le mlx_ptr, le win_ptr de la fenetre voulue, le pointeur image pour preciser l'image à afficher  et les coordonnées du pixel le plus en haut à gauche de l'image pour la position.

### ATTENTION ÇA LEAKS

```C
mlx_destroy_image(void *mlx_ptr, void *mlx_img)
```

Pour prévenir de tout leaks, il faut utiliser la fonction mlx_destroy_image. En effet, char *img_str est une string qui est malloc. Il faut donc liberer cette espace avant de créer une autre image. Pour cela, il suffit de passer en argument le ptr de la mlx et le pointeur de l'image que vous voulez detruire.

### FAQ ?
#### Les questions qu'on me pose souvent
```
1. J'ai fais mon programme avec la fonction mlx_put_pixel. Est-ce que je dois tout recommencer ?
```
NON. En soit, cela ne change pas grand chose au fonctionnement d'un programme tel que fdf ou fractol. Vous devez simplement implementer la creation de l'image, remplacer tous les mlx_put_pixel par des put_pixel_image et enfin afficher l'image.
```
2. Est-ce que regarder/m'inspirer de ce cour c'est triché ?
```
Selon moi, <strong>NON</strong>. Pour moi, Github est la reponse parfait a l'adage : "rien ne sert de ré-inventé la roue"
. Le plus important c'est de comprendre le fonctionnement des images mlx. Même si vous reprennez certaines fonctions de ce Git, tant que vous les avez comprises, pour moi vous ne trichez pas.
