<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/150px-42_Logo.svg.png" align="right" />

# mlx_img pour les studs 42

### Introduction

En tant qu'étudiant 42 ayant fait la branche graphique, j'ai pu me rendre compte que la documentation sur la notion d'image de la mlx n'était pas forcément très fournie.

Dans ce guide, je partirais du principe que vous connaissez deja les bases expliquées dans les videos de 42. (mlx_init, mlx_loop, mlx_create_windows, mlx_put_pixel)

Ce guide n'a pas pour ambition d'apporter de réponse parfait. Il s'appuira sur mon experience personnelle. Il se peut donc qu'il y ait des erreurs.

### Les images mlx c'est quoi ?

Comme tout le monde le sait, les images/photos sont composées de milliers de pixel. Si vous êtes ici, vous savez que la mlx permet d'afficher des pixels sur la fenetre grâce à la fonction.

### La structure image

Elle n'est pas obligatoire mais je la conseil très fortement. En effet, les images sont définies par plusieurs variable.

### La création d'une image

```C
	mlx_put_pixel();
```

### Modifier un pixel

À la difference de la fonction mlx_put_pixel, vous ne devrez pas créer un pixel à afficher dans votre image. En réalité, la fonction mlx_create_windows créée une image complète avec des pixels vides. (Pixels noirs)

### Afficher une image dans une fenetre
