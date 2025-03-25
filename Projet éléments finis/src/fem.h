#ifndef _FEM_H_
#define _FEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef FEM_H
#define FEM_H

#include <stdio.h>
#include <stdlib.h>

/* ==================== Structures ==================== */

typedef struct {
    int id;
    double x, y;
} Node;

typedef struct {
    int id;
    int type; // 3 pour triangle, 4 pour quadrilatère
    int nodes[4]; // Max 4 pour quadrilatères
} Element;

typedef struct {
    int numNodes;
    int numElements;
    Node *nodes;
    Element *elements;
} Mesh;

typedef struct {
    double E;  // Module d'élasticité
    double nu; // Coefficient de Poisson
    int numForces;
    int *forceNodes;
    double *Fx, *Fy;
    int numBC;
    int *bcNodes;
    double *Ux, *Uy;
} Problem;

/* ==================== Prototypes des Fonctions ==================== */

/* Lecture du maillage */
void read_mesh(const char *filename, Mesh *mesh);

/* Lecture du problème */
void read_problem(const char *filename, Problem *problem);

/* Libération de la mémoire */
void free_mesh(Mesh *mesh);
void free_problem(Problem *problem);

#endif /* FEM_H */

