# Práctica 4
## Informática Gráfica

## Compilación y ejecución
Mediante make se compilará y lanzará el programa con el objeto ply "beethoven.ply"
```
make x
```

Para borrar y limpiar ejecutables y códigos objeto

```
make clean
```

## Controles
El programa inicia ya con la grúa visualizándose, en modo líneas
#### Modo de vista
- Q: Salir
- 1: Modo de puntos
- 2: Modo de aristas
- 3: Modo solido
- 4: Modo ajedrez
- 5: Iluminación sombreado plano
- 6: Iluminación sombreado suave

#### Objetos
- B: Ver grúa
- E: Ver esfera
- P: Ver pirámide
- C: Ver cubo
- A: Ver tanque
- O: Objeto ply cargado
- R: Ver objeto rotación

#### Controles
- F1/F2: Rotar pie de la grúa
- F3/F4: Mover brazo de la grúa
- F5/F6: Mover antebrazo de la grúa
- F7: Rotar taladro/herramienta de la grúa
- F8: Activar modo animación

## Animación
Rotará todas las piezas de la grúa dentro de sus ángulos permitidos, dando circulos completos la herramienta y el pie de la grúa, pero quedándose en ±45 la primera parte de la grúa y ±35 la segunda. Cuando se alcanza el máximo de grados posibles, comienza a realizar el giro en sentido contrario.
Además, activará una luz que va girando alrededor de las figuras