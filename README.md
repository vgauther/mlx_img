<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/150px-42_Logo.svg.png" align="right" />

# mlx_img pour les studs 42

### Introduction

En tant qu'étudiant 42 ayant fait la branche graphique, j'ai pu me rendre compte que la documentation sur la notion d'image de la mlx n'était pas forcément très fournie.

Dans ce guide, je partirai du principe que vous connaissez déjà les bases expliquées dans les vidéos de 42. (mlx_init, mlx_loop, mlx_create_windows, mlx_put_pixel)

Ce guide n'a pas pour ambition d'apporter de réponse parfaite. Il s'appuiera sur mon expérience personnelle. Il se peut donc qu'il y ait des erreurs.

### Les images mlx c'est quoi ?

Comme tout le monde le sait, les images/photos sont composées de milliers de pixel. Si vous êtes ici, vous savez que la mlx permet d'afficher des pixels sur la fenêtre grâce à la fonction mlx_put_pixel. Or, cette fonction ne permet d'afficher que pixel par pixel. De plus, elle est obligé de créer un pixel (elle ne modfie pas le pixel) et elle doit afficher directement le pixel à l'écran. Cela génère beaucoup d'appels système et cela rend votre programme lent.

Les images mlx sont bien plus performantes. Elles sont générées en tant qu'image complète et non pas pixel par pixel. Il n'y a donc pas d'appel système pour la création des pixels. Puisqu'ici, vous le verrez, vos pixels sont stockés dans une string. De plus, l'affichage se fait une fois pour tous les pixels. Et non pas à chaque pixel.

Vous le verrez, les images mlx permettent de faire beaucoup de choses.

### La structure image

```C
typedef struct	s_img
{
	void  *img;      /* pointeur qui permet d'identifier l'image */
	char  *img_str;  /* string contenant tous les pixels de l'image */
	int   bits;      /* nombre de bits par pixels */
	int   size_line; /* taille de la img_str */
	int   endian;    /* permet de signifier la fin d'une image */
}               t_img;
```

Elle n'est pas obligatoire mais je la conseille très fortement. En effet, les images sont définies par plusieurs variables.
Pour ma part, je n'ai jamais eu à utiliser les 3 int de cette structure. J'essayerai donc de vous expliquer au mieux ce que j'ai compris à leur sujet.

### La création d'une image

```C
mlx_new_image(void *mlx_ptr, int largeur, int hauteur)
```

Cette fonction vous renvoie un pointeur image qui permet à votre programme de reconnaitre l'image sur laquelle vous travaillez.

### Récupération de la *img_str

La *img_str est une chaîne de caractères qui va regrouper tout les pixels de votre image. C'est cette string que vous devrez modifier pour modfier vos pixels. Pour la récupérer on utilise :

```C
img_str = mlx_get_data_addr(void *img, int *bits, *int size_line, *int endian);
```

Tout d'abord, la fonction a besoin du pointeur de votre image. De cette façon, la fonction vous renvera les informations sur l'image que vous souhaitez.

Ensuite, on constate que la fonction attends des int* c'est-à-dire qu'il faut lui envoyer des adresses de variable int.

Vous l'aurez compris, c'est grâce a cette fonction que vous pouvez récupérer toutes les informations sur votre images.

### Modifier un pixel

C'est sans doute la partie la plus difficile. Mais n'ayez crainte vous allez y arriver.

À la difference de la fonction mlx_put_pixel, vous ne devrez pas créer un pixel à afficher dans votre image. En réalité, la fonction mlx_new_image créée une image complète avec des pixels vides. (Pixels noirs) Vous pouvez modifier les pixels de cette image en modifiant la string retournée par mlx_get_data_addr.

Le problème, c'est qu'il n'y a pas de fonction de la mlx pour le faire correctement. Une fonction mlx_put_pixel_image par exemple. Il faut donc créer la vôtre. Dans ce git, il y a la fonction put_pixel_image. Cette fonction est assez complexe car elle a été optimisée au maximum. Je vais donc vous l'expliquer.

```C
void	put_pixel_image(t_pixel pixel, char *str, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = WIN_LEN; /* En réalité, il s'agit de la longueur de votre image. Ici, mon image et ma fenêtre font la même taille */

	/* in this part you'll see how i decompose a decimal color in a third part decimal color rgb(255, 255, 255) */
	/* Dans cette partie, voici comment je decompose une couleur decimal en une couleur décimale en trois partie rgb(255, 255, 255) */
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;

	/* (pixel.x * 4) + (len * 4 * pixel.y) : cible le premier bit d'un pixel */
	str[(pixel.x * 4) + (len * 4 * pixel.y)] = b;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 1] = g;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 2] = r;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 3] = 0;
}
```

### Afficher une image dans une fenêtre

```C
mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img, int corner_left_x, int corner_left_y)
```
Rien de plus simple, on passe en argument le mlx_ptr, le win_ptr de la fenêtre voulue, le pointeur image pour préciser l'image à afficher et les coordonnées du pixel le plus en haut à gauche de l'image pour la position.

### ATTENTION ÇA LEAKS

```C
mlx_destroy_image(void *mlx_ptr, void *mlx_img)
```

Pour prévenir de tout leaks, il faut utiliser la fonction mlx_destroy_image. En effet, char *img_str est une string qui est malloc. Il faut donc libérer cet espace avant de créer une autre image. Pour cela, il suffit de passer en argument le ptr de la mlx et le pointeur de l'image que vous voulez détruire.

### FAQ ?
#### Les questions qu'on me pose souvent
```
1. J'ai fais mon programme avec la fonction mlx_put_pixel. Est-ce que je dois tout recommencer ?
```
<strong>Réponse : NON</strong>. En soit, cela ne change pas grand chose au fonctionnement d'un programme tel que fdf ou fractol. Vous devez simplement implémenter la création de l'image, remplacer tous les mlx_put_pixel par des put_pixel_image et enfin afficher l'image.
```
2. Est-ce que regarder/m'inspirer de ce cour c'est triché ?
```
<strong>Réponse :</strong> Selon moi, <strong>NON</strong>. Pour moi, Github est la réponse parfait à l'adage : "rien ne sert de réinventer la roue"
. Le plus important c'est de comprendre le fonctionnement des images mlx. Même si vous reprennez certaines fonctions de ce Git, tant que vous les avez comprises, pour moi vous ne trichez pas.
